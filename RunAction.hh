#ifndef RUN_HH
#define RUN_HH

#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"		//ya no es g4root.hh, ahora es este que puse.

class RunAction : public G4UserRunAction
{
 public:
  RunAction();
  ~RunAction();

  virtual void BeginOfRunAction(const G4Run*);
  virtual void EndOfRunAction(const G4Run*);
};

#endif
