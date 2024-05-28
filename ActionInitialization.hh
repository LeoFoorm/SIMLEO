// En la parte de virtual void se define la función principal de la clase ActionInitialization corre la particle_gun y calcula los pasos. Es muy importante.

#ifndef ACTIONINITIALIZATION_HH
#define ACTIONINITIALIZATION_HH

#include "G4VUserActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh" //<--- 20/05 00:30 am
#include "EventAction.hh" //<--- 23/05 11 pm
#include "SteppingAction.hh"
class ActionInitialization : public G4VUserActionInitialization
{
 public:
  ActionInitialization();
  ~ActionInitialization();

 virtual void Build() const;

};   

#endif
