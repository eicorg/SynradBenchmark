#include "SteppingAction.hh"

SteppingAction::SteppingAction(RunAction* runAct) : runAction(runAct)
{}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step *step)
{
	G4Track* track = step->GetTrack();

	G4StepPoint*            preStep         = step->GetPreStepPoint();
	G4StepPoint*            postStep        = step->GetPostStepPoint();
	G4VPhysicalVolume*      prePV           = preStep->GetPhysicalVolume();
	G4VPhysicalVolume*      postPV          = postStep->GetPhysicalVolume();

	// the monitor is associated with one of the magnets
	G4String mon_name = prePV->GetName();

	//--------------------------------------------------------------------------//
	//- Kill primaries leaving the vacuum
	if(	track->GetTrackID() == 1 && // primary particle
		postStep->GetStepStatus() == fGeomBoundary && // at boundary
		postPV->GetName() == "world") // entering world
	{
		runAction->_beamKillPosX.push_back(postStep->GetPosition().getX()/cm);
		runAction->_beamKillPosY.push_back(postStep->GetPosition().getY()/cm);
		runAction->_beamKillPosZ.push_back(postStep->GetPosition().getZ()/cm);

		track->SetTrackStatus(fStopAndKill); 
		return;
	}
	//--------------------------------------------------------------------------//
	//-- Store killed photon info
	// check if the track (=gamma) is killed
	if(/*postPV && */track->GetTrackStatus() == fStopAndKill && 
		track->GetParticleDefinition()->GetPDGEncoding() == G4Gamma::Gamma()->GetPDGEncoding())
	{	
		if(!postPV)
		{
			G4cout<<"\n\n=================================================================="<<G4endl;
			G4cout<<"[WARNING] SteppingAction::UserSteppingAction"<<G4endl;
			G4cout<<" No postStep volume is assigned. Please check your geometry."<<G4endl;
			G4cout<<" All vacuum volumes where SR should propagate must have the 'vac_' prefix."<<G4endl;
			G4cout<<" The SR photon is skipped!"<<G4endl;
			G4cout<<"==================================================================\n"<<G4endl;
			return;
		}

		runAction->_gammaVtxPosX.push_back(track->GetVertexPosition().getX()/cm);
		runAction->_gammaVtxPosY.push_back(track->GetVertexPosition().getY()/cm);
		runAction->_gammaVtxPosZ.push_back(track->GetVertexPosition().getZ()/cm);
		runAction->_gammaVtxDirX.push_back(track->GetVertexMomentumDirection().getX());
		runAction->_gammaVtxDirY.push_back(track->GetVertexMomentumDirection().getY());
		runAction->_gammaVtxDirZ.push_back(track->GetVertexMomentumDirection().getZ());

		runAction->_gammaPostPV.push_back(postStep->GetPhysicalVolume()->GetName());
		runAction->_gammaPrePV.push_back(preStep->GetPhysicalVolume()->GetName());
		runAction->_gammaPosX.push_back(postStep->GetPosition().getX()/cm);
		runAction->_gammaPosY.push_back(postStep->GetPosition().getY()/cm);
		runAction->_gammaPosZ.push_back(postStep->GetPosition().getZ()/cm);
		runAction->_gammaMomX.push_back(postStep->GetMomentum().getX()/eV);
		runAction->_gammaMomY.push_back(postStep->GetMomentum().getY()/eV);
		runAction->_gammaMomZ.push_back(postStep->GetMomentum().getZ()/eV);
		runAction->_gammaEnergy.push_back(track->GetTotalEnergy()/eV);
		runAction->_gammaTime.push_back(track->GetGlobalTime()/ms); // time from the start of the event
	}

	return;
}
