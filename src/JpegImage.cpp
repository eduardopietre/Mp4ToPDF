#include "JpegImage.h"


JpegImage::JpegImage(cv::Mat mat) {
	_mat = mat;
	_jpegBuffer = JpegBufferFromMat(&_mat);

	cv::Size size = _mat.size();
	_encodedImageSize = EncodedImageSize(&_jpegBuffer, size);
}


std::vector<uchar> JpegBufferFromMat(const cv::Mat* mat) {
	std::vector<uchar> buffer;
	std::vector<int> param = { cv::IMWRITE_JPEG_QUALITY, 100 };  // 0-100
	cv::imencode(".jpg", *mat, buffer, param);
	return std::move(buffer);
}


