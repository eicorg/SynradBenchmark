const Double_t beamCurrent_A = 1.0;
const Double_t nElectrons_synradg4 = 10*1000; // 10 files x 1000 e-/file

void compare(	TString fName_synradp = "../Synrad+/ana/output/output_all.root",
		TString fName_synrad3d = "../Synrad3D/ana/output/output_all.root",
		TString fName_synradg4 = "../SynradG4/ana/output/output_all.root"
	)
{
	const Double_t minDirx = -0.13, maxDirx =  0.01;
	const Double_t minDiry = -0.02, maxDiry =  0.02;
	const Double_t minDirz =  0.95, maxDirz =  1.01;
	const Double_t minX_eV = -5.02, maxX_eV = -4.90;
	const Double_t minY_eV = -1.00, maxY_eV =  1.00;
	const Double_t minZ_eV = -3400, maxZ_eV = -2300;

	gStyle->SetOptStat(0);

	//------- get Synrad+ data
	TFile *file_synradp = TFile::Open(fName_synradp.Data());
	TH1D* h1_ene_synradp = (TH1D*)file_synradp->Get("h1_ene");
	TH1D* h1_dirx_synradp = (TH1D*)file_synradp->Get("h1_dirx");
	TH1D* h1_diry_synradp = (TH1D*)file_synradp->Get("h1_diry");
	TH1D* h1_dirz_synradp = (TH1D*)file_synradp->Get("h1_dirz");
	TH1D* h1_posx_synradp = (TH1D*)file_synradp->Get("h1_posx");
	TH1D* h1_posy_synradp = (TH1D*)file_synradp->Get("h1_posy");
	TH1D* h1_posz_synradp = (TH1D*)file_synradp->Get("h1_posz");

	//------- get Synrad3D data
	TFile *file_synrad3d = TFile::Open(fName_synrad3d.Data());
	TH1D* h1_ene_synrad3d = (TH1D*)file_synrad3d->Get("h1_ene");
	TH1D* h1_dirx_synrad3d = (TH1D*)file_synrad3d->Get("h1_dirx");
	TH1D* h1_diry_synrad3d = (TH1D*)file_synrad3d->Get("h1_diry");
	TH1D* h1_dirz_synrad3d = (TH1D*)file_synrad3d->Get("h1_dirz");
	TH1D* h1_posx_synrad3d = (TH1D*)file_synrad3d->Get("h1_posx");
	TH1D* h1_posy_synrad3d = (TH1D*)file_synrad3d->Get("h1_posy");
	TH1D* h1_posz_synrad3d = (TH1D*)file_synrad3d->Get("h1_posz");

	// scale
	h1_ene_synrad3d->Scale(beamCurrent_A/TMath::Qe());
	h1_dirx_synrad3d->Scale(beamCurrent_A/TMath::Qe());
	h1_diry_synrad3d->Scale(beamCurrent_A/TMath::Qe());
	h1_dirz_synrad3d->Scale(beamCurrent_A/TMath::Qe());
	h1_posx_synrad3d->Scale(beamCurrent_A/TMath::Qe());
	h1_posy_synrad3d->Scale(beamCurrent_A/TMath::Qe());
	h1_posz_synrad3d->Scale(beamCurrent_A/TMath::Qe());

	//------- get SynradG4 data
	TFile *file_synradg4 = TFile::Open(fName_synradg4.Data());
	TH1D* h1_ene_synradg4 = (TH1D*)file_synradg4->Get("h1_ene");
	TH1D* h1_dirx_synradg4 = (TH1D*)file_synradg4->Get("h1_dirx");
	TH1D* h1_diry_synradg4 = (TH1D*)file_synradg4->Get("h1_diry");
	TH1D* h1_dirz_synradg4 = (TH1D*)file_synradg4->Get("h1_dirz");
	TH1D* h1_posx_synradg4 = (TH1D*)file_synradg4->Get("h1_posx");
	TH1D* h1_posy_synradg4 = (TH1D*)file_synradg4->Get("h1_posy");
	TH1D* h1_posz_synradg4 = (TH1D*)file_synradg4->Get("h1_posz");

	// scale
	h1_ene_synradg4->Scale(beamCurrent_A/(nElectrons_synradg4*TMath::Qe()));
	h1_dirx_synradg4->Scale(beamCurrent_A/(nElectrons_synradg4*TMath::Qe()));
	h1_diry_synradg4->Scale(beamCurrent_A/(nElectrons_synradg4*TMath::Qe()));
	h1_dirz_synradg4->Scale(beamCurrent_A/(nElectrons_synradg4*TMath::Qe()));
	h1_posx_synradg4->Scale(beamCurrent_A/(nElectrons_synradg4*TMath::Qe()));
	h1_posy_synradg4->Scale(beamCurrent_A/(nElectrons_synradg4*TMath::Qe()));
	h1_posz_synradg4->Scale(beamCurrent_A/(nElectrons_synradg4*TMath::Qe()));

	//=========================================================================================//
	// plot data
	TCanvas* c0 = new TCanvas("c0","c0",900,900);
	c0->cd();

	h1_ene_synradp->Rebin(100);
	h1_ene_synrad3d->Rebin(100);
	h1_ene_synradg4->Rebin(100);
	cout<<"[INFO] Energy binning:"<<endl;
	cout<<" - h1_ene_synradp bin width = "<<h1_ene_synradp->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<" - h1_ene_synrad3d bin width = "<<h1_ene_synrad3d->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<" - h1_ene_synradg4 bin width = "<<h1_ene_synradg4->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;

	h1_ene_synradp->SetLineWidth(3);
	h1_ene_synrad3d->SetLineWidth(3);
	h1_ene_synradg4->SetLineWidth(3);

	h1_ene_synradp->SetLineColor(kBlack);
	h1_ene_synrad3d->SetLineColor(kBlue);
	h1_ene_synradg4->SetLineColor(kRed);

	h1_ene_synrad3d->SetFillStyle(3345);
	h1_ene_synrad3d->SetFillColorAlpha(kBlue,0.2);
	h1_ene_synradg4->SetFillColorAlpha(kRed,0.2);

	h1_ene_synradp->GetXaxis()->SetRangeUser(0,20e3);
	h1_ene_synradp->SetMinimum(1e10);
	h1_ene_synradp->SetMaximum(1e19);

	h1_ene_synradp->Draw("HIST");
	h1_ene_synrad3d->Draw("SAME & HIST");
	h1_ene_synradg4->Draw("SAME & HIST");

	TLegend* leg0 = new TLegend(0.6,0.7,0.9,0.9);
	leg0->AddEntry(h1_ene_synradp,"Synrad+","f");
	leg0->AddEntry(h1_ene_synrad3d,"Synrad3D","f");
	leg0->AddEntry(h1_ene_synradg4,"SynradG4","f");
	leg0->Draw();

	gPad->SetGrid();
	gPad->SetLogy();

//	c0->SaveAs("c0.png");
/*
	//=========================================================================================//
	TCanvas* c1 = new TCanvas("c1","c1",1800,900);
	c1->Divide(3,2);

	//-- dirx
	c1->cd(1);

	h1_dirx_synradp->Rebin(10);
	h1_dirx_synradg4->Rebin(10);
	cout<<"h1_dirx_synradp bin width = "<<h1_dirx_synradp->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<"h1_dirx_synradg4 bin width = "<<h1_dirx_synradg4->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;

	h1_dirx_synradp->SetLineWidth(3);
	h1_dirx_synradg4->SetLineWidth(1);
	h1_dirx_synradp->SetLineColor(kBlack);
	h1_dirx_synradg4->SetLineColor(kRed);
	h1_dirx_synradg4->SetFillColorAlpha(kRed,0.2);

	h1_dirx_synradp->GetXaxis()->SetRangeUser(minDirx,maxDirx);
	h1_dirx_synradp->SetMinimum(1e11);
	h1_dirx_synradp->SetMaximum(1e16);

	h1_dirx_synradp->Draw("HIST");
	h1_dirx_synradg4->Draw("SAME & HIST");

	TLegend* leg_dirx = new TLegend(0.2,0.7,0.5,0.9);
	leg_dirx->AddEntry(h1_dirx_synradp,"Synrad+","f");
	leg_dirx->AddEntry(h1_dirx_synradg4,"Geant4","f");
	leg_dirx->Draw();

	gPad->SetGrid();
	gPad->SetLogy();

	//-- diry
	c1->cd(2);

	h1_diry_synradp->Rebin(10);
	h1_diry_synradg4->Rebin(10);
	cout<<"h1_diry_synradp bin width = "<<h1_diry_synradp->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<"h1_diry_synradg4 bin width = "<<h1_diry_synradg4->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;

	h1_diry_synradp->SetLineWidth(3);
	h1_diry_synradg4->SetLineWidth(1);
	h1_diry_synradp->SetLineColor(kBlack);
	h1_diry_synradg4->SetLineColor(kRed);
	h1_diry_synradg4->SetFillColorAlpha(kRed,0.2);

	h1_diry_synradp->GetXaxis()->SetRangeUser(minDiry,maxDiry);
	h1_diry_synradp->SetMinimum(1e11);
	h1_diry_synradp->SetMaximum(1e19);

	h1_diry_synradp->Draw("HIST");
	h1_diry_synradg4->Draw("SAME & HIST");

	TLegend* leg_diry = new TLegend(0.6,0.7,0.9,0.9);
	leg_diry->AddEntry(h1_diry_synradp,"Synrad+","f");
	leg_diry->AddEntry(h1_diry_synradg4,"Geant4","f");
	leg_diry->Draw();

	gPad->SetGrid();
	gPad->SetLogy();

	//-- dirz
	c1->cd(3);

	h1_dirz_synradp->Rebin(100);
	h1_dirz_synradg4->Rebin(100);
	cout<<"h1_dirz_synradp bin width = "<<h1_dirz_synradp->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<"h1_dirz_synradg4 bin width = "<<h1_dirz_synradg4->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;

	h1_dirz_synradp->SetLineWidth(3);
	h1_dirz_synradg4->SetLineWidth(1);
	h1_dirz_synradp->SetLineColor(kBlack);
	h1_dirz_synradg4->SetLineColor(kRed);
	h1_dirz_synradg4->SetFillColorAlpha(kRed,0.2);

	h1_dirz_synradp->GetXaxis()->SetRangeUser(minDirz,maxDirz);
	h1_dirz_synradp->SetMinimum(1e11);
	h1_dirz_synradp->SetMaximum(1e22);

	h1_dirz_synradp->Draw("HIST");
	h1_dirz_synradg4->Draw("SAME & HIST");

	TLegend* leg_dirz = new TLegend(0.6,0.7,0.9,0.9);
	leg_dirz->AddEntry(h1_dirz_synradp,"Synrad+","f");
	leg_dirz->AddEntry(h1_dirz_synradg4,"Geant4","f");
	leg_dirz->Draw();

	gPad->SetGrid();
	gPad->SetLogy();

	//-- posx
	c1->cd(4);

	h1_posx_synradp->Rebin(1);
	h1_posx_synradg4->Rebin(1);
	cout<<"h1_posx_synradp bin width = "<<h1_posx_synradp->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<"h1_posx_synradg4 bin width = "<<h1_posx_synradg4->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;

	h1_posx_synradp->SetLineWidth(3);
	h1_posx_synradg4->SetLineWidth(1);
	h1_posx_synradp->SetLineColor(kBlack);
	h1_posx_synradg4->SetLineColor(kRed);
	h1_posx_synradg4->SetFillColorAlpha(kRed,0.2);

	h1_posx_synradp->GetXaxis()->SetRangeUser(minX_eV,maxX_eV);
	h1_posx_synradp->SetMinimum(1e11);
	h1_posx_synradp->SetMaximum(1e20);

	h1_posx_synradp->Draw("HIST");
	h1_posx_synradg4->Draw("SAME & HIST");

	TLegend* leg_posx = new TLegend(0.6,0.7,0.9,0.9);
	leg_posx->AddEntry(h1_posx_synradp,"Synrad+","f");
	leg_posx->AddEntry(h1_posx_synradg4,"Geant4","f");
	leg_posx->Draw();

	gPad->SetGrid();
	gPad->SetLogy();

	//-- posy
	c1->cd(5);

	h1_posy_synradp->Rebin(10);
	h1_posy_synradg4->Rebin(10);
	cout<<"h1_posy_synradp bin width = "<<h1_posy_synradp->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<"h1_posy_synradg4 bin width = "<<h1_posy_synradg4->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;

	h1_posy_synradp->SetLineWidth(3);
	h1_posy_synradg4->SetLineWidth(1);
	h1_posy_synradp->SetLineColor(kBlack);
	h1_posy_synradg4->SetLineColor(kRed);
	h1_posy_synradg4->SetFillColorAlpha(kRed,0.2);

	h1_posy_synradp->GetXaxis()->SetRangeUser(minY_eV,maxY_eV);
	h1_posy_synradp->SetMinimum(1e11);
	h1_posy_synradp->SetMaximum(1e20);

	h1_posy_synradp->Draw("HIST");
	h1_posy_synradg4->Draw("SAME & HIST");

	TLegend* leg_posy = new TLegend(0.6,0.7,0.9,0.9);
	leg_posy->AddEntry(h1_posy_synradp,"Synrad+","f");
	leg_posy->AddEntry(h1_posy_synradg4,"Geant4","f");
	leg_posy->Draw();

	gPad->SetGrid();
	gPad->SetLogy();

	//-- posz
	c1->cd(6);

	h1_posz_synradp->Rebin(10);
	h1_posz_synradg4->Rebin(10);
	cout<<"h1_posz_synradp bin width = "<<h1_posz_synradp->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<"h1_posz_synradg4 bin width = "<<h1_posz_synradg4->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;

	h1_posz_synradp->SetLineWidth(3);
	h1_posz_synradg4->SetLineWidth(1);
	h1_posz_synradp->SetLineColor(kBlack);
	h1_posz_synradg4->SetLineColor(kRed);
	h1_posz_synradg4->SetFillColorAlpha(kRed,0.2);

	h1_posz_synradp->GetXaxis()->SetRangeUser(minZ_eV,maxZ_eV);
	h1_posz_synradp->SetMinimum(1e14);
	h1_posz_synradp->SetMaximum(1e17);

	h1_posz_synradp->Draw("HIST");
	h1_posz_synradg4->Draw("SAME & HIST");

	TLegend* leg_posz = new TLegend(0.6,0.7,0.9,0.9);
	leg_posz->AddEntry(h1_posz_synradp,"Synrad+","f");
	leg_posz->AddEntry(h1_posz_synradg4,"Geant4","f");
	leg_posz->Draw();

	gPad->SetGrid();
	gPad->SetLogy();

	c1->SaveAs("c1.png");
	//=========================================================================================//
*/
	return;
}
