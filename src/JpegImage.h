#pragma once

#include "EncodedImageSize.h"

#include <opencv2/core.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>


class JpegImage {
public:
	JpegImage(const cv::Mat mat);
	const EncodedImageSize* GetEncodedImageSize();
	const std::vector<uchar>* GetJpegBuffer();

private:
	cv::Mat _mat;
	std::vector<uchar> _jpegBuffer;
	EncodedImageSize _encodedImageSize;
};

std::vector<uchar> JpegBufferFromMat(const cv::Mat* mat);
