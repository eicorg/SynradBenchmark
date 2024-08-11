#include "EventAction.hh"
#include "RunAction.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"

EventAction::EventAction(RunAction* runAct) : runAction(runAct)
{
	_timer = new G4Timer;
}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event* event)
{
	_timer->Start();
    	runAction->_event = event->GetEventID();

    	if((runAction->_event)%1000 == 0)
        	printf("[INFO] EventAction::BeginOfEventAction ==> BeginOfEvent: %12d\n",runAction->_event);

	return;
}

void EventAction::EndOfEventAction(const G4Event*)
{
    	runAction->_tree->Fill();

	// clean variables
	runAction->_beamPdg.clear();
	runAction->_beamPosX.clear();
	runAction->_beamPosY.clear();
	runAction->_beamPosZ.clear();
	runAction->_beamMomX.clear();
	runAction->_beamMomY.clear();
	runAction->_beamMomZ.clear();
	runAction->_beamEnergy.clear();
	runAction->_beamKillPosX.clear();
	runAction->_beamKillPosY.clear();
	runAction->_beamKillPosZ.clear();

	runAction->_gammaVtxPosX.clear();
	runAction->_gammaVtxPosY.clear();
	runAction->_gammaVtxPosZ.clear();
	runAction->_gammaVtxDirX.clear();
	runAction->_gammaVtxDirY.clear();
	runAction->_gammaVtxDirZ.clear();

	runAction->_gammaPostPV.clear();
	runAction->_gammaPrePV.clear();
	runAction->_gammaPosX.clear();
	runAction->_gammaPosY.clear();
	runAction->_gammaPosZ.clear();
	runAction->_gammaMomX.clear();
	runAction->_gammaMomY.clear();
	runAction->_gammaMomZ.clear();
	runAction->_gammaEnergy.clear();
	runAction->_gammaTime.clear();

    	_timer->Stop();
	// 'real' is wall clock time - time from start to finish of the call. This is all elapsed time 
	// including time slices used by other processes and time the process spends blocked (for example 
	// if it is waiting for I/O to complete).
	runAction->_avgEventTime += _timer->GetRealElapsed();

	return;
}
