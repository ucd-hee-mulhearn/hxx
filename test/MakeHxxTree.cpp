#include <iostream>
#include <utility>
#include <vector>

#include "TROOT.h"
#include "TSystem.h"
#include "TApplication.h"

#include "TString.h"

#include "TH2.h"
#include "THStack.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TClonesArray.h"
#include "TLorentzVector.h"
#include "TCanvas.h"
#include "TRandom.h"

#include "classes/DelphesClasses.h"

#include "ExRootAnalysis/ExRootTreeReader.h"
#include "ExRootAnalysis/ExRootTreeWriter.h"
#include "ExRootAnalysis/ExRootTreeBranch.h"
#include "ExRootAnalysis/ExRootResult.h"
#include "ExRootAnalysis/ExRootUtilities.h"


#include "koptions.h"
#include "hxx_tree.h"

using namespace std;
using namespace kutil;

void usage(){
   cout << "usage:  MakeHxxTree  [OPTIONS] <input_file> <output_file>\n";
   cout << "\n";
   cout << " --seed=<n>          (0)     set rng seed if non-zero\n";
   cout << " --sample=<n>        (0)     set sample id to <n>\n";
   cout << " --lumi=<l>          (14)    set weight for lumi <l> [fb^-1]\n";
   cout << " --xsec=<x>          (0)     set weight for xsec <x> [fb]\n";
   cout << " --smear_met=<mu>    (0)     set resolution for MET smearing\n";
   cout << " --smear_num=<n>     (1)     smear each event <n> times\n";
   exit(0);
}

int main(int argc, char *argv[])
{
   TRandom rng;
   hxx_tree data;
   int    seed = 0;
   int    sample = 0;
   double lumi = 14.0;
   double xsec = 0.0;
   double weight = 1.0; 
   double smear_met = 0;
   int    smear_num = 1;
   
   std::string opt, infile, outfile;
   koptions options(argc, argv);
   
   //check for the --help option:
   if ( options.find("--help") ) { usage(); }
   options.set("--seed=", seed);   
   if (seed > 0) rng.SetSeed(seed);

   options.set("--sample=", sample);   
   options.set("--lumi=", lumi);
   options.set("--xsec=", xsec);
   options.set("--smear_met=", smear_met);
   options.set("--smear_num=", smear_num);
   

   //check for unrecognized options (beginning with -- or -)
   while(options.unrecognized_option(opt)){
      cout << "WARNING: unrecognized option:" << opt << "\n";
      usage();
   } 

   if (options.size() != 2){
      usage();
   }

   options.shift_argument(infile);
   options.shift_argument(outfile);

   cout << "INFO: reading Delphes tree file:   " << infile << "\n";
   cout << "INFO: writing analysis tree file:  " << outfile << "\n";
   cout << "INFO: sample id is " << sample << "\n";
   if ((smear_met > 0.0) && (smear_num > 0)){
      cout << "INFO: smearing MET by resolution " << smear_met << "\n";
      cout << "INFO: smearing each event " << smear_num << " times. \n";
   }


   TChain chain("Delphes");
   chain.Add(infile.c_str());
   ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
   Long64_t numberOfEntries = treeReader->GetEntries();
   if (numberOfEntries == 0) { cout << "Zero entries...\n"; return 0; }
   // Get pointers to branches used in this analysis
   TClonesArray *branchJet      = treeReader->UseBranch("Jet");
   TClonesArray *branchElec     = treeReader->UseBranch("Electron");
   TClonesArray *branchMuon     = treeReader->UseBranch("Muon");
   TClonesArray *branchMET      = treeReader->UseBranch("MissingET");  

   // calculate appropriate weight:
   if (xsec > 0.0){
      double Ngen = numberOfEntries;
      double Lgen = Ngen / xsec;
      weight = lumi * xsec / Ngen;
      cout << "INFO:  calculating event weights:\n";
      cout << "INFO:  Ngen = " << Ngen << "\n";
      cout << "INFO:  lumi = " << lumi << "\n";
      cout << "INFO:  xsec = " << xsec << "\n";
      cout << "INFO:  Lgen = " << Lgen << "\n";
      cout << "INFO:  weight = " << weight << "\n";
      cout << "INFO:  Ntot = " << weight * Ngen << "\n";
   } else {
      cout << "INFO:  no xsec provided, using weight=1";
      weight = 1;
   }

   TFile * file = new TFile(outfile.c_str(), "RECREATE");
   TTree * tree = new TTree("hxxtree", "");
   data.WriteTree(tree);

  
   int count = 0;
   int nupdate = numberOfEntries / 20;
   if (nupdate < 1) nupdate=1;
   cout << "PROGRESS:  ";

   // Loop over all events
   for(Int_t entry = 0; entry < numberOfEntries; ++entry)
   {
      count++;
      if (count % nupdate == 0) { cout << "."; cout.flush(); }
      treeReader->ReadEntry(entry);
      
      data.Clear();
      data.sample = sample;
      data.weight = weight;
      data.weight_met = 0;

      data.nelec = branchElec->GetEntries();
      data.nmuon = branchMuon->GetEntries();
      data.njet  = branchJet->GetEntries();
      
      if (data.nmuon >= data.nelec) {
         data.lepton_flavor = LFMUMU;
         if (branchMuon->GetEntries() > 0) {
            Muon * mu1 = (Muon*) branchMuon->At(0);
            data.l1_pt = mu1->PT;
            data.l1_eta = mu1->Eta;
            data.l1_phi = mu1->Phi;
         }
         if (branchMuon->GetEntries() > 1) {
            Muon * mu1 = (Muon*) branchMuon->At(0);
            Muon * mu2 = (Muon*) branchMuon->At(1);
            data.l2_pt = mu2->PT;
            data.l2_eta = mu2->Eta;
            data.l2_phi = mu2->Phi;
            data.mll = ((mu1->P4()) + (mu2->P4())).M(); 
         }
      } else {
         data.lepton_flavor = LFEMEM;
         if (branchElec->GetEntries() > 0) {
            Electron * elec1 = (Electron*) branchElec->At(0);
            data.l1_pt = elec1->PT;
            data.l1_eta = elec1->Eta;
            data.l1_phi = elec1->Phi;
         }
         if (branchElec->GetEntries() > 1) {
            Electron * elec1 = (Electron*) branchElec->At(0);
            Electron * elec2 = (Electron*) branchElec->At(1);
            data.l2_pt = elec1->PT;
            data.l2_eta = elec1->Eta;
            data.l2_phi = elec1->Phi;
            data.mll = ((elec1->P4()) + (elec2->P4())).M(); 
         }
      }

      int nJet = branchJet->GetEntries();
      for (int i=0; i<nJet; i++){
         Jet * jet = (Jet*) branchJet->At(i);
         data.jet_pt     ->push_back(jet->PT);
         data.jet_eta    ->push_back(jet->Eta);
         data.jet_phi    ->push_back(jet->Phi);
         data.jet_btag   ->push_back((int) jet->BTag);
         data.jet_tautag ->push_back((int) jet->TauTag);
      }      


      if (branchMET->GetEntries() > 0) {
         MissingET * met = (MissingET *) branchMET->At(0);
         data.nopu_met = met->MET;
         data.nopu_met_phi = met->Phi;
      }

      if ((smear_met > 0.0) && (smear_num > 0)){
         data.weight_met = weight / smear_num;

         for (int i=0; i<smear_num; i++){
            double metx = data.nopu_met * cos(data.nopu_met_phi);
            double mety = data.nopu_met * sin(data.nopu_met_phi);
            metx += rng.Gaus() * smear_met;
            mety += rng.Gaus() * smear_met;
            data.met = sqrt(metx*metx + mety*mety);
            data.met_phi = atan2(mety, metx);
            if (i==0){
               data.weight=weight;
            } else {
               data.weight=0.0;
            }
            tree->Fill();
         }
      } else {
         data.met     = data.nopu_met;
         data.met_phi = data.nopu_met_phi;
         tree->Fill();
      }
   }
   cout << "\n";

   cout << "SUMMARY:  wrote " << tree->GetEntries() << " to analysis tree from " << count << " events\n";

   file->cd();
   tree->Write();
   file->Close();   

   cout << "SUMMARY:  done writing files.\n";
}


