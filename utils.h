#pragma once
#include <iostream>
#include <unordered_map>
#include "pipeline.h"

#define INPUT_LINE(in, str) getline(in>>std::ws, str); \
						std::cerr << str << std::endl

#define PRINT_PARAM(out, x) out<< #x << "=" << x << std::endl

class redirect_output_wrapper
{
	std::ostream& stream;
	std::streambuf* const old_buf;
public:
	redirect_output_wrapper(std::ostream& src)
		:old_buf(src.rdbuf()), stream(src)
	{
	}

	~redirect_output_wrapper() {
		stream.rdbuf(old_buf);
	}
	void redirect(std::ostream& dest)
	{
		stream.rdbuf(dest.rdbuf());
	}
};

int verification(int minvalue, int maxvalue);

bool verificationbool();

void menu();

void delete_menu();

void sort_menu();

void action();

template <typename T>
void ID_verification(std::unordered_map<int, T>& objects, int todo)
{
	std::cout << "Input ID: " << std::endl;
	int choice = verification(1, T::get_MaxID());
	if (objects.contains(choice)) {
		switch (todo)
		{
		case 0:
			objects[choice].edit();
			break;
		case 1:
			objects.erase(choice);
			break;
		}
	}
	else {
		std::cout << "ID doesn't exist" << std::endl;
	}
}

template <typename T>
T GetCorrectNumber(T min, T max)
{
	T x;
	while ((std::cin >> x).fail()	// check type
		|| std::cin.peek() != '\n'	// is buffer empty (int/float check)
		|| x < min || x > max)		// check range
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Type number (" << min << "-" << max << "):";
	}
	std::cerr << x << std::endl;
	return x;
}