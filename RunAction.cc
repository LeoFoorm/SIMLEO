#include "RunAction.hh"

RunAction::RunAction()
{
 G4AnalysisManager *man = G4AnalysisManager::Instance();

//"man" stands for Manager

//The next is to define what kind of information we want to store
// The first means the name and then the description.
//then, the others are just names

 man->CreateNtuple("Photons","information about the Photons generated by scintillation");
 man->CreateNtupleIColumn("fEvent");
 man->CreateNtupleDColumn("p_on_X");
 man->CreateNtupleDColumn("p_on_Y");
 man->CreateNtupleDColumn("p_on_Z");
 man->CreateNtupleDColumn("fwlen");
 man->CreateNtupleDColumn("fGTime");
 man->CreateNtupleDColumn("fLTime"); 
 man->FinishNtuple(0);


 man->CreateNtuple("hits","Just to verify the number of photons detected by the SiPM");
 man->CreateNtupleIColumn("fEvent");
 man->CreateNtupleDColumn("hits_on_Z_in_[mm]");
 man->FinishNtuple(1);


 //man->CreateH1("Energy Deposition","Energy Deposition",100,0.,10.*MeV); 
 man->CreateNtuple("Edep","Energy deposited byt the muon");
 man->CreateNtupleDColumn("Energy_Deposition");
 man->CreateNtupleDColumn("Muon_Momentum"); //<----------------------- 21/09/2024 
 //man->CreateNtupleDColumn("Muon_momentum");
 man->FinishNtuple(2);

 
}

RunAction::~RunAction()
{}


void RunAction:: BeginOfRunAction(const G4Run* run)
{
 G4AnalysisManager *man = G4AnalysisManager::Instance();   // IMPORTANTE

 G4int runID = run->GetRunID();

 std::stringstream strRunID;
 strRunID << runID;

 man->OpenFile("Output"+strRunID.str()+".root");

 photonHits = 0; 

}

void RunAction::EndOfRunAction(const G4Run*)
{
 G4AnalysisManager *man = G4AnalysisManager::Instance();
 
 man->Write();
 man->CloseFile();

 G4cout << "NUMBER OF PHOTONS DETECTED: " << photonHits << G4endl; 

}
