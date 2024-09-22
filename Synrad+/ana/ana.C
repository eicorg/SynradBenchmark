vector<Double_t> Pos_X_cm;
vector<Double_t> Pos_Y_cm;
vector<Double_t> Pos_Z_cm;
vector<Double_t> Pos_u;
vector<Double_t> Pos_v;
vector<Double_t> Dir_X;
vector<Double_t> Dir_Y;
vector<Double_t> Dir_Z;
vector<Double_t> Dir_theta_rad;
vector<Double_t> Dir_phi_rad; 
vector<Double_t> LowFluxRatio;
vector<Double_t> Energy_eV;
vector<Double_t> Flux_phs;
vector<Double_t> Power_W;

vector<Int_t> vtx_Index;
vector<Double_t> vtx_L_cm;
vector<Double_t> vtx_Orbit_pos_X_cm;
vector<Double_t> vtx_Orbit_pos_Y_cm;
vector<Double_t> vtx_Orbit_pos_Z_cm;
vector<Double_t> vtx_Beam_cood_S_m; 
vector<Double_t> vtx_Orbit_dirX;
vector<Double_t> vtx_Orbit_dirY;
vector<Double_t> vtx_Orbit_dirZ;
vector<Double_t> vtx_Photon_Natural_divX_rad;
vector<Double_t> vtx_Photon_Natural_divY_rad;
vector<Double_t> vtx_Photon_Energy;
vector<Double_t> vtx_Photon_Flux_Hz;
vector<Double_t> vtx_Photon_Power_W;

void readCSVfile(TString fName);
void readSynRadData(TString inputFileName);
void readOrbitData(TString fName);
void getFileList(TString fDirName, TString fName);

vector<TString> fList;

TH1D* h1_ene = new TH1D("h1_ene","SR photon spectrum;E_{#gamma} [eV];Flux [ph/s]",1e6,0,1e6); 
TH1D* h1_dirx = new TH1D("h1_dirx","SR photon momentum X; Px_{#gamma}/E_{#gamma};Flux [ph/s]",4e6,-2,2); 
TH1D* h1_diry = new TH1D("h1_diry","SR photon momentum Y; Py_{#gamma}/E_{#gamma};Flux [ph/s]",4e6,-2,2); 
TH1D* h1_dirz = new TH1D("h1_dirz","SR photon momentum Z; Pz_{#gamma}/E_{#gamma};Flux [ph/s]",4e6,-2,2); 
TH1D* h1_posx = new TH1D("h1_posx","SR photon position X; X_{#gamma} [eV];Flux [ph/s]",2000,-100,100);  
TH1D* h1_posy = new TH1D("h1_posy","SR photon position Y; Y_{#gamma} [eV];Flux [ph/s]",2000,-100,100); 
TH1D* h1_posz = new TH1D("h1_posz","SR photon position Z; Z_{#gamma} [eV];Flux [ph/s]",7000,-1000,6000);

// vertex
TH1F* h1_vtx = new TH1F("h1_vtx","Vertex SR photon energy;E_{#gamma} [eV];# of photons",1e6,0,1e6);
TH1F* h2_vtx = new TH1F("h2_vtx","Vertex SR photon position X;X_{#gamma} [cm];Flux [ph/s]",2000,-100,100);
TH1F* h3_vtx = new TH1F("h3_vtx","Vertex SR photon position Y;Y_{#gamma} [cm];Flux [ph/s]",20000,-10,10);
TH1F* h4_vtx = new TH1F("h4_vtx","Vertex SR photon position Z;Z_{#gamma} [cm];Flux [ph/s]",7000,-1000,6000);
TH1F* h5_vtx = new TH1F("h5_vtx","Vertex SR photon direction X;Px_{#gamma}/E_{#gamma};Flux [ph/s]",4e6,-2,2);
TH1F* h6_vtx = new TH1F("h6_vtx","Vertex SR photon direction Y;Py_{#gamma}/E_{#gamma};Flux [ph/s]",4e6,-2,2);
TH1F* h7_vtx = new TH1F("h7_vtx","Vertex SR photon direction Z;Pz_{#gamma}/E_{#gamma};Flux [ph/s]",4e6,-2,2);


void ana(	TString outputFileName = "./output_diff/output_all.root", 
		TString fListName = "fileList.txt",
		TString fDirName = "../sim/output_diff",
		TString fOrbitName = "../sim/orbit.coord")
{
	// Get the list of input files
	getFileList(fDirName,fListName);
	// read SR data
	for(auto &name: fList){readSynRadData(name);}
	// read orbit data
	readOrbitData(fOrbitName.Data());	

	// vertex
	TRandom *rnd = new TRandom3();
	for(Int_t i = 0; i < vtx_Index.size(); i++)
	{
		h1_vtx->Fill(vtx_Photon_Energy.at(i),vtx_Photon_Flux_Hz.at(i));
		h2_vtx->Fill(vtx_Orbit_pos_X_cm.at(i),vtx_Photon_Flux_Hz.at(i));
		h3_vtx->Fill(vtx_Orbit_pos_Y_cm.at(i),vtx_Photon_Flux_Hz.at(i));
		h4_vtx->Fill(vtx_Orbit_pos_Z_cm.at(i),vtx_Photon_Flux_Hz.at(i));
		//-- w/o smearing - beam orbit
		// h5_vtx->Fill(vtx_Orbit_dirX.at(i),vtx_Photon_Flux_Hz.at(i));
		// h6_vtx->Fill(vtx_Orbit_dirY.at(i),vtx_Photon_Flux_Hz.at(i));
		// h7_vtx->Fill(vtx_Orbit_dirZ.at(i),vtx_Photon_Flux_Hz.at(i));
		//-- w/ -smearing - SR vertex
		Double_t dirX = rnd->Gaus(vtx_Orbit_dirX.at(i),vtx_Photon_Natural_divX_rad.at(i));
		Double_t dirY = rnd->Gaus(vtx_Orbit_dirY.at(i),vtx_Photon_Natural_divY_rad.at(i));
		Double_t dirZ = TMath::Sqrt(1.0 - dirX*dirX - dirY*dirY);
		h5_vtx->Fill(dirX,vtx_Photon_Flux_Hz.at(i));
		h6_vtx->Fill(dirY,vtx_Photon_Flux_Hz.at(i));
		h7_vtx->Fill(dirZ,vtx_Photon_Flux_Hz.at(i));
	}

	TFile* file = new TFile(outputFileName.Data(),"recreate");
	file->cd();
	h1_ene->Write();
	h1_dirx->Write();
	h1_diry->Write();
	h1_dirz->Write();
	h1_posx->Write();
	h1_posy->Write();
	h1_posz->Write();
	// vertex
	h1_vtx->Write();
	h2_vtx->Write();
	h3_vtx->Write();
	h4_vtx->Write();
	h5_vtx->Write();
	h6_vtx->Write();
	h7_vtx->Write();

	file->Close();

	cout<<"Output Synrad+ file name = "<<file->GetName()<<endl;

	return;
}

void getFileList(TString fDirName, TString fName)
{
	string line;
	fstream f;
	f.open(fName.Data(),ios::in);
	if(f.is_open())
	{
		while(getline(f,line))
		{
			fList.push_back(Form("%s/%s",fDirName.Data(),line.c_str()));
		}
		f.close();
	}
	else
	{
		cout<<"[ERROR] Cannot open or read the file: "<<fName<<endl;
		exit(-1);
	}
	// print the list of files
	cout<<"[INFO] List of input files:"<<endl;
	for(auto &name: fList){cout<<" - "<<name<<endl;}
	return;
}

void readSynRadData(TString inputFileName)
{
	// clean data vectors
	Pos_X_cm.clear();
	Pos_Y_cm.clear();
	Pos_Z_cm.clear();
	Pos_u.clear();
	Pos_v.clear();
	Dir_X.clear();
	Dir_Y.clear();
	Dir_Z.clear();
	Dir_theta_rad.clear();
	Dir_phi_rad.clear(); 
	LowFluxRatio.clear();
	Energy_eV.clear();
	Flux_phs.clear();
	Power_W.clear();

	// read a CSV file
	readCSVfile(inputFileName);

	for(Int_t i = 0; i < Energy_eV.size(); i++)
	{
		if(40e2 < Pos_Z_cm.at(i) && Pos_Z_cm.at(i) < 45e2)
		{
			h1_ene->Fill(Energy_eV.at(i),Flux_phs.at(i));
			h1_posx->Fill(Pos_X_cm.at(i),Flux_phs.at(i));
			h1_posy->Fill(Pos_Y_cm.at(i),Flux_phs.at(i));
			h1_posz->Fill(Pos_Z_cm.at(i),Flux_phs.at(i));
			h1_dirx->Fill(Dir_X.at(i),Flux_phs.at(i));
			h1_diry->Fill(Dir_Y.at(i),Flux_phs.at(i));
			h1_dirz->Fill(Dir_Z.at(i),Flux_phs.at(i));
		}
	}

	return;
}

void readCSVfile(TString fName)
{
	cout<<"Input file name: "<<fName<<endl;

	// Create an input filestream
    	ifstream myFile(fName.Data());

    	// Helper vars
    	string line, colname;
    	Double_t val;

    	// Read data, line by line
	getline(myFile, line); // skip the first title line

    	while(getline(myFile, line))
    	{
        	// Create a stringstream of the current line
        	stringstream ss(line);
        
        	// Keep track of the current column index
        	Int_t colIdx = 0;
        
        	// Extract each value
        	while(ss >> val)
		{
            		// Add the current integer to the 'colIdx' column's values vector
			switch(colIdx)
			{
				case 0:
					Pos_X_cm.push_back(val);
					break;
				case 1:
					Pos_Y_cm.push_back(val);
					break;
				case 2:
					Pos_Z_cm.push_back(val);
					break;
				case 3:
					Pos_u.push_back(val);
					break;
				case 4:
					Pos_v.push_back(val);
					break;
				case 5:
					Dir_X.push_back(val);
					break;
				case 6:
					Dir_Y.push_back(val);
					break;
				case 7:
					Dir_Z.push_back(val);
					break;
				case 8:
					Dir_theta_rad.push_back(val);
					break;
				case 9:
					Dir_phi_rad.push_back(val);
					break;
				case 10:
					LowFluxRatio.push_back(val);
					break;
				case 11:
					Energy_eV.push_back(val);
					break;
				case 12:
					Flux_phs.push_back(val);
					break;
				case 13:
					Power_W.push_back(val);
					break;
			}
            
            		// If the next token is a comma, ignore it and move on
            		if(ss.peek() == ',') ss.ignore();
            
            		// Increment the column index
            		colIdx++;
        	}
    	}

    	// Close file
    	myFile.close();

	return;
}

void readOrbitData(TString fName)
{
	cout<<"Input file name: "<<fName<<endl;

	// Create an input filestream
    	ifstream myFile(fName.Data());

    	// Helper vars
    	string line, colname;
    	Double_t val;

    	// Read data, line by line
	getline(myFile, line); // skip the first title line
	cout<<"[INFO] Header:"<<endl<<line<<endl;

    	while(getline(myFile, line))
    	{
        	// Create a stringstream of the current line
        	stringstream ss(line);
        
        	// Keep track of the current column index
        	Int_t colIdx = 0;
        
        	// Extract each value
        	while(ss >> val)
		{
            		// Add the current integer to the 'colIdx' column's values vector
			switch(colIdx)
			{
				case 0:
					vtx_Index.push_back(val);
					break;
				case 1:
					vtx_L_cm.push_back(val);
					break;
				case 2:
					vtx_Orbit_pos_X_cm.push_back(val);
					break;
				case 3:
					vtx_Orbit_pos_Y_cm.push_back(val);
					break;
				case 4:
					vtx_Orbit_pos_Z_cm.push_back(val);
					break;
				case 5:
					vtx_Beam_cood_S_m.push_back(val);
					break;
				case 6:
					vtx_Orbit_dirX.push_back(val);
					break;
				case 7:
					vtx_Orbit_dirY.push_back(val);
					break;
				case 8:
					vtx_Orbit_dirZ.push_back(val);
					break;
				case 9:
					vtx_Photon_Natural_divX_rad.push_back(val);
					break;
				case 10:
					vtx_Photon_Natural_divY_rad.push_back(val);
					break;
				case 11:
					vtx_Photon_Energy.push_back(val);
					break;
				case 12:
					vtx_Photon_Flux_Hz.push_back(val);
					break;
				case 13:
					vtx_Photon_Power_W.push_back(val);
					break;
			}
           
            		// If the next token is a comma, ignore it and move on
            		if(ss.peek() == ',') ss.ignore();
            
            		// Increment the column index
            		colIdx++;
        	}
    	}

    	// Close file
    	myFile.close();

	return;
}
