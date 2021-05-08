#include "Testing.h"
#include "../src/Mp4ToPDF.h"

#include <iostream>


std::string filename = "C:/Users/User/Desktop/desk/mp4topdf tests/test.mp4";
std::string outfilename = filename + ".pdf";
int frameskip = 100;


int main(int argc, char* argv[]) {
	std::cout << "Starting TestsMain" << std::endl;

	TESTING_TIME_EXECUTION("One Mp4ToPDF Conversion", {
		DoMp4ToPDF(filename, outfilename, frameskip);
	});

	return 0;
}
