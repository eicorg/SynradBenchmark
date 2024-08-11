#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include "RunAction.hh"
#include "G4Gamma.hh"
#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4VParticleChange.hh"
#include "G4ParticleChange.hh"
#include "G4TransportationManager.hh"
#include "G4Navigator.hh"
#include "G4Transform3D.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4ProcessManager.hh"

class G4LogicalVolume;
class RunAction;

class SteppingAction : public G4UserSteppingAction
{
public:
    	SteppingAction(RunAction*);
    	virtual ~SteppingAction();
    	virtual void UserSteppingAction(const G4Step *);

private:
    	RunAction* runAction;
};

#endif
