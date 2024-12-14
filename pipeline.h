#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include "utils.h"
#include "compressorstation.h"

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

	void make_edges(std::unordered_map<int, pipeline>& pipelines, std::unordered_map<int, compressorstation>& css);

	void make_matrix(std::unordered_map<int, pipeline>& pipelines, const std::unordered_map<int, compressorstation>& css, std::unordered_map<int, std::unordered_set<int>>& to_sort);

	void visualising_graph(const std::unordered_map<int, pipeline>& pipelines, const std::string& filename);


private:
	int CS_in;
	int CS_out;
	static int MaxID;
	int id;
	int size;
	std::string pipename = "None";
	int pipelength = 0;
	int pipediameter = 0;
	bool piperepair = false;
};