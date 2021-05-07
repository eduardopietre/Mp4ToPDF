#pragma once

#include "TQueue.h"
#include "ImageDifference.h"
#include "JpegImage.h"
#include "PDFWriter.h"

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
	void FindAndSaveUniques();

private:
	void SaveUniques();
	void ProcessWaitQueue();

	TQueue<cv::Mat>* _framesQueue;
	const std::string _outfilename;
	std::list<cv::Mat> _uniqueFrames;
	cv::Mat* _previousFrame = NULL;
	bool _isFirstFrame = true;

	ImageDifference _imageDifference;
};
