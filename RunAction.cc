#include "RunAction.hh"

RunAction::RunAction()
{}

RunAction::~RunAction()
{}

void RunAction:: BeginOfRunAction(const G4Run*)
{
 G4AnalysisManager *man = G4AnalysisManager::Instance();

 man->OpenFile("OutputIntento.root");
 //The next is to define what kind of information we want to store
 //man->CreateNtuple("hits","hits");
 //man->CreateNtupleIColumn();
}

void RunAction::EndOfRunAction(const G4Run*)
{
 G4AnalysisManager *man = G4AnalysisManager::Instance();
 
 man->Write();
 man->CloseFile();
}
