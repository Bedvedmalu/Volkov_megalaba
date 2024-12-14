#include <iostream>
#include <string>
#include <fstream>
#include "pipeline.h"
#include "utils.h"
#include <vector>


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
	std::cerr << pipename << std::endl;
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

void pipeline::show_p(const unordered_map<int, pipeline>& pipelines)
{
	for (const auto& [id, p] : pipelines) {
		cout << "------PIPELINE------" <<
			"\nID:" << id <<
			"\nName: " << p.pipename <<
			"\nLength: " << p.pipelength <<
			"\nDiameter: " << p.pipediameter <<
			"\nUnder repair? " << p.piperepair <<
			"\nCS id in: " << p.CS_in <<
			"\nCS id out: " << p.CS_out << 
			"\n--------------------" << endl;
	}

}

void pipeline::save_p(ofstream& fout, unordered_map<int, pipeline>& pipelines) // save pipeline
{
	string Marker = "PIPELINE";
	for (const auto& [id, p] : pipelines) {
		if (pipename == "") fout << Marker << endl;
		else
		{
			fout << Marker << endl;
			fout << id << endl;
			fout << pipelines[id].pipename << endl;
			fout << pipelines[id].pipelength << endl;
			fout << pipelines[id].pipediameter << endl;
			fout << pipelines[id].piperepair << endl;
			fout << pipelines[id].CS_in << endl;
			fout << pipelines[id].CS_out << endl;
		}
	}
}

void pipeline::load_p(ifstream& fin, unordered_map<int, pipeline>& pipelines) // load pipeline
{
	pipelines.clear();

	string Marker;
	while (true) {

		getline(fin, Marker);

		if (fin.eof()) break;

		if (Marker != "PIPELINE") continue;


		if (!(fin >> id >> pipelines[id].pipename >> pipelines[id].pipelength >> pipelines[id].pipediameter >> pipelines[id].piperepair >> pipelines[id].CS_in >> pipelines[id].CS_out)) break;

		MaxID++;
	}

}

void pipeline::search_pipename(std::unordered_set<int>& keys, const std::unordered_map<int, pipeline>& pipelines, const std::string& name) {
	for (const auto& [id, p] : pipelines) {
		if (p.pipename.find(name) != string::npos) {
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
			"\nID: " << key <<
			"\nName: " << pipelines[key].pipename <<
			"\nLength: " << pipelines[key].pipelength <<
			"\nDiameter " << pipelines[key].pipediameter <<
			"\nUnder repair? " << pipelines[key].piperepair <<
			endl;
	}
}

void pipeline::make_edges(std::unordered_map<int, pipeline>& pipelines, std::unordered_map<int, compressorstation>& css) {
	for (auto& [id, p] : pipelines) {
		/*if ((p.pipediameter != 500) && (p.pipediameter != 700) && (p.pipediameter != 1000) && (p.pipediameter != 1400)) {
			continue;
		}*/
		cout << "Enter id of pipeline out: ";
		INPUT_INT(cin, p.CS_out);
		cout << "\nEnter id of pipeline in: ";
		INPUT_INT(cin, p.CS_in);
	}
}

void pipeline::make_matrix(std::unordered_map<int, pipeline>& pipelines, const std::unordered_map<int, compressorstation>& css, unordered_map<int, unordered_set<int>>& to_sort) {
	vector<vector<int>> matrix(pipelines.size(), vector<int>(pipelines.size(),0));
	unordered_set<int> tops;
	for (const auto& [id, p] : pipelines) {
		matrix[p.CS_out-1][p.CS_in-1] = 1;
	}
	for (int i = 0; i < css.size(); i++) {
		for (int j = 0; j < css.size(); j++) {
			if (matrix[i][j] == 1) {
				tops.insert(i+1);
			}
		}
		to_sort[i] = tops;
		tops.clear();
	}
	cout << "Graph created" << endl;
}

void pipeline::visualising_graph(const unordered_map<int, pipeline>& pipelines, const string& filename) {
	ofstream file("graph.dot");
	if (!file.is_open()) {
		cerr << "Couldnt open file";
		return;
	}
	cout << "Opened" << endl;
	file << "digraph G {" << endl;
	cout << "Writing OK" << endl;
	if (pipelines.empty()) {
		cerr << "Pipelines doesnt exist" << endl;
		return;
	}

	for (const auto& [id, p] : pipelines) {
		file << "    " << p.CS_out << " -> " << p.CS_in << ";" << endl;
	}
	cout << "Zapis OK" << endl;
	file << "}" << endl;
	file.flush();
	file.close();

	string command = "\"C:\\Program Files\\Graphviz\\bin\\dot\" -Tpng graph.dot -o graph.png";
	int result = system(command.c_str());

	if (result == 0) cout << "Saved in " << filename << ".png" << endl;
	else cerr << "Couldnt save" << endl;
}