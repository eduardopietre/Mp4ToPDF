#include "Mp4ToPDF.h"


int main(int argc, char* argv[]) {
	ArgParser args = ArgParser(argc, argv);
	if (!args.isValid) {
		return 1;
	}

	cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);

	std::cout << "Started conversion of \"" << args.filename << "\", will be exported as \"" << args.outfilename << "\"." << std::endl;

	auto start = std::chrono::high_resolution_clock::now();

	DoMp4ToPDF(args.filename, args.outfilename, args.frameskip, true);

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
	std::cout << "Done. Conversion took " << duration.count() << " seconds." << std::endl;

	return 0;
}
