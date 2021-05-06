#include "Mp4ToPDF.h"


int main()
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);
	std::string filename = "D:/Development/Python/PyMp4ToPDF/test.mp4";

	auto start = std::chrono::high_resolution_clock::now();

	TQueue<cv::Mat>* queue = new TQueue<cv::Mat>();
	Mp4FileReader* fileReader = new Mp4FileReader(queue, filename, 100);
	UniqueImageIdentifier* uniqueImageIdentifier = new UniqueImageIdentifier(queue, filename);

	std::thread threadIO(&Mp4FileReader::ExtractFramesFromVideoFile, fileReader);
	std::thread threadProcessing(&UniqueImageIdentifier::ProcessWaitQueue, uniqueImageIdentifier);

	threadIO.join();
	threadProcessing.join();

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
	std::cout << "Time elapsed: " << duration.count() << " seconds." << std::endl;

	return 0;
}
