

#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4OpticalPhysics.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;



/// Detector construction class to define materials and geometry.

class myDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    

  myDetectorConstruction();
  ~myDetectorConstruction();

  G4double wavelength, lightOutput;

//lo que sigue es lo importante de definir esta clase
//toda la construccion del detector va a estar dentro de la funcion Construct()

  //G4VPhysicalVolume* Construct() override;
    
//Por lo que entiendo, sería igual poner
  virtual G4VPhysicalVolume *Construct(); 

    
};



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
