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
	void WritePDFHeader(FILE* fp);
	void WriteImagesInfo( FILE* fp);
	void WriteImages(FILE* fp);
	void WritePDFTail(FILE* fp);

	void AddObjectsPos(FILE* fp);

	std::string _filename;
	std::vector<JpegImage> _images;
	std::vector<fpos_t> _pdfObjectsPos;
	int _lenImages;
	int _pdfNumElemJ;
};
