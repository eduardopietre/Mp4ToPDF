#include "Mp4ToPDF.h"


void DoMp4ToPDF(const std::string& filename, const std::string& outfilename, int frameskip) {
	TQueue<cv::Mat>* queue = new TQueue<cv::Mat>();
	Mp4FileReader* fileReader = new Mp4FileReader(queue, filename, frameskip);
	UniqueImageIdentifier* uniqueImageIdentifier = new UniqueImageIdentifier(queue, outfilename);

	std::thread threadIO(&Mp4FileReader::ExtractFramesFromVideoFile, fileReader);
	std::thread threadProcessing(&UniqueImageIdentifier::FindAndSaveUniques, uniqueImageIdentifier);

	threadIO.join();
	threadProcessing.join();
}


int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cout << "Insuficient Arguments. Usage: Mp4ToPDF.exe inputfile.mp4 24" << std::endl;
		return 1;
	}

	cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);
	std::string filename = argv[1];
	std::string outfilename = filename + ".pdf";
	int frameskip = std::stoi(argv[2]);

	std::cout << "Started conversion of \"" << filename << "\", will be exported as \"" << outfilename << "\"." << std::endl;

	auto start = std::chrono::high_resolution_clock::now();

	DoMp4ToPDF(filename, outfilename, frameskip);

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
	std::cout << "Done. Conversion took " << duration.count() << " seconds." << std::endl;

	return 0;
}
