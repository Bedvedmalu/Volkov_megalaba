#include <iostream>
#include <string>
#include <fstream>
#include "pipeline.h"
#include "utils.h"


using namespace std;

int pipeline::MaxID = 1;

int pipeline::get_id()
{
	return id;
}

int pipeline::get_MaxID()
{
	return MaxID;
}

void pipeline::add_pipe() // add pipeline
{
	cout << "Choose a name for the pipeline\n";
	cin.ignore(10000, '\n');
	getline(cin, pipename);

	cout << "Choose pipe length\n";
	pipelength = verification(0, 2000);

	cout << "Choose pipe diameter\n";
	pipediameter = verification(0, 1000);

	cout << "Under repair?\n0. No\n1. Yes\n";
	piperepair = verificationbool();

	id = MaxID;
	MaxID++;
}

void pipeline::edit() // edit pipeline
{
	if (pipename != "")
	{
		cout << "Under repair?\n0. No\n1. Yes\n";
		piperepair = verificationbool();
	}
	else
	{
		cout << "Create pipeline first" << endl;
	}
}

void pipeline::show_p(const int& id)
{
	cout << "------PIPELINE------" <<
		"\nID:" << id <<
		"\nName: " << pipename <<
		"\nLength: " << pipelength <<
		"\nDiameter: " << pipediameter <<
		"\nUnder repair? " << piperepair <<
		"\n--------------------" << endl;
}

void pipeline::save_p(ofstream& fout, unordered_map<int, pipeline>& pipelines) // save pipeline
{
	string Marker = "PIPELINE";
	for (const auto& [id, p] : pipelines) {
		if (pipename == "None") fout << Marker << endl;
		else
		{
			fout << Marker << endl;
			fout << pipelines[id].pipename << endl;
			fout << pipelines[id].pipelength << endl;
			fout << pipelines[id].pipediameter << endl;
			fout << pipelines[id].piperepair << endl;
		}
	}
}

void pipeline::load_p(ifstream& fin, unordered_map<int, pipeline>& pipelines) // load pipeline
{

	string Marker;
	while (true) {

		getline(fin >> ws, Marker);

		if (fin.eof()) break;

		if (Marker != "PIPELINE") continue;


		if (!(fin >> pipelines[MaxID].pipename >> pipelines[MaxID].pipelength >> pipelines[MaxID].pipediameter >> pipelines[MaxID].piperepair)) break;

		MaxID++;
	}

}

void pipeline::search_pipename(std::unordered_set<int>& keys, const std::unordered_map<int, pipeline>& pipelines, const std::string& name) {
	for (const auto& [id, p] : pipelines) {
		if (name == p.pipename) {
			keys.insert(id);
		}
	}
}

void pipeline::search_piperepair(std::unordered_set<int>& keys, const std::unordered_map<int, pipeline>& pipelines, const bool& inrep) {
	for (const auto& [id, p] : pipelines) {
		if (inrep == p.piperepair) {
			keys.insert(id);
		}

	}
}

void pipeline::delete_searched(std::unordered_map<int, pipeline>& pipelines, const std::unordered_set<int>& keys) {
	for (const int& key : keys) {
		pipelines.erase(key);
	}
}

void pipeline::edit_searched(std::unordered_map<int, pipeline>& pipelines, const std::unordered_set<int>& keys) {
	for (const int& key : keys) {
		if (pipelines.count(key) != 0) {
			cout << "Now changing sign of repair for ID: " << key << endl;
			cin >> pipelines[key].piperepair; 
		}
	}
}

void pipeline::show_searched(std::unordered_map<int, pipeline>& pipelines, const std::unordered_set<int>& keys) {
	for (const int& key : keys) {
		cout << 
			"\nID: " << pipelines[key].id <<
			"\nName: " << pipelines[key].pipename <<
			"\nLength: " << pipelines[key].pipelength <<
			"\nDiameter " << pipelines[key].pipediameter <<
			"\nUnder repair? " << pipelines[key].piperepair <<
			 endl;
	}
}

