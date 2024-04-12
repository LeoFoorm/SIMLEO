#include "construction.hh"
#include "G4SystemOfUnits.hh"



//los que estan a continuacion supongo que se van a usar despues

myDetectorConstruction::myDetectorConstruction()
{}

myDetectorConstruction::~myDetectorConstruction()
{}

//all the important information to Construct() to construct the detector
G4VPhysicalVolume *myDetectorConstruction::Construct()
{

// Get nist material manager
  G4NistManager *nist = G4NistManager::Instance();
  G4Material *worldMaterial = nist->FindOrBuildMaterial("G4_AIR");

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





  //the mother volume always needs this return
  return PhysicalWorld;
}
