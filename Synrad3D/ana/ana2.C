#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void ConvertASCIItoROOT(TString fInName, TString fOutName);

void ana2(	TString fInName = "./output/synrad3d_converted.dat",
		TString fOutName = "./output/synrad3d_converted.root")
{

	ConvertASCIItoROOT(fInName,fOutName);

	return;
}


void ConvertASCIItoROOT(TString fInName, TString fOutName)
{
	cout<<"[INFO] __"<<__FUNCTION__<<"__"<<endl;
	fstream f;
	f.open(fInName.Data(),ios::in); //open a file to perform read operation using file object
	if(f.is_open()) //checking whether the file is open
	{ 
		Int_t index;
		Float_t x_ini, y_ini, z_ini, vx_ini, vy_ini, vz_ini;
		Float_t x_fin, y_fin, z_fin, vx_fin, vy_fin, vz_fin, ene, weight;

		// Create the output file and tree
		TFile* file = new TFile(fOutName.Data(),"RECREATE");
		TTree* tree = new TTree("tree","Synrad3D data");
		// Add branches
		tree->Branch("index",	&index);
		tree->Branch("x_ini",	&x_ini);
		tree->Branch("y_ini",	&y_ini);
		tree->Branch("z_ini",	&z_ini);
		tree->Branch("vx_ini",	&vx_ini);
		tree->Branch("vy_ini",	&vy_ini);
		tree->Branch("vz_ini",	&vz_ini);
		tree->Branch("x_fin",	&x_fin);
		tree->Branch("y_fin",	&y_fin);
		tree->Branch("z_fin",	&z_fin);
		tree->Branch("vx_fin",	&vx_fin);
		tree->Branch("vy_fin",	&vy_fin);
		tree->Branch("vz_fin",	&vz_fin);
		tree->Branch("ene",	&ene);
		tree->Branch("weight",	&weight);

		string line;
		// get the header line
		getline(f,line);
		cout<<"[INFO] Header: "<<line<<endl;
		while(getline(f,line)) //read data from file object and put it into string.
		{
			// Initialise the istringstream
    			// with the given string
    			istringstream iss(line);
    			// Iterate the istringstream
    			// using do-while loop
    			while(	iss >> index >> 
				x_ini >> y_ini >> z_ini >> vx_ini >> vy_ini >> vz_ini >> 
				x_fin >> y_fin >> z_fin >> vx_fin >> vy_fin >> vz_fin >> 
				ene >> weight) 
			{
				// Fill the tree
				tree->Fill();
    			} 
      		}
		cout<<"[INFO] Num. of entries = "<<tree->GetEntries()<<endl;
      		f.close(); //close the file object.
		file->cd();
		tree->Write();
		file->Close();
		cout<<"[INFO] Output file: "<<file->GetName()<<endl;
   	}
	return;
}
