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


EncodedImageSize::EncodedImageSize(std::vector<uchar>* jpegBuffer, cv::Size& size) {

}
