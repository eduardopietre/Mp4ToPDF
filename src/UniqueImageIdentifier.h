#pragma once

#include "TQueue.h"
#include "StructuralSimilarityIndex.h"

#include <opencv2/core.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <list>


class UniqueImageIdentifier {
public:
	UniqueImageIdentifier(TQueue<cv::Mat>* queue, const std::string& outfilename) :
		_framesQueue(queue), _outfilename(outfilename) {};
	void ProcessWaitQueue();
	bool DifferentFromPreviousFrame(cv::Mat& newFrame);

private:
	bool DifferentFromPreviousFrameRawDiff(cv::Mat& newFrame, double floatingMargin = 0.3, double threshold = 0.90);
	bool DifferentFromPreviousFrameSSIM(cv::Mat& newFrame, double threshold = 0.90);

	TQueue<cv::Mat>* _framesQueue;
	const std::string _outfilename;
	std::list<cv::Mat> _uniqueFrames;
	cv::Mat* _previousFrame;
	bool _isFirstFrame = true;

	BufferSSIM _bufferSSIM;
};
