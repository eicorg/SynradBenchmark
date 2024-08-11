#include "PrimaryGeneratorAction.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction(RunAction* runAct) : runAction(runAct)
{
    	fParticleGun = new G4ParticleGun(1);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    	delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    	G4ParticleDefinition* particleDef;
    	particleDef = particleTable->FindParticle("e-");

	G4double mass = particleDef->GetPDGMass();
	G4double gamma = 35225.121;
	G4double Mom = sqrt(pow(gamma,2) - 1.0)*mass;
	G4double Ekin = sqrt(pow(Mom,2) + pow(mass,2)) - mass;

	// generate the primary beam 
    	fParticleGun->SetParticleDefinition(particleDef);
    	fParticleGun->SetParticleEnergy(Ekin);
    	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));
    	fParticleGun->SetParticlePosition(G4ThreeVector(0,0,0));

    	fParticleGun->GeneratePrimaryVertex(anEvent);

	// Store Coordinates
	StorePrimaryCoordinates(anEvent);

	return;
}

void PrimaryGeneratorAction::StorePrimaryCoordinates(const G4Event* anEvent) 
{
	// Loop over vertices
	for(G4int ivtx = 0; ivtx < anEvent->GetNumberOfPrimaryVertex(); ivtx++)
	{
		G4PrimaryVertex* vtx = anEvent->GetPrimaryVertex(ivtx);
		// Loop over particles
		for(G4int iptc = 0; iptc < vtx->GetNumberOfParticle(); iptc++)
		{
			G4PrimaryParticle* ptc = vtx->GetPrimary(iptc);

			runAction->_beamPdg.push_back(ptc->GetPDGcode());
			runAction->_beamPosX.push_back(vtx->GetX0()/cm);
			runAction->_beamPosY.push_back(vtx->GetY0()/cm);
			runAction->_beamPosZ.push_back(vtx->GetZ0()/cm);
			runAction->_beamMomX.push_back(ptc->GetPx()/eV);
			runAction->_beamMomY.push_back(ptc->GetPy()/eV);
			runAction->_beamMomZ.push_back(ptc->GetPz()/eV);
			runAction->_beamEnergy.push_back(ptc->GetTotalEnergy()/eV);
		}
	}

	return;
}
