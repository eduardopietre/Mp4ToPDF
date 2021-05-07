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

	void SetWidth(unsigned int w);
	void SetHeight(unsigned int h);
	void SetLength(unsigned long l);

	unsigned int GetWidth();
	unsigned int GetHeight();
	unsigned long GetLength();

private:
	unsigned int _width = 0;
	unsigned int _height = 0;
	unsigned long _length = 0;
};
