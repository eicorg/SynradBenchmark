#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"
#include "SimParameters.hh"
#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4RayleighScattering.hh"

#include "G4eMultipleScattering.hh"
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4MuMultipleScattering.hh"
#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

#include "G4hMultipleScattering.hh"
#include "G4hIonisation.hh"
#include "G4hBremsstrahlung.hh"
#include "G4hPairProduction.hh"

#include "G4SynchrotronRadiation.hh"
#include "G4SynchrotronRadiationInMat.hh"

#include "G4StepLimiter.hh"
#include "G4UserSpecialCuts.hh"
#include "G4DecayPhysics.hh"

#include "G4SystemOfUnits.hh"
#include "GammaReflectionProcess.hh"

class G4DecayPhysics;
class SimParameters;

class PhysicsList: public G4VUserPhysicsList
{
public:
  	PhysicsList(G4String);
  	virtual ~PhysicsList();

  	// Construct particles
  	virtual void ConstructParticle();

  	// Construct processes and register them
  	virtual void ConstructProcess();

private:

  	void ConstructEM();

  	G4DecayPhysics* fDecayPhysics;
	SimParameters* simPar;
};

#endif

