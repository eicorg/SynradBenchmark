#ifndef RunAction_h
#define RunAction_h 1

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#include "TROOT.h"
#include "TTree.h"
#include "TFile.h"
#include "TBranch.h"
#include "TH1.h"
#pragma GCC diagnostic pop

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4PhysicalConstants.hh"
#include "G4Timer.hh"
#include "RunMessenger.hh"
#include "G4Run.hh"

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <utility> // pair
#include <stdexcept> // runtime_error
#include <sstream> // stringstream
#include <stdio.h>

using namespace std;

class G4Run;
class RunMessenger;

class RunAction: public G4UserRunAction
{
public:
	RunAction(G4String,G4long);
    	~RunAction();

    	void BeginOfRunAction(const G4Run*);
    	void EndOfRunAction(const G4Run*);

    	G4String GetOutputFileName() { return _output_filename;}

    	void SetOutputFileName(G4String name){_output_filename = name;}

	TFile* _hfile;
    	TTree* _tree;
    	TTree* _xml;

    	G4int _event;
	G4long _seed;

	vector<G4int> _beamPdg;
	vector<G4float> _beamPosX;
	vector<G4float> _beamPosY;
	vector<G4float> _beamPosZ;
	vector<G4float> _beamMomX;
	vector<G4float> _beamMomY;
	vector<G4float> _beamMomZ;
	vector<G4float> _beamEnergy;
	vector<G4float> _beamKillPosX;
	vector<G4float> _beamKillPosY;
	vector<G4float> _beamKillPosZ;

	vector<G4float> _gammaVtxPosX;
	vector<G4float> _gammaVtxPosY;
	vector<G4float> _gammaVtxPosZ;
	vector<G4float> _gammaVtxDirX;
	vector<G4float> _gammaVtxDirY;
	vector<G4float> _gammaVtxDirZ;

	vector<string> _gammaPostPV;
	vector<string> _gammaPrePV;
	vector<G4float> _gammaPosX;
	vector<G4float> _gammaPosY;
	vector<G4float> _gammaPosZ;
	vector<G4float> _gammaMomX;
	vector<G4float> _gammaMomY;
	vector<G4float> _gammaMomZ;
	vector<G4float> _gammaEnergy;
	vector<G4float> _gammaTime;

	G4double _avgEventTime;

	string _settings;

private:
    	G4Timer* timer;
    	G4String _output_filename;
	G4String _xml_filename;
    	RunMessenger* fRunMessenger;
	void DumpXmlFile();
};

#endif
