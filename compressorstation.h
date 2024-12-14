#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

class compressorstation {
public:

	void add_cs();

	void edit();

	void show_c(const std::unordered_map<int, compressorstation>& css);

	void save_c(std::ofstream& fout, std::unordered_map<int, compressorstation>& css);

	void load_c(std::ifstream& fin, std::unordered_map<int, compressorstation>& css);

	int get_id();

	static int get_MaxID();

	void search_csname(const std::unordered_map<int, compressorstation>& css, std::unordered_set<int>& keys, const std::string& name);

	void search_cspercent(const std::unordered_map<int, compressorstation>& css, std::unordered_set<int>& keys, const int& percent);

	void delete_searched(std::unordered_map<int, compressorstation>& css, const std::unordered_set<int>& keys);

	void edit_searched(std::unordered_map<int, compressorstation>& css, const std::unordered_set<int>& keys);

	void show_searched(std::unordered_map<int, compressorstation>& css, const std::unordered_set<int>& keys);


private:

	static int MaxID;
	int id;
	std::string csname = "None";
	int csshop = 0;
	int csworkshop = 0;
	double csefficiency = 0.0;
	std::unordered_set<int> in;
	std::unordered_set<int> out;
};