#include "Mp4ToPDF.h"


void DoMp4ToPDF(const std::string& filename, const std::string& outfilename, int frameskip, bool verbose = false) {
	TQueue<cv::Mat>* queue = new TQueue<cv::Mat>();
	Mp4FileReader* fileReader = new Mp4FileReader(queue, filename, frameskip, verbose);
	UniqueImageIdentifier* uniqueImageIdentifier = new UniqueImageIdentifier(queue, outfilename, verbose);

	std::thread threadIO(&Mp4FileReader::ExtractFramesFromVideoFile, fileReader);
	std::thread threadProcessing(&UniqueImageIdentifier::FindAndSaveUniques, uniqueImageIdentifier);

	threadIO.join();
	threadProcessing.join();
}
