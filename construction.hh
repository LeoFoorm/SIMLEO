

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
#include "detector.hh"
#include "G4GenericMessenger.hh" //*  06/05 6:30 pm
#include "G4OpticalSurface.hh"//* 13/05 1:46 pm
#include "G4LogicalSkinSurface.hh" //* 13/05 4:24 pm
class G4VPhysicalVolume;
class G4LogicalVolume;



/// Detector construction class to define materials and geometry.

class myDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    

  myDetectorConstruction();
  ~myDetectorConstruction();
  
  

//lo que sigue es lo importante de definir esta clase
//toda la construccion del detector va a estar dentro de la funcion Construct()
  virtual G4VPhysicalVolume *Construct(); 
  void ConstructProtoDetector();//*  06/05 6:50 pm
  void ConstructAtmosphere();//*  06/05 6:50 pm

  G4LogicalVolume *GetScoringVolume() const {return fScoringVolume;}//<---- 24/05 12 pm

  G4double wavelength, lightOutput;

  private: 
    G4LogicalVolume *Logicsipm;
  //In order to give the sensity characteristic to the detector, we have to references to this object outsid. That's why we create this private
    virtual void ConstructSDandField();//here I define this function in order to give th detector characteristics. Private means that this function is previously define on Geant4.

    G4double env_sizeX, env_sizeY, env_sizeZ; //*  06/05 6:40 pm

    G4GenericMessenger *fMessenger; //*  06/05 6:30 pm

    G4Box  *SolidWorld, *Solidbar, *Solidsipm, *SolidAtmos, *Solidmylar;
    G4LogicalVolume *LogicWorld, *Logicbar, *LogicAtmos[5], *Logicmylar;  //<------- Posible problema futuro con el numero de layers
    G4VPhysicalVolume *PhysicalWorld, *Physicalbar, *Physicalsipm, *PhysicalAtmos[5], *Physicalmylar;

    void DefineMaterials();

    G4Material *plastic, *worldMaterial, *Air[5], *mylarMaterial;
    G4Element *N, *O; //*  06/05 7:26 pm
    
    
    G4bool Atmospheric, ProtoDetector; //*  06/05 6:30 pm

    G4OpticalSurface *mirrorsurface; //based on the PET video 13/05 1:46 pm

    G4LogicalVolume *fScoringVolume;


};



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
