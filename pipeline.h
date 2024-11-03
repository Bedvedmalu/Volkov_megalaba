#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class pipeline {
public:

	static int MaxID;

	void add_pipe();

	void edit_pipe();

	void show_p(const int& id);

	void search_pipe(const string& name);

	void save_p(ofstream& fout);

	void load_p(ifstream& fin);

	

private:
	string pipename = "None";
	int pipelength = 0;
	int pipediameter = 0;
	bool piperepair = false;
	int id;

	int verification(int minvalue, int maxvalue);
	bool verificationbool();
	void id_p();
};
