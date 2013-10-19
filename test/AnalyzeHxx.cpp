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
   cout << "usage:  AnalyzeHxx  [OPTIONS] <input_file> <output_root> <output_dir>\n";
   cout << "\n";
   cout << "  --met_smear=<x>   : extra amount to smear MET.\n";
   cout << "  --num_smear=<n>   : number of times to smear MET.\n";
   cout << "  --fake_rate=<x>   : apply simple (whole event) fake rate <x> to W+jets.\n";
   cout << "  --8tev            : 8 tev settings (default 14 tev).\n";
   cout << "  --pub_plots       : generate publication plots.\n";
   exit(0);
}

void best_mjj(double target_mZ, hxx_tree & data, double & mjj, double & mjjll, int & j1, int & j2){
   TLorentzVector v1, v2, v3, v4, v;
   int n = data.jet_pt->size();
   
   mjj = mjjll = 0;
   j1 = j2 = 0;
   

   //for (int i=0; i<n-1;i++){
   //for (int j=i+1; j<n;j++){
   //v1.SetPtEtaPhiM(data.jet_pt->at(i), data.jet_eta->at(i), data.jet_phi->at(i), 0.0);
   //v2.SetPtEtaPhiM(data.jet_pt->at(j), data.jet_eta->at(j), data.jet_phi->at(j), 0.0);
   //v = v1 + v2;
   //double m = v.M();
   //if ((mjj==0)|| (fabs(m - target_mZ) < fabs(mjj-target_mZ))){
   //mjj = m;
   //j1 = i;
   //j2 = j;
   //} } }

   j1 = 0;
   j2 = 1;
   v1.SetPtEtaPhiM(data.jet_pt->at(j1), data.jet_eta->at(j1), data.jet_phi->at(j1), 0.0);
   v2.SetPtEtaPhiM(data.jet_pt->at(j2), data.jet_eta->at(j2), data.jet_phi->at(j2), 0.0);
   v = v1 + v2;
   mjj = v.M();

   
   if (mjj > 0.0){
     double eps = 90.0 / mjj;
     eps = 1.0; // no correction...
     
     v1.SetPtEtaPhiM(eps*data.jet_pt->at(j1), data.jet_eta->at(j1), data.jet_phi->at(j1), 0.0);
     v2.SetPtEtaPhiM(eps*data.jet_pt->at(j2), data.jet_eta->at(j2), data.jet_phi->at(j2), 0.0);
     v3.SetPtEtaPhiM(data.l1_pt, data.l1_eta, data.l1_phi,0);
     v4.SetPtEtaPhiM(data.l2_pt, data.l2_eta, data.l2_phi,0);
     v = v1 + v2 + v3 + v4;
     mjjll = v.M();
   }
}

void apply_fake_rate(TRandom & rng, hxx_tree & data, double rate){
  data.weight *= rate;

  //if (data.l1_pt <= 0.0) return;
  //if (data.l2_pt > 0.0) return;
  
  int n = data.jet_pt->size();

  if (n <= 0) return;

  int i = (int) (rng.Uniform() * n);
  //cout << i << " of " << n << "\n";

  double pt = data.jet_pt->at(i);

  if (pt > data.l1_pt){
    data.l2_pt  = data.l1_pt;
    data.l2_eta = data.l1_eta;
    data.l2_phi = data.l1_phi;
    data.l1_pt  = pt;
    data.l1_eta = data.jet_eta->at(i);
    data.l1_phi = data.jet_phi->at(i);
  } else {
    data.l2_pt  = pt;
    data.l2_eta = data.jet_eta->at(i);
    data.l2_phi = data.jet_phi->at(i);
  }

  data.erase_jet(i);

  if (data.l2_pt <= 0.0) {
    data.mll = 0.0;
    return;
  }

  TLorentzVector v, v1, v2;
  v1.SetPtEtaPhiM(data.l1_pt, data.l1_eta, data.l1_phi, 0.0);
  v2.SetPtEtaPhiM(data.l2_pt, data.l2_eta, data.l2_phi, 0.0);
  v = v1 + v2;
  data.mll = v.M();
  
  //cout << data.mll << "\n";
  //cout << "   " << data.l1_pt << "\n";
  //cout << "   " << data.l2_pt << "\n";

}


void best_mjl(hxx_tree & data, double & mjl, int j1, int j2){
      // Investigating new variables here:
      TLorentzVector v, vl1, vj1, vl2, vj2; 

      // could try j1/j2 here too:      
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

      mjl = maxmin;
}


double sensitivity(TH1F * hsig, TH1F * hbkg, double sigtot){
  int n = hsig->GetNbinsX() + 2;
  double best_sens = 0.0;

  for (int i=0; i<n; i++){
    double s = 0;
    double b = 0;
    for (int j=i; j<n; j++){
      s += sigtot * hsig->GetBinContent(i);
      b += hbkg->GetBinContent(i);
    }    
    double sens = 0;
    if (b > 0.0) sens = s / sqrt(b);
    if (sens > best_sens) best_sens = sens;
  }
  return best_sens;
}





int main(int argc, char *argv[])
{
   TRandom rng;
   rng.SetSeed(2013);
   hxx_tree data;
   
   std::string opt, infile, outroot, outdir;
   koptions options(argc, argv);
   
   //check for the --help option:
   if ( options.find("--help") ) { usage(); }
   //options.set("--seed=", seed);   
   //if (seed > 0) rng.SetSeed(seed);
   double met_smear = 30.0;
   options.set("--met_smear=", met_smear);   
   int    num_smear = 1;
   options.set("--num_smear=", num_smear);   
   double fake_rate = 0.0;
   options.set("--fake_rate=", fake_rate);   
   int mode_8tev = options.find("--8tev");
   int pub_plots = options.find("--pub_plots");

   int zll_offshell = 1;
   


   double lumi = 300;
   double met_cut = 200.0;

   if (mode_8tev){
     lumi = 20.0;
     met_cut = 200;
     cout << "INFO:  settings for sqrt(s) = 8 TeV\n";
   } else {
     cout << "INFO:  settings for sqrt(s) = 14 TeV\n";

   }
   cout << "INFO:  lumi:     " << lumi << "\n";
   cout << "INFO:  MET cut:  " << met_cut << "\n";

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
   options.shift_argument(outdir);

   cout << "INFO: reading analysis tree file:    " << infile  << "\n";
   cout << "INFO: writing histogram root file:   " << outroot << "\n";
   cout << "INFO: writing results to directory:  " << outdir  << "\n";
   cout << "INFO: MET smearing amount is " << met_smear << "\n";
   cout << "INFO: MET smearing number is " << num_smear << "\n";
   cout << "INFO: W+jets fake rate is " << fake_rate << "\n";

   auto_write aw;

   cutflow_tool cutflow;
   histogram_manager h0mll(new TH1F("h0mll","",100,0.0,200.0));

   if (pub_plots) {
     h0mll.add_sample(1,  "_ewk");
     h0mll.add_sample(2,  "_h");
     h0mll.add_sample(3,  "_vh");
     h0mll.add_sample(4,  "_top");
     h0mll.add_sample(5,  "_wjjj");

     cutflow.add_sample_name(1, "Electroweak");
     cutflow.add_sample_name(2, "H");
     cutflow.add_sample_name(3, "ZH,WH");
     cutflow.add_sample_name(4, "tt");
     cutflow.add_sample_name(5, "W+jets");

   } else {
     h0mll.add_sample(1,  "_zjj");
     h0mll.add_sample(2,  "_zz_zw");
     h0mll.add_sample(3,  "_ww");
     h0mll.add_sample(4,  "_tt");
     h0mll.add_sample(5,  "_hzz");
     h0mll.add_sample(6,  "_zh");
     h0mll.add_sample(7,  "_wh");
     h0mll.add_sample(8,  "_wjjj");

     cutflow.add_sample_name(1, "Zjj");
     cutflow.add_sample_name(2, "ZZ,ZW");
     cutflow.add_sample_name(3, "WW");
     cutflow.add_sample_name(4, "tt");
     cutflow.add_sample_name(5, "HZZ");
     cutflow.add_sample_name(6, "ZH");
     cutflow.add_sample_name(7, "WH");
     cutflow.add_sample_name(8, "W+jets");
   }




   h0mll.add_sample(20,  "_hxx1");
   h0mll.add_sample(21,  "_hxx10");
   h0mll.add_sample(22,  "_hxx100");
   h0mll.add_sample(23,  "_hxx500");
   h0mll.add_sample(24,  "_hxx1000");
   
   cutflow.add_sample_name(20, "HXX1");
   cutflow.add_sample_name(21, "HXX10");
   cutflow.add_sample_name(22, "HXX100");
   cutflow.add_sample_name(23, "HXX500");
   cutflow.add_sample_name(24, "HXX1000");
   
   
   h0mll.add_auto_write(aw);

   double met_upper = 300.0;



   TH1F hfit_bkg("sample_1","",  100,0.0,300.0);
   TH1F hfit_sig20("signal20","",  100,0.0,300.0);
   TH1F hfit_sig21("signal21","",  100,0.0,300.0);
   TH1F hfit_sig22("signal22","",  100,0.0,300.0);
   TH1F hfit_sig23("signal23","",  100,0.0,300.0);
   TH1F hfit_sig24("signal24","",  100,0.0,300.0);

   int    nsig = 0;
   double wsig = 0.0;
   hfit_bkg.Sumw2();
   hfit_sig20.Sumw2();
   hfit_sig21.Sumw2();
   hfit_sig22.Sumw2();
   hfit_sig23.Sumw2();
   hfit_sig24.Sumw2();

   histogram_manager htestx(new TH1F("htestx","",  100,0.0,200.0),  h0mll, aw);
   histogram_manager htesty(new TH1F("htesty","",  100,-10.0,10.0), h0mll, aw);
   histogram_manager htestz(new TH1F("htestz","",  100,0.0,200.0),  h0mll, aw);

   histogram_manager h0mjj   (new TH1F("h0mjj","",  100,0.0,200.0), h0mll, aw);
   histogram_manager h0mjl   (new TH1F("h0mjl","",  100,0.0,200.0), h0mll, aw);
   histogram_manager h0mjjll (new TH1F("h0mjjll","",100,00.0,500.0), h0mll, aw);
   histogram_manager h0met   (new TH1F("h0met","",  100,0.0, met_upper), h0mll, aw);
   histogram_manager h0njet  (new TH1F("h0njet","", 8, 2.0, 10.0), h0mll, aw);
   histogram_manager h0nbjet (new TH1F("h0nbjet","", 8, 0.0, 8.0), h0mll, aw);
   histogram_manager h0ht    (new TH1F("h0ht","",    100,0.0,500.0), h0mll, aw);

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
   histogram_manager h1mjl   (new TH1F("h1mjl","",  100,0.0,200.0), h0mll, aw);
   histogram_manager h1mjjll (new TH1F("h1mjjll","",100,00.0,500.0), h0mll, aw);
   histogram_manager h1met   (new TH1F("h1met","",  100,0.0, met_upper), h0mll, aw);
   histogram_manager h1njet  (new TH1F("h1njet","", 8, 2.0, 10.0), h0mll, aw);
   histogram_manager h1nbjet (new TH1F("h1nbjet","", 8, 0.0, 8.0), h0mll, aw);

   histogram_manager h2mll   (new TH1F("h2mll","",100,0.0,200.0), h0mll, aw);
   histogram_manager h2mjj   (new TH1F("h2mjj","",  100,0.0,200.0), h0mll, aw);
   histogram_manager h2mjl   (new TH1F("h2mjl","",  100,0.0,200.0), h0mll, aw);
   histogram_manager h2mjjll (new TH1F("h2mjjll","",100,0.0,500.0), h0mll, aw);
   histogram_manager h2met   (new TH1F("h2met","",  100,0.0, met_upper), h0mll, aw);
   histogram_manager h2njet  (new TH1F("h2njet","", 8, 2.0, 10.0), h0mll, aw);
   histogram_manager h2nbjet (new TH1F("h2nbjet","", 8, 0.0, 8.0), h0mll, aw);

   histogram_manager h3mll   (new TH1F("h3mll","",100,0.0,200.0), h0mll, aw);
   histogram_manager h3mjj   (new TH1F("h3mjj","",  100,0.0,200.0), h0mll, aw);
   histogram_manager h3mjl   (new TH1F("h3mjl","",  100,0.0,200.0), h0mll, aw);
   histogram_manager h3mjjll (new TH1F("h3mjjll","",100,0.0,500.0), h0mll, aw);
   histogram_manager h3met   (new TH1F("h3met","",  100,0.0, met_upper), h0mll, aw);
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

   //tree->Print();
  
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
      

      // First, apply W+jets fake rate if applicable:
      if (fake_rate > 0.0 && data.sample == 8){
	apply_fake_rate(rng, data, fake_rate);
      }


      // remap sample id for publication plots:
      if (pub_plots) {
	switch (data.sample){
	case 1: data.sample = 1; break;
	case 2: data.sample = 1; break;
	case 3: data.sample = 1; break;
	case 4: data.sample = 4; break;
	case 5: data.sample = 2; break;
	case 6: data.sample = 3; break;
	case 7: data.sample = 3; break;     
	case 8: data.sample = 5; break;     
	}
      }

      //if (data.l1_pt < 12.0) continue;
      //if (data.l2_pt < 12.0) continue;

      if (data.l1_pt < 20.0) continue;
      if (data.l2_pt < 15.0) continue;

      // prune jet list according to analysis selection:
      for (int i=0; i<data.jet_pt->size(); i++){
         int veto = 0;
         if (data.jet_pt->at(i) < 15.0) veto = 1;
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

      //preselection cuts:
      if (data.jet_pt->size() < 2) continue;
      if (data.nmuon + data.nelec > 2) continue;
      
      cutflow.increment(0, data.sample, data.weight);      


      // Here we smear the MET to account for pile-up effects:
      vector<double> met;
      vector<double> met_phi;

      // use reduced weight when looping over entire MET vector:
      double met_weight = (data.weight / (double) num_smear);

      double nopu_metx = data.nopu_met * cos(data.nopu_met_phi);
      double nopu_mety = data.nopu_met * sin(data.nopu_met_phi);
      
      for (int i=0; i<num_smear; i++){
         double metx        = nopu_metx + rng.Gaus() * met_smear;
         double mety        = nopu_mety + rng.Gaus() * met_smear;
         double new_met     = sqrt(metx*metx + mety*mety);
         double new_met_phi = atan2(mety, metx);
         met.push_back(new_met);
         met_phi.push_back(new_met_phi);
      }

      // Stage 0, 2 jets, mu+mu- or e+e- pt > 12, no additional e/mu, 
      
      double mjj, mjl, mjjll;
      int i,j;      
      best_mjj(30.0, data, mjj, mjjll, i, j);
      best_mjl(data, mjl, i, j);


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
      h0mjl.Fill(data.sample, mjl, data.weight);      
      h0mjjll.Fill(data.sample, mjjll, data.weight);      
      h0ht.Fill(data.sample, data.ht, data.weight);      

      if (data.mll <= 20) continue;

      // onshell Z->ll requirement:
      if (data.mll < 76) continue;
      if (data.mll > 100) continue;

      // offshell Z->ll requirement:
      //if (data.mll > 76) continue;

      htestx.Fill(data.sample, mjl, data.weight);
      cutflow.increment(1, data.sample, data.weight);

      h1njet.Fill(data.sample, data.jet_pt->size(), data.weight);
      h1mll.Fill(data.sample, data.mll, data.weight);
      h1met.Fill(data.sample, met[0], data.weight);
      h1mjj.Fill(data.sample, mjj, data.weight);      
      h1mjl.Fill(data.sample, mjl, data.weight);      
      h1mjjll.Fill(data.sample, mjjll, data.weight);      


      if (mjj > 120) continue;
      if (mjjll > 200.0) continue;

      cutflow.increment(2, data.sample, data.weight);

      h2njet.Fill(data.sample, data.jet_pt->size(), data.weight);
      h2mll.Fill(data.sample, data.mll, data.weight);
      h2met.Fill(data.sample, met[0], data.weight);
      h2mjj.Fill(data.sample, mjj, data.weight);      
      h2mjl.Fill(data.sample, mjl, data.weight);      
      h2mjjll.Fill(data.sample, mjjll, data.weight);      

      
      if (mjl > 80.0) continue;
      cutflow.increment(3, data.sample, data.weight);

      h3njet.Fill(data.sample, data.jet_pt->size(), data.weight);
      h3mll.Fill(data.sample, data.mll, data.weight);
      h3mjj.Fill(data.sample, mjj, data.weight);
      h3mjl.Fill(data.sample, mjl, data.weight);            
      h3mjjll.Fill(data.sample, mjjll, data.weight);      
      for (int i=0; i<met.size(); i++) h3met.Fill(data.sample, met[i], met_weight);

      for (int i=0; i<met.size(); i++){
         if (met_weight > 100){
            cout << "WARNING:  large weight at MET stage:  " << met_weight << "\n";  
         }

         if (data.sample < 20)  hfit_bkg.Fill(met[i], met_weight);

         if (data.sample == 20) hfit_sig20.Fill(met[i], met_weight);         
         if (data.sample == 21) hfit_sig21.Fill(met[i], met_weight);         
         if (data.sample == 22) hfit_sig22.Fill(met[i], met_weight);         
         if (data.sample == 23) hfit_sig23.Fill(met[i], met_weight);         
         if (data.sample == 24) hfit_sig24.Fill(met[i], met_weight);         

	 if (met[i] > met_cut)	 
	   cutflow.increment(4, data.sample, met_weight);
      }
      
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
   foutroot->Close();

   //cout << "SUMMARY:  done writing files.\n";

   cout << "Cutflow:  Stage 0 (lljj preselection)\n";
   cutflow.print(0);

   cout << "Cutflow:  Stage 1 (mll cut)\n";
   cutflow.print(1);

   cout << "Cutflow:  Stage 2 (after mjj cut) \n";
   cutflow.print(2);

   cout << "Cutflow:  Stage 3 (after mjjll cut) \n";
   cutflow.print(3);

   cout << "Cutflow:  Stage 4 (after MET cut) \n";
   cutflow.print(4);

   cout << "Fit Histogram Summary:  \n";
   double SIGTOT = lumi * 149.8;
   hfit_sig20.Scale(1.0/SIGTOT);
   hfit_sig21.Scale(1.0/SIGTOT);
   hfit_sig22.Scale(1.0/SIGTOT);
   hfit_sig23.Scale(1.0/SIGTOT);
   hfit_sig24.Scale(1.0/SIGTOT);
   cout << " -> using total signal events of :    " << SIGTOT << "\n";
   cout << " -> background integral (evts):       " << hfit_bkg.GetSumOfWeights() << "\n";
   cout << " -> signal 1    integral (eff):       " << hfit_sig20.GetSumOfWeights() << "\n";
   cout << " -> signal 10   integral (eff):       " << hfit_sig21.GetSumOfWeights() << "\n";
   cout << " -> signal 100  integral (eff):       " << hfit_sig22.GetSumOfWeights() << "\n";
   cout << " -> signal 500  integral (eff):       " << hfit_sig23.GetSumOfWeights() << "\n";
   cout << " -> signal 1000 integral (eff):       " << hfit_sig24.GetSumOfWeights() << "\n";
   cout << " -> local count of signal events:     " << nsig << "\n";
   cout << " -> local integral of signal weight:  " << wsig << "\n";

   cout << " --> signal 1    sensitivity:  " << sensitivity(&hfit_sig20, &hfit_bkg, SIGTOT) << "\n";
   cout << " --> signal 10   sensitivity:  " << sensitivity(&hfit_sig21, &hfit_bkg, SIGTOT) << "\n";
   cout << " --> signal 100  sensitivity:  " << sensitivity(&hfit_sig22, &hfit_bkg, SIGTOT) << "\n";
   cout << " --> signal 500  sensitivity:  " << sensitivity(&hfit_sig23, &hfit_bkg, SIGTOT) << "\n";
   cout << " --> signal 1000 sensitivity:  " << sensitivity(&hfit_sig24, &hfit_bkg, SIGTOT) << "\n";

   char name[100];
   TFile * f = NULL;
   TH1F * h = NULL;

   sprintf(name, "%s/mchi1.root", outdir.c_str());
   f = new TFile(name, "RECREATE");
   f->cd();
   h = (TH1F *) hfit_sig20.Clone("signal");
   h->Write();
   hfit_bkg.Write();
   f->Close();

   sprintf(name, "%s/mchi10.root", outdir.c_str());
   f = new TFile(name, "RECREATE");
   f->cd();
   h = (TH1F *) hfit_sig21.Clone("signal");
   h->Write();
   hfit_bkg.Write();
   f->Close();

   sprintf(name, "%s/mchi100.root", outdir.c_str());
   f = new TFile(name, "RECREATE");
   f->cd();
   h = (TH1F *) hfit_sig22.Clone("signal");
   h->Write();
   hfit_bkg.Write();
   f->Close();

   sprintf(name, "%s/mchi500.root", outdir.c_str());
   f = new TFile(name, "RECREATE");
   f->cd();
   h = (TH1F *) hfit_sig23.Clone("signal");
   h->Write();
   hfit_bkg.Write();
   f->Close();

   sprintf(name, "%s/mchi1000.root", outdir.c_str());
   f = new TFile(name, "RECREATE");
   f->cd();
   h = (TH1F *) hfit_sig24.Clone("signal");
   h->Write();
   hfit_bkg.Write();
   f->Close();



}


