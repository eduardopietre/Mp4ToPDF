#include "ArgParser.h"


ArgParser::ArgParser(int argc, char* argv[]) {
	if (argc < 2 || argc > 3) { // Update 3 to acomodate more args.
		std::cout << "Too few or too much arguments." << std::endl;
		std::cout << "Usage: Mp4ToPDF.exe inputfile.mp4 <24>\nArguments inside <> are optional." << std::endl;

		isValid = false;
		return;
	}

	if (argc >= 2) {
		filename = argv[1];
		outfilename = filename + ".pdf";
	}

	if (argc >= 3) {
		frameskip = std::stoi(argv[2]);
	}
}
