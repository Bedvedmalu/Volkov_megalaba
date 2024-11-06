#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <format>
#include "pipeline.h"

using namespace std;

//int MaxID = 1;

int verification(int minvalue, int maxvalue) // verification of int data
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

bool verificationbool() // verification of bool data
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


class compressorstation {
public:
	void add_cs() // add compressors station
	{
		cout << "Choose a name for the cs\n";
		//cin.ignore(10000, '\n');
		getline(cin, csname);

		cout << "Enter the number of workshops\n";
		csshop = verification(0, 1000);

		cout << "Enter the number of working workshops\n";
		csworkshop = verification(0, csshop);

		csefficiency = double(csworkshop) / csshop;
	}

	void edit_cs() // edit compressor station
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

	void show_c()
	{
		if (csname != "") // show compressors station
		{
			cout << "------CS------" <<
				//"\nID: " << id <<
				"\nName: " << csname <<
				"\nNumber of workshops: " << csshop <<
				"\nNumber of working shops: " << csworkshop <<
				"\nEfficiency: " << csefficiency <<
				"\n--------------------" << endl;
		}
		else
		{
			cout << "Create cs first" << endl;
		}
	}

	void save_c(ofstream& fout) // save compressors station
	{
		string Marker = "CS";
		if (csname == "None") fout << Marker << endl;
		else
		{
			fout << csname << endl;
			fout << csshop << endl;
			fout << csworkshop << endl;
			fout << csefficiency << endl;
		}
	}

	void load_c(ifstream& fin) // load compressor station
	{
		string Marker;
		getline(fin >> ws, Marker);
		if (Marker != "CS")
		{
			csname = Marker;
			fin >> csshop;
			fin >> csworkshop;
			fin >> csefficiency;
		}
	}

private:
	string csname = "None";
	int csshop = 0;
	int csworkshop = 0;
	double csefficiency = 0.0;
	//int id = MaxID++;
};

void menu() // menu
{
	cout <<
		"0. Escape\n" <<
		"1. Add new pipeline\n" <<
		"2. Add new cs\n" <<
		"3. Show all objects\n" <<
		"4. Edit pipeline\n" <<
		"5. Edit cs\n" <<
		"6. Save \n" <<
		"7. Load \n" <<
		"8. Delete pipeline" << endl;
};

void sort_menu()
{
	cout <<
		"0. Escape\n" <<
		"1. Sort pipelines by name \n" <<
		"2. Sort pipelines by repair \n" <<
		"3. Sort CS by name \n" <<
		"4. Sort CS by workshops \n" << endl;
}

template <typename type_map, typename name_map>
void ID_verification(unordered_map<type_map, name_map>& objects, int choice, int todo)
{
	cout << "Input ID: " << endl;
	choice = verification(1, 1000);
	if (objects.find(choice) != objects.end()) {
		switch (todo)
		{
		case 0:
			objects[choice].edit_pipe();
			break;
		case 1:
			objects.erase(choice);
			break;
		}
	}
	else {
		cout << "ID doesn't exist" << endl;
	}
}

int main()
{
	int choice;
	string txt;
	compressorstation c;
	unordered_map <int, pipeline> pipelines;
	unordered_map <int, compressorstation> css;

	while (true)
	{
		menu();
		choice = verification(0, 9);
		switch (choice)
		{
		case 0: // escape
		{
			return 0;
		}
		case 1: // add new pipeline
		{
			pipeline p;
			p.add_pipe();
			pipelines.emplace(p.get_id(), p);
			break;
		}
		case 2: // add new cs
		{
			c.add_cs();

			break;
		}
		case 3: // show all objects
		{
			for (const auto& [id, p] : pipelines)
			{
				pipelines[id].show_p(id);
			}

			c.show_c();

			break;
		}
		case 4: // edit pipe
		{
			ID_verification(pipelines, choice, 0);
			break;
		}
		case 5: // edit cs
		{
			c.edit_cs();

			break;
		}
		case 6: // save 
		{
			cout << "Enter file name: ";
			cin >> txt;

			ofstream fout(txt + ".txt");
			if (fout.is_open())
			{
				//p.save_p(fout);
				c.save_c(fout);
				fout.close();
				cout << "Saved" << endl;
			}
			else
			{
				cout << "Failed to save" << endl;
			}
			break;
		}
		case 7: // load
		{
			cout << "Enter file name: ";
			cin >> txt;

			ifstream fin(txt + ".txt");
			if (fin.is_open())
			{
				//p.load_p(fin);
				c.load_c(fin);
				fin.close();
				cout << "Loaded" << endl;
			}
			else
			{
				cout << "Failed to load" << endl;
			}
			break;
		}
		case 8: // delete pipe
		{
			ID_verification(pipelines, choice, 1);
			break;
		}
		case 9:
		{
			choice = verification(0, 4);
			switch (choice)
			{
			case 0:
			{
				break;
			}

			case 1:
			{
				cout << "Enter a name which you want to find" << endl;
				getline(cin, txt);
				pipeline p;

				for (const auto& [id, p] : pipelines)
				{
					if (pipelines[id].search_pipename(id, txt) == false) {
						choice += 1;
					}
				}
				if ((choice - 1) == (p.get_id() - 1)) {
					cout << "Pipe with that name doesnt exist";
				}
				break;
			}

			case 2:
			{
				cout << "Enter the attribute of pipe" << endl;
				bool inrep;
				cin >> inrep;
				pipeline p;

				for (const auto& [id, p] : pipelines)
				{
					if (pipelines[id].search_piperepair(id, inrep) == false) {
						choice += 1;
					}
				}

				if ((choice - 2) == (p.get_id() - 1)) {
					cout << "Pipe with that attribute doesnt exist" << endl;
				}

				break;
			}

			default:
			{
				break;
			}
			}

		}
		default: // unexpected error
		{
			break;
		}
		}
	}
}