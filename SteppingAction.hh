//   STEPPING ACTION HEADER

#ifndef STEPPING_HH 
#define STEPPING_HH

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "construction.hh"
#include "EventAction.hh"
#include "G4OpticalPhoton.hh"
#include "G4RandomTools.hh"
#include "G4Poisson.hh"


class SteppingAction : public G4UserSteppingAction
{
    
public:

 SteppingAction(EventAction *eventaction);
 ~SteppingAction();
 
 virtual void UserSteppingAction(const G4Step*);


private:

 EventAction *fEventAction;

 G4double generated_photons;  //<--
 
};

#endif
