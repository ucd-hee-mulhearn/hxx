/*
root -l examples/Example1.C\(\"delphes_output.root\"\)
*/

//------------------------------------------------------------------------------

void Example1(const char *inputFile)
{
  gSystem->Load("libDelphes");
  TChain chain("Delphes");
  chain.Add(inputFile);
  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Long64_t numberOfEntries = treeReader->GetEntries();
  
  // Get pointers to branches used in this analysis
  TClonesArray *branchJet      = treeReader->UseBranch("Jet");
  TClonesArray *branchElectron = treeReader->UseBranch("Electron");
  TClonesArray *branchMuon     = treeReader->UseBranch("Muon");
  TClonesArray *branchMET     = treeReader->UseBranch("MissingET");
  
  // Book histograms
  TH1 *histJetPT = new TH1F("jet_pt", "jet P_{T}", 100, 0.0, 500.0);
  TH1 *histMass = new TH1F("mass", "M_{inv}(l_{1}, l_{2})", 100, 40.0, 140.0);
  TH1 *histMET = new TH1F("mass", "MET", 100, 0.0, 500.0);

  // Loop over all events
  for(Int_t entry = 0; entry < numberOfEntries; ++entry)
  {
    // Load selected branches with data from specified event
    treeReader->ReadEntry(entry);
  
    // If event contains at least 1 jet
    if(branchJet->GetEntries() > 0)
    {
      // Take first jet
      Jet *jet = (Jet*) branchJet->At(0);
      
      // Plot jet transverse momentum
      histJetPT->Fill(jet->PT);
      
      // Print jet transverse momentum
      //cout << jet->PT << endl;
    }

    Electron *elec1, *elec2;

    // If event contains at least 2 electrons
    if(branchElectron->GetEntries() > 1)
    {
      // Take first two electrons
      elec1 = (Electron *) branchElectron->At(0);
      elec2 = (Electron *) branchElectron->At(1);

      // Plot their invariant mass
      histMass->Fill(((elec1->P4()) + (elec2->P4())).M());
    }

    Muon *muon1, *muon2;

    // If event contains at least 2 muontrons
    if(branchMuon->GetEntries() == 2)
    {
      // Take first two electrons
      muon1 = (Muon *) branchMuon->At(0);
      muon2 = (Muon *) branchMuon->At(1);

      // Plot their invariant mass
      histMass->Fill(((muon1->P4()) + (muon2->P4())).M());
    }

    MissingET *met;
    if(branchMET->GetEntries() > 0)
    {
       met = (MissingET *) branchMET->At(0);
       histMET->Fill(met->MET);
    }
  }

  TCanvas * c1 = new TCanvas("c1","");
  histMET->Draw();

  TCanvas * c2 = new TCanvas("c2","");
  histMass->Draw();

  // Show resulting histograms
  //histJetPT->Draw();

}
