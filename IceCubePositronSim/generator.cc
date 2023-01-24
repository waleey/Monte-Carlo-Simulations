#include "generator.hh"
#include <iostream>
#include <random>
#include <cmath>

//uniform random number generator

G4double randomGen(G4double minLim, G4double maxLim){

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(minLim, maxLim);

    return dis(gen);
}
//change your particle gun position, energy, direction here.
//this generator function creates one photon per event.

PrimaryGenerator::PrimaryGenerator()

{
	fParticleGun= new G4ParticleGun(1);
}
PrimaryGenerator::~PrimaryGenerator()
{
	delete fParticleGun;
}

void PrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{

    G4int numParticles = 1000;

	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName = "e+";
	G4ParticleDefinition *particle = particleTable->FindParticle("e+");

	/*G4ThreeVector pos(0.,0.,-0.5*m); //change photon generating position later.
	G4ThreeVector mom(0.,0.,1.); //direction of momentum

	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(mom);
	fParticleGun->SetParticleMomentum(3.*MeV); //change photon energy as necessary
	fParticleGun->SetParticleDefinition(particle);

	fParticleGun->GeneratePrimaryVertex(anEvent);*/



	//new experiment


	/*G4ParticleTable *particleTable2 = G4ParticleTable::GetParticleTable();
	G4String particleName2 = "opticalphoton2";
	G4ParticleDefinition *particle2 = particleTable->FindParticle("opticalphoton");

	G4ThreeVector pos2(0.,0.,0.*m); //change photon generating position later.
	G4ThreeVector mom2(0.,1.,0.); //direction of momentum

	fParticleGun->SetParticlePosition(pos2);
	fParticleGun->SetParticleMomentumDirection(mom2);
	fParticleGun->SetParticleMomentum(3.*MeV); //change photon energy as necessary
	fParticleGun->SetParticleDefinition(particle2);

	fParticleGun->GeneratePrimaryVertex(anEvent);*/

	for(G4int i =0; i<numParticles; i++){

	G4double positionRandom[3] = {randomGen(-0.5,0.5),randomGen(-0.5,0.5),randomGen(-0.5,0.5)};
	G4double orientationRandom[3] = {randomGen(-1,1),randomGen(-1,1),randomGen(-1,1)};
	G4double mode = std::sqrt(std::pow(orientationRandom[0],2)+std::pow(orientationRandom[1],2)+std::pow(orientationRandom[2],2));
    G4double orientDirection[3] = {orientationRandom[0]/mode,orientationRandom[1]/mode,orientationRandom[2]/mode}; //just divided the orientationRandom by it's value to normalize it to 1 since it's a unit vector.

    G4ThreeVector pos(positionRandom[0]*m,positionRandom[1]*m,positionRandom[2]*m); //change photon generating position later.
	G4ThreeVector mom(orientDirection[0],orientDirection[1],orientDirection[2]); //direction of momentum

	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(mom);
	fParticleGun->SetParticleEnergy(3.*MeV); //change photon energy as necessary
	fParticleGun->SetParticleDefinition(particle);

	fParticleGun->GeneratePrimaryVertex(anEvent);


	}

}


