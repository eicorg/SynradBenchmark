#include "AnalysisSR.hh"

AnalysisSR::AnalysisSR() : _fChain(0) 
{}

AnalysisSR::~AnalysisSR()
{
   	if(_fChain)
		delete _fChain->GetCurrentFile();
}

void AnalysisSR::Init(TString treeName = "tree")
{
	_fChain = new TChain(treeName.Data());
   	if(!_fChain){return;};
	_fChain->Add(_inputFileName.Data());

	cout<<"\n\n=================================================================="<<endl;
	cout<<"\n[INFO] AnalysisSR::Init ==> Added files:"<<endl;
	_fChain->ls();
	cout<<"==================================================================\n\n"<<endl;

   	// set object pointer
	beamPdg = nullptr;
	beamPosX_cm = nullptr;
	beamPosY_cm = nullptr;
	beamPosZ_cm = nullptr;
	beamMomX_eV = nullptr;
	beamMomY_eV = nullptr;
	beamMomZ_eV = nullptr;
	beamEnergy_eV = nullptr;
	beamRefPosX_cm = nullptr;
	beamRefPosY_cm = nullptr;
	beamRefPosZ_cm = nullptr;
	beamRefAngle_rad = nullptr;

	monName = new string();
	gammaVtxPosX_cm = nullptr;
	gammaVtxPosY_cm = nullptr;
	gammaVtxPosZ_cm = nullptr;
	gammaVtxDirX = nullptr;
	gammaVtxDirY = nullptr;
	gammaVtxDirZ = nullptr;
	gammaPosX_cm = nullptr;
	gammaPosY_cm = nullptr;
	gammaPosZ_cm = nullptr;
	gammaMomX_eV = nullptr;
	gammaMomY_eV = nullptr;
	gammaMomZ_eV = nullptr;
	gammaEnergy_eV = nullptr;
	gammaTime_ms = nullptr;
	magName = nullptr;
	magNph = nullptr;
	magSumEph_eV = nullptr;

	// set branch addresses and branch pointers
   	_fChain->SetBranchAddress("event", &event, &b_event);
   	_fChain->SetBranchAddress("beamPdg", &beamPdg, &b_beamPdg);
   	_fChain->SetBranchAddress("beamPosX_cm", &beamPosX_cm, &b_beamPosX_cm);
   	_fChain->SetBranchAddress("beamPosY_cm", &beamPosY_cm, &b_beamPosY_cm);
   	_fChain->SetBranchAddress("beamPosZ_cm", &beamPosZ_cm, &b_beamPosZ_cm);
   	_fChain->SetBranchAddress("beamMomX_eV", &beamMomX_eV, &b_beamMomX_eV);
   	_fChain->SetBranchAddress("beamMomY_eV", &beamMomY_eV, &b_beamMomY_eV);
   	_fChain->SetBranchAddress("beamMomZ_eV", &beamMomZ_eV, &b_beamMomZ_eV);
   	_fChain->SetBranchAddress("beamEnergy_eV", &beamEnergy_eV, &b_beamEnergy_eV);
   	_fChain->SetBranchAddress("beamRefPosX_cm", &beamRefPosX_cm, &b_beamRefPosX_cm);
   	_fChain->SetBranchAddress("beamRefPosY_cm", &beamRefPosY_cm, &b_beamRefPosY_cm);
   	_fChain->SetBranchAddress("beamRefPosZ_cm", &beamRefPosZ_cm, &b_beamRefPosZ_cm);
   	_fChain->SetBranchAddress("beamRefAngle_rad", &beamRefAngle_rad, &b_beamRefAngle_rad);

   	_fChain->SetBranchAddress("magName", &magName, &b_magName);
   	_fChain->SetBranchAddress("magNph", &magNph, &b_magNph);
   	_fChain->SetBranchAddress("magSumEph_eV", &magSumEph_eV, &b_magSumEph_eV);

   	_fChain->SetBranchAddress("gammaVtxPosX_cm", &gammaVtxPosX_cm, &b_gammaVtxPosX_cm);
   	_fChain->SetBranchAddress("gammaVtxPosY_cm", &gammaVtxPosY_cm, &b_gammaVtxPosY_cm);
   	_fChain->SetBranchAddress("gammaVtxPosZ_cm", &gammaVtxPosZ_cm, &b_gammaVtxPosZ_cm);
   	_fChain->SetBranchAddress("gammaVtxDirX", &gammaVtxDirX, &b_gammaVtxDirX);
   	_fChain->SetBranchAddress("gammaVtxDirY", &gammaVtxDirY, &b_gammaVtxDirY);
   	_fChain->SetBranchAddress("gammaVtxDirZ", &gammaVtxDirZ, &b_gammaVtxDirZ);

   	_fChain->SetBranchAddress("gammaPosX_cm", &gammaPosX_cm, &b_gammaPosX_cm);
   	_fChain->SetBranchAddress("gammaPosY_cm", &gammaPosY_cm, &b_gammaPosY_cm);
   	_fChain->SetBranchAddress("gammaPosZ_cm", &gammaPosZ_cm, &b_gammaPosZ_cm);
   	_fChain->SetBranchAddress("gammaMomX_eV", &gammaMomX_eV, &b_gammaMomX_eV);
   	_fChain->SetBranchAddress("gammaMomY_eV", &gammaMomY_eV, &b_gammaMomY_eV);
   	_fChain->SetBranchAddress("gammaMomZ_eV", &gammaMomZ_eV, &b_gammaMomZ_eV);

   	_fChain->SetBranchAddress("gammaEnergy_eV", &gammaEnergy_eV, &b_gammaEnergy_eV);
   	_fChain->SetBranchAddress("gammaTime_ms", &gammaTime_ms, &b_gammaTime_ms);

   	_fChain->SetBranchAddress("monName", &monName, &b_monName);
   	_fChain->SetBranchAddress("monPosX_cm", &monPosX_cm, &b_monPosX_cm);
   	_fChain->SetBranchAddress("monPosY_cm", &monPosY_cm, &b_monPosY_cm);
   	_fChain->SetBranchAddress("monPosZ_cm", &monPosZ_cm, &b_monPosZ_cm);
   	_fChain->SetBranchAddress("monMomX_eV", &monMomX_eV, &b_monMomX_eV);
   	_fChain->SetBranchAddress("monMomY_eV", &monMomY_eV, &b_monMomY_eV);
   	_fChain->SetBranchAddress("monMomZ_eV", &monMomZ_eV, &b_monMomZ_eV);
   	_fChain->SetBranchAddress("monRefPosX_cm", &monRefPosX_cm, &b_monRefPosX_cm);
   	_fChain->SetBranchAddress("monRefPosY_cm", &monRefPosY_cm, &b_monRefPosY_cm);
   	_fChain->SetBranchAddress("monRefPosZ_cm", &monRefPosZ_cm, &b_monRefPosZ_cm);
   	_fChain->SetBranchAddress("monRefAngle_rad", &monRefAngle_rad, &b_monRefAngle_rad);

	_fChain->GetEntry(0);
	// histograms
	_h1 = new TH1F("h1","SR photon energy;E_{#gamma} [eV];# of photons",101000,-1000,100000);
	_h2 = new TH2F("h2","SR photon position;Z_{#gamma} [cm];X_{#gamma} [cm]",7000,-1000,6000,2000,-100,100);
	_h3x = new TH2F("h3x","SR photon vertex position;Z_{vtx} [cm];X_{vtx} [cm]",7000,0,-1000,2000,-100,100);
	_h3y = new TH2F("h3y","SR photon vertex position;Z_{vtx} [cm];Y_{vtx} [cm]",7000,-1000,6000,2000,-100,100);
	_h21 = new TH2F("h21","SR photon position vs energy;Z_{#gamma} [cm];X_{#gamma} [cm];E_{#gamma} [eV]",7000,-1000,6000,2000,-100,100);

	// for benchmark/debug
	h1_ene = new TH1D("h1_ene_g4","SR photon spectrum;E_{#gamma} [eV];Flux [ph/s]",1e6,0,1e6);
	h1_dirx = new TH1D("h1_dirx_g4","SR photon momDir X; Px_{#gamma}/E_{#gamma};Flux [ph/s]",4e6,-2,2);
	h1_diry = new TH1D("h1_diry_g4","SR photon momDir Y; Py_{#gamma}/E_{#gamma};Flux [ph/s]",4e6,-2,2);
	h1_dirz = new TH1D("h1_dirz_g4","SR photon momDir Z; Pz_{#gamma}/E_{#gamma};Flux [ph/s]",4e6,-2,2);
	h1_posx = new TH1D("h1_posx_g4","SR photon position X; X_{#gamma} [cm];Flux [ph/s]",200,-100,100);
	h1_posy = new TH1D("h1_posy_g4","SR photon position Y; Y_{#gamma} [cm];Flux [ph/s]",200,-100,100);
	h1_posz = new TH1D("h1_posz_g4","SR photon position Z; Z_{#gamma} [cm];Flux [ph/s]",7000,-1000,6000);
	h1_ene_dirx = 
		new TH2D("h1_ene_dirx_g4",
		"SR photon energy vs momDir X;Px_{#gamma}/E_{#gamma};E_{#gamma} [eV];Flux [ph/s]",
		4e3,-2,2,4e3,0,40e3);
	h1_ene_diry = 
		new TH2D("h1_ene_diry_g4",
		"SR photon energy vs momDir Y;Py_{#gamma}/E_{#gamma};E_{#gamma} [eV];Flux [ph/s]",
		4e3,-2,2,4e3,0,40e3);
	h1_ene_dirz = 
		new TH2D("h1_ene_dirz_g4",
		"SR photon energy vs momDir Z;Pz_{#gamma}/E_{#gamma};E_{#gamma} [eV];Flux [ph/s]",
		4e3,-2,2,4e3,0,40e3);

	return;
}

void AnalysisSR::Loop()
{
  	if(!_fChain){return;}

   	Long64_t nEntries = _fChain->GetEntries();
	cout<<"[INFO] AnalysisSR::Loop ==> nEntries = "<<nEntries<<endl;

	Float_t x, y, z, pinx, piny, pinz, px, py, pz, energy;
	Int_t pdg;

	Long64_t jentry = 0;
   	while(jentry < nEntries) 
	{
		// load the entry
		_fChain->GetEntry(jentry);
		
		if(jentry%1000 == 0)
        	{
           	 	printf("\r[INFO] Progress: %.3f [%%]",100.0*jentry/nEntries);
            		fflush(stdout);
        	}
		jentry++;
		
		// loop over SR photons
		for(Int_t i = 0; i < gammaEnergy_eV->size(); i++)
		{
			// for benchmark/debug
			if(	40e2 < gammaPosZ_cm->at(i) && gammaPosZ_cm->at(i) < 45e2	) // around the IP
			{
				h1_ene->Fill(gammaEnergy_eV->at(i));
				h1_dirx->Fill(gammaMomX_eV->at(i)/gammaEnergy_eV->at(i));
				h1_diry->Fill(gammaMomY_eV->at(i)/gammaEnergy_eV->at(i));
				h1_dirz->Fill(gammaMomZ_eV->at(i)/gammaEnergy_eV->at(i));
				h1_posx->Fill(gammaPosX_cm->at(i));
				h1_posy->Fill(gammaPosY_cm->at(i));
				h1_posz->Fill(gammaPosZ_cm->at(i));
				h1_ene_dirx->Fill(	gammaMomX_eV->at(i)/gammaEnergy_eV->at(i),
							gammaEnergy_eV->at(i));
				h1_ene_diry->Fill(	gammaMomY_eV->at(i)/gammaEnergy_eV->at(i),
							gammaEnergy_eV->at(i));
				h1_ene_dirz->Fill(	gammaMomZ_eV->at(i)/gammaEnergy_eV->at(i),
							gammaEnergy_eV->at(i));
			}
			
			//---------------------------------------------------------------------------
			// fill histograms
			_h1->Fill(gammaEnergy_eV->at(i));
			_h2->Fill(gammaPosZ_cm->at(i),gammaPosX_cm->at(i));
			_h21->Fill(gammaPosZ_cm->at(i),gammaPosX_cm->at(i),gammaEnergy_eV->at(i));
			_h3x->Fill(gammaVtxPosZ_cm->at(i),gammaVtxPosX_cm->at(i));
			_h3y->Fill(gammaVtxPosZ_cm->at(i),gammaVtxPosY_cm->at(i));
		}
   	}
 	printf("\r[INFO] Progress: %.3f [%%]\n",100.0*jentry/nEntries);

	TFile* f = new TFile(GetOutputFileNameRoot().Data(),"recreate");
	f->cd();
	_h1->Write();
	_h2->Write();
	_h3x->Write();
	_h3y->Write();
	_h21->Write();
	// for benchmark/debug
	h1_ene->Write();
	h1_dirx->Write();
	h1_diry->Write();
	h1_dirz->Write();
	h1_posx->Write();
	h1_posy->Write();
	h1_posz->Write();
	h1_ene_dirx->Write();
	h1_ene_diry->Write();
	h1_ene_dirz->Write();

	f->Close();

	return;
}
