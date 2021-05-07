#include "JpegImage.h"


JpegImage::JpegImage(cv::Mat mat) {
	_mat = mat;
	_jpegBuffer = JpegBufferFromMat(&_mat);

	cv::Size size = _mat.size();
	_encodedImageSize = EncodedImageSize(&_jpegBuffer, size);
	CalculateEncodedHeightWidth(&_jpegBuffer);
}


EncodedImageSize* JpegImage::GetEncodedImageSize() {
	return &_encodedImageSize;
}


std::vector<uchar>* JpegImage::GetJpegBuffer() {
	return &_jpegBuffer;
}


cv::Size JpegImage::Size() {
	return _mat.size();
}


std::vector<uchar> JpegBufferFromMat(const cv::Mat* mat) {
	std::vector<uchar> buffer;
	std::vector<int> param = { cv::IMWRITE_JPEG_QUALITY, 100 };  // 0-100
	cv::imencode(".jpg", *mat, buffer, param);
	return std::move(buffer);
}
