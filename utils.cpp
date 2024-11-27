#include <iostream>

using namespace std;

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
		"8. Delete object\n" <<
		"9. Filter" << endl;
};

void sort_menu()
{
	cout <<
		"0. Escape\n" <<
		"1. Sort pipelines by name \n" <<
		"2. Sort pipelines by repair \n" <<
		"3. Sort CS by name \n" <<
		"4. Sort CS by workshops \n";
}

void action()
{
	cout <<
		"1. Delete\n" <<
		"3. Edit\n";
}

