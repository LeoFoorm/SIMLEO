//   EVENT ACTION SOURCE

#include "EventAction.hh" 


EventAction::EventAction(RunAction*)
{
 fEdep = 0.;

 totalLocalTime = 0.; 
 photonHits = 0; 

 fTotaldEdx = 0.;
 muonCount = 0;

 fPhotonCount = 0;
 fGenerated_photons = 0; //<-- (#PUE)

 //PhotonDetected_perevent = 0; //<--
}


EventAction::~EventAction()
{}


//#####################################################
void EventAction::AccumulatedEdx(G4double dEdxStep)
{
    fTotaldEdx += dEdxStep; 
}
//#####################################################


//#####################################################
void EventAction::BeginOfEventAction(const G4Event*)
{
 fEdep = 0.;

 totalLocalTime = 0.; // Reset at the start of each event 
 photonHits = 0;      // Reset at the start of each event 

 fTotaldEdx = 0.;

 muonCount++;
 G4cout << "# # # ID EVENT: "  << muonCount << G4endl;

 fPhotonCount = 0;
 fGenerated_photons = 0; //<-- (#PUE)

 //PhotonDetected_perevent = 0; //<--
}
//#########################################################


//#########################################################
void EventAction::AddLocalTime(G4double ltime)
{
    totalLocalTime += ltime; // Accumulate local time
}
//#########################################################


//####################################################
void EventAction::AddPhotonHit()
{
    photonHits++; // Count photon hits
}
//####################################################


//#########################################################
void EventAction::AddPhotonG()
{
    fPhotonCount++; // Count the photons generated
}
//#########################################################



void EventAction::EndOfEventAction(const G4Event*)
{
G4AnalysisManager *man = G4AnalysisManager::Instance();  


G4double meanLocalTime;
if (photonHits > 0) 
{
    meanLocalTime = totalLocalTime / photonHits;
} 
else 
{
    meanLocalTime = 0.0;
}


G4cout << "ENERGY DEPOSITION:  " << fEdep << " MeV" << G4endl;

G4cout << "MEAN LOCAL TIME: " << meanLocalTime << " ns" << G4endl;

G4cout << "TOTAL dE/dx FOR THIS EVENT: " << fTotaldEdx << " MeV/mm" << G4endl;

G4cout << "NUMBER OF SCINTILLATION PHOTONS GENERATED: " << fPhotonCount << G4endl; //<-- (#PUE)

G4cout << "NUMBER OF SCINTILLATION PHOTONS GENERATED BY dE/dx: " << fGenerated_photons << G4endl; //<--(#PUE)

G4cout << "NUMBER OF PHOTONS DETECTED PER EVENT (SiPM): " << photonHits << G4endl;

man->FillNtupleDColumn(3,0,meanLocalTime);
man->AddNtupleRow(3);


man->FillNtupleDColumn(2,0,fEdep);
man->FillNtupleDColumn(2,2,fTotaldEdx);
man->FillNtupleDColumn(2,4,fPhotonCount);
man->FillNtupleDColumn(2,5,fGenerated_photons);
man->AddNtupleRow(2);

}
