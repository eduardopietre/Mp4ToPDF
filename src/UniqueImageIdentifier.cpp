#include "UniqueImageIdentifier.h"


void UniqueImageIdentifier::ProcessWaitQueue() {
	long expectedSize = _framesQueue->getSize();
	int count = 0;

	while (count < expectedSize) {
		cv::Mat item = _framesQueue->pop();
		if (!item.empty()) {
			if (_isFirstFrame || DifferentFromPreviousFrame(item)) {
				_uniqueFrames.push_back(item);
				_previousFrame = &_uniqueFrames.back();

				if (_isFirstFrame) {
					_isFirstFrame = false;
				}
			}
		}
		count++;
	}

	std::cout << "Size is " << _uniqueFrames.size() << std::endl;

	//for (const auto& frame : _uniqueFrames)
	//{
	//	cv::imshow("Frame", frame);
	//	cv::waitKey(200);
	//}
}


bool UniqueImageIdentifier::DifferentFromPreviousFrame(cv::Mat& newFrame) {
	return DifferentFromPreviousFrameRawDiff(newFrame) && DifferentFromPreviousFrameSSIM(newFrame);
}


bool UniqueImageIdentifier::DifferentFromPreviousFrameRawDiff(cv::Mat& newFrame, double floatingMargin, double threshold) {
	cv::Mat absdiffResult;
	cv::absdiff(newFrame, *_previousFrame, absdiffResult);

	cv::Mat comparationResult;
	cv::compare(absdiffResult, floatingMargin, comparationResult, cv::CMP_LT);

	cv::Scalar mean = cv::mean(comparationResult);
	double pctEqual = mean[0] / 255;  // true's are set to 255, so divide by it.

	return pctEqual < threshold;
}


bool UniqueImageIdentifier::DifferentFromPreviousFrameSSIM(cv::Mat& newFrame, double threshold) {
	double ssmi = StructuralSimilarityIndexMultichannelCUDA(newFrame, *_previousFrame, _bufferSSIM);
	// std::cout << "ssmi is " << ssmi << std::endl;
	return ssmi < threshold;
}
