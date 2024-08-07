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

void readCSVfile(TString fName);
void readSynRadData(TString inputFileName, TH1D* h1_ene, TH1D* h1_dirx, TH1D* h1_diry, TH1D* h1_dirz, TH1D* h1_posx, TH1D* h1_posy, TH1D* h1_posz);
void getSynRadData(TString outputFileName = "synrad_data.root");

const Double_t beamCurrent_A = 0.227;
const Double_t nElectrons_g4 = 10*1e5; // 10 files x 1e5 e-/file

//void compareSpectrum_2(TString fName = "28755_2400s_noLowFlux.csv")
//void compareSpectrum_2(TString fName = "28755_2400s_noLowFlux_newModel.csv")
//void compareSpectrum_2(TString fName = "28755_2400s.csv")

TH2D* _h1_cut_sr = new TH2D("_h1_cut_sr","Synrad+ Data;#theta_{graz} [rad];E_{#gamma} [eV]",3e3,0.0,0.03,7e3,0,7e4);

void compareSpectrum_2()
{
	const Double_t minE_eV =  0.00, maxE_eV =  20e3;
	const Double_t minDirx = -0.13, maxDirx =  0.01;
	const Double_t minDiry = -0.02, maxDiry =  0.02;
	const Double_t minDirz =  0.95, maxDirz =  1.01;
	const Double_t minX_eV = -5.02, maxX_eV = -4.90;
	const Double_t minY_eV = -1.00, maxY_eV =  1.00;
	const Double_t minZ_eV = -3400, maxZ_eV = -2300;

	gStyle->SetOptStat(0);

	//-- read the csv file
	// getSynRadData("synrad_data.root"); 
	// _h1_cut_sr->SaveAs("h1_cut_sr.root");
	// return;

	// get synrad+ data
	TFile *file_sr = TFile::Open("synrad_data.root");
	TH1D* h1_ene_sr = (TH1D*)file_sr->Get("h1_ene_sr");
	TH1D* h1_dirx_sr = (TH1D*)file_sr->Get("h1_dirx_sr");
	TH1D* h1_diry_sr = (TH1D*)file_sr->Get("h1_diry_sr");
	TH1D* h1_dirz_sr = (TH1D*)file_sr->Get("h1_dirz_sr");
	TH1D* h1_posx_sr = (TH1D*)file_sr->Get("h1_posx_sr");
	TH1D* h1_posy_sr = (TH1D*)file_sr->Get("h1_posy_sr");
	TH1D* h1_posz_sr = (TH1D*)file_sr->Get("h1_posz_sr");

	// get geant4 data
	TFile *file_g4 = TFile::Open("geant4_data.root");
	TH1D* h1_ene_g4 = (TH1D*)file_g4->Get("h1_ene_g4");
	TH1D* h1_dirx_g4 = (TH1D*)file_g4->Get("h1_dirx_g4");
	TH1D* h1_diry_g4 = (TH1D*)file_g4->Get("h1_diry_g4");
	TH1D* h1_dirz_g4 = (TH1D*)file_g4->Get("h1_dirz_g4");
	TH1D* h1_posx_g4 = (TH1D*)file_g4->Get("h1_posx_g4");
	TH1D* h1_posy_g4 = (TH1D*)file_g4->Get("h1_posy_g4");
	TH1D* h1_posz_g4 = (TH1D*)file_g4->Get("h1_posz_g4");

	// scale geant4 -> synrad
	h1_ene_g4->Scale(beamCurrent_A/(nElectrons_g4*TMath::Qe()));
	h1_dirx_g4->Scale(beamCurrent_A/(nElectrons_g4*TMath::Qe()));
	h1_diry_g4->Scale(beamCurrent_A/(nElectrons_g4*TMath::Qe()));
	h1_dirz_g4->Scale(beamCurrent_A/(nElectrons_g4*TMath::Qe()));
	h1_posx_g4->Scale(beamCurrent_A/(nElectrons_g4*TMath::Qe()));
	h1_posy_g4->Scale(beamCurrent_A/(nElectrons_g4*TMath::Qe()));
	h1_posz_g4->Scale(beamCurrent_A/(nElectrons_g4*TMath::Qe()));

	//=========================================================================================//
	// plot data
	TCanvas* c0 = new TCanvas("c0","c0",900,900);
	c0->cd();

	h1_ene_sr->Rebin(100);
	h1_ene_g4->Rebin(100);
	cout<<"h1_ene_sr bin width = "<<h1_ene_sr->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<"h1_ene_g4 bin width = "<<h1_ene_g4->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;

	h1_ene_sr->SetLineWidth(3);
	h1_ene_g4->SetLineWidth(1);
	h1_ene_sr->SetLineColor(kBlack);
	h1_ene_g4->SetLineColor(kRed);
	h1_ene_g4->SetFillColorAlpha(kRed,0.2);

	h1_ene_sr->GetXaxis()->SetRangeUser(minE_eV,maxE_eV);
	h1_ene_sr->SetMinimum(1e15);
	h1_ene_sr->SetMaximum(1e19);

	h1_ene_sr->Draw("HIST");
	h1_ene_g4->Draw("SAME & HIST");

	TLegend* leg0 = new TLegend(0.6,0.7,0.9,0.9);
	leg0->AddEntry(h1_ene_sr,"Synrad+","f");
	leg0->AddEntry(h1_ene_g4,"Geant4","f");
	leg0->Draw();

	gPad->SetGrid();
	gPad->SetLogy();

	c0->SaveAs("c0.png");

	//=========================================================================================//
	TCanvas* c1 = new TCanvas("c1","c1",1800,900);
	c1->Divide(3,2);

	//-- dirx
	c1->cd(1);

	h1_dirx_sr->Rebin(10);
	h1_dirx_g4->Rebin(10);
	cout<<"h1_dirx_sr bin width = "<<h1_dirx_sr->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<"h1_dirx_g4 bin width = "<<h1_dirx_g4->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;

	h1_dirx_sr->SetLineWidth(3);
	h1_dirx_g4->SetLineWidth(1);
	h1_dirx_sr->SetLineColor(kBlack);
	h1_dirx_g4->SetLineColor(kRed);
	h1_dirx_g4->SetFillColorAlpha(kRed,0.2);

	h1_dirx_sr->GetXaxis()->SetRangeUser(minDirx,maxDirx);
	h1_dirx_sr->SetMinimum(1e11);
	h1_dirx_sr->SetMaximum(1e16);

	h1_dirx_sr->Draw("HIST");
	h1_dirx_g4->Draw("SAME & HIST");

	TLegend* leg_dirx = new TLegend(0.2,0.7,0.5,0.9);
	leg_dirx->AddEntry(h1_dirx_sr,"Synrad+","f");
	leg_dirx->AddEntry(h1_dirx_g4,"Geant4","f");
	leg_dirx->Draw();

	gPad->SetGrid();
	gPad->SetLogy();

	//-- diry
	c1->cd(2);

	h1_diry_sr->Rebin(10);
	h1_diry_g4->Rebin(10);
	cout<<"h1_diry_sr bin width = "<<h1_diry_sr->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<"h1_diry_g4 bin width = "<<h1_diry_g4->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;

	h1_diry_sr->SetLineWidth(3);
	h1_diry_g4->SetLineWidth(1);
	h1_diry_sr->SetLineColor(kBlack);
	h1_diry_g4->SetLineColor(kRed);
	h1_diry_g4->SetFillColorAlpha(kRed,0.2);

	h1_diry_sr->GetXaxis()->SetRangeUser(minDiry,maxDiry);
	h1_diry_sr->SetMinimum(1e11);
	h1_diry_sr->SetMaximum(1e19);

	h1_diry_sr->Draw("HIST");
	h1_diry_g4->Draw("SAME & HIST");

	TLegend* leg_diry = new TLegend(0.6,0.7,0.9,0.9);
	leg_diry->AddEntry(h1_diry_sr,"Synrad+","f");
	leg_diry->AddEntry(h1_diry_g4,"Geant4","f");
	leg_diry->Draw();

	gPad->SetGrid();
	gPad->SetLogy();

	//-- dirz
	c1->cd(3);

	h1_dirz_sr->Rebin(100);
	h1_dirz_g4->Rebin(100);
	cout<<"h1_dirz_sr bin width = "<<h1_dirz_sr->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<"h1_dirz_g4 bin width = "<<h1_dirz_g4->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;

	h1_dirz_sr->SetLineWidth(3);
	h1_dirz_g4->SetLineWidth(1);
	h1_dirz_sr->SetLineColor(kBlack);
	h1_dirz_g4->SetLineColor(kRed);
	h1_dirz_g4->SetFillColorAlpha(kRed,0.2);

	h1_dirz_sr->GetXaxis()->SetRangeUser(minDirz,maxDirz);
	h1_dirz_sr->SetMinimum(1e11);
	h1_dirz_sr->SetMaximum(1e22);

	h1_dirz_sr->Draw("HIST");
	h1_dirz_g4->Draw("SAME & HIST");

	TLegend* leg_dirz = new TLegend(0.6,0.7,0.9,0.9);
	leg_dirz->AddEntry(h1_dirz_sr,"Synrad+","f");
	leg_dirz->AddEntry(h1_dirz_g4,"Geant4","f");
	leg_dirz->Draw();

	gPad->SetGrid();
	gPad->SetLogy();

	//-- posx
	c1->cd(4);

	h1_posx_sr->Rebin(1);
	h1_posx_g4->Rebin(1);
	cout<<"h1_posx_sr bin width = "<<h1_posx_sr->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<"h1_posx_g4 bin width = "<<h1_posx_g4->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;

	h1_posx_sr->SetLineWidth(3);
	h1_posx_g4->SetLineWidth(1);
	h1_posx_sr->SetLineColor(kBlack);
	h1_posx_g4->SetLineColor(kRed);
	h1_posx_g4->SetFillColorAlpha(kRed,0.2);

	h1_posx_sr->GetXaxis()->SetRangeUser(minX_eV,maxX_eV);
	h1_posx_sr->SetMinimum(1e11);
	h1_posx_sr->SetMaximum(1e20);

	h1_posx_sr->Draw("HIST");
	h1_posx_g4->Draw("SAME & HIST");

	TLegend* leg_posx = new TLegend(0.6,0.7,0.9,0.9);
	leg_posx->AddEntry(h1_posx_sr,"Synrad+","f");
	leg_posx->AddEntry(h1_posx_g4,"Geant4","f");
	leg_posx->Draw();

	gPad->SetGrid();
	gPad->SetLogy();

	//-- posy
	c1->cd(5);

	h1_posy_sr->Rebin(10);
	h1_posy_g4->Rebin(10);
	cout<<"h1_posy_sr bin width = "<<h1_posy_sr->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<"h1_posy_g4 bin width = "<<h1_posy_g4->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;

	h1_posy_sr->SetLineWidth(3);
	h1_posy_g4->SetLineWidth(1);
	h1_posy_sr->SetLineColor(kBlack);
	h1_posy_g4->SetLineColor(kRed);
	h1_posy_g4->SetFillColorAlpha(kRed,0.2);

	h1_posy_sr->GetXaxis()->SetRangeUser(minY_eV,maxY_eV);
	h1_posy_sr->SetMinimum(1e11);
	h1_posy_sr->SetMaximum(1e20);

	h1_posy_sr->Draw("HIST");
	h1_posy_g4->Draw("SAME & HIST");

	TLegend* leg_posy = new TLegend(0.6,0.7,0.9,0.9);
	leg_posy->AddEntry(h1_posy_sr,"Synrad+","f");
	leg_posy->AddEntry(h1_posy_g4,"Geant4","f");
	leg_posy->Draw();

	gPad->SetGrid();
	gPad->SetLogy();

	//-- posz
	c1->cd(6);

	h1_posz_sr->Rebin(10);
	h1_posz_g4->Rebin(10);
	cout<<"h1_posz_sr bin width = "<<h1_posz_sr->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<"h1_posz_g4 bin width = "<<h1_posz_g4->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;

	h1_posz_sr->SetLineWidth(3);
	h1_posz_g4->SetLineWidth(1);
	h1_posz_sr->SetLineColor(kBlack);
	h1_posz_g4->SetLineColor(kRed);
	h1_posz_g4->SetFillColorAlpha(kRed,0.2);

	h1_posz_sr->GetXaxis()->SetRangeUser(minZ_eV,maxZ_eV);
	h1_posz_sr->SetMinimum(1e14);
	h1_posz_sr->SetMaximum(1e17);

	h1_posz_sr->Draw("HIST");
	h1_posz_g4->Draw("SAME & HIST");

	TLegend* leg_posz = new TLegend(0.6,0.7,0.9,0.9);
	leg_posz->AddEntry(h1_posz_sr,"Synrad+","f");
	leg_posz->AddEntry(h1_posz_g4,"Geant4","f");
	leg_posz->Draw();

	gPad->SetGrid();
	gPad->SetLogy();

	c1->SaveAs("c1.png");
	//=========================================================================================//

	return;
}

void getSynRadData(TString outputFileName = "synrad_data.root")
{
	TFile* file = new TFile(outputFileName.Data(),"recreate");
	file->cd();

	TH1D* h1_ene_sr = new TH1D("h1_ene_sr","SR photon spectrum;E_{#gamma} [eV];Flux [ph/s]",1e6,0,1e6); 
	TH1D* h1_dirx_sr = new TH1D("h1_dirx_sr","SR photon momentum X; Px_{#gamma}/E_{#gamma};Flux [ph/s]",4e6,-2,2); 
	TH1D* h1_diry_sr = new TH1D("h1_diry_sr","SR photon momentum Y; Py_{#gamma}/E_{#gamma};Flux [ph/s]",4e6,-2,2); 
	TH1D* h1_dirz_sr = new TH1D("h1_dirz_sr","SR photon momentum Z; Pz_{#gamma}/E_{#gamma};Flux [ph/s]",4e6,-2,2); 
	TH1D* h1_posx_sr = new TH1D("h1_posx_sr","SR photon position X; X_{#gamma} [eV];Flux [ph/s]",10000,-10,0);  
	TH1D* h1_posy_sr = new TH1D("h1_posy_sr","SR photon position Y; Y_{#gamma} [eV];Flux [ph/s]",2000,-1,1); 
	TH1D* h1_posz_sr = new TH1D("h1_posz_sr","SR photon position Z; Z_{#gamma} [eV];Flux [ph/s]",11000,-3400,-2300);

	readSynRadData("28754_2400s.csv",h1_ene_sr,h1_dirx_sr,h1_diry_sr,h1_dirz_sr,h1_posx_sr,h1_posy_sr,h1_posz_sr);
	readSynRadData("28755_2400s.csv",h1_ene_sr,h1_dirx_sr,h1_diry_sr,h1_dirz_sr,h1_posx_sr,h1_posy_sr,h1_posz_sr);

	h1_ene_sr->Write();
	h1_dirx_sr->Write();
	h1_diry_sr->Write();
	h1_dirz_sr->Write();
	h1_posx_sr->Write();
	h1_posy_sr->Write();
	h1_posz_sr->Write();
	file->Close();

	cout<<"Output Synrad+ file name = "<<file->GetName()<<endl;

	return;
}

void readSynRadData(TString inputFileName, TH1D* h1_ene, TH1D* h1_dirx, TH1D* h1_diry, TH1D* h1_dirz, TH1D* h1_posx, TH1D* h1_posy, TH1D* h1_posz)
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
		h1_ene->Fill(Energy_eV.at(i),Flux_phs.at(i));
		h1_posx->Fill(Pos_X_cm.at(i),Flux_phs.at(i));
		h1_posy->Fill(Pos_Y_cm.at(i),Flux_phs.at(i));
		h1_posz->Fill(Pos_Z_cm.at(i),Flux_phs.at(i));
		h1_dirx->Fill(Dir_X.at(i),Flux_phs.at(i));
		h1_diry->Fill(Dir_Y.at(i),Flux_phs.at(i));
		h1_dirz->Fill(Dir_Z.at(i),Flux_phs.at(i));

		// cut
		if(Dir_X.at(i) > -0.025 && Dir_X.at(i) < -0.005 
			&& abs(Dir_Y.at(i)) < 0.00001)
		{
			_h1_cut_sr->Fill(TMath::PiOver2() - TMath::ACos(abs(Dir_X.at(i))),Energy_eV.at(i),Flux_phs.at(i));
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
	getline(myFile, line); // skepp the first title line

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
