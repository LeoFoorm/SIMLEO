//      SENSITIVE DETECTOR SORUCE

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
    G4double time = preStepPoint->GetGlobalTime();      //since the primary particle was created; since the beggining of the event;Muon to Scintillator
    G4double ltime = preStepPoint->GetLocalTime();      //since the particle was created; photon to SiPM
    G4double wlen = (1.239841939*eV/momentumphoton.mag())*1E+03;        //Units [nm]

    //G4cout<<" PHOTON POSITION "<<posPhoton<<G4endl;  //position of the detected photons
    
    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
    G4VPhysicalVolume *PhysVol = touchable->GetVolume();
    G4ThreeVector posDetector = PhysVol->GetTranslation();

    //G4cout << " DETECTOR POSITION:  " << posDetector << G4endl;
    //G4cout << " PHOTON WAVELENGTH:  " << wlen << G4endl;
    //G4cout << " GLOBAL TIME  " << time << G4endl;
    //G4cout << " LOCAL TIME  " << ltime << G4endl;

    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID(); 

     //################################################# NUMBER OF DETECTED PHOTONS
    const RunAction *runaction = static_cast< const RunAction* >(G4RunManager::GetRunManager()->GetUserRunAction());
    RunAction *runactionNonConst = const_cast<RunAction *>(runaction); 
    runactionNonConst->AddPhotonHit();


    //################################################# NUMBER OF DETECTED PHOTONS PER EVENT
   // const EventAction *eventaction_photons = static_cast< const EventAction* >(G4RunManager::GetRunManager()->GetUserEventAction());
    //EventAction *eventactionNonConst = const_cast<EventAction *>(eventaction_photons); 
    //eventactionnNonConst->AddPhotonHit();

    
    //################################################# ACOMULATE LOCAL TIME
    const EventAction* constEventAction = static_cast<const EventAction*>(G4RunManager::GetRunManager()->GetUserEventAction());
    EventAction* eventAction = const_cast<EventAction*>(constEventAction);  // Correct the cast
     eventAction->AddPhotonHit();
     eventAction->AddLocalTime(ltime);



    G4AnalysisManager *man = G4AnalysisManager::Instance(); 

    man->FillNtupleIColumn(0,0,evt); 
    man->FillNtupleDColumn(0,1,momentumphoton[0]);
    man->FillNtupleDColumn(0,2,momentumphoton[1]);
    man->FillNtupleDColumn(0,3,momentumphoton[2]);
    man->FillNtupleDColumn(0,4,wlen);  
    man->FillNtupleDColumn(0,5,time);
    man->FillNtupleDColumn(0,6,ltime);
    man->AddNtupleRow(0); 

    man->FillNtupleIColumn(1,0,evt); 
    man->FillNtupleDColumn(1,1,posDetector[2]); //ES PARA LA POSICIÓN Z    
    man->AddNtupleRow(1);
     
}
