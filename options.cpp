#include "options.h"



using namespace std;
using namespace chrono;

void option1(unordered_map<int, pipeline>& pipelines) {
	pipeline p;
	p.add_pipe();
	pipelines.emplace(p.get_id(), p);
	return;
}

void option2(unordered_map<int, compressorstation>& css) {
	compressorstation c;
	c.add_cs();
	css.emplace(c.get_id(), c);
	return;
}

void option3(unordered_map<int, pipeline>& pipelines, unordered_map<int, compressorstation>& css) {
	pipeline p;
	compressorstation c;
	p.show_p(pipelines);
	c.show_c(css);
	return;
}

void option4(unordered_map<int, pipeline>& pipelines) {
	if (!pipelines.empty()) ID_verification(pipelines, 0);
	else cout << "Create pipeline first" << endl;
	return;
}

void option5(unordered_map<int, compressorstation>& css) {
	if (!css.empty()) ID_verification(css, 0);
	else cout << "Create CS first" << endl;
	return;
}

void option6(unordered_map<int, pipeline>& pipelines, unordered_map<int, compressorstation>& css) {
	string txt;
	pipeline p;
	compressorstation c;
	cout << "Enter file name" << endl;
	INPUT_LINE(cin, txt);
	ofstream fout(txt + ".txt");

	if (fout.is_open()) {
		c.save_c(fout, css);
		p.save_p(fout, pipelines);
		fout.close();
		cout << "Saved" << endl;
	}
	else cout << "Failed to save" << endl;
	return;
}

void option7(unordered_map<int, pipeline>& pipelines, unordered_map<int, compressorstation>& css) {
	string filename;
	pipeline p;
	compressorstation c;

	cout << "Enter file name: ";

	INPUT_LINE(cin, filename);

	ifstream fin(filename + ".txt");

	if (fin.is_open())
	{
		c.load_c(fin, css);
		fin.clear();
		fin.seekg(0, ios::beg);
		p.load_p(fin, pipelines);
		fin.close();
		cout << "Loaded" << endl;
		cerr << filename << endl;
	}
	else cout << "Failed to load" << endl;
	return;
}

void option8(unordered_map<int, pipeline>& pipelines, unordered_map<int, compressorstation>& css) {
	delete_menu();
	switch (GetCorrectNumber(1, 2)) {
	case 1:
	{
		if (!pipelines.empty()) {
			ID_verification(pipelines, 1);
			break;
		}
		else {
			cout << "Create pipeline first" << endl;
			break;
		}
	}
	case 2:
	{
		if (!css.empty()) {
			ID_verification(css, 1);
			break;
		}
		else {
			cout << "Create CS first" << endl;
			break;
		}
	}
	default:
	{
		break;
	}
	}
	return;
}

void option9(unordered_map<int, pipeline>& pipelines, unordered_map<int, compressorstation>& css, unordered_set<int>& keys) {
	pipeline p;
	compressorstation c;
	cin.clear();
	cin.ignore(1000, '\n');
	if ((pipelines.size() == 0) && (css.size() == 0)) {
		cout << "Objects doesn't exist" << endl;
		return;
	}
	sort_menu();
	string txt;
	bool flag;

	switch (GetCorrectNumber(1, 4)) {
	case 1:
	{
		cin.clear();
		cin.ignore(1000, '\n');
		flag = true;
		cout << "Enter pipeline name: " << endl;
		INPUT_LINE(cin, txt);
		p.search_pipename(keys, pipelines, txt);
		p.show_searched(pipelines, keys);

		if (keys.size() == 0) {
			cout << "Pipelines doesn't exist" << endl;
			return;
		}
		break;
	}

	case 2:
	{
		cin.clear();
		cin.ignore(1000, '\n');
		bool rep;
		flag = true;
		cout << "Enter pipeline's sign of repair: " << endl;
		rep = verificationbool();
		p.search_piperepair(keys, pipelines, rep);
		p.show_searched(pipelines, keys);

		if (keys.size() == 0) {
			cout << "Pipelines doesn't exist" << endl;
			break;
		}
		break;
	}

	case 3:
	{
		cin.clear();
		cin.ignore(1000, '\n');
		flag = false;
		cout << "Enter cs's name: " << endl;
		INPUT_LINE(cin, txt);
		c.search_csname(css, keys, txt);
		c.show_searched(css, keys);
		if (keys.size() == 0) {
			cout << "CS's doesn't exist" << endl;
			break;
		}
		break;
	}

	case 4:
	{
		cin.clear();
		cin.ignore(1000, '\n');
		flag = false;
		cout << "Enter cs's workshops: " << endl;
		c.search_cspercent(css, keys, GetCorrectNumber(0, 10000));
		c.show_searched(css, keys);
		if (keys.size() == 0) {
			cout << "CS's doesn't exist" << endl;
			break;
		}
		break;
	}
	}
	unordered_set<int> new_keys;
	cout << "Choose some ID's?" << endl << "0 - No" << endl << "1 - Yes" << endl;
	switch (GetCorrectNumber(0, 1))
	{
	case 1:
	{
		cout << "Enter ID's separated by spaces" << endl;
		cin.clear();
		cin.ignore(1000, '\n');
		INPUT_LINE(cin, txt);
		int number;
		istringstream stream(txt);
		while (stream >> number) {
			if (!keys.contains(number)) {
				cout << "ID doesnt exist: " << number << endl;
			}
			else {
				new_keys.insert(number);
			}
		}
		action();
		switch (GetCorrectNumber(1, 2)) {
		case 1:
		{
			if (flag) p.delete_searched(pipelines, new_keys);
			else c.delete_searched(css, new_keys);
			break;
		}
		case 2:
		{
			if (flag) p.edit_searched(pipelines, new_keys);
			else c.edit_searched(css, new_keys);
			break;
		}
		}
	}
	//else {
	case 0:
	{
		action();
		switch (GetCorrectNumber(1, 2)) {
		case 1:
		{
			if (flag) p.delete_searched(pipelines, keys);
			else c.delete_searched(css, keys);
			break;
		}
		case 2:
		{
			if (flag) p.edit_searched(pipelines, keys);
			else c.edit_searched(css, keys);
			break;
		}
		}
	}
	new_keys.clear();
	keys.clear();
	}
}

void option10(unordered_map<int, pipeline>& pipelines, unordered_map<int, compressorstation>& css) {
	compressorstation c;
	pipeline p;
	unordered_map<int, unordered_set<int>> to_sort;
	//p.make_edges(pipelines, css);
	p.make_matrix(pipelines, css, to_sort);
	
	p.visualising_graph(pipelines, "graph");
	for (int top : Kan_by_Volkov(to_sort)) {
		cout << top << " ";
	}
	cout << endl;
}

