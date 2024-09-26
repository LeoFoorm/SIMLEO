#include "EventAction.hh" 


EventAction::EventAction(RunAction*)
{
 fEdep = 0.;

 totalLocalTime = 0.; 
 photonHits = 0; 
}


EventAction::~EventAction()
{}


void EventAction::BeginOfEventAction(const G4Event*)
{
 fEdep = 0.;

 totalLocalTime = 0.; // Reset at the start of each event 
 photonHits = 0;      // Reset at the start of each event 
}

//#########################################################
void EventAction::AddLocalTime(G4double ltime)
{
    totalLocalTime += ltime; // Accumulate local time
}

void EventAction::AddPhotonHit()
{
    photonHits++; // Count photon hits
}
//####################################################

void EventAction::EndOfEventAction(const G4Event*)
{

G4AnalysisManager *man = G4AnalysisManager::Instance();  

  //G4double meanLocalTime = (photonHits > 0) ? totalLocalTime / photonHits : 0.0;
G4double meanLocalTime;

if (photonHits > 0) {
    meanLocalTime = totalLocalTime / photonHits;
} else {
    meanLocalTime = 0.0;
}

 G4cout << "ENERGY DEPOSITION:  " << fEdep << G4endl;

G4cout << "MEAN LOCAL TIME: " << meanLocalTime << " ns" << G4endl;

man->FillNtupleDColumn(3,0,meanLocalTime);
man->AddNtupleRow(3);


man->FillNtupleDColumn(2,0,fEdep);
man->AddNtupleRow(2);

}
