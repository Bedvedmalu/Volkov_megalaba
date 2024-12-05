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
#include "options.h"
using namespace std;
using namespace chrono;

int main()
{
	unordered_set<int> keys;
	unordered_map <int, pipeline> pipelines;
	unordered_map <int, compressorstation> css;

	redirect_output_wrapper cerr_out(cerr);
	string time = std::format("{:%d_%m_%Y_%H_%M_%OS}", system_clock::now());
	ofstream logfile("log_" + time);
	if (logfile) cerr_out.redirect(logfile);

	while (true)
	{
		menu();
		switch (GetCorrectNumber(0, 9))
		{
		case 0: return 0;// escape

		case 1: option1(pipelines); break; // add new pipeline

		case 2: option2(css); break; // add new cs

		case 3: option3(pipelines, css); break; // show all objects

		case 4: option4(pipelines); break; // edit pipe

		case 5: option5(css); break; // edit cs

		case 6: option6(pipelines, css); break; // save 

		case 7: option7(pipelines, css); break;// load

		case 8: option8(pipelines, css); break; // delete pipeline

		case 9: option9(pipelines, css, keys); break;

		default: break;
		}
	}
}