#include "EncodedImageSize.h"


void EncodedImageSize::SetWidth(unsigned int w) {
	_width = w;
}


void EncodedImageSize::SetHeight(unsigned int h) {
	_height = h;
}


void EncodedImageSize::SetLength(unsigned long l) {
	_length = l;
}


unsigned int EncodedImageSize::GetWidth() {
	return _width;
}


unsigned int EncodedImageSize::GetHeight() {
	return _height;
}


unsigned long EncodedImageSize::GetLength() {
	return _length;
}


EncodedImageSize::EncodedImageSize(const std::vector<uchar>* jpegBuffer, const cv::Size& size) {
	_width = size.width;
	_height = size.height;
	_length = jpegBuffer->size();
}
