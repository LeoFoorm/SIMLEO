#ifndef STEPPING_HH 
#define STEPPING_HH
//<--- 23/05 11 pm
#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "construction.hh"
#include "EventAction.hh"

class SteppingAction : public G4UserSteppingAction
{
public:
 SteppingAction(EventAction *eventaction);
 ~SteppingAction();
 
 virtual void UserSteppingAction(const G4Step*);

private:
 EventAction *fEventAction;
 
};

#endif
