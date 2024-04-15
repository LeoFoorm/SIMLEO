#include "PrimaryGeneratorAction.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{

 fParticleGun = new G4ParticleGun(1); //argument is particle per event

}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{

 delete fParticleGun;

}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

//here we define what kind of prticle we want to creat
 G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
 G4String particleName = "opticalphoton"; //maybe its name is "opticalphoton"
 G4ParticleDefinition *particle = particleTable->FindParticle("opticalphoton");

 G4ThreeVector position(0.,0.,0.);
 G4ThreeVector momentum(0.,0.,1.);
 fParticleGun->SetParticlePosition(position);
 fParticleGun->SetParticleMomentumDirection(momentum); //only direction
 fParticleGun->SetParticleMomentum(1.*GeV);
 fParticleGun->SetParticleDefinition(particle);

 fParticleGun->GeneratePrimaryVertex(anEvent);

}
