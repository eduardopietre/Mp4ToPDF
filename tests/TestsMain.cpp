#include "Testing.h"
#include "../src/Mp4ToPDF.h"


std::string filename = "C:/Users/User/Desktop/desk/mp4topdf tests/test.mp4";
std::string outfilename = filename + ".pdf";
int frameskip = 100;


int main(int argc, char* argv[]) {
	cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);

	std::cout << "Starting TestsMain" << std::endl;

	TESTING_TIME_EXECUTION("One Mp4ToPDF Conversion", {
		DoMp4ToPDF(filename, outfilename, frameskip);
	});

	return 0;
}
