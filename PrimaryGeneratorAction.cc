//      PRIMARY GENERATOR ACTION SOURCE FILE

#include "PrimaryGeneratorAction.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
 
 fParticleGun = new G4ParticleGun(1); //argument is particle per event

 G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();

 G4ParticleDefinition *particle = particleTable->FindParticle("mu+"); //muon+. Its number on the Particle Data Group



 G4ThreeVector position(0.,0.01*m,0.);
 G4ThreeVector momentum(0.,-1.,0.);  
 fParticleGun->SetParticlePosition(position);
 fParticleGun->SetParticleMomentumDirection(momentum); //only direction
 //fParticleGun->SetParticleMomentum(1.*GeV); //*
 fParticleGun->SetParticleDefinition(particle);


}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
 delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
 G4double minMomentum = 0.; // estan en MeV Lo cambié de 500 a 1,500 por ordenes del doctor
 G4double maxMomentum = 2; 
 G4double randomNumber = G4UniformRand(); //random number between 0 and 1
 G4double momentumParticle = minMomentum + ( maxMomentum - minMomentum )*randomNumber;

 G4cout << "MOMENTUM FOR THIS EVENT: " << momentumParticle << " GeV" << G4endl;
//                                                                l  lo señalado con "l" cuidado


G4double momentum_onMeV = momentumParticle*1000;
//G4cout << "MOMENTUM FOR THIS EVENT ON MeV: " << momentum_onMeV << " MeV" << G4endl;

 fParticleGun->SetParticleMomentum(momentumParticle*GeV);
 fParticleGun->GeneratePrimaryVertex(anEvent);

G4AnalysisManager *man = G4AnalysisManager::Instance();  

man->FillNtupleDColumn(2,1,momentumParticle);
man->FillNtupleDColumn(2,3,momentum_onMeV);

}
