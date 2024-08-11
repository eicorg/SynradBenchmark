#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#include "TROOT.h"
#include "TGraph.h"
#pragma GCC diagnostic pop

#include "G4VUserDetectorConstruction.hh"
#include "G4Material.hh"
#include "G4VSolid.hh"
#include "G4RotationMatrix.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4Trd.hh"
#include "G4EllipticalTube.hh"
#include "G4Polycone.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "G4PhysicalConstants.hh"
#include "G4RunManager.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "G4MagneticField.hh"
#include "G4FieldManager.hh"
#include "G4UniformMagField.hh"
#include "G4QuadrupoleMagField.hh"
#include "G4UserLimits.hh"
#include "G4ChordFinder.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4IntersectionSolid.hh"
#include "G4Torus.hh"
#include "G4EllipticalCone.hh"
#include "G4EllipticalTube.hh"
#include "G4ExtrudedSolid.hh"

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    	DetectorConstruction();
    	~DetectorConstruction();

    	G4VPhysicalVolume* Construct();

private:

	G4bool visibility; // components visibility
	G4Material* mat_vac; // vacuum material
	G4VPhysicalVolume* world_phys; // world PV
	G4LogicalVolume* world_log; // world LV

	G4double mass;
	G4double gamma;

	void BuildMaterials();
	void BuildWorld();
	void CreateBeamPipeSolid();
	void BuildParticles();
};

#endif

