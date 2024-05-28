#include "ActionInitialization.hh"

ActionInitialization::ActionInitialization()
{}

ActionInitialization::~ActionInitialization()
{}

void ActionInitialization::Build() const
{
    PrimaryGeneratorAction *generator = new PrimaryGeneratorAction();
    SetUserAction(generator);

    RunAction *runaction = new RunAction();//<--- 20/05 00:30 am
    SetUserAction(runaction);

    EventAction *eventaction = new EventAction(runaction); //<---- 23/05 11 pm
    SetUserAction(eventaction);

    SteppingAction *steppingaction = new SteppingAction(eventaction);
    SetUserAction(steppingaction);
}
