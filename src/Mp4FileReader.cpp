#include "Mp4FileReader.h"


void Mp4FileReader::ExtractFramesFromVideoFile() {
	cv::VideoCapture videoFile(_filename);

	if (!videoFile.isOpened()) {
		throw "At ExtractFramesFromVideoFile: Error when reading input file.";
	}

	int framerCount = (int) videoFile.get(cv::CAP_PROP_FRAME_COUNT);
	long size = (long) std::floor(framerCount / _everyXFrames);
	_framesQueue->setSize(size);

	// Back to front
	for (int i = (_everyXFrames * size) - 1; i > 0; i -= _everyXFrames) {
		videoFile.set(cv::CAP_PROP_POS_FRAMES, i);

		cv::Mat singleFrame;
		if (videoFile.read(singleFrame)) {
			_framesQueue->push(std::move(singleFrame));
		} else {
			break;
		}
	}
	if (_verbose) {
		std::cout << "Extracted " << size << " frames from video." << std::endl;
	}
}
