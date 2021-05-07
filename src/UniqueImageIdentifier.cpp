#include "UniqueImageIdentifier.h"


void UniqueImageIdentifier::FindAndSaveUniques() {
	ProcessWaitQueue();
	SaveUniques();
}


void UniqueImageIdentifier::SaveUniques() {
	std::string out = "D:/Development/Python/PyMp4ToPDF/cpptest.pdf";
	PDFWriter writer(out, &_uniqueFrames);
	writer.Write();
}


void UniqueImageIdentifier::ProcessWaitQueue() {
	long expectedSize = _framesQueue->getSize();
	for (int i = 0; i < expectedSize; i++) {
		cv::Mat item = _framesQueue->pop();
		if (!item.empty()) {
			if (_isFirstFrame || _imageDifference.PassDifferenceTest(item, *_previousFrame)) {
				_uniqueFrames.push_back(item);
				_previousFrame = &_uniqueFrames.back();

				if (_isFirstFrame) {
					_isFirstFrame = false;
				}
			}
		}
	}
}
