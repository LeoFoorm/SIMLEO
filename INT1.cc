#include <iostream>
#include "G4RunManager.hh"

#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "construction.hh"


//argc and argv are parameters used to process command-line arguments. argc argument count and
// argv argument vector.



int main(int argc,char** argv)
{
    G4RunManager *runManager = new G4RunManager;
    
    runManager->SetUserInitialization(new myDetectorConstruction());
    runManager->SetUserInitialization(new PhysicsList());
    
    
    runManager->Initialize();
    
    G4UIExecutive *ui = new G4UIExecutive(argc,argv);
    
    G4VisManager * visManager = new G4VisExecutive();
    visManager->Initialize();
    
    G4UImanager *UImamager = G4UImanager::GetUIpointer();

     UImanager->ApplyCommand("/vis/open OGL");
    //UImanager->ApplyCommand("/vis/viewer/set/ViewpointVector 1 1 1");
     UImanager->ApplyCommand("/vis/drawVolume");
    
    ui->SessionStart();
    
    return 0;
}

