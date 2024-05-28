#include "construction.hh"
#include "G4SystemOfUnits.hh"
#include <fstream>
#include <vector>
#include <iostream>
#include <tuple>

//los que estan a continuacion supongo que se van a usar despues

myDetectorConstruction::myDetectorConstruction()
{
  fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construction");//*  06/05 6:35 pm
  fMessenger->DeclareProperty("ProtoDetector", ProtoDetector, "Construct Protodetector");//*  06/05 6:56 pm
  fMessenger->DeclareProperty("Atmosphere", Atmospheric, "Construct Atmospheric");//*  06/05 6:56 pm

  DefineMaterials();//*  06/05 6:35 pm
  ProtoDetector = true; //*  06/05 6:35 pm
  Atmospheric = false; //<-------------------------------------

  env_sizeX = 5*m;
  env_sizeY = 5*m;//*  06/05 6:51 pm
  env_sizeZ = 5*m;
  //creo que esto se mide en mitades, es decir en x serian realmente 40 
}

myDetectorConstruction::~myDetectorConstruction()
{
  
}

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

    //while(!file.eof()){
        //file >> wavelength>>lightOutput;
        //G4double Energy=1.239841939*eV/((wavelength/1000));
        //lightOutput= lightOutput/100;
        //energy.push_back(Energy);
        //fraction.push_back(lightOutput);
        //RI.push_back(RefIndex);
        //absSC.push_back(AbsSC);
      //}

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

 G4NistManager *nist = G4NistManager::Instance();
 G4OpticalParameters::Instance()->SetScintFiniteRiseTime(true);

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
 
 //############################ Atmospheric #################################
 G4double density0 =  1.29*kg/m3;   //*  06/05 7:21 pm
 G4double aN = 14.01*g/mole;   //Molar mass of nitrogene *  06/05 7:21 pm
 G4double aO = 16.00*g/mole;  //Molar mass of oxigene *  06/05 7:21 pm
 //PUEDE QUE FALTEN MÁS GASES QUE HAY EN LA ATMOSFERA

 N = new G4Element("Nitrogen", "N", 7, aN);//*  06/05 7:26 pm
 O = new G4Element("Oxygen", "O", 8, aO); //*  06/05 7:26 pm

//*  06/05 7:30 pm
//lo siguiente es una funcion que modela la atmosfera (la densidad)
 G4double f = 3;  //degrees of freedom 
 G4double R = 8.3144626181532; //gas constant
 G4double g0 = 9.81; //gravitation
 G4double kappa = (f+2)/f; // some definition on thermodynamics
 G4double T = 293.15;  //temp on ground level
 G4double M = (0.3*aO + 0.7*aN)/1000; //average mole mass
 
 // + 06/05 10.44 pm
 for(G4int i = 0; i < 5; i++)
 {
  std::stringstream stri; //this method change the integrer i into a string
  stri <<i;
  G4double h = 5/5.*i;//the high of every layer
  G4double density = density0*pow((1-(kappa)/kappa*M*g0*h/(R*T)),(1/(kappa-1)));
  Air[i]= new G4Material("G4_AIR_"+stri.str(), density, 2); //method of define material
  Air[i]->AddElement(N, 70*perCent);
  Air[i]->AddElement(O, 30*perCent);
 }
//###########################################################################

 propworld->AddProperty("RINDEX",energy, rindexWorld,numberOfEntries);
 prop->AddProperty("RINDEX",energy, RI,numberOfEntries);
 prop->AddProperty("SCINTILLATIONCOMPONENT1",energy,fraction,numberOfEntries);//como el FASTCOMPONENT
 prop->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 1.8*ns);
 prop->AddConstProperty("SCINTILLATIONRISETIME1", 0.7*ns); //decay time of the scintillator
 prop->AddConstProperty("SCINTILLATIONYIELD", 10./keV);//amount of photons per (in this case) KeV
 prop->AddConstProperty("RESOLUTIONSCALE", 1.);
 prop->AddProperty("ABSLENGTH",energy,absSC,numberOfEntries);///lo solucioné sólo poniendolo en un ciclo, no en ambos
 mirror->AddProperty("REFLECTIVITY", energy, reflectivity);
 propmylar->AddProperty("RINDEX",energy, rindexmylar,numberOfEntries);

 worldMaterial->SetMaterialPropertiesTable(propworld);
 plastic->SetMaterialPropertiesTable(prop);
 mirrorsurface->SetMaterialPropertiesTable(mirror);
 mylarMaterial->SetMaterialPropertiesTable(propmylar);
//las propiedades que se usan en addproperties son para cada elemento de los vectores definidos.
}




void myDetectorConstruction::ConstructProtoDetector()
{ //*  06/05 6:49 pm
   //############################ BARRA ###########################

  G4double bar_X = 5*cm;
  G4double bar_Y = 1*cm;
  G4double bar_Z = 100*cm;
  
  Solidbar = new G4Box("Solidbar", bar_X, bar_Y, bar_Z );
  Logicbar = new G4LogicalVolume(Solidbar, plastic, "Logicbar");
  Physicalbar = new G4PVPlacement(0, G4ThreeVector(), Logicbar, "Physicalbar", LogicWorld, false, 0, true);


//############################ DETECTOR ###########################

  G4double sipm_X = 0.6*cm;
  G4double sipm_Y = 0.6*cm;
  G4double sipm_Z = 0.01*cm;
  //position vector for sipm
  G4ThreeVector possipm = G4ThreeVector(0, 0, 100.0051*cm);
  
  Solidsipm = new G4Box("Solidsipm", sipm_X, sipm_Y, sipm_Z );
  Logicsipm = new G4LogicalVolume(Solidsipm, worldMaterial, "Logicsipm");

  fScoringVolume = Logicsipm;

  Physicalsipm = new G4PVPlacement(0, possipm, Logicsipm, "Physicalsipm", LogicWorld, false, 0, true);

 

//############################# MYLAR ###############################
 G4double mylar_x = 5.001*cm;
 G4double mylar_y = 1.001*cm;
 G4double mylar_z = 100.0011*cm;

 Solidmylar = new G4Box("Solidmylar", mylar_x, mylar_y, mylar_z);
 Logicmylar = new G4LogicalVolume(Solidmylar,mylarMaterial,"Logicmylar");
 G4LogicalSkinSurface *skin= new G4LogicalSkinSurface("skin", Logicmylar, mirrorsurface); //<--- 24/05 2 pm (estaba en la barra. Aqui ya está correcto)
 Physicalmylar = new G4PVPlacement(0,G4ThreeVector(),Logicmylar,"Physicalmylar",LogicWorld,false,0,true);
 

 //####################################################################

}


void myDetectorConstruction::ConstructAtmosphere() //* 06/05 11:26 pm
{
  SolidAtmos = new G4Box("SolidAtmos", env_sizeX/5., env_sizeY/5., env_sizeZ/5.);

  for (G4int i = 0; i<5; i++)
  {
    LogicAtmos[i] = new G4LogicalVolume(SolidAtmos,Air[i] ,"LogicAtmos" );

    PhysicalAtmos[i] = new G4PVPlacement(0, G4ThreeVector(0,0,env_sizeZ/5.*2*i - env_sizeZ + env_sizeZ/5.), LogicAtmos[i], "PhysicalAtmos", LogicWorld, i, true);
  }
}

//all the important information to Construct() to construct the detector
G4VPhysicalVolume *myDetectorConstruction::Construct()
{
  

  //world
  SolidWorld = new G4Box("SolidWorld", env_sizeX, env_sizeY, env_sizeZ);
  
  //logical
  //primer parametro es el solid world, el siguiente el material y el ultimo el nombre del logical
  LogicWorld = new G4LogicalVolume(SolidWorld, worldMaterial, "LogicWorld");

  //Physical
  //parametros: rotation, origen (0,0,0), el logical volume, su nombre, si va a estar dentro de otro volumen, copias, check overlaps
  PhysicalWorld = new G4PVPlacement(0, G4ThreeVector(), LogicWorld, "PhysicalWorld", 0, false, 0, true);

  if(ProtoDetector) //*  06/05 7:06 pm
   ConstructProtoDetector();

  if(Atmospheric) //*  06/05 7:06 pm
   ConstructAtmosphere();
 
  //the mother volume always needs this return
  return PhysicalWorld; 
}


void myDetectorConstruction::ConstructSDandField()
{
 SensitiveDetector *sensDet = new SensitiveDetector("SensitiveDetector");
 //if(ProtoDetector)  //*  06/05 7:06 pm
 Logicsipm->SetSensitiveDetector(sensDet);
}
