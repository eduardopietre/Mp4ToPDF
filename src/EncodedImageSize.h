#pragma once

#include <opencv2/core.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <stdlib.h>


class EncodedImageSize {
public:
	EncodedImageSize() {};
	EncodedImageSize(const std::vector<uchar>* jpegBuffer, const cv::Size& size);

	unsigned int GetWidth();
	unsigned int GetHeight();
	unsigned long GetLength();

	unsigned int GetEncodedWidth();
	unsigned int GetEncodedHeight();

private:
	unsigned int _width = 0;
	unsigned int _height = 0;
	unsigned long _length = 0;

	unsigned int _encodedWidth = 0;
	unsigned int _encodedHeight = 0;
};

std::pair<int, int> CalculateEncodedHeightWidth(const std::vector<uchar>* jpegBuffer);
