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

 if (step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName() == "Logicbar") {
    
    // Muon is passing through Logicbar
 G4cout << "  YES  "  << G4endl;
}



 const myDetectorConstruction *detectorconstruction = static_cast < const myDetectorConstruction* > (G4RunManager::GetRunManager()->GetUserDetectorConstruction());

 Gputop el q   ue lño l4LogicalVolume *fScoringVolume = detectorconstruction->GetScoringVolume();

 if(scoringvolume != fScoringVolume)
 {
    return;
 }

 G4double edep = step->GetTotalEnergyDeposit();

 if (edep > 0.) {
 
 fEventAction->AddEdep(edep); 

 }

}
