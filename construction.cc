#include "construction.hh"
#include "G4SystemOfUnits.hh"
#include <fstream>
#include <vector>
#include <iostream>
#include <tuple>


//los que estan a continuacion supongo que se van a usar despues

myDetectorConstruction::myDetectorConstruction()
{}

myDetectorConstruction::~myDetectorConstruction()
{}

//all the important information to Construct() to construct the detector
G4VPhysicalVolume *myDetectorConstruction::Construct()
{

  //#################################################################
  //reflective index
    std::ifstream file("bc404.txt");
    std::vector<G4double> energy;
    std::vector<G4double> RI;
    std::vector<G4double> fraction;
    std::vector<G4double> absSC;
    G4double RefIndex=1.58;
    G4double AbsSC = 160.*cm;

    while(!file.eof()){
        file >> wavelength>>lightOutput;
        G4double Energy=1.239841939*eV/((wavelength/1000));
        lightOutput= lightOutput/100;
        energy.push_back(Energy);
        fraction.push_back(lightOutput);
        RI.push_back(RefIndex);
        absSC.push_back(AbsSC);
      }

    G4int numberOfEntries=energy.size();
    G4int contador = 0;
    while(contador<numberOfEntries){
       RI.push_back(RefIndex);
       absSC.push_back(AbsSC);
       contador++;
      } 
// Get nist material manager
  G4OpticalParameters::Instance()->SetScintFiniteRiseTime(true);
  G4NistManager *nist = G4NistManager::Instance();
  G4Material *worldMaterial = nist->FindOrBuildMaterial("G4_AIR");
  G4Material *plastic = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");

  G4MaterialPropertiesTable *prop=new G4MaterialPropertiesTable();
    prop->AddProperty("RINDEX",energy, RI,numberOfEntries);
    prop->AddProperty("SCINTILLATIONCOMPONENT1",energy,fraction,numberOfEntries);
    prop->AddConstProperty("SCINTILLATIONYIELD", 10./keV);
    prop->AddConstProperty("RESOLUTIONSCALE", 1.);
    prop->AddProperty("ABSLENGTH",energy,absSC,numberOfEntries);
    plastic->SetMaterialPropertiesTable(prop);
//#################################################################
  
  G4double env_sizeX = 20*cm;
  G4double env_sizeY = 20*cm;
  G4double env_sizeZ = 130*cm;
  //creo que esto se mide en mitades, es decir en x serian realmente 40 

  //world

  G4Box *SolidWorld = new G4Box("SolidWorld", env_sizeX, env_sizeY, env_sizeZ);
  
  //logical
 //primer parametro es el solid world, el siguiente el material y el ultimo el nombre del logical
  G4LogicalVolume *LogicWorld = new G4LogicalVolume(SolidWorld, worldMaterial, "LogicWorld");

  //Physical

  //parametros: rotation, origen (0,0,0), el logical volume, su nombre, si va a estar dentro de otro volumen, copias, check overlaps
  G4VPhysicalVolume *PhysicalWorld = new G4PVPlacement(0, G4ThreeVector(), LogicWorld, "PhysicalWorld", 0, false, 0, true);

//BARRA
  G4double bar_X = 5*cm;
  G4double bar_Y = 1*cm;
  G4double bar_Z = 100*cm;
  
  G4Box *Solidbar = new G4Box("Solidbar", bar_X, bar_Y, bar_Z );
  G4LogicalVolume *Logicbar = new G4LogicalVolume(Solidbar, plastic, "Logicbar");
  G4VPhysicalVolume *Physicalbar = new G4PVPlacement(0, G4ThreeVector(), Logicbar, "Physicalbar", LogicWorld, false, 0, true);



  //the mother volume always needs this return
  return PhysicalWorld;
}
