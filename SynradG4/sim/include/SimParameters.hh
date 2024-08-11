#ifndef SimParameters_h
#define SimParameters_h

#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

#include <vector>

using namespace std;

class SimParameters
{
public: 
	SimParameters();
	~SimParameters();
private:
	G4int _reflType;
	G4bool _reflPrint;
	G4double _sigmaRatio;
        G4double _surfaceRoughness;
	G4double _autoCorrLength;
public:
	// print functions
	void InitDefault();	
	void PrintSRprocParameters();
	void ReadXML(G4String fName);

	// get functions
	G4int GetReflType(){return _reflType;}
	G4bool GetReflPrint(){return _reflPrint;}
	G4double GetSigmaRatio(){return _sigmaRatio;}
	G4double GetSurfRoughness(){return _surfaceRoughness;}
	G4double GetAutoCorrLength(){return _autoCorrLength;}

private:
	// set functions
	void SetReflType(G4int val){_reflType = val; return;}
	void SetReflPrint(G4int val){if(val == 1){_reflPrint=true;}else{_reflPrint=false;}return;}
	void SetSigmaRatio(G4double val){_sigmaRatio = val; return;}
	void SetSurfRoughness(G4double val){_surfaceRoughness = val; return;}
	void SetAutoCorrLength(G4double val){_autoCorrLength = val; return;}

	G4bool FileExists(const G4String& fName);
};

#endif
