#include "compressorstation.h"
#include "utils.h"
#include <iostream>
#include <fstream>

using namespace std;

int compressorstation::MaxID = 1;

int compressorstation::get_id()
{
	return id;
}

int compressorstation::get_MaxID()
{
	return MaxID;
}

void compressorstation::add_cs() // add compressors station
{
	cin.ignore(10000, '\n');
	cout << "Choose a name for the cs\n";
	getline(cin, csname);

	cout << "Enter the number of workshops\n";
	csshop = verification(0, 1000);

	cout << "Enter the number of working workshops\n";
	csworkshop = verification(0, csshop);

	csefficiency = double(csworkshop) / csshop;

	id = MaxID;
	MaxID++;
}

void compressorstation::edit() // edit compressor station
{
	if (csname != "")
	{
		cout << "Enter the number of working workshops\n";
		csworkshop = verification(0, csshop);
	}
	else
	{
		cout << "Create cs first" << endl;
	}
	csefficiency = double(csworkshop) / csshop;
}

void compressorstation::show_c(const unordered_map<int,compressorstation>& css)
{
	for (const auto& [id, c] : css) {
		cout << "------CS------" <<
			"\nID: " << id <<
			"\nName: " << c.csname <<
			"\nNumber of workshops: " << c.csshop <<
			"\nNumber of working shops: " << c.csworkshop <<
			"\nEfficiency: " << c.csefficiency <<
			"\n--------------------" << endl;
	}
}

void compressorstation::save_c(ofstream& fout, unordered_map<int, compressorstation>& css) // save compressors station
{
	string Marker = "CS";
	for (const auto& [id, c] : css) {
		if (csname == "None") fout << Marker << endl;
		else
		{
			fout << Marker << endl;
			fout << id << endl;
			fout << css[id].csname << endl;
			fout << css[id].csshop << endl;
			fout << css[id].csworkshop << endl;
			fout << css[id].csefficiency << endl;
		}
	}
}

void compressorstation::load_c(ifstream& fin, unordered_map<int, compressorstation>& css) // load compressor station
{
	css.clear();

	string Marker;
	while (true) {

		getline(fin >> ws, Marker);

		if (fin.eof()) break;

		if (Marker != "CS") continue;


		fin >> css[id].csname >> css[id].csshop >> css[id].csworkshop >> css[id].csefficiency;

		MaxID++;
	}
}

void compressorstation::search_csname(const std::unordered_map<int, compressorstation>& css, std::unordered_set<int>& keys, const std::string& name) {
	for (const auto& [id, cs] : css) {
		if (name == cs.csname) {
			keys.insert(id);
		}
	}
}

void compressorstation::search_cspercent(const std::unordered_map<int, compressorstation>& css, std::unordered_set<int>& keys, const int& percent) {
	for (const auto& [id, cs] : css) {
		if (percent == ((100*cs.csshop - 100*cs.csworkshop)/cs.csshop)) {
			keys.insert(id);
		}
	}
}

void compressorstation::delete_searched(std::unordered_map<int, compressorstation>& css, const std::unordered_set<int>& keys) {
	for (const auto& key : keys) {
		css.erase(key);
	}
}

void compressorstation::edit_searched(std::unordered_map<int, compressorstation>& css, const std::unordered_set<int>& keys) {
	for (auto& [id, c] : css) {
		if (keys.find(id) != keys.end()) {
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> css[id].csworkshop;
		}
	}
}

void compressorstation::show_searched(std::unordered_map<int, compressorstation>& css, const std::unordered_set<int>& keys) {
	for (const int& key : keys) {
		cout << "--------CS--------" <<
			"\nID: " << css[key].id <<
			"\nName: " << css[key].csname <<
			"\nAll shops: " << css[key].csshop <<
			"\nWorking shops: " << css[key].csworkshop <<
			"\nEfficiency: " << css[key].csefficiency <<
			"\n------------------" << endl;
	}
}