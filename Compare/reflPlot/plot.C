{
	const Int_t nDeg = 11;
	Float_t deg[nDeg] = {0.1,0.2,0.4,0.5,0.6,0.8,1.0,1.5,2.0,2.5,90.0};
	TGraph* gr[nDeg];

	TCanvas* c0 = new TCanvas("c0","c0",900,900);
	c0->cd();
	TPad* p0 = new TPad("p0","p0",0,0,1,1);
   	p0->SetTopMargin(0.1);
	p0->SetBottomMargin(0.14);
	p0->SetLeftMargin(0.14);
	p0->SetRightMargin(0.2);
	p0->Draw();
	p0->cd();

	Int_t markerColor[nDeg] = {1,2,3,4,5,6,7,8,9,40,41};

	TLegend* leg0 = new TLegend(0.81,0.14,0.99,0.9);
	
	for(Int_t i = 0; i < nDeg; i++)
	{
		TString fName = Form("%.1f.txt",deg[i]);
		gr[i] = new TGraph(fName.Data());

		gr[i]->SetMarkerStyle(20);
		gr[i]->SetMarkerSize(0.7);
		gr[i]->SetMarkerColor(markerColor[i]);
		
		gr[i]->SetMinimum(0);
		gr[i]->SetMaximum(1);
		gr[i]->GetXaxis()->SetRangeUser(0,20e3);

		gr[i]->GetYaxis()->SetLabelSize(0.04);
		gr[i]->GetXaxis()->SetLabelSize(0.04);
		gr[i]->GetYaxis()->SetTitleSize(0.04);
		gr[i]->GetXaxis()->SetTitleSize(0.04);
		gr[i]->GetYaxis()->SetTitleOffset(1.6);
		gr[i]->GetXaxis()->SetTitleOffset(1.2);
		gr[i]->GetYaxis()->SetNdivisions(5);
		gr[i]->GetXaxis()->SetNdivisions(5);
		gr[i]->SetTitle("");
		gr[i]->GetYaxis()->SetTitle("Reflectivity [arb. unit]");
		gr[i]->GetXaxis()->SetTitle("E_{#gamma} [eV]");
	
		if(i == 0){gr[i]->Draw("APL");}
		else{gr[i]->Draw("SAME & PL");}

		leg0->AddEntry(gr[i],Form("%.1f",deg[i]),"pl");
	}
	leg0->Draw();

	TLatex *t = new TLatex(21000,1.03,"#theta_{graz.} [deg]");
	t->SetTextFont(42);
	t->SetTextSize(0.04);
   	t->Draw();

	c0->SaveAs("Reflectivity.pdf");

}
