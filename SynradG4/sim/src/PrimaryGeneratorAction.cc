#include "PrimaryGeneratorAction.hh"

// Beam tail function 
// Ref.[Christoph Montag, "Transverse Beam Tails and Beam Lifetime in the EIC Electron Storage Ring" (July 1, 2021)]
Double_t getBeamTailDistribution(Double_t *x, Double_t *par){return ( par[0]/pow(x[0],3) );}

PrimaryGeneratorAction::PrimaryGeneratorAction(RunAction* runAct, G4String xmlFileName) : runAction(runAct)
{
    	fParticleGun = new G4ParticleGun(1);
	simPar = new SimParameters();
	simPar->InitDefault();
	simPar->ReadXML(xmlFileName);
	simPar->PrintGenerator();

	if(simPar->GetGenerator() == "Beam")
	{
		if(simPar->GetBeamType() == "tail")
		{
			fBeamTailX = new TF1("fBeamTailX",getBeamTailDistribution,
				simPar->GetBeamTailMin(),simPar->GetBeamTailMax(),1);
			fBeamTailY = new TF1("fBeamTailY",getBeamTailDistribution,
				simPar->GetBeamTailMin(),simPar->GetBeamTailMax(),1);
			fBeamTailX->SetParameter(0,simPar->GetBeamTailKx());
			fBeamTailY->SetParameter(0,simPar->GetBeamTailKy());
		}
	}
	else if(simPar->GetGenerator() == "HepMC")
	{
		fHepMcAsciiInput = new HepMC3::ReaderAscii(simPar->GetHepMcFileName());
	}
	else
	{
		throw runtime_error(
			"[ERROR] PrimaryGeneratorAction::PrimaryGeneratorAction ==> Wrong particle generator name\n");
	}
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
	if(simPar->GetGenerator() == "HepMC")
	{
		fHepMcAsciiInput->close();
		delete fHepMcAsciiInput;
	}
    	delete fParticleGun;
	delete simPar;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	if(simPar->GetGenerator() == "Beam")
	{
		GenerateBeamPrimaries(anEvent);
	}
	else if(simPar->GetGenerator() == "HepMC")
	{
		GenerateHepMcPrimaries(anEvent);
	}
	else
	{
		throw runtime_error(
			"[ERROR] PrimaryGeneratorAction::PrimaryGeneratorAction ==> Wrong particle generator name\n");
	}

	return;
}

void PrimaryGeneratorAction::StorePrimaryCoordinates(
	const G4Event* anEvent, const G4ThreeVector magVector, 
	const G4double angle, const G4double Q2, const G4double x)
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
			runAction->_beamRefPosX.push_back(magVector.x()/cm);
			runAction->_beamRefPosY.push_back(magVector.y()/cm);
			runAction->_beamRefPosZ.push_back(magVector.z()/cm);
			runAction->_beamRefAngle.push_back(angle/rad);
			runAction->_beamTransfMomSqr.push_back(Q2/GeV/GeV);
			runAction->_beamBjorkenX.push_back(x);
		}
	}

	return;
}

void PrimaryGeneratorAction::GenerateHepMcPrimaries(G4Event* g4event)
{
	// [https://gitlab.cern.ch/hepmc/HepMC3/-/tree/master/include/HepMC3?ref_type=heads]
	// [https://pythia.org/latest-manual/ParticleProperties.html]
	// [https://twiki.cern.ch/twiki/bin/view/Main/MC_status_code]

    	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    	G4ParticleDefinition* particleDef;
    	particleDef = particleTable->FindParticle(simPar->GetBeamName().c_str());
	G4PrimaryParticle* g4prim;
	G4PrimaryVertex* g4vtx;
	G4double Q2 = 0, E_i = 0, E_f = 0, targetMass = 0, E_2 = 0;
	G4LorentzVector q, p2;

	// Construct an event
	HepMC3::GenEvent hepmcevt(HepMC3::Units::GEV,HepMC3::Units::MM);
	// Check if there are available events
	if(fHepMcAsciiInput->failed())
		G4RunManager::GetRunManager()->AbortRun();
	// Read event from input file
	fHepMcAsciiInput->read_event(hepmcevt);
	// Print the first event info
	if(g4event->GetEventID() == 0)
	{
		HepMC3::Print::listing(hepmcevt);
		HepMC3::Print::content(hepmcevt);
	}

	bool gotParticles = false;
	// Loop over vertices
	for (const auto& vertex : hepmcevt.vertices())
	{
		// Loop over outcoming particles
		// Only for a real vertex (i.e., stable particle or the one which will decay later)
		for(const auto& particle : vertex->particles_out()) 
		{
			// Select only electrons
			if (!particle->end_vertex() && particle->status() == 1 && particle->pid() == 11) 
			{
				// Select the particle from the beam only (find a grandparent)
				bool fromBeam = false;
				HepMC3::FourVector momBeam;
				G4double massBeam;
				for(const auto& parent : particle->parents())
					for(const auto& grandparent : parent->parents()) 
						if(grandparent->status() == 4 && grandparent->pid() == 11) 
						{
							momBeam = grandparent->momentum();
							massBeam = grandparent->generated_mass();
							fromBeam = true;
						}
				if(!fromBeam){continue;}

				// Check world boundary
				HepMC3::FourVector pos = vertex->position();
				G4LorentzVector xvtx(pos.x(), pos.y(), pos.z(), pos.t());
				if (! CheckVertexInsideWorld(xvtx.vect() * mm)) continue;

				// Create G4PrimaryVertex and associated G4PrimaryParticles
				g4vtx = new G4PrimaryVertex(
					xvtx.x()*mm, xvtx.y()*mm, xvtx.z()*mm,xvtx.t()*mm/c_light);

				G4int pdgcode = particle->pid();
				HepMC3::FourVector mom = particle->momentum();
				// Note the possible loss of precision in the calculation of E^2 - p^2;
				// for particles the correct mass is stored separately to avoid such problems.
				// [https://pythia.org/latest-manual/Welcome.html]
				G4double mass = particle->generated_mass();
				E_f = sqrt(
						pow(mom.x(),2) +
						pow(mom.y(),2) + 
						pow(mom.z(),2) + 
						pow(mass,2));
				E_i = sqrt(	pow(momBeam.x(),2) + 
						pow(momBeam.y(),2) + 
						pow(momBeam.z(),2) + 
						pow(massBeam,2));
				G4LorentzVector k_f(mom.px(), mom.py(), mom.pz(), E_f);
				G4LorentzVector k_i(momBeam.px(), momBeam.py(), momBeam.pz(), E_i);
				q = k_i - k_f;
				Q2 = -q.m2();

				g4prim = new G4PrimaryParticle(pdgcode, k_f.x()*GeV, k_f.y()*GeV, k_f.z()*GeV);
				g4vtx->SetPrimary(g4prim);

				gotParticles = true;
      			}
			// we need only one scattered electron, skip the rest of particles
			if(gotParticles){break;}
    		}
                // Loop over incoming particles
                // Only for a real vertex (i.e., stable particle or the one which will decay later)
                for(const auto& particle : vertex->particles_in()) 
                {
                        // Select only the beam proton
                        if (particle->status() == 4 && particle->pid() == 2212)
                        {
				targetMass = particle->generated_mass();
				HepMC3::FourVector targetMom = particle->momentum();
				E_2 = sqrt(     pow(targetMom.x(),2) +
						pow(targetMom.y(),2) +
						pow(targetMom.z(),2) +
						pow(targetMass,2));

				p2 = G4LorentzVector(targetMom.px(), targetMom.py(), targetMom.pz(), E_2);
				break;
			}
                }
		// we need only one scattered electron, skip the rest of vertices
		if(gotParticles){break;}
	}

	// generate the primary beam 
    	fParticleGun->SetParticleDefinition(particleDef);
    	fParticleGun->SetParticleEnergy(g4prim->GetKineticEnergy());
    	fParticleGun->SetParticleMomentumDirection(g4prim->GetMomentumDirection());
    	fParticleGun->SetParticlePosition(g4vtx->GetPosition());

    	fParticleGun->GeneratePrimaryVertex(g4event);

	// Store Coordinates
	StorePrimaryCoordinates(g4event,G4ThreeVector(0,0,0),0,Q2*GeV*GeV,Q2/(2.*p2*q));

	return;
}

G4bool PrimaryGeneratorAction::CheckVertexInsideWorld(const G4ThreeVector& pos) const
{
	G4Navigator* navigator = G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking();
	G4VPhysicalVolume* world = navigator->GetWorldVolume();
	G4VSolid* solid = world->GetLogicalVolume()->GetSolid();
	EInside qinside = solid->Inside(pos);

	if( qinside != kInside) return false;
	else return true;
}

void PrimaryGeneratorAction::GenerateBeamPrimaries(G4Event* anEvent)
{
    	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    	G4ParticleDefinition* particleDef;
    	particleDef = particleTable->FindParticle(simPar->GetBeamName().c_str());

	G4double mass = particleDef->GetPDGMass();
	G4double gamma = simPar->GetBeamGamma();
	G4double Mom = sqrt(pow(gamma,2) - 1.0)*mass;
	G4double Ekin = sqrt(pow(Mom,2) + pow(mass,2)) - mass;

	// generate the primary beam 
    	fParticleGun->SetParticleDefinition(particleDef);
    	fParticleGun->SetParticleEnergy(Ekin);
    	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));
    	fParticleGun->SetParticlePosition(G4ThreeVector(0,0,0));

    	fParticleGun->GeneratePrimaryVertex(anEvent);

	// Store Coordinates
	StorePrimaryCoordinates(anEvent,G4ThreeVector(0,0,0),0,0,0);

	return;
}
