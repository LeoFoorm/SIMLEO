//   EVENT ACTION HEADER

#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4AnalysisManager.hh"
#include "RunAction.hh"


class EventAction : public G4UserEventAction
{
public:

 EventAction(RunAction*);

 ~EventAction();

 
 virtual void BeginOfEventAction(const G4Event*);

 virtual void EndOfEventAction(const G4Event*);


 void AddLocalTime(G4double ltime); 
 void AddPhotonHit(); // New function 


 void AccumulatedEdx(G4double dEdxStep);
 

//The method AddEdep(G4double edep){ fEdep += edep; } 
//is used to accumulate energy deposition (edep) in an event.
//' edep ' is a parameter representing the energy deposited in a single step or process.
//' fEdep += edep ' adds this deposited energy to the TOTAL ENERGY DEPOSITION (fEdep) for the current event.
void AddEdep(G4double edep){ fEdep += edep; }

void AddEdepOne(G4double edep){ fEdep_one += edep; } //
void AddEdepTwo(G4double edep){ fEdep_two += edep; } //


void AddPhotonG();//G4double generated_photons_G4){fPhotonCount +=  generated_photons_G4;}
G4int GetPhotonCount() const{return fPhotonCount;}


void AddPhotonG_UsingEdep(G4double generated_photons){fGenerated_photons += generated_photons;}
G4int GetPhotonCount_Edep() const{return fGenerated_photons;} 


private:

 G4double fEdep;

 G4double fEdep_one;//
 G4double fEdep_two;//

 G4double totalLocalTime; // To accumulate local time
 G4int photonHits;        // To count detected photons
 G4double fTotaldEdx;
 G4int muonCount;

 G4int fPhotonCount;
 G4int fGenerated_photons; //<-- #photons using Edep (#PUE)


};

#endif
