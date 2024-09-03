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


//The method AddEdep(G4double edep){ fEdep += edep; } 
//is used to accumulate energy deposition (edep) in an event.
//' edep ' is a parameter representing the energy deposited in a single step or process.
//' fEdep += edep ' adds this deposited energy to the TOTAL ENERGY DEPOSITION (fEdep) for the current event.


 void AddEdep(G4double edep){ fEdep += edep; }


private:

 G4double fEdep;
 
};

#endif
