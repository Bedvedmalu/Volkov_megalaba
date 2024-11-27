#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <format>
#include "pipeline.h"
#include "compressorstation.h"
#include "utils.h"

using namespace std;
using namespace chrono;

int main()
{
	int choice;
	bool rep;
	string txt;
	unordered_set<int> keys;

	pipeline p;
	compressorstation c;

	unordered_map <int, pipeline> pipelines;
	unordered_map <int, compressorstation> css;

	redirect_output_wrapper cerr_out(cerr);
	string time = std::format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now());
	ofstream logfile("log_" + time);
	if (logfile)
		cerr_out.redirect(logfile);

	while (true)
	{
		menu();
		switch (GetCorrectNumber(0, 9))
		{
		case 0: // escape
		{
			return 0;
		}
		case 1: // add new pipeline
		{
			p.add_pipe();
			pipelines.emplace(p.get_id(), p);
			break;
		}
		case 2: // add new cs
		{
			c.add_cs();
			css.emplace(c.get_id(), c);
			break;
		}
		case 3: // show all objects
		{
			for (const auto& [id, p] : pipelines)
			{
				pipelines[id].show_p(id);
			}

			for (const auto& [id, c] : css)
			{
				css[id].show_c(id);
			}

			break;
		}
		case 4: // edit pipe
		{
			ID_verification(pipelines, 0);
			break;
		}
		case 5: // edit cs
		{
			ID_verification(css, 0);
			break;
		}
		case 6: // save 
		{
			cout << "Enter file name: ";
			cin >> txt;

			ofstream fout(txt + ".txt");
			if (fout.is_open())
			{
				p.save_p(fout, pipelines);
				c.save_c(fout,css);
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
				c.load_c(fin, css);
				
				fin.clear();
				fin.seekg(0, ios::beg);

				p.load_p(fin, pipelines);
				
				fin.close();
				cout << "Loaded" << endl;
			}
			else
			{
				cout << "Failed to load" << endl;
			}
			break;
		}
		case 8: // delete pipeline
		{
			cout
				<< "Delete: \n"
				<< "1. Pipeline \n"
				<< "2. CS" << endl;
			choice = verification(1, 2);
			switch (choice)
			{
			case 1:
			{
				ID_verification(pipelines, 1);
				break;
			}
			case 2:
			{
				ID_verification(css, 1);
				break;
			}
			default:
			{
				break;
			}
			}
			break;
		}
		case 9:
		{
			bool flag{};
			sort_menu();
			choice = verification(0, 4);

			switch (choice) {
			case 0:
			{
				break;
			}

			case 1:
			{
				flag = true;
				cout << "Enter pipeline name: " << endl;
				getline(cin, txt);
				p.search_pipename(keys, pipelines, txt);
				cout << "Searched pipes: " << endl;
				p.show_searched(pipelines, keys);
				break;
			}

			case 2:
			{
				flag = true;
				cout << "Enter pipelline's sign of repair: " << endl;
				cin >> rep;
				p.search_piperepair(keys, pipelines, rep);
				cout << "Searched pipes: " << endl;
				p.show_searched(pipelines, keys);
				break;

			}

			case 3:
			{
				flag = false;
				cout << "Enter cs's name: " << endl;
				getline(cin, txt);
				c.search_csname(css, keys, txt);
				cout << "Searched cs's: " << endl;
				c.show_searched(css, keys);
				break;
			}

			case 4:
			{
				flag = false;
				cout << "Enter cs's workshops: " << endl;
				choice = verification(0, 10000);
				c.search_cspercent(css, keys, choice);
				cout << "Searched cs's: " << endl;
				c.show_searched(css, keys);
			}

			default:
			{
				break;
			}

			}
			if (keys.size() == 0) {
				cout << "Can't search any objects" << endl;
				break;
			}
			cout << "Do you want choose some ID's?" << endl << "0 - No" << endl << "1 - Yes" << endl;
			rep = verificationbool();

			if (rep) {
				cout << "Input the ID separated by spaces" << endl;
				getline(cin, txt);
				istringstream stream(txt);
				while (stream >> choice) {
					if (!keys.contains(choice)) {
						cout << "That Id doesn't exist: " << choice << endl;
					}
				}
			}

			action();
			switch (GetCorrectNumber(1, 3)) {
			case 1:
				if (flag == true) {
					p.delete_searched(pipelines, keys);
				}
				else {
					c.delete_searched(css, keys);
				}
				break;
			case 2:
				if (flag == true) {
					p.edit_searched(pipelines, keys);
				}
				else {
					c.edit_searched(css, keys);
				}
				break;
			default:
				break;
			}
			
			
			keys.clear();
		}

		default:
		{
			break;
		}

		}
	}
}