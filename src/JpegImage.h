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
	EncodedImageSize* GetEncodedImageSize();
	std::vector<uchar>* GetJpegBuffer();
	cv::Size Size();

private:
	cv::Mat _mat;
	std::vector<uchar> _jpegBuffer;
	EncodedImageSize _encodedImageSize;
};

std::vector<uchar> JpegBufferFromMat(const cv::Mat* mat);
