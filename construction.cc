//  DETECTOR CONSTRCTION SOURCE


#include "construction.hh"
#include "G4SystemOfUnits.hh"
#include <fstream>
#include <vector>
#include <iostream>
#include <tuple>


myDetectorConstruction::myDetectorConstruction()
{
  fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construction");

  fMessenger->DeclareProperty("Single_bar", Single_bar, "Construct Single bar detector");
  fMessenger->DeclareProperty("MID_Module", MID_Module, "Construct MID module detector");
  fMessenger->DeclareProperty("distance_modules", distance_modules, "The distance between both modules");
  fMessenger->DeclareProperty("Two_Bars", Two_Bars, "Construct Two Bars array as a detector");

  DefineMaterials();

  env_sizeX = 5*m;
  env_sizeY = 5*m;
  env_sizeZ = 5*m;

  distance_modules = 20*cm + 1.04*cm;

  Single_bar = false; 
  MID_Module = true; 
  Two_Bars = false;
}


myDetectorConstruction::~myDetectorConstruction()
{}


void myDetectorConstruction::DefineMaterials()
{
  
  std::vector<G4double> wavelength = {499.83,496.62,491.92,487.22,482.51,477.81,473.10,468.40,463.69,458.99,454.28,449.58,445.30,441.45,438.03,434.18,429.69,425.20,417.03,415.36,414.08,413.22,412.53,411.60,410.66,409.80, 408.53,405.80,402.75,400.18,399.32,397.27,396.33,395.48,394.62,394.28,392.91,392.27,391.41,390.34,389.70,388.42,386.63,384.57,381.58,380.31};
  std::vector<G4double> lightOutput = {2.55,2.56,2.97,3.59,4.40,5.49,6.93,8.52,10.68,13.38,17.07,21.41,26.21,31.27,36.04,40.53,45.23,49.04,53.41,58.78,63.62,68.61,73.05,78.28,83.01,88.07,92.45,96.07,99.46,96.00,91.32,86.66,80.18,73.98,69.53,64.76,58.40,50.56,44.59,38.14,33.28,29.14,23.55,17.68,12.13,6.27,4.06};
  std::vector<G4double> energy;
  std::vector<G4double> RI;
  std::vector<G4double> fraction;
  std::vector<G4double> absSC;
  std::vector<G4double> rindexWorld;
  std::vector<G4double> reflectivity;
  std::vector<G4double> rindexmylar;

  G4double RefIndex=1.58;

  G4double AbsSC = 160.*cm;

  G4double RIWorld = 1.0;

  G4double Reflectivity = 0.9999;

  G4double Rindexmylar = 1.655;


  for (size_t i = 0; i < wavelength.size(); ++i) {

    G4double Energy = 1.239841939 * eV / (wavelength[i] / 1000);

    G4double normalizedLightOutput = lightOutput[i] / 100;

    energy.push_back(Energy);

    fraction.push_back(normalizedLightOutput);

    RI.push_back(RefIndex);

    absSC.push_back(AbsSC);

    rindexWorld.push_back(RIWorld);

    reflectivity.push_back(Reflectivity);

    rindexmylar.push_back(Rindexmylar);
    }
  
  G4int numberOfEntries = energy.size();


 G4OpticalParameters::Instance()->SetScintFiniteRiseTime(true);   // Setting finite rise time for scintillation 

 G4NistManager *nist = G4NistManager::Instance();

 worldMaterial = nist->FindOrBuildMaterial("G4_AIR");
 plastic = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
 mylarMaterial = nist->FindOrBuildMaterial("G4_MYLAR");
 mirrorsurface = new G4OpticalSurface("mirrorsurface");

 mirrorsurface->SetType(dielectric_dielectric);
 mirrorsurface->SetFinish(polishedfrontpainted);
 mirrorsurface->SetModel(unified);

 G4MaterialPropertiesTable *mirror=new G4MaterialPropertiesTable();
 G4MaterialPropertiesTable *prop=new G4MaterialPropertiesTable();
 G4MaterialPropertiesTable *propworld=new G4MaterialPropertiesTable();
 G4MaterialPropertiesTable *propmylar=new G4MaterialPropertiesTable();
 
//##########################################################################
 
 propworld->AddProperty("RINDEX",energy, rindexWorld,numberOfEntries);
 prop->AddProperty("RINDEX",energy, RI,numberOfEntries);
 prop->AddProperty("SCINTILLATIONCOMPONENT1",energy,fraction,numberOfEntries);
 prop->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 1.8*ns);
 prop->AddConstProperty("SCINTILLATIONRISETIME1", 0.7*ns); //decay time of the scintillator
 prop->AddConstProperty("SCINTILLATIONYIELD", 10.666666/keV);//amount of photons per (in this case) KeV       <------- ATENTION 
 prop->AddConstProperty("RESOLUTIONSCALE", 1.);
 prop->AddProperty("ABSLENGTH",energy,absSC,numberOfEntries);
 mirror->AddProperty("REFLECTIVITY", energy, reflectivity);
 propmylar->AddProperty("RINDEX",energy, rindexmylar,numberOfEntries);


 worldMaterial->SetMaterialPropertiesTable(propworld);
 plastic->SetMaterialPropertiesTable(prop);
 mirrorsurface->SetMaterialPropertiesTable(mirror);
 mylarMaterial->SetMaterialPropertiesTable(propmylar);
}



void myDetectorConstruction::ConstructSingleBar()
{ 

//########################## SCINTILLATION BAR ###############################  
  

  Physicalbar = new G4PVPlacement(0, G4ThreeVector(), Logicbar, "Physicalbar", LogicWorld, false, 0, true);
  //fScoringVolume = Logicbar;
  
//############################ DETECTOR (SiPM)  ###########################
  G4ThreeVector possipm = G4ThreeVector(0, 0, 50.03*cm);
  
  Physicalsipm = new G4PVPlacement(0, possipm, Logicsipm, "Physicalsipm", LogicWorld, false, 0, true);
 

//############################# MYLAR  #############################

  Physicalmylar = new G4PVPlacement(0,G4ThreeVector(),Logicmylar,"Physicalmylar",LogicWorld,false,0,true);

}



//-------------------------------------------------------------------
void myDetectorConstruction::ConstructMIDModule() //<---
{
//############ 20 SCINTILLATION BARS A ####################
  for (G4int i = 0; i <20; i++)
  {
  Physical_MID_A = new  G4PVPlacement(0, G4ThreeVector(-47.88 * cm + (5.04*i) * cm, 0, 0),
                                    Logicbar, "Physical_MID_A", LogicWorld, false, i, true);
  }


//############ 20 SiPM A ####################
 for (G4int j = 0; j<20; j++)
 {
  Physical_SiPM_MID_A = new  G4PVPlacement(0, G4ThreeVector(-47.88 * cm + (5.04*j) * cm, 0, 50.03*cm),
                                    Logicsipm, "Physical_SiPM_MID_A", LogicWorld, false, j, true);
 }


//############ 20 MYLAR A ####################
  for(G4int k = 0; k<20; k++)
  {
  Physical_Mylar_MID_A = new  G4PVPlacement(0, G4ThreeVector(-47.88 * cm + (5.04*k) * cm, 0, 0),
                                    Logicmylar, "Physical_Mylar_MID_A", LogicWorld, false, k, true);
  }

//----------------------------------------------------------------------

//############ 20 SCINTILLATION BARS B ####################
  G4RotationMatrix* rotationY = new G4RotationMatrix(); //<--
  rotationY->rotateY(90*deg); //<---


  for (G4int l = 0; l <20; l++)
  {
  Physical_MID_B = new  G4PVPlacement(rotationY, G4ThreeVector( 0, distance_modules, -47.88 * cm + (5.04*l) * cm),
                                    Logicbar, "Physical_MID_B", LogicWorld, false, l, true);
  }


//############ 20 SiPM B ####################
 for (G4int m = 0; m<20; m++)
 {
  Physical_SiPM_MID_B = new  G4PVPlacement(rotationY, G4ThreeVector(50.03*cm, distance_modules,  -47.88 * cm + (5.04*m) * cm),
                                    Logicsipm, "Physical_SiPM_MID_B", LogicWorld, false, m, true);
 }


//############ 20 MYLAR B  ####################
  for(G4int n = 0; n<20; n++)
  {
  Physical_Mylar_MID_B = new  G4PVPlacement(rotationY, G4ThreeVector(0, distance_modules, -47.88 * cm + (5.04*n) * cm),
                                    Logicmylar, "Physical_Mylar_MID_B", LogicWorld, false, n, true);
  }
}
//-------------------------------------------------------------------




//-------------------------------------------------------------------
void myDetectorConstruction::ConstructTwoBars() //<---
{
//############ ANOTHER BAR BUT ROTATE ####################
  
  Phys_Bar_One = new G4PVPlacement(0, G4ThreeVector(), Logicbar, "Phys_Bar_One", LogicWorld, false, 0, true);
  fScoringVolume_one = Logicbar; //
  
  G4ThreeVector possipm = G4ThreeVector(0, 0, 50.03*cm);
  
  Phys_Bar_One_SiPM = new G4PVPlacement(0, possipm, Logicsipm, "Phys_Bar_One_SiPM", LogicWorld, false, 0, true);
 
  Phys_Bar_One_Mylar = new G4PVPlacement(0,G4ThreeVector(),Logicmylar,"Phys_Bar_One_Mylar",LogicWorld,false,0,true);


  G4RotationMatrix* rotationY_Two = new G4RotationMatrix(); 
  rotationY_Two->rotateY(90*deg); 

  Phys_Bar_Two = new G4PVPlacement(rotationY_Two, G4ThreeVector(0,distance_modules,0), Logicbar, "Phys_Bar_Two", LogicWorld, false, 1, true);
  fScoringVolume_one = Logicbar; //

  G4ThreeVector possipm_Two = G4ThreeVector(50.03*cm, distance_modules,0);
  
  Phys_Bar_Two_SiPM = new G4PVPlacement(rotationY_Two, possipm_Two, Logicsipm, "Phys_Bar_Two_SiPM", LogicWorld, false, 1, true);
 
  Phys_Bar_Two_Mylar = new G4PVPlacement(rotationY_Two,G4ThreeVector(0,distance_modules,0),Logicmylar,"Phys_Bar_Two_Mylar",LogicWorld,false,1,true);
  
}
//-------------------------------------------------------------------



G4VPhysicalVolume *myDetectorConstruction::Construct()
{
  // Solid world
  SolidWorld = new G4Box("SolidWorld", env_sizeX, env_sizeY, env_sizeZ);
  
  //logical
  LogicWorld = new G4LogicalVolume(SolidWorld, worldMaterial, "LogicWorld");

  //Physical
  //parametros: rotation, origen (0,0,0), el logical volume, su nombre, si va a estar dentro de otro volumen, copias, check overlaps
  PhysicalWorld = new G4PVPlacement(0, G4ThreeVector(), LogicWorld, "PhysicalWorld", 0, false, 0, true);


//############################ BAR ###########################
  G4double bar_X = 2.5*cm;
  G4double bar_Y = 0.5*cm;
  G4double bar_Z = 50*cm;
  
  Solidbar = new G4Box("Solidbar", bar_X, bar_Y, bar_Z );
  Logicbar = new G4LogicalVolume(Solidbar, plastic, "Logicbar");
  fScoringVolume = Logicbar;


//########################## SiPM #############################
  G4double sipm_X = 0.3*cm;
  G4double sipm_Y = 0.3*cm;
  G4double sipm_Z = 0.025*cm;
  
  Solidsipm = new G4Box("Solidsipm", sipm_X, sipm_Y, sipm_Z );
  Logicsipm = new G4LogicalVolume(Solidsipm, worldMaterial, "Logicsipm");
 

//############################# MYLAR ##############################
  G4double mylar_x = 2.52*cm;
  G4double mylar_y = 0.52*cm;
  G4double mylar_z = 50.08*cm;

 
 Solidmylar = new G4Box("Solidmylar", mylar_x, mylar_y, mylar_z);
 SolidInnermylar = new G4Box("SolidInnermylar", mylar_x-0.01*cm, mylar_y-0.01*cm, mylar_z-0.01*cm);

 G4SubtractionSolid* hollowMylarBox = new G4SubtractionSolid("HollowMylarBox", Solidmylar, SolidInnermylar);

 Logicmylar = new G4LogicalVolume(hollowMylarBox, mylarMaterial, "Logicmylar");

 G4LogicalSkinSurface *skin= new G4LogicalSkinSurface("skin", Logicmylar, mirrorsurface); 


  if(Single_bar) 
   ConstructSingleBar();//<---

  if (MID_Module)
   ConstructMIDModule(); //<---

  if(Two_Bars)
   ConstructTwoBars(); 

  //the mother volume always needs this return
  return PhysicalWorld; 
}


void myDetectorConstruction::ConstructSDandField()
{
 SensitiveDetector *sensDet = new SensitiveDetector("SensitiveDetector");
 
  Logicsipm->SetSensitiveDetector(sensDet);

  
}

