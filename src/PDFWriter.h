#pragma once

#include "JpegImage.h"
#include "EncodedImageSize.h"

#include <opencv2/core.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <iostream>
#include <cstdio>
#include <string>
#include <stdlib.h>
#include <list>
#include <vector>


class PDFWriter {
public:
	PDFWriter(const std::string filename, std::list<cv::Mat>* images) : _filename(filename) {
		_images = std::vector<cv::Mat>(std::begin(*images), std::end(*images));
	};
	bool Write();

private:
	const std::string _filename;
	std::vector<cv::Mat> _images;
};


void AddPosInVector(FILE* fp, std::vector<fpos_t>* positionVector);
