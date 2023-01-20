#include "generator.hh"


//change your particle gun position, energy, direction here.
//this generator function creates one photon per event.

PrimaryGenerator::PrimaryGenerator()

{
	fParticleGun= new G4ParticleGun(1000);
}
PrimaryGenerator::~PrimaryGenerator()
{
	delete fParticleGun;
}

void PrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{

	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName = "opticalphoton";
	G4ParticleDefinition *particle = particleTable->FindParticle("opticalphoton");

	G4ThreeVector pos(0.,0.,-0.5*m); //change photon generating position later.
	G4ThreeVector mom(0.,0.,1.); //direction of momentum

	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(mom);
	fParticleGun->SetParticleMomentum(3.*eV); //change photon energy as necessary
	fParticleGun->SetParticleDefinition(particle);

	fParticleGun->GeneratePrimaryVertex(anEvent);
}


