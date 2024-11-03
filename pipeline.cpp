#include "pipeline.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int pipeline::MaxID = 1;

void pipeline::id_p()
{
	id = MaxID++;
}

int pipeline::verification(int minvalue, int maxvalue) // verification of int data
{
	int value;
	while (true)
	{
		if ((cin >> value).good() && value >= minvalue && value <= maxvalue)
		{
			cin.clear();
			cin.ignore(10000, '\n');
			return value;
		}
		else
		{
			cout << "Incorrect data. Please, try again" << endl;
			cin.clear();
			cin.ignore(10000, '\n');
		}
	}
}

bool pipeline::verificationbool() // verification of bool data
{
	bool value;
	while (true)
	{
		if ((cin >> value).good())
		{
			cin.clear();
			cin.ignore(10000, '\n');
			return value;
		}
		else
		{
			cout << "Incorrect data. Please, try again" << endl;
			cin.clear();
			cin.ignore(10000, '\n');
		}
	}
}

void pipeline::add_pipe() // add pipeline
{
	cout << "Choose a name for the pipeline\n";
	getline(cin, pipename);
	//cin.ignore(10000, '\n');

	cout << "Choose pipe length\n";
	pipelength = verification(0, 2000);

	cout << "Choose pipe diameter\n";
	pipediameter = verification(0, 1000);

	cout << "Under repair?\n0. No\n1. Yes\n";
	piperepair = verificationbool();



}

void pipeline::edit_pipe() // edit pipeline
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

void pipeline::search_pipe(const string& name)
{
	if (name == pipename) {
		cout << "------PIPELINE------" <<
			"\nID:" << id <<
			"\nName: " << pipename <<
			"\nLength: " << pipelength <<
			"\nDiameter: " << pipediameter <<
			"\nUnder repair? " << piperepair <<
			"\n--------------------" << endl;
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

void pipeline::save_p(ofstream& fout) // save pipeline
{
	string Marker = "PIPELINE";
	if (pipename == "None") fout << Marker << endl;
	else
	{
		fout << pipename << endl;
		fout << pipelength << endl;
		fout << pipediameter << endl;
		fout << piperepair << endl;
	}
}

void pipeline::load_p(ifstream& fin) // load pipeline
{
	string Marker;
	getline(fin >> ws, Marker);
	if (Marker != "PIPELINE")
	{
		pipename = Marker;
		fin >> pipelength;
		fin >> pipediameter;
		fin >> piperepair;
	}
}

