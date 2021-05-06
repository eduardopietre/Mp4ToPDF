#pragma once

#include "StructuralSimilarityIndex.h"

#include <opencv2/core.hpp>


class ImageDifference {
public:
	ImageDifference(double floatingMargin = 0.3, double rawThreshold = 0.90, double ssmiThreshold = 0.90) : _floatingMargin(floatingMargin), _rawThreshold(rawThreshold), _ssmiThreshold(ssmiThreshold) {};
	bool PassDifferenceTest(const cv::Mat& img1, const cv::Mat& img2);
	bool PassRawDifferenceTest(const cv::Mat& img1, const cv::Mat& img2);
	bool PassSSIMDifferenceTest(const cv::Mat& img1, const cv::Mat& img2);

private:
	double _floatingMargin;
	double _rawThreshold;
	double _ssmiThreshold;
	BufferSSIM _bufferSSIM;
};
