#include "SteppingAction.hh"

SteppingAction::SteppingAction(EventAction *eventaction)
{
 fEventAction = eventaction;
}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step *step)
{
 
 G4LogicalVolume *scoringvolume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

 const myDetectorConstruction *detectorconstruction = static_cast < const myDetectorConstruction* > (G4RunManager::GetRunManager()->GetUserDetectorConstruction());

 G4LogicalVolume *fScoringVolume = detectorconstruction->GetScoringVolume();

 if(scoringvolume != fScoringVolume)
{
    return;
}

 G4double edep = step->GetTotalEnergyDeposit();
 
 fEventAction->AddEdep(edep); 

}
//<--- 23/05 11 pm