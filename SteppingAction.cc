//  STEPPING ACTION SOURCE

#include "SteppingAction.hh"

SteppingAction::SteppingAction(EventAction *eventaction)
{
 fEventAction = eventaction;
}


SteppingAction::~SteppingAction()
{}


//------------------------------------------------------------


void SteppingAction::UserSteppingAction(const G4Step *step)
{
 //--------------- Getting Edep ---------------------
 G4LogicalVolume *scoringvolume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
 const myDetectorConstruction *detectorconstruction = static_cast < const myDetectorConstruction* > (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
 G4LogicalVolume *fScoringVolume = detectorconstruction->GetScoringVolume();

 if(scoringvolume != fScoringVolume)
 {
   return;                             //This checks if the current step is within the scoring volume. 
 }                                     //If it is not, the method returns immediately, doing nothing for this step.
 
G4double edep = step->GetTotalEnergyDeposit();
if (edep > 0.) 
{
 fEventAction->AddEdep(edep); 
}


//---------- Getting Nu. generated photons using Edep:
 G4Material *plastic_scin = step->GetPreStepPoint()->GetMaterial(); //<-- (#PUE)
 G4MaterialPropertiesTable *Yield = plastic_scin->GetMaterialPropertiesTable();  //<-- (#PUE)
 G4double Scintillation_Yield = Yield->GetConstProperty("SCINTILLATIONYIELD");  //<-- (#PUE)
 
 generated_photons = edep * Scintillation_Yield;  //<-- (#PUE)
 
 generated_photons = G4Poisson(generated_photons);  //<-- (#PUE)
 
 fEventAction->AddPhotonG_UsingEdep(generated_photons);  //<--  check the variable using in event action
 

 //--------------- Getting dE/dx ---------------------
 // Getting the step lengh and Energy deposited by each step
 // Retrieve the particle type
G4ParticleDefinition* particle = step->GetTrack()->GetDefinition();

if (particle->GetParticleName() == "pi+")
{
 G4double stepLength = step->GetStepLength();
 
 G4double dEdxStep = 0.;                                                // Initialize dEdxStep to 0
 
  if (edep > 0. && stepLength > 0.) 
  {
      dEdxStep = edep / stepLength;                                  // dE/dx for this step in MeV/mm
      
      fEventAction->AccumulatedEdx(dEdxStep);                       // Stores dE/dx in order to track it for every event
  //G4cout << "dE/dx [MeV/mm] FOR THIS STEP: " << dEdxStep << G4endl;
  }
}
 

 //---------- Getting the generated scintillation photons
 // Check if the current step generates optical photons (scintillation photons)
G4ParticleDefinition* particle_photon = step->GetTrack()->GetDefinition();
if (particle_photon == G4OpticalPhoton::OpticalPhotonDefinition()) 
{
      // Get the process that created this photon
   const G4VProcess* creatorProcess = step->GetTrack()->GetCreatorProcess();
      // Check if the photon was created by the scintillation process
   if (creatorProcess && creatorProcess->GetProcessName() == "Scintillation") 
   {
   // Count the photon by calling EventAction
      fEventAction->AddPhotonG();  // You can implement AddPhoton() in EventAction
   }
}

}
