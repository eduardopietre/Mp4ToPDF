#pragma once

#include <iostream>
#include <string>


struct Arguments {
	std::string filename;
	std::string outfilename;
	int frameskip;
	// TODO: Finish implementing diff arguments.
	//double rawDiffThreshold;
	//double ssimThreshold;

	bool isValid = true;

	Arguments(bool valid) : isValid(valid) {}
	Arguments(const std::string& file, int skip = 48) :
		filename(file), frameskip(skip), outfilename(file + ".pdf") {}

	// TODO: Finish implementing diff arguments.
	/*Arguments(const std::string& file, int skip = 48, double rawThresh = 0.90, double ssimThresh = 0.90) :
		filename(file), frameskip(skip), rawDiffThreshold(rawThresh), ssimThreshold(ssimThresh), outfilename(file + ".pdf") {}*/
};


Arguments ParseArguments(int argc, char* argv[]);
