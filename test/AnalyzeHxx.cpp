#include <iostream>
#include <utility>
#include <vector>
#include <math.h>

#include "TROOT.h"
#include "TSystem.h"
#include "TApplication.h"

#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"
#include "TRandom.h"
#include "TLorentzVector.h"

#include "koptions.h"
#include "hxx_tree.h"
#include "histogram_manager.h"
#include "cutflow_tool.h"

using namespace std;
using namespace kutil;

void usage(){
   cout << "usage:  AnalyzeHxx  [OPTIONS] <input_file> <output_root> <output_txt>\n";
   cout << "\n";
   exit(0);
}

void best_mjj(hxx_tree & data, double & mjj, double & mjjll, int & j1, int & j2){
   const double mZ = 60.0;
   TLorentzVector v1, v2, v3, v4, v;
   int n = data.jet_pt->size();
   
   mjj = mjjll = 0;
   j1 = j2 = 0;
   
   for (int i=0; i<n-1;i++){
      for (int j=i+1; j<n;j++){
         v1.SetPtEtaPhiM(data.jet_pt->at(i), data.jet_eta->at(i), data.jet_phi->at(i), 0.0);
         v2.SetPtEtaPhiM(data.jet_pt->at(j), data.jet_eta->at(j), data.jet_phi->at(j), 0.0);
         v = v1 + v2;
         double m = v.M();
         if (fabs(m - mZ) < fabs(mjj-mZ)){
            mjj = m;
            j1 = i;
            j2 = i;
         }
      }
   }
   
   if (mjj > 0.0){
      double eps = 60.0 / mjj;

      v1.SetPtEtaPhiM(eps*data.jet_pt->at(j1), data.jet_eta->at(j1), data.jet_phi->at(j1), 0.0);
      v2.SetPtEtaPhiM(eps*data.jet_pt->at(j2), data.jet_eta->at(j2), data.jet_phi->at(j2), 0.0);
      v3.SetPtEtaPhiM(data.l1_pt, data.l1_eta, data.l1_phi,0);
      v4.SetPtEtaPhiM(data.l2_pt, data.l2_eta, data.l2_phi,0);
      v = v1 + v2 + v3 + v4;
      mjjll = v.M();
   }
}


int main(int argc, char *argv[])
{
   TRandom rng;
   rng.SetSeed(2013);
   hxx_tree data;
   
   std::string opt, infile, outroot, outtxt;
   koptions options(argc, argv);
   
   //check for the --help option:
   if ( options.find("--help") ) { usage(); }
   //options.set("--seed=", seed);   
   //if (seed > 0) rng.SetSeed(seed);
   //options.set("--sample=", sample);   

   //check for unrecognized options (beginning with -- or -)
   while(options.unrecognized_option(opt)){
      cout << "WARNING: unrecognized option:" << opt << "\n";
      usage();
   } 

   if (options.size() != 3){
      usage();
   }

   options.shift_argument(infile);
   options.shift_argument(outroot);
   options.shift_argument(outtxt);

   cout << "INFO: reading analysis tree file:   " << infile  << "\n";
   cout << "INFO: writing histogram root file:  " << outroot << "\n";
   cout << "INFO: appending cut flow txt file:  " << outtxt  << "\n";
   cout << "INFO: sample id is " << data.sample << "\n";

   auto_write aw;

   cutflow_tool cutflow;
   histogram_manager h0mll(new TH1F("h0mll","",100,0.0,200.0));
   h0mll.add_sample(1,  "_zjj");
   h0mll.add_sample(2,  "_zz_zw");
   h0mll.add_sample(3,  "_ww");
   h0mll.add_sample(4,  "_tt");
   h0mll.add_sample(5,  "_hzz");
   h0mll.add_sample(6,  "_zh");
   h0mll.add_sample(7,  "_wh");
   h0mll.add_sample(20,  "_hxx1");

   cutflow.add_sample_name(1, "Zjj");
   cutflow.add_sample_name(2, "ZZ,ZW");
   cutflow.add_sample_name(3, "WW");
   cutflow.add_sample_name(4, "tt");
   cutflow.add_sample_name(5, "HZZ");
   cutflow.add_sample_name(6, "ZH");
   cutflow.add_sample_name(7, "WH");
   cutflow.add_sample_name(20, "HXX1");
   
   h0mll.add_auto_write(aw);


   histogram_manager htestx(new TH1F("htestx","",  100,0.0,200.0),  h0mll, aw);
   histogram_manager htesty(new TH1F("htesty","",  100,-10.0,10.0), h0mll, aw);
   histogram_manager htestz(new TH1F("htestz","",  100,0.0,200.0),  h0mll, aw);

   histogram_manager h0mjj   (new TH1F("h0mjj","",  100,0.0,200.0), h0mll, aw);
   histogram_manager h0mjjll (new TH1F("h0mjjll","",100,0.0,200.0), h0mll, aw);
   histogram_manager h0met   (new TH1F("h0met","",  100,0.0,200.0), h0mll, aw);
   histogram_manager h0njet  (new TH1F("h0njet","", 8, 2.0, 10.0), h0mll, aw);
   histogram_manager h0nbjet (new TH1F("h0nbjet","", 8, 0.0, 8.0), h0mll, aw);

   histogram_manager h0l1pt(new TH1F("h0l1pt","",100,0.0,200.0), h0mll, aw);
   histogram_manager h0l2pt(new TH1F("h0l2pt","",100,0.0,200.0), h0mll, aw);
   histogram_manager h0j1pt(new TH1F("h0j1pt","",100,0.0,200.0), h0mll, aw);
   histogram_manager h0j2pt(new TH1F("h0j2pt","",100,0.0,200.0), h0mll, aw);

   histogram_manager h0l1eta(new TH1F("h0l1eta","", 60, -3.0, 3.0), h0mll, aw);
   histogram_manager h0l2eta(new TH1F("h0l2eta","", 60, -3.0, 3.0), h0mll, aw);
   histogram_manager h0j1eta(new TH1F("h0j1eta","", 60, -3.0, 3.0), h0mll, aw);
   histogram_manager h0j2eta(new TH1F("h0j2eta","", 60, -3.0, 3.0), h0mll, aw);

   histogram_manager h1mll   (new TH1F("h1mll","",100,0.0,200.0), h0mll, aw);
   histogram_manager h1mjj   (new TH1F("h1mjj","",  100,0.0,200.0), h0mll, aw);
   histogram_manager h1mjjll (new TH1F("h1mjjll","",100,0.0,200.0), h0mll, aw);
   histogram_manager h1met   (new TH1F("h1met","",  100,0.0,200.0), h0mll, aw);
   histogram_manager h1njet  (new TH1F("h1njet","", 8, 2.0, 10.0), h0mll, aw);
   histogram_manager h1nbjet (new TH1F("h1nbjet","", 8, 0.0, 8.0), h0mll, aw);

   histogram_manager h2mll   (new TH1F("h2mll","",100,0.0,200.0), h0mll, aw);
   histogram_manager h2mjj   (new TH1F("h2mjj","",  100,0.0,200.0), h0mll, aw);
   histogram_manager h2mjjll (new TH1F("h2mjjll","",100,0.0,200.0), h0mll, aw);
   histogram_manager h2met   (new TH1F("h2met","",  100,0.0,200.0), h0mll, aw);
   histogram_manager h2njet  (new TH1F("h2njet","", 8, 2.0, 10.0), h0mll, aw);
   histogram_manager h2nbjet (new TH1F("h2nbjet","", 8, 0.0, 8.0), h0mll, aw);

   histogram_manager h3mll   (new TH1F("h3mll","",100,0.0,200.0), h0mll, aw);
   histogram_manager h3mjj   (new TH1F("h3mjj","",  100,0.0,200.0), h0mll, aw);
   histogram_manager h3mjjll (new TH1F("h3mjjll","",100,0.0,200.0), h0mll, aw);
   histogram_manager h3met   (new TH1F("h3met","",  100,0.0,200.0), h0mll, aw);
   histogram_manager h3njet  (new TH1F("h3njet","", 8, 2.0, 10.0), h0mll, aw);
   histogram_manager h3nbjet (new TH1F("h3nbjet","", 8, 0.0, 8.0), h0mll, aw);

   cout << "INFO: opening file: " << infile << "\n";

   TFile * file = new TFile(infile.c_str());
   TTree * tree = (TTree*) file->Get("hxxtree");

   if (! tree) {
      cout << "ERROR:  could not open tree.\n";
      exit(0);
   }

   data.ReadTree(tree);
   long int numberOfEntries = tree->GetEntries();

   tree->Print();
  
   int count = 0;
   int nupdate = numberOfEntries / 20;
   if (nupdate < 1) nupdate=1;
   cout << "PROGRESS:  ";

   // Loop over all events
   for(Int_t entry = 0; entry < numberOfEntries; ++entry)
   {
      count++;
      if (count % nupdate == 0) { cout << "."; cout.flush(); }

      tree->GetEntry(entry);

      if (data.l1_pt < 12.0) continue;
      if (data.l2_pt < 12.0) continue;

      // prune jet list according to analysis selection:
      for (int i=0; i<data.jet_pt->size(); i++){
         int veto = 0;
         if (data.jet_pt->at(i) < 20.0) veto = 1;
         if (fabs(data.jet_eta->at(i)) > 2.5) veto = 1;         
         if (veto) {
            data.erase_jet(i); 
            i--;
         }
      }
      if (data.jet_pt->size() != data.jet_btag->size()){
         cout << "ERROR:  Jet vectors out of sync.  Something is wrong.\n";
         exit(0);
      }

      int nbtag = 0;
      for (int i=0; i<data.jet_btag->size(); i++){
         if (data.jet_btag->at(i)) nbtag++;
      }
      
      if (data.jet_pt->size() < 2) continue;
      if (data.nmuon + data.nelec > 2) continue;
      //if (nbtag > 0) continue;
      //if (nbtag < 1) continue;

      //if (data.jet_pt->size() > 2) continue;

      // Here we smear the MET to account for pile-up effects:
      vector<double> met;
      vector<double> met_phi;

      // smear MET by 20 for 8 TeV  (now in Analysis...)
      // smear MET by 30 for 14 TeV (now in Analysis...)
      double met_smear  = 30;
      //int    met_num    = 100;
      int    met_num    = 1000;
      // use reduced weight when looping over entire MET vector:
      double met_weight = (data.weight / (double) met_num);

      double nopu_metx = data.nopu_met * cos(data.nopu_met_phi);
      double nopu_mety = data.nopu_met * sin(data.nopu_met_phi);
      
      for (int i=0; i<met_num; i++){
         double metx        = nopu_metx + rng.Gaus() * met_smear;
         double mety        = nopu_mety + rng.Gaus() * met_smear;
         double new_met     = sqrt(metx*metx + mety*mety);
         double new_met_phi = atan2(mety, metx);
         met.push_back(new_met);
         met_phi.push_back(new_met_phi);
      }

      // Stage 0, 2 jets, mu+mu- or e+e- pt > 12, no additional e/mu, 
      
      double mjj, mjjll;
      int i,j;      
      best_mjj(data, mjj, mjjll, i, j);


      // Investigating new variables here:
      TLorentzVector v, vl1, vj1, vl2, vj2; 
      
      vl1.SetPtEtaPhiM(data.l1_pt, data.l1_eta, data.l1_phi, 0.0);
      vj1.SetPtEtaPhiM(data.jet_pt->at(0), data.jet_eta->at(0), data.jet_phi->at(0), 0.0);
      vl2.SetPtEtaPhiM(data.l2_pt, data.l2_eta, data.l2_phi, 0.0);
      vj2.SetPtEtaPhiM(data.jet_pt->at(1), data.jet_eta->at(1), data.jet_phi->at(1), 0.0);

      v = vl1 + vj1;
      double m11 = v.M();
      v = vl2 + vj2;
      double m22 = v.M();
      double mina, maxa;
      if (m11 < m22){
         mina = m11;
         maxa = m22;
      } else {
         mina = m22;
         maxa = m11;
      }

      v = vl1 + vj2;
      double m12 = v.M();
      v = vl2 + vj1;
      double m21 = v.M();
      double minb, maxb;
      if (m12 < m21){
         minb = m12;
         maxb = m21;
      } else {
         minb = m21;
         maxb = m12;
      }

      double minmin, minmax, maxmin, maxmax;
      if (mina < minb) {
         minmin = mina;
         maxmin = minb;
      } else {            
         minmin = mina;
         maxmin = minb;
      }
      if (maxa < maxb) {
         minmax = maxa;
         maxmax - maxb;
      } else {            
         minmax = maxa;
         maxmax = maxb;
      }








      //v = vl1 + vl1;
      //double m11 = v.M();
      //v = vl1 + vl2;
      //double m12 = v.M();
      //v = vl2 + vl1;
      //double m21 = v.M();
      //v = vl2 + vl2;
      //double m22 = v.M();




      if (data.jet_pt->size() > 0) {
         h0j1pt  .Fill(data.sample, data.jet_pt ->at(0));
         h0j1eta .Fill(data.sample, data.jet_eta->at(0));
      }
      if (data.jet_pt->size() > 1) {
         h0j2pt  .Fill(data.sample, data.jet_pt ->at(1));
         h0j2eta .Fill(data.sample, data.jet_eta->at(1));
      }
      h0l1pt  .Fill(data.sample, data.l1_pt,  data.weight);
      h0l1eta .Fill(data.sample, data.l1_eta, data.weight);
      h0l2pt  .Fill(data.sample, data.l2_pt,  data.weight);
      h0l2eta .Fill(data.sample, data.l2_eta, data.weight);

      h0njet.Fill(data.sample, data.jet_pt->size(), data.weight);
      h0nbjet.Fill(data.sample, nbtag, data.weight);
      h0mll.Fill(data.sample, data.mll, data.weight);
      h0met.Fill(data.sample, met[0], data.weight);
      h0mjj.Fill(data.sample, mjj, data.weight);      
      h0mjjll.Fill(data.sample, mjjll, data.weight);      

      cutflow.increment(0, data.sample, data.weight);


      if (data.mll < 50) continue;
      if (data.mll > 65) continue;

      htestx.Fill(data.sample, minmin, data.weight);


      cutflow.increment(1, data.sample, data.weight);

      h1njet.Fill(data.sample, data.jet_pt->size(), data.weight);
      h1mll.Fill(data.sample, data.mll, data.weight);
      h1met.Fill(data.sample, met[0], data.weight);
      h1mjj.Fill(data.sample, mjj, data.weight);      
      h1mjjll.Fill(data.sample, mjjll, data.weight);      

      if (mjj < 45) continue;
      if (mjj > 75) continue;

      cutflow.increment(2, data.sample, data.weight);

      h2njet.Fill(data.sample, data.jet_pt->size(), data.weight);
      h2mll.Fill(data.sample, data.mll, data.weight);
      h2met.Fill(data.sample, met[0], data.weight);
      h2mjj.Fill(data.sample, mjj, data.weight);      
      h2mjjll.Fill(data.sample, mjjll, data.weight);      

      //if (mjjll < 60) continue;
      if (mjjll > 110) continue;
      if (maxmax > 60) continue;

      cutflow.increment(3, data.sample, data.weight);

      h3njet.Fill(data.sample, data.jet_pt->size(), data.weight);
      h3mll.Fill(data.sample, data.mll, data.weight);
      h3mjj.Fill(data.sample, mjj, data.weight);      
      h3mjjll.Fill(data.sample, mjjll, data.weight);      

      for (int i=0; i<met.size(); i++) h3met.Fill(data.sample, met[i], met_weight);



      
      //if (met[0] < 100.0) continue;

      //cutflow.increment(3, data.sample, data.weight);

      //if (mjjll < 100) continue;
      //if (mjjll > 150) continue;


      // mjjll cut:

      //cutflow.increment(3, data.sample, data.weight);
      //if (data.lepton_flavor == LFMUMU){
      //cutflow.increment(4, data.sample, data.weight);
      //} else {
      //cutflow.increment(5, data.sample, data.weight);
      //}
   }
   cout << "\n";

   cout << "SUMMARY:  read " << count << " of " << tree->GetEntries() << " events from analysis tree.\n";
   
   TFile * foutroot = new TFile(outroot.c_str(), "RECREATE");
   foutroot->cd();
   aw.WriteAll();

   //cout << "SUMMARY:  done writing files.\n";

   cout << "Cutflow:  Stage 0 (lljj preselection)\n";
   cutflow.print(0);

   cout << "Cutflow:  Stage 1 (mll cut)\n";
   cutflow.print(1);

   cout << "Cutflow:  Stage 2 (after mjj cut) \n";
   cutflow.print(2);

   cout << "Cutflow:  Stage 3 (after mjjll cut) \n";
   cutflow.print(3);


   
}


