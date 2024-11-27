//    DETECTOR CONSTRUCTION HEADER

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
#include "G4SubtractionSolid.hh"


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


    void ConstructSingleBar();
    void ConstructMIDModule();     //<--- 
    void ConstructTwoBars();


    G4LogicalVolume *GetScoringVolume() const {return fScoringVolume;}  //<---- for the edep 
    G4LogicalVolume *GetScoringVolume1() const {return fScoringVolume_one;} //
    G4LogicalVolume *GetScoringVolume2() const {return fScoringVolume_two;} //

    G4double wavelength, lightOutput;

    G4bool Single_bar; 
    G4bool MID_Module; 
    G4bool Two_Bars;
    G4double distance_modules; 
    
    bool Is_Single_Bar() const {return Single_bar; }; //
    bool Is_MID() const {return MID_Module;}; //
    bool Is_Two_Bars() const { return Two_Bars;} //


  private: 

   //G4LogicalVolume *Logicsipm; 


   //In order to give the sensitivity characteristic to the detector, we have to references to this object outsid. That's why we create this private
    virtual void ConstructSDandField();//here I define this function in order to give th detector characteristics. Private means that this function is previously define on Geant4.


    G4double env_sizeX, env_sizeY, env_sizeZ; 

    G4GenericMessenger *fMessenger;  


    G4Box  *SolidWorld, *Solidbar, *Solidsipm, *Solidmylar, *SolidInnermylar;
    G4LogicalVolume *LogicWorld, *Logicbar, *Logicmylar, *Logicsipm;  
    G4VPhysicalVolume *PhysicalWorld, *Physicalbar, *Physicalsipm, *Physicalmylar, 
                      *Physical_MID_A, *Physical_SiPM_MID_A, *Physical_Mylar_MID_A, 
                      *Physical_MID_B, *Physical_SiPM_MID_B, *Physical_Mylar_MID_B,
                      *Phys_Bar_One, *Phys_Bar_One_SiPM, *Phys_Bar_One_Mylar,
                      *Phys_Bar_Two, *Phys_Bar_Two_SiPM, *Phys_Bar_Two_Mylar;

    
    void DefineMaterials();


    G4Material *plastic, *worldMaterial, *mylarMaterial;
   
    
    
    //G4bool Single_bar; 
    //G4bool MID_Module; 
    //G4bool Two_Bars;
    //G4double distance_modules; 


    G4OpticalSurface *mirrorsurface; //based on the PET video 13/05 1:46 pm
    

    G4LogicalVolume *fScoringVolume; //<-----

    G4LogicalVolume *fScoringVolume_one; //
    G4LogicalVolume *fScoringVolume_two; //

};

#endif
