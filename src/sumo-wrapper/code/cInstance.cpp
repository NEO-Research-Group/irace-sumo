#include "cInstance.hpp"
#include <fstream>
#include <cassert>

using namespace std;

cInstance::cInstance()
{}

cInstance::cInstance(string fileInput)
{
	this->read(fileInput);
}

cInstance::~cInstance()
{}

string cInstance::getPath() const
{
	return _path;
}

string cInstance::getName() const
{
	return _name;
}

unsigned cInstance::getNumberOfTLlogics() const
{
	return _nTLlogics; // This number should be the same to _phases.size()
}

unsigned cInstance::getTotalNumberOfPhases() const
{
	return _nPhases;
}
string cInstance::getTLID(unsigned position) const // From 0 to getNumberOfTLlogics()-1
{
	if(position < _phases.size())
		return _phases[position].id;
	else
		return "";
}
vector<string> cInstance::getPhases(unsigned position) const
{
	vector<string> v;
	if(position < _phases.size())
		return _phases[position].phases;
	else
		return v;
}
/*
unsigned cInstance::getNumberOfVehicles() const
{
	return _nVehicles;
}
*/
unsigned cInstance::getSimulationTime() const
{
	return _time;
}

#include <algorithm>
static string dirname(string source)
{
    if (source.length() <= 1) {
        return source;
    }
    if (source.back() == '/') { //Remove trailing slash if it exists.
        source.pop_back();
    }
    source.erase(std::find(source.rbegin(), source.rend(), '/').base(), 
                 source.end());
    return source;
}

bool cInstance::read(string fileInput)
{
    ifstream fin(fileInput.c_str());
    
    if(!fin.good()) return false;
    
    const char * instancepath = realpath(fileInput.c_str(), NULL);
    string path (instancepath);
    path = dirname(path);
    getline(fin, _name);
    getline(fin, _path);
    _path = path + '/' + _path;
    string linestr;
    // Coordinates? Make this optional.
    getline(fin, linestr);
    getline(fin, linestr);
    fin >> _nTLlogics;
    fin >> _nPhases;
    assert(_nTLlogics > 0 && _nTLlogics < 200);
    assert(_nPhases > 0 && _nPhases < 1000);
    
    for (unsigned i = 0; i < _nTLlogics; i++) {
        unsigned phases_per_tl;
        string phase;
        tTL tl;
        double coord;
        fin >> tl.id;
        // Skip coordinates.
        fin >> coord;
        fin >> coord;
        fin >> phases_per_tl;
        assert(phases_per_tl > 0);
        assert(phases_per_tl < 100);
        tl.phases.clear();
        for(unsigned j = 0; j < phases_per_tl; j++)
        {
            fin >> phase;
            tl.phases.push_back(phase);
        }	
        _phases.push_back(tl);
    }

    /* This value is ignored. We use the value from the route file */
    fin >> _nVehicles;
    _nVehicles = 0;
    fin >> _time;
    
    fin.close();
    return true;
}


ostream &operator << (ostream &os,const cInstance &i)
{
	vector<string> phases;
	os << "Instance name: " << i.getName() << endl;
	os << "Path: " << i.getPath() << endl;
	os << "Number of TL logics: " << i.getNumberOfTLlogics() << endl;
	os << "Total Number of Phases: " << i.getTotalNumberOfPhases() << endl;
	os << "TL Phases: " << endl;
	for(int j = 0; j < i.getNumberOfTLlogics(); j++)
	{
		cout << "\t ID: " << i.getTLID(j) << " - ";
		phases = i.getPhases(j);
		for(int k = 0; k < phases.size(); k++)
			cout << phases[k] << " ";
		cout << endl;
	}
        //	os << "Number of Vehicles: " << i.getNumberOfVehicles() << endl;
	os << "Simulation time: " << i.getSimulationTime() << endl;

	return os;
}
