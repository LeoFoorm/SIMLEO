//    RUN ACTION SOURCE

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
 man->CreateNtupleDColumn("fMeanLTime");
 man->FinishNtuple(0);


 man->CreateNtuple("hits","Just to verify the number of photons detected by the SiPM");
 man->CreateNtupleIColumn("fEvent");
 man->CreateNtupleDColumn("hits_on_Z_in_[mm]");
 man->FinishNtuple(1);


 man->CreateNtuple("Edep","Energy deposited byt the muon");
 man->CreateNtupleDColumn("Energy_Deposition_MeV");
 man->CreateNtupleDColumn("Particle_Momentum_GeV");  
 man->CreateNtupleDColumn("EnergyDep_MeVmm");  
 man->CreateNtupleDColumn("Particle_Momentum_MeV");
 man->CreateNtupleDColumn("Photons_Generated_G4method");
 man->CreateNtupleDColumn("Photons_Generated_Edep");
 man->FinishNtuple(2);


 man->CreateNtuple("Times","The global, local and mean local time");
 man->CreateNtupleDColumn("Mean_Local_time");  
 man->FinishNtuple(3);
 
}

RunAction::~RunAction()
{}


void RunAction:: BeginOfRunAction(const G4Run* run)
{
 G4AnalysisManager *man = G4AnalysisManager::Instance();   //

 G4int runID = run->GetRunID();

 std::stringstream strRunID;
 strRunID << runID;

 man->OpenFile("Output"+strRunID.str()+".root");

 photonHits = 0; 
}


void RunAction::EndOfRunAction(const G4Run*)
{
 G4AnalysisManager *man = G4AnalysisManager::Instance();

 
 G4cout << "NUMBER OF PHOTONS DETECTED: " << photonHits << G4endl; 
 
 man->Write();
 man->CloseFile();
}
