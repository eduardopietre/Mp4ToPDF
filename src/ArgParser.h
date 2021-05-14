#pragma once

#include <iostream>
#include <string>


class ArgParser {
public:
	std::string filename = "";
	std::string outfilename = "";

	// Defaults
	int frameskip = 48;
	// TODO: Finish implementing diff arguments.
	//double rawDiffThreshold;
	//double ssimThreshold;

	bool isValid = true;

	ArgParser(int argc, char* argv[]);
};
