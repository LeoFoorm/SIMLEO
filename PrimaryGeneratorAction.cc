#include "PrimaryGeneratorAction.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
 
 fParticleGun = new G4ParticleGun(1); //argument is particle per event

 G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();

 G4ParticleDefinition *particle = particleTable->FindParticle(13); //muon+



 G4ThreeVector position(0.,0.1*m,0.);
 G4ThreeVector momentum(0.,-1.,0.);  
 fParticleGun->SetParticlePosition(position);
 fParticleGun->SetParticleMomentumDirection(momentum); //only direction
 //fParticleGun->SetParticleMomentum(1.*GeV); //*
 fParticleGun->SetParticleDefinition(particle);

//man->FillNtupleDColumn(2,0,fEdep);
//man->AddNtupleRow(2); //<------------------------

}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
 delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

 G4double randomNumber = G4UniformRand();
 G4double momentumParticle = std::round(randomNumber * 20) * 0.5 * GeV;

 G4cout << "MOMENTUM FOR THIS EVENT: " << momentumParticle / GeV << " GeV" << G4endl;



 fParticleGun->SetParticleMomentum(momentumParticle);
 fParticleGun->GeneratePrimaryVertex(anEvent);

G4AnalysisManager *man = G4AnalysisManager::Instance();  

man->FillNtupleDColumn(2,1,momentumParticle);
man->AddNtupleRow(2);

}
