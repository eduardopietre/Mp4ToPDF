#pragma once

#include "TQueue.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>


class Mp4FileReader {
public:
	Mp4FileReader(TQueue<cv::Mat>* queue, const std::string& filename, int everyXFrames = 24, bool verbose = false) : 
		_framesQueue(queue), _filename(filename), _everyXFrames(everyXFrames), _verbose(verbose) {};
	void ExtractFramesFromVideoFile();

private:
	TQueue<cv::Mat>* _framesQueue;
	const std::string _filename;
	const int _everyXFrames;
	bool _verbose;
};
