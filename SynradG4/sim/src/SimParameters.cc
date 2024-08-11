#include "SimParameters.hh"  
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <sys/stat.h>

using namespace boost::property_tree;

SimParameters::SimParameters()
{}    	

SimParameters::~SimParameters()
{}

void SimParameters::ReadXML(G4String fName)
{
    	// Create empty property tree object
    	ptree tree;

    	// Parse the XML into the property tree.
	if(!FileExists(fName)){return;}
    	read_xml(fName, tree);

    	// Use get_child to find the node containing the a specific data, and iterate over
    	// its children. If the path cannot be resolved, get_child throws.
    	// A C++11 for-range loop would also work.


	// SR model
	BOOST_FOREACH(ptree::value_type &child_node, tree.get_child("xml.srmodel"))
	{
		// The data function is used to access the data stored in a node.
		if(child_node.second.get<string>("<xmlattr>.name") == "type")
			SetReflType(stoi(child_node.second.data()));
		else if(child_node.second.get<string>("<xmlattr>.name") == "print")
			SetReflPrint(stoi(child_node.second.data()));
		else if(child_node.second.get<string>("<xmlattr>.name") == "sigma" &&
			child_node.second.get<string>("<xmlattr>.unit") == "")
			SetSigmaRatio(stod(child_node.second.data()));	
		else if(child_node.second.get<string>("<xmlattr>.name") == "roughness" &&
			child_node.second.get<string>("<xmlattr>.unit") == "m")
			SetSurfRoughness(stod(child_node.second.data())*m);
		else if(child_node.second.get<string>("<xmlattr>.name") == "corrlength" &&
			child_node.second.get<string>("<xmlattr>.unit") == "m")
			SetAutoCorrLength(stod(child_node.second.data())*m);
		else
			throw runtime_error("[ERROR] SimParameters::ReadXML ==> Bad XML data\n");
	}
	
	return;
}

G4bool SimParameters::FileExists(const G4String& fName) 
{
  	struct stat buffer;   
  	return (stat (fName.c_str(), &buffer) == 0); 
}

void SimParameters::InitDefault()
{
	_reflType = 3;
	_reflPrint = true;
	_sigmaRatio = 5e-3;
	_surfaceRoughness = 50e-9*m;
	_autoCorrLength = 10000e-9*m;

	return;
}

void SimParameters::PrintSRprocParameters()
{
	G4cout<<"\n\n=================================================================="<<G4endl;
	G4cout<<"[INFO] SimParameters::PrintSRprocParameters"<<G4endl;
	G4cout<<" SR photon reflection type = "<<GetReflType()<<G4endl;
	G4cout<<" 	0 - Geant4 (Xray,Névot-Croce)"<<G4endl;
	G4cout<<" 	1 - Synrad+ (Gamma,Debye-Waller)"<<G4endl;
	G4cout<<" 	2 - Synrad+ (Gamma,perturb norm - old model)"<<G4endl;
	G4cout<<" 	3 - Synrad+ (Gamma,Debye-Waller,perturb refl - new model)"<<G4endl;
	G4cout<<" Print surface material data = "<<GetReflPrint()<<G4endl;
	G4cout<<" 	0 - no"<<G4endl;
	G4cout<<" 	1 - yes"<<G4endl;
	G4cout<<" Sigma ratio = "<<GetSigmaRatio()<<G4endl;
	G4cout<<" Surface roughness = "<<GetSurfRoughness()/m<<" [m]"<<G4endl;
	G4cout<<" Surface autocorrelation length = "<<GetAutoCorrLength()/m<<" [m]"<<G4endl;
	G4cout<<"==================================================================\n\n"<<G4endl;

	return;
}
