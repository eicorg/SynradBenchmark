void ana3(	TString _inputFileName = "./output/synrad3d_converted.root",
		TString _outputFileName = "./output/output_all.root")
{
	TString treeName = "tree";
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

	TChain* fChain = new TChain(treeName.Data());
   	if(!fChain){return;}
	fChain->Add(_inputFileName.Data());

	fChain->ls();

	// Declaration of leaf types
	Int_t           index;
	Float_t         x_ini;
	Float_t         y_ini;
	Float_t         z_ini;
	Float_t         vx_ini;
	Float_t         vy_ini;
	Float_t         vz_ini;
	Float_t         x_fin;
	Float_t         y_fin;
	Float_t         z_fin;
	Float_t         vx_fin;
	Float_t         vy_fin;
	Float_t         vz_fin;
	Float_t         ene;
	Float_t         weight;

	// List of branches
	TBranch        *b_index;   //!
	TBranch        *b_x_ini;   //!
	TBranch        *b_y_ini;   //!
	TBranch        *b_z_ini;   //!
	TBranch        *b_vx_ini;   //!
	TBranch        *b_vy_ini;   //!
	TBranch        *b_vz_ini;   //!
	TBranch        *b_x_fin;   //!
	TBranch        *b_y_fin;   //!
	TBranch        *b_z_fin;   //!
	TBranch        *b_vx_fin;   //!
	TBranch        *b_vy_fin;   //!
	TBranch        *b_vz_fin;   //!
	TBranch        *b_ene;   //!
	TBranch        *b_weight;   //!

	fChain->SetBranchAddress("index", &index, &b_index);
	fChain->SetBranchAddress("x_ini", &x_ini, &b_x_ini);
	fChain->SetBranchAddress("y_ini", &y_ini, &b_y_ini);
	fChain->SetBranchAddress("z_ini", &z_ini, &b_z_ini);
	fChain->SetBranchAddress("vx_ini", &vx_ini, &b_vx_ini);
	fChain->SetBranchAddress("vy_ini", &vy_ini, &b_vy_ini);
	fChain->SetBranchAddress("vz_ini", &vz_ini, &b_vz_ini);
	fChain->SetBranchAddress("x_fin", &x_fin, &b_x_fin);
	fChain->SetBranchAddress("y_fin", &y_fin, &b_y_fin);
	fChain->SetBranchAddress("z_fin", &z_fin, &b_z_fin);
	fChain->SetBranchAddress("vx_fin", &vx_fin, &b_vx_fin);
	fChain->SetBranchAddress("vy_fin", &vy_fin, &b_vy_fin);
	fChain->SetBranchAddress("vz_fin", &vz_fin, &b_vz_fin);
	fChain->SetBranchAddress("ene", &ene, &b_ene);
	fChain->SetBranchAddress("weight", &weight, &b_weight);

	// histograms
	_h1 = new TH1F("h1","SR photon energy;E_{#gamma} [eV];# of photons",101000,-1000,100000);
	_h2 = new TH2F("h2","SR photon position;Z_{#gamma} [cm];X_{#gamma} [cm]",7000,-1000,6000,2000,-100,100);
	_h3x = new TH2F("h3x","SR photon vertex position;Z_{vtx} [cm];X_{vtx} [cm]",7000,0,-1000,2000,-100,100);
	_h3y = new TH2F("h3y","SR photon vertex position;Z_{vtx} [cm];Y_{vtx} [cm]",7000,-1000,6000,2000,-100,100);
	_h21 = new TH2F("h21","SR photon position vs energy;Z_{#gamma} [cm];X_{#gamma} [cm];E_{#gamma} [eV]",7000,-1000,6000,2000,-100,100);

	// for benchmark/debug
	h1_ene = new TH1D("h1_ene","SR photon spectrum;E_{#gamma} [eV];Flux [ph/s]",1e6,0,1e6);
	h1_dirx = new TH1D("h1_dirx","SR photon momDir X; Px_{#gamma}/E_{#gamma};Flux [ph/s]",4e6,-2,2);
	h1_diry = new TH1D("h1_diry","SR photon momDir Y; Py_{#gamma}/E_{#gamma};Flux [ph/s]",4e6,-2,2);
	h1_dirz = new TH1D("h1_dirz","SR photon momDir Z; Pz_{#gamma}/E_{#gamma};Flux [ph/s]",4e6,-2,2);
	h1_posx = new TH1D("h1_posx","SR photon position X; X_{#gamma} [cm];Flux [ph/s]",200,-100,100);
	h1_posy = new TH1D("h1_posy","SR photon position Y; Y_{#gamma} [cm];Flux [ph/s]",200,-100,100);
	h1_posz = new TH1D("h1_posz","SR photon position Z; Z_{#gamma} [cm];Flux [ph/s]",7000,-1000,6000);
	h1_ene_dirx = 
		new TH2D("h1_ene_dirx",
		"SR photon energy vs momDir X;Px_{#gamma}/E_{#gamma};E_{#gamma} [eV];Flux [ph/s]",
		4e3,-2,2,4e3,0,40e3);
	h1_ene_diry = 
		new TH2D("h1_ene_diry",
		"SR photon energy vs momDir Y;Py_{#gamma}/E_{#gamma};E_{#gamma} [eV];Flux [ph/s]",
		4e3,-2,2,4e3,0,40e3);
	h1_ene_dirz = 
		new TH2D("h1_ene_dirz",
		"SR photon energy vs momDir Z;Pz_{#gamma}/E_{#gamma};E_{#gamma} [eV];Flux [ph/s]",
		4e3,-2,2,4e3,0,40e3);

   	Long64_t nEntries = fChain->GetEntries();
	cout<<"[INFO] nEntries = "<<nEntries<<endl;

	Float_t x, y, z, pinx, piny, pinz, px, py, pz, energy;
	Int_t pdg;

	Long64_t jentry = 0;
   	while(jentry < nEntries) 
	{
		// load the entry
		fChain->GetEntry(jentry);

		x_ini *= 1e2; // m -> cm
		y_ini *= 1e2; // m -> cm
		z_ini *= 1e2; // m -> cm
		x_fin *= 1e2; // m -> cm
		y_fin *= 1e2; // m -> cm
		z_fin *= 1e2; // m -> cm

		if(jentry%1000 == 0)
        	{
           	 	printf("\r[INFO] Progress: %.3f [%%]",100.0*jentry/nEntries);
            		fflush(stdout);
        	}
		jentry++;
		
		// for benchmark/debug
		if(	40e2 < z_fin && z_fin < 45e2	) // around the IP
		{
			h1_ene->Fill(ene,weight);
			h1_dirx->Fill(vx_fin,weight);
			h1_diry->Fill(vy_fin,weight);
			h1_dirz->Fill(vz_fin,weight);
			h1_posx->Fill(x_fin,weight);
			h1_posy->Fill(y_fin,weight);
			h1_posz->Fill(z_fin,weight);
			h1_ene_dirx->Fill(vx_fin,ene*weight);
			h1_ene_diry->Fill(vy_fin,ene*weight);
			h1_ene_dirz->Fill(vz_fin,ene*weight);
		}
		//---------------------------------------------------------------------------
		// fill histograms
		_h1->Fill(ene,weight);
		_h2->Fill(z_fin,x_fin,weight);
		_h21->Fill(z_fin,x_fin,ene*weight);
		_h3x->Fill(z_ini,x_ini,weight);
		_h3y->Fill(z_ini,y_ini,weight);
   	}
 	printf("\r[INFO] Progress: %.3f [%%]\n",100.0*jentry/nEntries);

	TFile* f = new TFile(_outputFileName.Data(),"recreate");
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
	cout<<"[INFO] Output file name: "<<f->GetName()<<endl;

	return;
}
