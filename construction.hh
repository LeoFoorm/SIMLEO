

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
#include "G4GenericMessenger.hh" 
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh" 


class G4VPhysicalVolume;
class G4LogicalVolume;



/// Detector construction class to define materials and geometry.

class myDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    

    myDetectorConstruction();
    ~myDetectorConstruction();
  
  
    //toda la construccion del detector va a estar dentro de la funcion Construct()
    virtual G4VPhysicalVolume *Construct(); 


    void ConstructProtoDetector();
    void ConstructAtmosphere();     // ELIMINAR LO ANTES POSIBLE


    G4LogicalVolume *GetScoringVolume() const {return fScoringVolume;}  //<---- 


    G4double wavelength, lightOutput;


  private: 


    G4LogicalVolume *Logicsipm; 


   //In order to give the sensitivity characteristic to the detector, we have to references to this object outsid. That's why we create this private
    virtual void ConstructSDandField();//here I define this function in order to give th detector characteristics. Private means that this function is previously define on Geant4.


    G4double env_sizeX, env_sizeY, env_sizeZ; 

    G4GenericMessenger *fMessenger; 


    G4Box  *SolidWorld, *Solidbar, *Solidsipm, *SolidAtmos, *Solidmylar;
    G4LogicalVolume *LogicWorld, *Logicbar, *LogicAtmos[5], *Logicmylar;  
    G4VPhysicalVolume *PhysicalWorld, *Physicalbar, *Physicalsipm, *PhysicalAtmos[5], *Physicalmylar;

    
    void DefineMaterials();


    G4Material *plastic, *worldMaterial, *Air[5], *mylarMaterial;
    G4Element *N, *O; 
    
    
    G4bool Atmospheric, ProtoDetector; 


    G4OpticalSurface *mirrorsurface; //based on the PET video 13/05 1:46 pm
    

    G4LogicalVolume *fScoringVolume; //<-----


};

#endif
