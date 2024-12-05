#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include "utils.h"

class pipeline {
public:

	void add_pipe();

	void edit();

	void show_p(const std::unordered_map<int, pipeline>& pipelines);

	void save_p(std::ofstream& fout, std::unordered_map<int, pipeline>& pipellines);

	void load_p(std::ifstream& fin, std::unordered_map<int, pipeline>& pipelines);

	void search_pipename(std::unordered_set<int>& keys, const std::unordered_map<int, pipeline>& pipelines, const std::string& name);

	int get_id();

	static int get_MaxID();

	void search_piperepair(std::unordered_set<int>& keys, const std::unordered_map<int, pipeline>& pipelines, const bool& inrep);

	void delete_searched(std::unordered_map<int, pipeline>& pipelines, const std::unordered_set<int>& keys);

	void show_searched(std::unordered_map<int, pipeline>& pipelines, const std::unordered_set<int>& keys);

	void edit_searched(std::unordered_map<int, pipeline>& pipelines, const std::unordered_set<int>& keys);


private:

	static int MaxID;
	int id;
	std::string pipename = "None";
	int pipelength = 0;
	int pipediameter = 0;
	bool piperepair = false;

};