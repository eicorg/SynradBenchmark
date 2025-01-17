#include "RunAction.hh"

RunAction::RunAction(G4String xmlFileName, G4long seed) : _xml_filename(xmlFileName), _seed(seed)
{
	// default value
   	_output_filename = "output.root";

    	timer = new G4Timer;
    	fRunMessenger = new RunMessenger(this);
}

RunAction::~RunAction()
{
    	delete timer;
    	delete fRunMessenger;
}

void RunAction::BeginOfRunAction(const G4Run* run)
{	
	G4cout<<"\n\n=================================================================="<<G4endl;
	G4cout<<"[INFO] RunAction::BeginOfRunAction"<<G4endl;
	G4cout<<"Output ROOT file name: "<<_output_filename<<G4endl;
	G4cout<<"==================================================================\n\n"<<G4endl;

    	timer->Start();

	_hfile = new TFile(_output_filename.c_str(), "RECREATE");
    	if(_hfile->IsZombie())
		throw runtime_error("\n\n[ERROR] RunAction::EndOfRunAction ==> Cannot open the file to write\n");
	_hfile->cd();

    	_tree = new TTree("tree", "Collected Data");
    	_tree->Branch("event",		&_event);

    	_tree->Branch("beamPdg",	&_beamPdg);
    	_tree->Branch("beamPosX_cm",	&_beamPosX);
    	_tree->Branch("beamPosY_cm",	&_beamPosY);
    	_tree->Branch("beamPosZ_cm",	&_beamPosZ);
    	_tree->Branch("beamMomX_eV",	&_beamMomX);
    	_tree->Branch("beamMomY_eV",	&_beamMomY);
    	_tree->Branch("beamMomZ_eV",	&_beamMomZ);
    	_tree->Branch("beamEnergy_eV",	&_beamEnergy);
	_tree->Branch("beamKillPosX_cm",	&_beamKillPosX);
    	_tree->Branch("beamKillPosY_cm",	&_beamKillPosY);
    	_tree->Branch("beamKillPosZ_cm",	&_beamKillPosZ);

    	_tree->Branch("gammaVtxPosX_cm",	&_gammaVtxPosX);
    	_tree->Branch("gammaVtxPosY_cm",	&_gammaVtxPosY);
    	_tree->Branch("gammaVtxPosZ_cm",	&_gammaVtxPosZ);
    	_tree->Branch("gammaVtxDirX",		&_gammaVtxDirX);
    	_tree->Branch("gammaVtxDirY",		&_gammaVtxDirY);
    	_tree->Branch("gammaVtxDirZ",		&_gammaVtxDirZ);

    	_tree->Branch("gammaPostPV",	&_gammaPostPV);
    	_tree->Branch("gammaPrePV",	&_gammaPrePV);
    	_tree->Branch("gammaPosX_cm",	&_gammaPosX);
    	_tree->Branch("gammaPosY_cm",	&_gammaPosY);
    	_tree->Branch("gammaPosZ_cm",	&_gammaPosZ);
    	_tree->Branch("gammaMomX_eV",	&_gammaMomX);
    	_tree->Branch("gammaMomY_eV",	&_gammaMomY);
    	_tree->Branch("gammaMomZ_eV",	&_gammaMomZ);
    	_tree->Branch("gammaEnergy_eV",	&_gammaEnergy);
    	_tree->Branch("gammaTime_ms",	&_gammaTime);

	_avgEventTime = 0;

	_xml = new TTree("xml", "Simulation settings from the XML file");
	_xml->Branch("settings",	&_settings); 
    	_xml->Branch("seed",		&_seed);

	DumpXmlFile();

	return;
}

void RunAction::EndOfRunAction(const G4Run* run)
{
    	if(_hfile->IsZombie())
		throw runtime_error("\n\n[ERROR] RunAction::EndOfRunAction ==> Cannot open the file to write\n");

	_hfile->cd();
    	_xml->Write();
    	_tree->Write();

    	delete _hfile;

    	timer->Stop();

	G4cout<<"\n\n=================================================================="<<G4endl;
    	G4cout<<"[INFO] RunAction::EndOfRunAction"<<G4endl;
	G4cout<<"Output ROOT file name: "<<_output_filename<<G4endl;
    	G4cout<<"Run time: "<<*timer<<G4endl;
	G4cout<<"Avg. event time: "<<_avgEventTime/run->GetNumberOfEvent()<<" [sec]"<<G4endl;
	G4cout<<"==================================================================\n\n"<<G4endl;

	return;
}

void RunAction::DumpXmlFile()
{
    	fstream in_file;

    	// open a file to perform read operation using file object.
    	in_file.open(_xml_filename.c_str(), ios::in); 
    
    	// Checking whether the file is open.
    	if (in_file.is_open()) 
	{ 
        	string sa;
    		_settings = _xml_filename + "\n";
        	// Read data from the file object and put it into a string.
        	while (getline(in_file, sa)) 
		{ 
            		// Print the data of the string.
            		_settings += sa + "\n"; 
        	}
		_xml->Fill();
        	// Close the file object.
        	in_file.close(); 
	}
	else
	{
		G4cout<<"\n\n=================================================================="<<G4endl;
		G4cout<<"[WARNING] RunAction::DumpXmlFile ==> Cannot find or open the XML file: "<<_xml_filename<<G4endl;
		G4cout<<"==================================================================\n\n"<<G4endl;
	}

	return;
}
