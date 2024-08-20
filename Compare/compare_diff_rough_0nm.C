const Double_t beamCurrent_A = 1.0;
const Double_t nElectrons_synradg4 = 10*1000000; // N files x M e-/file
const Double_t nElectrons_synradrl = 10*1000000; // N files x M e-/file

void compare_diff_rough_0nm(	
			TString fName_synradp = "../Synrad+/ana/output_spec/output_all.root",
			TString fName_synrad3d = "../Synrad3D/ana/output_spec/output_all.root",
			TString fName_synradg4 = "../SynradG4/ana/output_2/sim_output_all.root",
			TString fName_synradrl = "../SynradG4/ana/output_1/sim_output_all.root"
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
	// absorbed
	TFile *file_synradp = TFile::Open(fName_synradp.Data());
	TH1D* h1_ene_synradp = (TH1D*)file_synradp->Get("h1_ene");
	TH1D* h1_dirx_synradp = (TH1D*)file_synradp->Get("h1_dirx");
	TH1D* h1_diry_synradp = (TH1D*)file_synradp->Get("h1_diry");
	TH1D* h1_dirz_synradp = (TH1D*)file_synradp->Get("h1_dirz");
	TH1D* h1_posx_synradp = (TH1D*)file_synradp->Get("h1_posx");
	TH1D* h1_posy_synradp = (TH1D*)file_synradp->Get("h1_posy");
	TH1D* h1_posz_synradp = (TH1D*)file_synradp->Get("h1_posz");

	// vertex
	TH1D* h2_ene_synradp = (TH1D*)file_synradp->Get("h1_vtx");
	TH1D* h2_posx_synradp = (TH1D*)file_synradp->Get("h2_vtx");
	TH1D* h2_posy_synradp = (TH1D*)file_synradp->Get("h3_vtx");
	TH1D* h2_posz_synradp = (TH1D*)file_synradp->Get("h4_vtx");
	TH1D* h2_dirx_synradp = (TH1D*)file_synradp->Get("h5_vtx");
	TH1D* h2_diry_synradp = (TH1D*)file_synradp->Get("h6_vtx");
	TH1D* h2_dirz_synradp = (TH1D*)file_synradp->Get("h7_vtx");

	//------- get Synrad3D data
	// absorbed
	TFile *file_synrad3d = TFile::Open(fName_synrad3d.Data());
	TH1D* h1_ene_synrad3d = (TH1D*)file_synrad3d->Get("h1_ene");
	TH1D* h1_dirx_synrad3d = (TH1D*)file_synrad3d->Get("h1_dirx");
	TH1D* h1_diry_synrad3d = (TH1D*)file_synrad3d->Get("h1_diry");
	TH1D* h1_dirz_synrad3d = (TH1D*)file_synrad3d->Get("h1_dirz");
	TH1D* h1_posx_synrad3d = (TH1D*)file_synrad3d->Get("h1_posx");
	TH1D* h1_posy_synrad3d = (TH1D*)file_synrad3d->Get("h1_posy");
	TH1D* h1_posz_synrad3d = (TH1D*)file_synrad3d->Get("h1_posz");

	// vertex
	TH1D* h2_ene_synrad3d = (TH1D*)file_synrad3d->Get("h1_vtx");
	TH1D* h2_posx_synrad3d = (TH1D*)file_synrad3d->Get("h2_vtx");
	TH1D* h2_posy_synrad3d = (TH1D*)file_synrad3d->Get("h3_vtx");
	TH1D* h2_posz_synrad3d = (TH1D*)file_synrad3d->Get("h4_vtx");
	TH1D* h2_dirx_synrad3d = (TH1D*)file_synrad3d->Get("h5_vtx");
	TH1D* h2_diry_synrad3d = (TH1D*)file_synrad3d->Get("h6_vtx");
	TH1D* h2_dirz_synrad3d = (TH1D*)file_synrad3d->Get("h7_vtx");

	// scale
	h1_ene_synrad3d->Scale(beamCurrent_A/TMath::Qe());
	h1_dirx_synrad3d->Scale(beamCurrent_A/TMath::Qe());
	h1_diry_synrad3d->Scale(beamCurrent_A/TMath::Qe());
	h1_dirz_synrad3d->Scale(beamCurrent_A/TMath::Qe());
	h1_posx_synrad3d->Scale(beamCurrent_A/TMath::Qe());
	h1_posy_synrad3d->Scale(beamCurrent_A/TMath::Qe());
	h1_posz_synrad3d->Scale(beamCurrent_A/TMath::Qe());
	h2_ene_synrad3d->Scale(beamCurrent_A/TMath::Qe());
	h2_dirx_synrad3d->Scale(beamCurrent_A/TMath::Qe());
	h2_diry_synrad3d->Scale(beamCurrent_A/TMath::Qe());
	h2_dirz_synrad3d->Scale(beamCurrent_A/TMath::Qe());
	h2_posx_synrad3d->Scale(beamCurrent_A/TMath::Qe());
	h2_posy_synrad3d->Scale(beamCurrent_A/TMath::Qe());
	h2_posz_synrad3d->Scale(beamCurrent_A/TMath::Qe());

	//------- get SynradG4 data
	// absorbed
	TFile *file_synradg4 = TFile::Open(fName_synradg4.Data());
	TH1D* h1_ene_synradg4 = (TH1D*)file_synradg4->Get("h1_ene");
	TH1D* h1_dirx_synradg4 = (TH1D*)file_synradg4->Get("h1_dirx");
	TH1D* h1_diry_synradg4 = (TH1D*)file_synradg4->Get("h1_diry");
	TH1D* h1_dirz_synradg4 = (TH1D*)file_synradg4->Get("h1_dirz");
	TH1D* h1_posx_synradg4 = (TH1D*)file_synradg4->Get("h1_posx");
	TH1D* h1_posy_synradg4 = (TH1D*)file_synradg4->Get("h1_posy");
	TH1D* h1_posz_synradg4 = (TH1D*)file_synradg4->Get("h1_posz");

	// vertex
	TH1D* h2_ene_synradg4 = (TH1D*)file_synradg4->Get("h1_vtx");
	TH1D* h2_posx_synradg4 = (TH1D*)file_synradg4->Get("h2_vtx");
	TH1D* h2_posy_synradg4 = (TH1D*)file_synradg4->Get("h3_vtx");
	TH1D* h2_posz_synradg4 = (TH1D*)file_synradg4->Get("h4_vtx");
	TH1D* h2_dirx_synradg4 = (TH1D*)file_synradg4->Get("h5_vtx");
	TH1D* h2_diry_synradg4 = (TH1D*)file_synradg4->Get("h6_vtx");
	TH1D* h2_dirz_synradg4 = (TH1D*)file_synradg4->Get("h7_vtx");

	// scale
	h1_ene_synradg4->Scale(beamCurrent_A/(nElectrons_synradg4*TMath::Qe()));
	h1_dirx_synradg4->Scale(beamCurrent_A/(nElectrons_synradg4*TMath::Qe()));
	h1_diry_synradg4->Scale(beamCurrent_A/(nElectrons_synradg4*TMath::Qe()));
	h1_dirz_synradg4->Scale(beamCurrent_A/(nElectrons_synradg4*TMath::Qe()));
	h1_posx_synradg4->Scale(beamCurrent_A/(nElectrons_synradg4*TMath::Qe()));
	h1_posy_synradg4->Scale(beamCurrent_A/(nElectrons_synradg4*TMath::Qe()));
	h1_posz_synradg4->Scale(beamCurrent_A/(nElectrons_synradg4*TMath::Qe()));
	h2_ene_synradg4->Scale(beamCurrent_A/(nElectrons_synradg4*TMath::Qe()));
	h2_dirx_synradg4->Scale(beamCurrent_A/(nElectrons_synradg4*TMath::Qe()));
	h2_diry_synradg4->Scale(beamCurrent_A/(nElectrons_synradg4*TMath::Qe()));
	h2_dirz_synradg4->Scale(beamCurrent_A/(nElectrons_synradg4*TMath::Qe()));
	h2_posx_synradg4->Scale(beamCurrent_A/(nElectrons_synradg4*TMath::Qe()));
	h2_posy_synradg4->Scale(beamCurrent_A/(nElectrons_synradg4*TMath::Qe()));
	h2_posz_synradg4->Scale(beamCurrent_A/(nElectrons_synradg4*TMath::Qe()));

	//------- get Geant4-release data
	// absorbed
	TFile *file_synradrl = TFile::Open(fName_synradrl.Data());
	TH1D* h1_ene_synradrl = (TH1D*)file_synradrl->Get("h1_ene");
	TH1D* h1_dirx_synradrl = (TH1D*)file_synradrl->Get("h1_dirx");
	TH1D* h1_diry_synradrl = (TH1D*)file_synradrl->Get("h1_diry");
	TH1D* h1_dirz_synradrl = (TH1D*)file_synradrl->Get("h1_dirz");
	TH1D* h1_posx_synradrl = (TH1D*)file_synradrl->Get("h1_posx");
	TH1D* h1_posy_synradrl = (TH1D*)file_synradrl->Get("h1_posy");
	TH1D* h1_posz_synradrl = (TH1D*)file_synradrl->Get("h1_posz");

	// vertex
	TH1D* h2_ene_synradrl = (TH1D*)file_synradrl->Get("h1_vtx");
	TH1D* h2_posx_synradrl = (TH1D*)file_synradrl->Get("h2_vtx");
	TH1D* h2_posy_synradrl = (TH1D*)file_synradrl->Get("h3_vtx");
	TH1D* h2_posz_synradrl = (TH1D*)file_synradrl->Get("h4_vtx");
	TH1D* h2_dirx_synradrl = (TH1D*)file_synradrl->Get("h5_vtx");
	TH1D* h2_diry_synradrl = (TH1D*)file_synradrl->Get("h6_vtx");
	TH1D* h2_dirz_synradrl = (TH1D*)file_synradrl->Get("h7_vtx");

	// scale
	h1_ene_synradrl->Scale(beamCurrent_A/(nElectrons_synradrl*TMath::Qe()));
	h1_dirx_synradrl->Scale(beamCurrent_A/(nElectrons_synradrl*TMath::Qe()));
	h1_diry_synradrl->Scale(beamCurrent_A/(nElectrons_synradrl*TMath::Qe()));
	h1_dirz_synradrl->Scale(beamCurrent_A/(nElectrons_synradrl*TMath::Qe()));
	h1_posx_synradrl->Scale(beamCurrent_A/(nElectrons_synradrl*TMath::Qe()));
	h1_posy_synradrl->Scale(beamCurrent_A/(nElectrons_synradrl*TMath::Qe()));
	h1_posz_synradrl->Scale(beamCurrent_A/(nElectrons_synradrl*TMath::Qe()));
	h2_ene_synradrl->Scale(beamCurrent_A/(nElectrons_synradrl*TMath::Qe()));
	h2_dirx_synradrl->Scale(beamCurrent_A/(nElectrons_synradrl*TMath::Qe()));
	h2_diry_synradrl->Scale(beamCurrent_A/(nElectrons_synradrl*TMath::Qe()));
	h2_dirz_synradrl->Scale(beamCurrent_A/(nElectrons_synradrl*TMath::Qe()));
	h2_posx_synradrl->Scale(beamCurrent_A/(nElectrons_synradrl*TMath::Qe()));
	h2_posy_synradrl->Scale(beamCurrent_A/(nElectrons_synradrl*TMath::Qe()));
	h2_posz_synradrl->Scale(beamCurrent_A/(nElectrons_synradrl*TMath::Qe()));

	//=========================================================================================//
	// plot data
	TCanvas* c0 = new TCanvas("c0","c0",900,900);
	c0->cd();
	TPad* p0 = new TPad("p0","p0",0,0,1,1);
   	p0->SetTopMargin(0.1);
	p0->SetBottomMargin(0.14);
	p0->SetLeftMargin(0.14);
	p0->SetRightMargin(0.1);
	p0->Draw();
	p0->cd();

	h1_ene_synradp->Rebin(20);
	h1_ene_synrad3d->Rebin(20);
	h1_ene_synradg4->Rebin(20);
	h1_ene_synradrl->Rebin(20);
	cout<<"[INFO] Energy binning:"<<endl;
	cout<<" - h1_ene_synradp bin width = "<<h1_ene_synradp->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<" - h1_ene_synrad3d bin width = "<<h1_ene_synrad3d->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<" - h1_ene_synradg4 bin width = "<<h1_ene_synradg4->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<" - h1_ene_synradrl bin width = "<<h1_ene_synradrl->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;

	h1_ene_synradp->SetLineWidth(2);
	h1_ene_synrad3d->SetLineWidth(5);
	h1_ene_synradg4->SetLineWidth(2);
	h1_ene_synradrl->SetLineWidth(1);

	h1_ene_synradp->SetLineColor(kRed);
	h1_ene_synrad3d->SetLineColor(kBlack);
	h1_ene_synradg4->SetLineColor(kBlue);
	h1_ene_synradrl->SetLineColor(kGreen+2);

	h1_ene_synradp->SetFillStyle(3654);
	h1_ene_synradp->SetFillColorAlpha(kRed,0.6);
	h1_ene_synradg4->SetFillColorAlpha(kBlue,0.2);
	h1_ene_synradrl->SetFillStyle(3395);
	h1_ene_synradrl->SetFillColorAlpha(kGreen+2,0.8);

	h1_ene_synrad3d->GetXaxis()->SetRangeUser(0,20e3);
	h1_ene_synrad3d->SetMinimum(1e13);
	h1_ene_synrad3d->SetMaximum(1e17);

	h1_ene_synrad3d->GetYaxis()->SetLabelSize(0.04);
	h1_ene_synrad3d->GetXaxis()->SetLabelSize(0.04);
	h1_ene_synrad3d->GetYaxis()->SetTitleSize(0.04);
	h1_ene_synrad3d->GetXaxis()->SetTitleSize(0.04);
	h1_ene_synrad3d->GetYaxis()->SetTitleOffset(1.6);
	h1_ene_synrad3d->GetXaxis()->SetTitleOffset(1.2);
	h1_ene_synrad3d->GetYaxis()->SetNdivisions(5);
	h1_ene_synrad3d->SetTitle("");
	h1_ene_synrad3d->GetYaxis()->SetTitle("Photon Rate [Hz]");

	h1_ene_synrad3d->Draw("HIST");
	h1_ene_synradg4->Draw("SAME & HIST");
	h1_ene_synradp->Draw("SAME & HIST");
	h1_ene_synradrl->Draw("SAME & HIST");

	TLegend* leg0 = new TLegend(0.55,0.7,0.9,0.9);
	leg0->AddEntry(h1_ene_synrad3d,"Synrad3D","f");
	leg0->AddEntry(h1_ene_synradp,"Synrad+","f");
	leg0->AddEntry(h1_ene_synradg4,"SynradG4","f");
	leg0->AddEntry(h1_ene_synradrl,"Geant4-11.2.0","f");
	leg0->SetTextSize(0.04);
	leg0->Draw();

//	gPad->SetGrid();
	gPad->SetLogy();
	gPad->SetLogx();

	c0->SaveAs("./pics/setup1.png");
	c0->SaveAs("./pics/setup1.pdf");

	//=========================================================================================//
	TCanvas* c1 = new TCanvas("c1","c1",1800,900);
	c1->Divide(3,2);

	//-- dirx
	c1->cd(1);

	h1_dirx_synradp->Rebin(1000);
	h1_dirx_synrad3d->Rebin(1000);
	h1_dirx_synradg4->Rebin(1000);
	h1_dirx_synradrl->Rebin(1000);
	cout<<"[INFO] X' binning:"<<endl;
	cout<<" - h1_dirx_synradp bin width = "<<h1_dirx_synradp->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<" - h1_dirx_synrad3d bin width = "<<h1_dirx_synrad3d->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<" - h1_dirx_synradg4 bin width = "<<h1_dirx_synradg4->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<" - h1_dirx_synradrl bin width = "<<h1_dirx_synradrl->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;

	h1_dirx_synradp->SetLineWidth(4);
	h1_dirx_synrad3d->SetLineWidth(3);
	h1_dirx_synradg4->SetLineWidth(1);
	h1_dirx_synradrl->SetLineWidth(1);

	h1_dirx_synradp->SetLineColor(kBlack);
	h1_dirx_synrad3d->SetLineColor(kBlue);
	h1_dirx_synradg4->SetLineColor(kRed);
	h1_dirx_synradrl->SetLineColor(kGreen+2);

	h1_dirx_synrad3d->SetFillStyle(3345);
	h1_dirx_synrad3d->SetFillColorAlpha(kBlue,0.2);
	h1_dirx_synradg4->SetFillColorAlpha(kRed,0.2);
	h1_dirx_synradrl->SetFillColorAlpha(kGreen+2,0.2);

	h1_dirx_synradp->GetXaxis()->SetRangeUser(-0.3,0.3);
	h1_dirx_synradp->SetMinimum(1e11);
	h1_dirx_synradp->SetMaximum(1e19);

	h1_dirx_synradp->Draw("HIST");
	h1_dirx_synrad3d->Draw("SAME & HIST");
	h1_dirx_synradg4->Draw("SAME & HIST");
	h1_dirx_synradrl->Draw("SAME & HIST");

	TLegend* leg_dirx = new TLegend(0.2,0.7,0.5,0.9);
	leg_dirx->AddEntry(h1_dirx_synradp,"Synrad+","f");
	leg_dirx->AddEntry(h1_dirx_synrad3d,"Synrad3D","f");
	leg_dirx->AddEntry(h1_dirx_synradg4,"SynradG4","f");
	leg_dirx->AddEntry(h1_dirx_synradrl,"Geant4-rel.","f");
	leg_dirx->Draw();

	gPad->SetGrid();
	gPad->SetLogy();

	//-- diry
	c1->cd(2);

	h1_diry_synradp->Rebin(100);
	h1_diry_synrad3d->Rebin(100);
	h1_diry_synradg4->Rebin(100);
	h1_diry_synradrl->Rebin(100);
	cout<<"[INFO] Y' binning:"<<endl;
	cout<<" - h1_diry_synradp bin width = "<<h1_diry_synradp->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<" - h1_diry_synrad3d bin width = "<<h1_diry_synrad3d->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<" - h1_diry_synradg4 bin width = "<<h1_diry_synradg4->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<" - h1_diry_synradrl bin width = "<<h1_diry_synradrl->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;

	h1_diry_synradp->SetLineWidth(4);
	h1_diry_synrad3d->SetLineWidth(3);
	h1_diry_synradg4->SetLineWidth(1);
	h1_diry_synradrl->SetLineWidth(1);

	h1_diry_synradp->SetLineColor(kBlack);
	h1_diry_synrad3d->SetLineColor(kBlue);
	h1_diry_synradg4->SetLineColor(kRed);
	h1_diry_synradrl->SetLineColor(kGreen+2);

	h1_diry_synrad3d->SetFillStyle(3345);
	h1_diry_synrad3d->SetFillColorAlpha(kBlue,0.2);
	h1_diry_synradg4->SetFillColorAlpha(kRed,0.2);
	h1_diry_synradrl->SetFillColorAlpha(kGreen+2,0.2);

	h1_diry_synradp->GetXaxis()->SetRangeUser(-0.01,0.01);
	h1_diry_synradp->SetMinimum(1e11);
	h1_diry_synradp->SetMaximum(1e19);

	h1_diry_synradp->Draw("HIST");
	h1_diry_synrad3d->Draw("SAME & HIST");
	h1_diry_synradg4->Draw("SAME & HIST");
	h1_diry_synradrl->Draw("SAME & HIST");

	TLegend* leg_diry = new TLegend(0.1,0.7,0.4,0.9);
	leg_diry->AddEntry(h1_diry_synradp,"Synrad+","f");
	leg_diry->AddEntry(h1_diry_synrad3d,"Synrad3D","f");
	leg_diry->AddEntry(h1_diry_synradg4,"SynradG4","f");
	leg_diry->AddEntry(h1_diry_synradg4,"Geant4-rel.","f");
	leg_diry->Draw();

	gPad->SetGrid();
	gPad->SetLogy();

	//-- dirz
	c1->cd(3);

	h1_dirz_synradp->Rebin(1000);
	h1_dirz_synrad3d->Rebin(1000);
	h1_dirz_synradg4->Rebin(1000);
	h1_dirz_synradrl->Rebin(1000);
	cout<<"[INFO] Z' binning:"<<endl;
	cout<<" - h1_dirz_synradp bin width = "<<h1_dirz_synradp->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<" - h1_dirz_synrad3d bin width = "<<h1_dirz_synrad3d->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<" - h1_dirz_synradg4 bin width = "<<h1_dirz_synradg4->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<" - h1_dirz_synradrl bin width = "<<h1_dirz_synradrl->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;

	h1_dirz_synradp->SetLineWidth(4);
	h1_dirz_synrad3d->SetLineWidth(3);
	h1_dirz_synradg4->SetLineWidth(1);
	h1_dirz_synradrl->SetLineWidth(1);

	h1_dirz_synradp->SetLineColor(kBlack);
	h1_dirz_synrad3d->SetLineColor(kBlue);
	h1_dirz_synradg4->SetLineColor(kRed);
	h1_dirz_synradrl->SetLineColor(kGreen+2);

	h1_dirz_synrad3d->SetFillStyle(3345);
	h1_dirz_synrad3d->SetFillColorAlpha(kBlue,0.2);
	h1_dirz_synradg4->SetFillColorAlpha(kRed,0.2);
	h1_dirz_synradrl->SetFillColorAlpha(kGreen+2,0.2);

	h1_dirz_synradp->GetXaxis()->SetRangeUser(0.965,1.01);
	h1_dirz_synradp->SetMinimum(1e11);
	h1_dirz_synradp->SetMaximum(1e19);

	h1_dirz_synradp->Draw("HIST");
	h1_dirz_synrad3d->Draw("SAME & HIST");
	h1_dirz_synradg4->Draw("SAME & HIST");
	h1_dirz_synradrl->Draw("SAME & HIST");

	TLegend* leg_dirz = new TLegend(0.1,0.7,0.4,0.9);
	leg_dirz->AddEntry(h1_dirz_synradp,"Synrad+","f");
	leg_dirz->AddEntry(h1_dirz_synrad3d,"Synrad3D","f");
	leg_dirz->AddEntry(h1_dirz_synradg4,"SynradG4","f");
	leg_dirz->AddEntry(h1_dirz_synradrl,"Geant4-rel.","f");
	leg_dirz->Draw();

	gPad->SetGrid();
	gPad->SetLogy();

	//-- posx
	c1->cd(4);

	h1_posx_synradp->Rebin(1);
	h1_posx_synrad3d->Rebin(1);
	h1_posx_synradg4->Rebin(1);
	h1_posx_synradrl->Rebin(1);
	cout<<"[INFO] X binning:"<<endl;
	cout<<" - h1_posx_synradp bin width = "<<h1_posx_synradp->GetXaxis()->GetBinWidth(1)<<" [cm]"<<endl;
	cout<<" - h1_posx_synrad3d bin width = "<<h1_posx_synrad3d->GetXaxis()->GetBinWidth(1)<<" [cm]"<<endl;
	cout<<" - h1_posx_synradg4 bin width = "<<h1_posx_synradg4->GetXaxis()->GetBinWidth(1)<<" [cm]"<<endl;
	cout<<" - h1_posx_synradrl bin width = "<<h1_posx_synradrl->GetXaxis()->GetBinWidth(1)<<" [cm]"<<endl;

	h1_posx_synradp->SetLineWidth(4);
	h1_posx_synrad3d->SetLineWidth(3);
	h1_posx_synradg4->SetLineWidth(1);
	h1_posx_synradrl->SetLineWidth(1);

	h1_posx_synradp->SetLineColor(kBlack);
	h1_posx_synrad3d->SetLineColor(kBlue);
	h1_posx_synradg4->SetLineColor(kRed);
	h1_posx_synradrl->SetLineColor(kGreen+2);

	h1_posx_synrad3d->SetFillStyle(3345);
	h1_posx_synrad3d->SetFillColorAlpha(kBlue,0.2);
	h1_posx_synradg4->SetFillColorAlpha(kRed,0.2);
	h1_posx_synradrl->SetFillColorAlpha(kGreen+2,0.2);

	h1_posx_synradp->GetXaxis()->SetRangeUser(-40,-30);
	h1_posx_synradp->GetXaxis()->SetTitle("X_{#gamma} [cm]");
	h1_posx_synradp->SetMinimum(1e11);
	h1_posx_synradp->SetMaximum(1e20);

	h1_posx_synradp->Draw("HIST");
	h1_posx_synrad3d->Draw("SAME & HIST");
	h1_posx_synradg4->Draw("SAME & HIST");
	h1_posx_synradrl->Draw("SAME & HIST");

	TLegend* leg_posx = new TLegend(0.6,0.7,0.9,0.9);
	leg_posx->AddEntry(h1_posx_synradp,"Synrad+","f");
	leg_posx->AddEntry(h1_posx_synrad3d,"Synrad3D","f");
	leg_posx->AddEntry(h1_posx_synradg4,"SynradG4","f");
	leg_posx->AddEntry(h1_posx_synradrl,"Geant4-rel.","f");
	leg_posx->Draw();

	gPad->SetGrid();
	gPad->SetLogy();

	//-- posy
	c1->cd(5);

	h1_posy_synradp->Rebin(1);
	h1_posy_synrad3d->Rebin(1);
	h1_posy_synradg4->Rebin(1);
	h1_posy_synradrl->Rebin(1);
	cout<<"[INFO] X binning:"<<endl;
	cout<<" - h1_posy_synradp bin width = "<<h1_posy_synradp->GetXaxis()->GetBinWidth(1)<<" [cm]"<<endl;
	cout<<" - h1_posy_synrad3d bin width = "<<h1_posy_synrad3d->GetXaxis()->GetBinWidth(1)<<" [cm]"<<endl;
	cout<<" - h1_posy_synradg4 bin width = "<<h1_posy_synradg4->GetXaxis()->GetBinWidth(1)<<" [cm]"<<endl;
	cout<<" - h1_posy_synradrl bin width = "<<h1_posy_synradrl->GetXaxis()->GetBinWidth(1)<<" [cm]"<<endl;

	h1_posy_synradp->SetLineWidth(4);
	h1_posy_synrad3d->SetLineWidth(3);
	h1_posy_synradg4->SetLineWidth(1);
	h1_posy_synradrl->SetLineWidth(1);

	h1_posy_synradp->SetLineColor(kBlack);
	h1_posy_synrad3d->SetLineColor(kBlue);
	h1_posy_synradg4->SetLineColor(kRed);
	h1_posy_synradrl->SetLineColor(kGreen+2);

	h1_posy_synrad3d->SetFillStyle(3345);
	h1_posy_synrad3d->SetFillColorAlpha(kBlue,0.2);
	h1_posy_synradg4->SetFillColorAlpha(kRed,0.2);
	h1_posy_synradrl->SetFillColorAlpha(kGreen+2,0.2);

	h1_posy_synradp->GetXaxis()->SetRangeUser(-1.5,-1.5);
	h1_posy_synradp->GetXaxis()->SetTitle("Y_{#gamma} [cm]");
	h1_posy_synradp->SetMinimum(1e11);
	h1_posy_synradp->SetMaximum(1e20);

	h1_posy_synradp->Draw("HIST");
	h1_posy_synrad3d->Draw("SAME & HIST");
	h1_posy_synradg4->Draw("SAME & HIST");
	h1_posy_synradrl->Draw("SAME & HIST");

	TLegend* leg_posy = new TLegend(0.6,0.7,0.9,0.9);
	leg_posy->AddEntry(h1_posy_synradp,"Synrad+","f");
	leg_posy->AddEntry(h1_posy_synrad3d,"Synrad3D","f");
	leg_posy->AddEntry(h1_posy_synradg4,"SynradG4","f");
	leg_posy->AddEntry(h1_posy_synradrl,"Geant4-rel.","f");
	leg_posy->Draw();

	gPad->SetGrid();
	gPad->SetLogy();

	//-- posz
	c1->cd(6);

	h1_posz_synradp->Rebin(1);
	h1_posz_synrad3d->Rebin(1);
	h1_posz_synradg4->Rebin(1);
	h1_posz_synradrl->Rebin(1);
	cout<<"[INFO] X binning:"<<endl;
	cout<<" - h1_posz_synradp bin width = "<<h1_posz_synradp->GetXaxis()->GetBinWidth(1)<<" [cm]"<<endl;
	cout<<" - h1_posz_synrad3d bin width = "<<h1_posz_synrad3d->GetXaxis()->GetBinWidth(1)<<" [cm]"<<endl;
	cout<<" - h1_posz_synradg4 bin width = "<<h1_posz_synradg4->GetXaxis()->GetBinWidth(1)<<" [cm]"<<endl;
	cout<<" - h1_posz_synradrl bin width = "<<h1_posz_synradrl->GetXaxis()->GetBinWidth(1)<<" [cm]"<<endl;

	h1_posz_synradp->SetLineWidth(4);
	h1_posz_synrad3d->SetLineWidth(3);
	h1_posz_synradg4->SetLineWidth(1);
	h1_posz_synradrl->SetLineWidth(1);

	h1_posz_synradp->SetLineColor(kBlack);
	h1_posz_synrad3d->SetLineColor(kBlue);
	h1_posz_synradg4->SetLineColor(kRed);
	h1_posz_synradrl->SetLineColor(kGreen+2);

	h1_posz_synrad3d->SetFillStyle(3345);
	h1_posz_synrad3d->SetFillColorAlpha(kBlue,0.2);
	h1_posz_synradg4->SetFillColorAlpha(kRed,0.2);
	h1_posz_synradrl->SetFillColorAlpha(kGreen+2,0.2);

	h1_posz_synradp->GetXaxis()->SetRangeUser(39e2,46e2);
	h1_posz_synradp->GetXaxis()->SetTitle("Z_{#gamma} [cm]");
	h1_posz_synradp->SetMinimum(1e11);
	h1_posz_synradp->SetMaximum(1e20);

	h1_posz_synradp->Draw("HIST");
	h1_posz_synrad3d->Draw("SAME & HIST");
	h1_posz_synradg4->Draw("SAME & HIST");
	h1_posz_synradrl->Draw("SAME & HIST");

	TLegend* leg_posz = new TLegend(0.6,0.7,0.9,0.9);
	leg_posz->AddEntry(h1_posz_synradp,"Synrad+","f");
	leg_posz->AddEntry(h1_posz_synrad3d,"Synrad3D","f");
	leg_posz->AddEntry(h1_posz_synradg4,"SynradG4","f");
	leg_posz->AddEntry(h1_posz_synradrl,"Geant4-rel.","f");
	leg_posz->Draw();

	gPad->SetGrid();
	gPad->SetLogy();

	c1->SaveAs("./pics/c1.png");

	//=========================================================================================//
	//=========================================================================================//
	//=========================================================================================//
	//=========================================================================================//
	//=========================================================================================//
	//=========================================================================================//
	//=========================================================================================//
	//=========================================================================================//
	// vertex
	TCanvas* cc0 = new TCanvas("cc0","cc0",900,900);
	cc0->cd();

	h2_ene_synradp->Rebin(10);
	h2_ene_synrad3d->Rebin(10);
	h2_ene_synradg4->Rebin(10);
	h2_ene_synradrl->Rebin(10);
	cout<<"[INFO] Energy binning:"<<endl;
	cout<<" - h2_ene_synradp bin width = "<<h2_ene_synradp->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<" - h2_ene_synrad3d bin width = "<<h2_ene_synrad3d->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<" - h2_ene_synradg4 bin width = "<<h2_ene_synradg4->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<" - h2_ene_synradrl bin width = "<<h2_ene_synradrl->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;

	h2_ene_synradp->SetLineWidth(4);
	h2_ene_synrad3d->SetLineWidth(3);
	h2_ene_synradg4->SetLineWidth(1);
	h2_ene_synradrl->SetLineWidth(1);

	h2_ene_synradp->SetLineColor(kBlack);
	h2_ene_synrad3d->SetLineColor(kBlue);
	h2_ene_synradg4->SetLineColor(kRed);
	h2_ene_synradrl->SetLineColor(kGreen+2);

	h2_ene_synrad3d->SetFillStyle(3345);
	h2_ene_synrad3d->SetFillColorAlpha(kBlue,0.2);
	h2_ene_synradg4->SetFillColorAlpha(kRed,0.2);
	h2_ene_synradrl->SetFillColorAlpha(kGreen+2,0.2);

	h2_ene_synradp->GetXaxis()->SetRangeUser(0,10e3);
	h2_ene_synradp->SetMinimum(1e10);
	h2_ene_synradp->SetMaximum(1e19);

	h2_ene_synradp->Draw("HIST");
	h2_ene_synrad3d->Draw("SAME & HIST");
	h2_ene_synradg4->Draw("SAME & HIST");
	h2_ene_synradrl->Draw("SAME & HIST");

	TLegend* legg0 = new TLegend(0.6,0.7,0.9,0.9);
	legg0->AddEntry(h2_ene_synradp,"Synrad+","f");
	legg0->AddEntry(h2_ene_synrad3d,"Synrad3D","f");
	legg0->AddEntry(h2_ene_synradg4,"SynradG4","f");
	legg0->AddEntry(h2_ene_synradrl,"Geant4-rel.","f");
	legg0->Draw();

	gPad->SetGrid();
	gPad->SetLogy();

	cc0->SaveAs("./pics/cc0.png");

	//=========================================================================================//
	TCanvas* cc1 = new TCanvas("cc1","cc1",1800,900);
	cc1->Divide(3,2);

	//-- dirx
	cc1->cd(1);

	h2_dirx_synradp->Rebin(1000);
	h2_dirx_synrad3d->Rebin(1000);
	h2_dirx_synradg4->Rebin(1000);
	h2_dirx_synradrl->Rebin(1000);
	cout<<"[INFO] X' binning:"<<endl;
	cout<<" - h2_dirx_synradp bin width = "<<h2_dirx_synradp->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<" - h2_dirx_synrad3d bin width = "<<h2_dirx_synrad3d->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<" - h2_dirx_synradg4 bin width = "<<h2_dirx_synradg4->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<" - h2_dirx_synradrl bin width = "<<h2_dirx_synradrl->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;

	h2_dirx_synradp->SetLineWidth(4);
	h2_dirx_synrad3d->SetLineWidth(3);
	h2_dirx_synradg4->SetLineWidth(1);
	h2_dirx_synradrl->SetLineWidth(1);

	h2_dirx_synradp->SetLineColor(kBlack);
	h2_dirx_synrad3d->SetLineColor(kBlue);
	h2_dirx_synradg4->SetLineColor(kRed);
	h2_dirx_synradrl->SetLineColor(kGreen+2);

	h2_dirx_synrad3d->SetFillStyle(3345);
	h2_dirx_synrad3d->SetFillColorAlpha(kBlue,0.2);
	h2_dirx_synradg4->SetFillColorAlpha(kRed,0.2);
	h2_dirx_synradrl->SetFillColorAlpha(kGreen+2,0.2);

	h2_dirx_synradp->GetXaxis()->SetRangeUser(-0.015,0.005);
	h2_dirx_synradp->SetMinimum(1e11);
	h2_dirx_synradp->SetMaximum(1e20);

	h2_dirx_synradp->Draw("HIST");
	h2_dirx_synrad3d->Draw("SAME & HIST");
	h2_dirx_synradg4->Draw("SAME & HIST");
	h2_dirx_synradrl->Draw("SAME & HIST");

	TLegend* legg_dirx = new TLegend(0.2,0.7,0.5,0.9);
	legg_dirx->AddEntry(h2_dirx_synradp,"Synrad+","f");
	legg_dirx->AddEntry(h2_dirx_synrad3d,"Synrad3D","f");
	legg_dirx->AddEntry(h2_dirx_synradg4,"SynradG4","f");
	legg_dirx->AddEntry(h2_dirx_synradrl,"Geant4-rel.","f");
	legg_dirx->Draw();

	gPad->SetGrid();
	gPad->SetLogy();

	//-- diry
	cc1->cd(2);

	h2_diry_synradp->Rebin(100);
	h2_diry_synrad3d->Rebin(100);
	h2_diry_synradg4->Rebin(100);
	h2_diry_synradrl->Rebin(100);
	cout<<"[INFO] Y' binning:"<<endl;
	cout<<" - h2_diry_synradp bin width = "<<h2_diry_synradp->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<" - h2_diry_synrad3d bin width = "<<h2_diry_synrad3d->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<" - h2_diry_synradg4 bin width = "<<h2_diry_synradg4->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<" - h2_diry_synradrl bin width = "<<h2_diry_synradrl->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;

	h2_diry_synradp->SetLineWidth(4);
	h2_diry_synrad3d->SetLineWidth(3);
	h2_diry_synradg4->SetLineWidth(1);
	h2_diry_synradrl->SetLineWidth(1);

	h2_diry_synradp->SetLineColor(kBlack);
	h2_diry_synrad3d->SetLineColor(kBlue);
	h2_diry_synradg4->SetLineColor(kRed);
	h2_diry_synradrl->SetLineColor(kGreen+2);

	h2_diry_synrad3d->SetFillStyle(3345);
	h2_diry_synrad3d->SetFillColorAlpha(kBlue,0.2);
	h2_diry_synradg4->SetFillColorAlpha(kRed,0.2);
	h2_diry_synradrl->SetFillColorAlpha(kGreen+2,0.2);

	h2_diry_synradp->GetXaxis()->SetRangeUser(-0.0005,0.0005);
	h2_diry_synradp->SetMinimum(1e11);
	h2_diry_synradp->SetMaximum(1e20);

	h2_diry_synradp->Draw("HIST");
	h2_diry_synrad3d->Draw("SAME & HIST");
	h2_diry_synradg4->Draw("SAME & HIST");
	h2_diry_synradrl->Draw("SAME & HIST");

	TLegend* legg_diry = new TLegend(0.1,0.7,0.4,0.9);
	legg_diry->AddEntry(h2_diry_synradp,"Synrad+","f");
	legg_diry->AddEntry(h2_diry_synrad3d,"Synrad3D","f");
	legg_diry->AddEntry(h2_diry_synradg4,"SynradG4","f");
	legg_diry->AddEntry(h2_diry_synradg4,"Geant4-rel.","f");
	legg_diry->Draw();

	gPad->SetGrid();
	gPad->SetLogy();

	//-- dirz
	cc1->cd(3);

	h2_dirz_synradp->Rebin(1000);
	h2_dirz_synrad3d->Rebin(1000);
	h2_dirz_synradg4->Rebin(1000);
	h2_dirz_synradrl->Rebin(1000);
	cout<<"[INFO] Z' binning:"<<endl;
	cout<<" - h2_dirz_synradp bin width = "<<h2_dirz_synradp->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<" - h2_dirz_synrad3d bin width = "<<h2_dirz_synrad3d->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<" - h2_dirz_synradg4 bin width = "<<h2_dirz_synradg4->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;
	cout<<" - h2_dirz_synradrl bin width = "<<h2_dirz_synradrl->GetXaxis()->GetBinWidth(1)<<" [eV]"<<endl;

	h2_dirz_synradp->SetLineWidth(4);
	h2_dirz_synrad3d->SetLineWidth(3);
	h2_dirz_synradg4->SetLineWidth(1);
	h2_dirz_synradrl->SetLineWidth(1);

	h2_dirz_synradp->SetLineColor(kBlack);
	h2_dirz_synrad3d->SetLineColor(kBlue);
	h2_dirz_synradg4->SetLineColor(kRed);
	h2_dirz_synradrl->SetLineColor(kGreen+2);

	h2_dirz_synrad3d->SetFillStyle(3345);
	h2_dirz_synrad3d->SetFillColorAlpha(kBlue,0.2);
	h2_dirz_synradg4->SetFillColorAlpha(kRed,0.2);
	h2_dirz_synradrl->SetFillColorAlpha(kGreen+2,0.2);

	h2_dirz_synradp->GetXaxis()->SetRangeUser(0.9998,1.00005);
	h2_dirz_synradp->SetMinimum(1e11);
	h2_dirz_synradp->SetMaximum(1e20);

	h2_dirz_synradp->Draw("HIST");
	h2_dirz_synrad3d->Draw("SAME & HIST");
	h2_dirz_synradg4->Draw("SAME & HIST");
	h2_dirz_synradrl->Draw("SAME & HIST");

	TLegend* legg_dirz = new TLegend(0.1,0.7,0.4,0.9);
	legg_dirz->AddEntry(h2_dirz_synradp,"Synrad+","f");
	legg_dirz->AddEntry(h2_dirz_synrad3d,"Synrad3D","f");
	legg_dirz->AddEntry(h2_dirz_synradg4,"SynradG4","f");
	legg_dirz->AddEntry(h2_dirz_synradrl,"Geant4-rel.","f");
	legg_dirz->Draw();

	gPad->SetGrid();
	gPad->SetLogy();

	//-- posx
	cc1->cd(4);

	h2_posx_synradp->Rebin(1);
	h2_posx_synrad3d->Rebin(1);
	h2_posx_synradg4->Rebin(1);
	h2_posx_synradrl->Rebin(1);
	cout<<"[INFO] X binning:"<<endl;
	cout<<" - h2_posx_synradp bin width = "<<h2_posx_synradp->GetXaxis()->GetBinWidth(1)<<" [cm]"<<endl;
	cout<<" - h2_posx_synrad3d bin width = "<<h2_posx_synrad3d->GetXaxis()->GetBinWidth(1)<<" [cm]"<<endl;
	cout<<" - h2_posx_synradg4 bin width = "<<h2_posx_synradg4->GetXaxis()->GetBinWidth(1)<<" [cm]"<<endl;
	cout<<" - h2_posx_synradrl bin width = "<<h2_posx_synradrl->GetXaxis()->GetBinWidth(1)<<" [cm]"<<endl;

	h2_posx_synradp->SetLineWidth(4);
	h2_posx_synrad3d->SetLineWidth(3);
	h2_posx_synradg4->SetLineWidth(1);
	h2_posx_synradrl->SetLineWidth(1);

	h2_posx_synradp->SetLineColor(kBlack);
	h2_posx_synrad3d->SetLineColor(kBlue);
	h2_posx_synradg4->SetLineColor(kRed);
	h2_posx_synradrl->SetLineColor(kGreen+2);

	h2_posx_synrad3d->SetFillStyle(3345);
	h2_posx_synrad3d->SetFillColorAlpha(kBlue,0.2);
	h2_posx_synradg4->SetFillColorAlpha(kRed,0.2);
	h2_posx_synradrl->SetFillColorAlpha(kGreen+2,0.2);

	h2_posx_synradp->GetXaxis()->SetRangeUser(-3,1);
	h2_posx_synradp->GetXaxis()->SetTitle("X_{#gamma} [cm]");
	h2_posx_synradp->SetMinimum(1e11);
	h2_posx_synradp->SetMaximum(1e20);

	h2_posx_synradp->Draw("HIST");
	h2_posx_synrad3d->Draw("SAME & HIST");
	h2_posx_synradg4->Draw("SAME & HIST");
	h2_posx_synradrl->Draw("SAME & HIST");

	TLegend* legg_posx = new TLegend(0.6,0.7,0.9,0.9);
	legg_posx->AddEntry(h2_posx_synradp,"Synrad+","f");
	legg_posx->AddEntry(h2_posx_synrad3d,"Synrad3D","f");
	legg_posx->AddEntry(h2_posx_synradg4,"SynradG4","f");
	legg_posx->AddEntry(h2_posx_synradrl,"Geant4-rel.","f");
	legg_posx->Draw();

	gPad->SetGrid();
	gPad->SetLogy();

	//-- posy
	cc1->cd(5);

	h2_posy_synradp->Rebin(1);
	h2_posy_synrad3d->Rebin(1);
	h2_posy_synradg4->Rebin(1);
	h2_posy_synradrl->Rebin(1);
	cout<<"[INFO] X binning:"<<endl;
	cout<<" - h2_posy_synradp bin width = "<<h2_posy_synradp->GetXaxis()->GetBinWidth(1)<<" [cm]"<<endl;
	cout<<" - h2_posy_synrad3d bin width = "<<h2_posy_synrad3d->GetXaxis()->GetBinWidth(1)<<" [cm]"<<endl;
	cout<<" - h2_posy_synradg4 bin width = "<<h2_posy_synradg4->GetXaxis()->GetBinWidth(1)<<" [cm]"<<endl;
	cout<<" - h2_posy_synradrl bin width = "<<h2_posy_synradrl->GetXaxis()->GetBinWidth(1)<<" [cm]"<<endl;

	h2_posy_synradp->SetLineWidth(4);
	h2_posy_synrad3d->SetLineWidth(3);
	h2_posy_synradg4->SetLineWidth(1);
	h2_posy_synradrl->SetLineWidth(1);

	h2_posy_synradp->SetLineColor(kBlack);
	h2_posy_synrad3d->SetLineColor(kBlue);
	h2_posy_synradg4->SetLineColor(kRed);
	h2_posy_synradrl->SetLineColor(kGreen+2);

	h2_posy_synrad3d->SetFillStyle(3345);
	h2_posy_synrad3d->SetFillColorAlpha(kBlue,0.2);
	h2_posy_synradg4->SetFillColorAlpha(kRed,0.2);
	h2_posy_synradrl->SetFillColorAlpha(kGreen+2,0.2);

	h2_posy_synradp->GetXaxis()->SetRangeUser(-0.01,0.01);
	h2_posy_synradp->GetXaxis()->SetTitle("Y_{#gamma} [cm]");
	h2_posy_synradp->SetMinimum(1e11);
	h2_posy_synradp->SetMaximum(1e20);

	h2_posy_synradp->Draw("HIST");
	h2_posy_synrad3d->Draw("SAME & HIST");
	h2_posy_synradg4->Draw("SAME & HIST");
	h2_posy_synradrl->Draw("SAME & HIST");

	TLegend* legg_posy = new TLegend(0.6,0.7,0.9,0.9);
	legg_posy->AddEntry(h2_posy_synradp,"Synrad+","f");
	legg_posy->AddEntry(h2_posy_synrad3d,"Synrad3D","f");
	legg_posy->AddEntry(h2_posy_synradg4,"SynradG4","f");
	legg_posy->AddEntry(h2_posy_synradrl,"Geant4-rel.","f");
	legg_posy->Draw();

	gPad->SetGrid();
	gPad->SetLogy();

	//-- posz
	cc1->cd(6);

	h2_posz_synradp->Rebin(1);
	h2_posz_synrad3d->Rebin(1);
	h2_posz_synradg4->Rebin(1);
	h2_posz_synradrl->Rebin(1);
	cout<<"[INFO] X binning:"<<endl;
	cout<<" - h2_posz_synradp bin width = "<<h2_posz_synradp->GetXaxis()->GetBinWidth(1)<<" [cm]"<<endl;
	cout<<" - h2_posz_synrad3d bin width = "<<h2_posz_synrad3d->GetXaxis()->GetBinWidth(1)<<" [cm]"<<endl;
	cout<<" - h2_posz_synradg4 bin width = "<<h2_posz_synradg4->GetXaxis()->GetBinWidth(1)<<" [cm]"<<endl;
	cout<<" - h2_posz_synradrl bin width = "<<h2_posz_synradrl->GetXaxis()->GetBinWidth(1)<<" [cm]"<<endl;

	h2_posz_synradp->SetLineWidth(4);
	h2_posz_synrad3d->SetLineWidth(3);
	h2_posz_synradg4->SetLineWidth(1);
	h2_posz_synradrl->SetLineWidth(1);

	h2_posz_synradp->SetLineColor(kBlack);
	h2_posz_synrad3d->SetLineColor(kBlue);
	h2_posz_synradg4->SetLineColor(kRed);
	h2_posz_synradrl->SetLineColor(kGreen+2);

	h2_posz_synrad3d->SetFillStyle(3345);
	h2_posz_synrad3d->SetFillColorAlpha(kBlue,0.2);
	h2_posz_synradg4->SetFillColorAlpha(kRed,0.2);
	h2_posz_synradrl->SetFillColorAlpha(kGreen+2,0.2);

	h2_posz_synradp->GetXaxis()->SetRangeUser(4.5e2,10.5e2);
	h2_posz_synradp->GetXaxis()->SetTitle("Z_{#gamma} [cm]");
	h2_posz_synradp->SetMinimum(1e11);
	h2_posz_synradp->SetMaximum(1e20);

	h2_posz_synradp->Draw("HIST");
	h2_posz_synrad3d->Draw("SAME & HIST");
	h2_posz_synradg4->Draw("SAME & HIST");
	h2_posz_synradrl->Draw("SAME & HIST");

	TLegend* legg_posz = new TLegend(0.6,0.7,0.9,0.9);
	legg_posz->AddEntry(h2_posz_synradp,"Synrad+","f");
	legg_posz->AddEntry(h2_posz_synrad3d,"Synrad3D","f");
	legg_posz->AddEntry(h2_posz_synradg4,"SynradG4","f");
	legg_posz->AddEntry(h2_posz_synradrl,"Geant4-rel.","f");
	legg_posz->Draw();

	gPad->SetGrid();
	gPad->SetLogy();

	cc1->SaveAs("./pics/cc1.png");
	//=========================================================================================//
/**/
	return;
}
