#include "UniqueImageIdentifier.h"
#include <fstream>


void UniqueImageIdentifier::FindAndSaveUniques() {
	ProcessWaitQueue();
	SaveUniques();
}


void UniqueImageIdentifier::SaveUniques() {

	for (cv::Mat frame : _uniqueFrames) {
		JpegImage image(frame);
		
	}
}


void UniqueImageIdentifier::ProcessWaitQueue() {
	long expectedSize = _framesQueue->getSize();
	for (int i = 0; i < expectedSize; i++) {
		cv::Mat item = _framesQueue->pop();
		if (!item.empty() && (_isFirstFrame || _imageDifference.PassDifferenceTest(item, *_previousFrame))) {
			_uniqueFrames.push_back(item);
			_previousFrame = &_uniqueFrames.back();

			if (_isFirstFrame) {
				_isFirstFrame = false;
			}
			break;
		}
	}
}
