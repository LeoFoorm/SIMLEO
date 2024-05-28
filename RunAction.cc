#include "RunAction.hh"

RunAction::RunAction()
{
 G4AnalysisManager *man = G4AnalysisManager::Instance();
//The next is to define what kind of information we want to store
 man->CreateNtuple("Photons","Photons"); //<--- 20/05 11pm 
 man->CreateNtupleIColumn("fEvent");
 man->CreateNtupleDColumn("fX");
 man->CreateNtupleDColumn("fY");
 man->CreateNtupleDColumn("fZ");
 man->CreateNtupleDColumn("fwlen");
 man->FinishNtuple(0);


 man->CreateNtuple("hits","hits");
 man->CreateNtupleIColumn("fEvent");
 man->CreateNtupleDColumn("fX"); //<----- esto se va a borrar después, es para ver si sirve
 man->CreateNtupleDColumn("fY");
 man->CreateNtupleDColumn("fZ");
 man->FinishNtuple(1);

 man->CreateNtuple("Scoring","Scoring"); //<----- 23/05 5:20 pm
 man->CreateNtupleDColumn("fEdep");
 man->FinishNtuple(2);
}

RunAction::~RunAction()
{}

void RunAction:: BeginOfRunAction(const G4Run* run)
{
 G4AnalysisManager *man = G4AnalysisManager::Instance();

 G4int runID = run->GetRunID();

 std::stringstream strRunID;
 strRunID << runID;

 man->OpenFile("Output"+strRunID.str()+".root");

 photonHits = 0; //<-- 27/05 7 pm

}

void RunAction::EndOfRunAction(const G4Run*)
{
 G4AnalysisManager *man = G4AnalysisManager::Instance();
 
 man->Write();
 man->CloseFile();

 G4cout << "NUMBER OF PHOTONS DETECTED: " << photonHits << G4endl; //<-- 27/05 7 pm
}
