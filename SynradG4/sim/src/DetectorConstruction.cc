#include "DetectorConstruction.hh"

using namespace std;

DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction()
{
	visibility = true;
	mat_vac = nullptr;
	world_phys = nullptr;
	world_log = nullptr;
	mass = -1;
	gamma = -1;
}

DetectorConstruction::~DetectorConstruction()
{}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
	BuildMaterials();
	BuildWorld();
	CreateBeamPipeSolid();

	return world_phys;
}

void DetectorConstruction::BuildMaterials()
{
	G4NistManager* nistManager = G4NistManager::Instance();
	//- Vacuum
	mat_vac = nistManager->FindOrBuildMaterial("G4_Galactic");

	return;	
}

void DetectorConstruction::BuildWorld()
{
	if(!mat_vac)
	{
		throw runtime_error(
		"[ERROR] DetectorConstruction::BuildWorld ==> Materials are not created\n");
	}

   	G4VSolid* world_box = new G4Box("world",2*m,2*m,100*m);
    	world_log = new G4LogicalVolume(world_box,mat_vac,"world");
    	world_phys = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.),world_log,"world",0,false,0,true);
	//- Visualization
	world_log->SetVisAttributes(G4VisAttributes::GetInvisible());

	return;
}

void DetectorConstruction::CreateBeamPipeSolid()
{
	if(!mat_vac)
	{
		throw runtime_error(
		"[ERROR] DetectorConstruction::CreateBeamPipeSolid ==> Materials are not created\n");
	}

	G4double D1_L = 5*m; // Drift 1
	G4double B1_L = 5*m; // Dipole
	G4double B1_A = 0.010*rad; // Bending angle of the dipole
	G4double D2_L = 40*m; // Drift 2
	G4double B1_R = (B1_L/2.)/sin(B1_A/2.); // Dipole radius
	G4double B1_S = B1_R * B1_A; // Dipole orbit length

	//====================================//
	//============== DRIFTS ==============//
	//====================================//
	G4Box* drift1_box = new G4Box("drift1_box",50*mm/2.,50*mm/2.,D1_L/2.);
	G4VSolid* drift2_box = new G4Box("drift2_box",50*mm/2.,50*mm/2.,10*m/2.);
	G4Trd* drift2_trd1 = new G4Trd("drift2_trd1",50*mm/2.,40*mm/2.,50*mm/2.,40*mm/2.,5*m/2.);
	G4Box* drift2_box2 = new G4Box("drift2_box2",40*mm/2.,40*mm/2.,5*m/2.);
	G4Trd* drift2_trd3 = new G4Trd("drift2_trd3",40*mm/2.,20*mm/2.,40*mm/2.,20*mm/2.,5*m/2.);
	G4Box* drift2_box4 = new G4Box("drift2_box4",20*mm/2.,20*mm/2.,15*m/2.);

	drift2_box = new G4UnionSolid("drift2_uni",
		drift2_box,drift2_trd1,0,G4ThreeVector(0,0,10*m/2.+5*m/2.));
	drift2_box = new G4UnionSolid("drift2_uni",
		drift2_box,drift2_box2,0,G4ThreeVector(0,0,10*m/2.+5*m+5*m/2.));
	drift2_box = new G4UnionSolid("drift2_uni",
		drift2_box,drift2_trd3,0,G4ThreeVector(0,0,10*m/2.+5*m+5*m+5*m/2.));
	drift2_box = new G4UnionSolid("drift2_uni",
		drift2_box,drift2_box4,0,G4ThreeVector(0,0,10*m/2.+5*m+5*m+5*m+15*m/2.));

	G4RotationMatrix* drift2_rot = new G4RotationMatrix();
	drift2_rot->rotateY(B1_A);

	G4VSolid* beampipeVac_solid = new G4UnionSolid("beampipeVac_solid",
		drift1_box,drift2_box,drift2_rot,G4ThreeVector(
				0-(B1_L)*sin(B1_A/2.)-(10*m/2.)*sin(B1_A),
				0,
				D1_L/2+(B1_L)*cos(B1_A/2.)+(10*m/2.)*cos(B1_A)));
	//- Vacuum (place the beam pipe without magnet and IP volumes) 
	G4LogicalVolume* beampipeVac_log = new G4LogicalVolume(beampipeVac_solid, mat_vac,"beampipeVac");
	// set tracking time limit in the volume
	new G4PVPlacement(0,G4ThreeVector(0,0,D1_L/2.),
		beampipeVac_log,"vac_beampipe",world_log,false,0,true);
	//- Visualization
	G4VisAttributes* beampipeVac_vis = new G4VisAttributes(G4Color::White());
	beampipeVac_vis->SetVisibility(visibility);
	beampipeVac_log->SetVisAttributes(beampipeVac_vis);

	//=======================================//
	//============== ABSORBERs ==============//
	//=======================================//

	G4Box* abs_box = new G4Box("abs_box",1*m/2,1*m/2,5*cm/2);

	//- Subtract vacuum beam pipe
	G4VSolid* abs_solid_0 = new G4SubtractionSolid("abs_solid_0",
		abs_box,beampipeVac_solid,0,G4ThreeVector(0,0,D1_L/2.));
	G4VSolid* abs_solid_1 = new G4SubtractionSolid("abs_solid_1",
		abs_box,beampipeVac_solid,0,G4ThreeVector(+0.4*m,0,D1_L/2.-50*m));

	G4LogicalVolume* abs_log_0 = new G4LogicalVolume(abs_solid_0,mat_vac, "abs_log_0");
	G4LogicalVolume* abs_log_1 = new G4LogicalVolume(abs_solid_1,mat_vac, "abs_log_1");
	new G4PVPlacement(0,G4ThreeVector(0,0,0),abs_log_0,"abs_0",world_log,false,0,true);
	new G4PVPlacement(0,G4ThreeVector(-0.4*m,0,50*m),abs_log_1,"abs_1",world_log,false,0,true);

	//- Visualization
	G4VisAttributes* abs_vis = new G4VisAttributes(G4Color::Magenta());
	abs_log_0->SetVisAttributes(abs_vis);
	abs_log_1->SetVisAttributes(abs_vis);

	//====================================//
	//============== DIPOLE ==============//
	//====================================//
	G4Tubs* dipole_tube = new G4Tubs("dipole_tube",B1_R-50*mm/2.,B1_R+50*mm/2.,50*mm/2.,0,B1_A);

	// magnet logic volume
	G4LogicalVolume* dipole_log = new G4LogicalVolume(dipole_tube,mat_vac,"dipole_log");
	// set tracking time limit in the volume

	//- Create magnetic field
	// Particles
	BuildParticles();

	// By[T]*rho[m] = 3.33564*pc[GeV]
	// rho[m] = l[m]/(2*sin(theta[rad]/2)) (RBEND)
	// pc = mc^2*sqrt(gamma^2 - 1)
	G4double By = ((3.33564*(mass/GeV)*sqrt(pow(gamma,2)-1.0))/
		((B1_L/m)/(2.*sin(B1_A/2.))))*tesla;
	G4MagneticField* dipole_field = new G4UniformMagField(G4ThreeVector(0,-By,0));

	// apply the field to logic volume
	G4FieldManager* localFieldMgr = new G4FieldManager(dipole_field);
	localFieldMgr->SetDetectorField(dipole_field);
	localFieldMgr->CreateChordFinder(dipole_field);
	dipole_log->SetFieldManager(localFieldMgr, true);

	// Place the dipole
	G4RotationMatrix* dipole_rot = new G4RotationMatrix();
	dipole_rot->rotateX(-M_PI/2.);
	new G4PVPlacement(dipole_rot,G4ThreeVector(-B1_R,0,D1_L),
		dipole_log,"mag_dipole",world_log,false,0,true);

	//- Visualization
	G4VisAttributes* dipole_vis = new G4VisAttributes(G4Color::Red());
	dipole_log->SetVisAttributes(dipole_vis);
	//====================================//
	//====================================//
	//====================================//

	return;
}

void DetectorConstruction::BuildParticles()
{
        G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
        G4ParticleDefinition* particleDef;
        particleDef = particleTable->FindParticle("e-");
        mass = particleDef->GetPDGMass();
        gamma = 35225.121;

	return;
}
