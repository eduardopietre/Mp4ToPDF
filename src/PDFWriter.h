#pragma once

// Heavily based on the example of https://gist.github.com/bencz/cebd1125dca7b81cdd23


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
	PDFWriter(const std::string filename, std::list<cv::Mat>* images);
	bool Write();

private:
	std::string _filename;
	std::vector<cv::Mat> _images;
};


void AddPosInVector(FILE* fp, std::vector<fpos_t>* positionVector);
