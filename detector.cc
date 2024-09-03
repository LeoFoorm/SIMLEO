#include "detector.hh"

SensitiveDetector::SensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

SensitiveDetector::~ SensitiveDetector()
{}

G4bool SensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    //Information about the position of the photon
    G4Track *track = aStep->GetTrack();

    track->SetTrackStatus(fStopAndKill);

    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint();


    G4ThreeVector posPhoton = preStepPoint->GetPosition();
    G4ThreeVector momentumphoton = preStepPoint->GetMomentum(); 
    G4double time = preStepPoint->GetGlobalTime(); //since the particle was created
    G4double wlen = (1.239841939*eV/momentumphoton.mag())*1E+03; //UNIDADES nanometros

    //G4cout<<" PHOTON POSITION "<<posPhoton<<G4endl;
    //THIS TO PRINT THE DETECTOR THAT HAVE BEEN HIT. BUT I ONLY HAVE ONE DETECTOR!

    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
    G4int copyNo = touchable->GetCopyNumber();
    
    G4VPhysicalVolume *PhysVol = touchable->GetVolume();
    G4ThreeVector posDetector = PhysVol->GetTranslation();

    G4cout << " DETECTOR POSITION:  " << posDetector << G4endl;
    G4cout << " PHOTON WAVELENGTH:  " << wlen << G4endl;
    G4cout << " GLOBAL TIME  " << time << G4endl;

    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID(); 

     //#################################################<-- 27/05 7 pm NUMBER OF DETECTED PHOTONS
    const RunAction *runaction = static_cast< const RunAction* >(G4RunManager::GetRunManager()->GetUserRunAction());
    RunAction *runactionNonConst = const_cast<RunAction *>(runaction); //<--- linea que resuelve error
    runactionNonConst->AddPhotonHit();
    //#################################################

    G4AnalysisManager *man = G4AnalysisManager::Instance(); 

    man->FillNtupleIColumn(0,0,evt); 
    man->FillNtupleDColumn(0,1,momentumphoton[0]);
    man->FillNtupleDColumn(0,2,momentumphoton[1]);
    man->FillNtupleDColumn(0,3,momentumphoton[2]);
    man->FillNtupleDColumn(0,4,wlen);  
    man->FillNtupleDColumn(0,5,time);
    man->AddNtupleRow(0); 

    man->FillNtupleIColumn(1,0,evt); 
    man->FillNtupleDColumn(1,1,posDetector[2]); //por qué solo el [2] ?
    man->AddNtupleRow(1);
}
