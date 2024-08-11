#include "StackingAction.hh"

StackingAction::StackingAction()
{
    	_kill_secondaries  = 0;
    	fStackingMessenger = new StackingMessenger(this);
}

StackingAction::~StackingAction()
{
    	delete fStackingMessenger;
}

G4ClassificationOfNewTrack
StackingAction::ClassifyNewTrack(const G4Track* track)
{
    	G4ClassificationOfNewTrack status = fUrgent;
   
	// kill secondaries
    	if(_kill_secondaries == 1 && track->GetTrackID() > 1){status = fKill;}

	// kill gammas
	if(track->GetTotalEnergy() < 30.0*eV){status = fKill;}

    	return status;
}
