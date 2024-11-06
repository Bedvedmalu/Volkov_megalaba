#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class pipeline {
public:

	void add_pipe();

	void edit_pipe();

	void show_p(const int& id);

	void save_p(ofstream& fout);

	void load_p(ifstream& fin);

	int get_id();

	bool search_pipename(const int& id, const string& name);
	
	bool search_piperepair(const int& id, const bool& inrep);

private:
	static int MaxID;
	string pipename = "None";
	int pipelength = 0;
	int pipediameter = 0;
	bool piperepair = false;
	int id;

	int verification(int minvalue, int maxvalue);
	bool verificationbool();

};
