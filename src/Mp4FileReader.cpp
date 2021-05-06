#include "Mp4FileReader.h"


void Mp4FileReader::ExtractFramesFromVideoFile() {
	cv::VideoCapture videoFile(_filename);

	if (!videoFile.isOpened()) {
		throw "At ExtractFramesFromVideoFile: Error when reading input file.";
	}

	int framerCount = videoFile.get(cv::CAP_PROP_FRAME_COUNT);
	_framesQueue->setSize(std::floor(framerCount / _everyXFrames));

	for (int i = 0; i < framerCount; i += _everyXFrames) {
		videoFile.set(cv::CAP_PROP_POS_FRAMES, i);

		cv::Mat singleFrame;
		if (videoFile.read(singleFrame)) {
			_framesQueue->push(std::move(singleFrame));
		} else {
			break;
		}
	}
}
