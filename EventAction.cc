#include "EventAction.hh" 


EventAction::EventAction(RunAction*)
{
 fEdep = 0.;
}


EventAction::~EventAction()
{}


void EventAction::BeginOfEventAction(const G4Event*)
{
 fEdep = 0.;
}


void EventAction::EndOfEventAction(const G4Event*)
{

 G4cout << "ENERGY DEPOSITION:  " << fEdep << G4endl;



 G4AnalysisManager *man = G4AnalysisManager::Instance();  // IMPORTANTE
 
  
man->FillNtupleDColumn(2,0,fEdep);
man->AddNtupleRow(2);

}
