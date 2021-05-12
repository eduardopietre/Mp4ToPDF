#include "ArgParser.h"


Arguments ParseArguments(int argc, char* argv[]) {
	switch (argc) {
		case 2:
			return Arguments(argv[1]);
		case 3:
			return Arguments(argv[1], std::stoi(argv[2]));
		// TODO: Finish implementing diff arguments.
		//case 4:
		//	return Arguments(argv[1], std::stoi(argv[2]), std::stod(argv[3]));
		//case 5:
		//	return Arguments(argv[1], std::stoi(argv[2]), std::stod(argv[3]), std::stod(argv[4]));

		default:
			break;
	}

	std::cout << "Too few or too much arguments. Usage: Mp4ToPDF.exe inputfile.mp4 <24>\nArguments inside <> are optional." << std::endl;
	return Arguments(false);
}
