#ifndef AnalysisSR_hh
#define AnalysisSR_hh

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TMath.h>
#include <TVector3.h>

#include "vector"
#include <ctime>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

class AnalysisSR {
public :
  	AnalysisSR();
	virtual ~AnalysisSR();

   	// Declaration of leaf types
	int             event;
	vector<int>     *beamPdg;
	vector<float>   *beamPosX_cm;
	vector<float>   *beamPosY_cm;
	vector<float>   *beamPosZ_cm;
	vector<float>   *beamMomX_eV;
	vector<float>   *beamMomY_eV;
	vector<float>   *beamMomZ_eV;
	vector<float>   *beamEnergy_eV;
	vector<float> 	*beamRefPosX_cm;
	vector<float> 	*beamRefPosY_cm;
	vector<float> 	*beamRefPosZ_cm;
	vector<float> 	*beamRefAngle_rad;

	vector<string>	*magName;
	vector<int>	*magNph;
	vector<float>	*magSumEph_eV;

	vector<float>   *gammaVtxPosX_cm;
	vector<float>   *gammaVtxPosY_cm;
	vector<float>   *gammaVtxPosZ_cm;
	vector<float>   *gammaVtxDirX;
	vector<float>   *gammaVtxDirY;
	vector<float>   *gammaVtxDirZ;

	vector<float>   *gammaPosX_cm;
	vector<float>   *gammaPosY_cm;
	vector<float>   *gammaPosZ_cm;
	vector<float>   *gammaMomX_eV;
	vector<float>   *gammaMomY_eV;
	vector<float>   *gammaMomZ_eV;

	vector<float>   *gammaEnergy_eV;
	vector<float>   *gammaTime_ms;

	string 		*monName;
	Float_t         monPosX_cm;
	Float_t         monPosY_cm;
	Float_t         monPosZ_cm;
	Float_t         monMomX_eV;
	Float_t         monMomY_eV;
	Float_t         monMomZ_eV;
	Float_t 	monRefPosX_cm;
	Float_t 	monRefPosY_cm;
	Float_t 	monRefPosZ_cm;
	Float_t 	monRefAngle_rad;

   	// List of branches
	TBranch        *b_event;   //!
	TBranch        *b_beamPdg;   //!
	TBranch        *b_beamPosX_cm;   //!
	TBranch        *b_beamPosY_cm;   //!
	TBranch        *b_beamPosZ_cm;   //!
	TBranch        *b_beamMomX_eV;   //!
	TBranch        *b_beamMomY_eV;   //!
	TBranch        *b_beamMomZ_eV;   //!
	TBranch        *b_beamEnergy_eV;   //!
	TBranch        *b_beamRefPosX_cm;   //!
	TBranch        *b_beamRefPosY_cm;   //!
	TBranch        *b_beamRefPosZ_cm;   //!
	TBranch        *b_beamRefAngle_rad;   //!

	TBranch        *b_magName;   //!
	TBranch        *b_magNph;   //!
	TBranch        *b_magSumEph_eV;   //!

	TBranch        *b_gammaVtxPosX_cm;   //!
	TBranch        *b_gammaVtxPosY_cm;   //!
	TBranch        *b_gammaVtxPosZ_cm;   //!
	TBranch        *b_gammaVtxDirX;   //!
	TBranch        *b_gammaVtxDirY;   //!
	TBranch        *b_gammaVtxDirZ;   //!

	TBranch        *b_gammaPosX_cm;   //!
	TBranch        *b_gammaPosY_cm;   //!
	TBranch        *b_gammaPosZ_cm;   //!
	TBranch        *b_gammaMomX_eV;   //!
	TBranch        *b_gammaMomY_eV;   //!
	TBranch        *b_gammaMomZ_eV;   //!

	TBranch        *b_gammaEnergy_eV;   //!
	TBranch        *b_gammaTime_ms;   //!

	TBranch        *b_monName;   //!
	TBranch        *b_monPosX_cm;   //!
	TBranch        *b_monPosY_cm;   //!
	TBranch        *b_monPosZ_cm;   //!
	TBranch        *b_monMomX_eV;   //!
	TBranch        *b_monMomY_eV;   //!
	TBranch        *b_monMomZ_eV;   //!
	TBranch        *b_monRefPosX_cm;   //!
	TBranch        *b_monRefPosY_cm;   //!
	TBranch        *b_monRefPosZ_cm;   //!
	TBranch        *b_monRefAngle_rad;   //!

 	void Init(TString);
	void Loop();
	void SetInputFileName(TString val){_inputFileName = val; return;}
	TString GetInputFileName(){return _inputFileName;}
	void SetOutputFileNameRoot(TString val){_outputFileName_root = val; return;}
	TString GetOutputFileNameRoot(){return _outputFileName_root;}

private:

	TString _inputFileName;
	TString _outputFileName_root;
   	TChain* _fChain;

	TH1F* _h1;
	TH2F* _h2;
	TH2F* _h21;
	TH2F* _h3x;
	TH2F* _h3y;

	// for benchmark/debug
	TH1D*	h1_ene;	
	TH1D*	h1_dirx;	
  	TH1D*	h1_diry;	
  	TH1D*	h1_dirz;	
  	TH1D*	h1_posx;	
  	TH1D*	h1_posy;
  	TH1D*	h1_posz;
	TH2D*	h1_ene_dirx;
	TH2D*	h1_ene_diry;
	TH2D*	h1_ene_dirz;
};
#endif
