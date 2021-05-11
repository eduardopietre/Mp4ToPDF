#include "EncodedImageSize.h"

// Heavily based on the example of https://gist.github.com/bencz/cebd1125dca7b81cdd23

unsigned int EncodedImageSize::GetWidth() {
	return _width;
}


unsigned int EncodedImageSize::GetHeight() {
	return _height;
}


unsigned long EncodedImageSize::GetLength() {
	return _length;
}


unsigned int EncodedImageSize::GetEncodedWidth() {
	return _encodedWidth;
}


unsigned int EncodedImageSize::GetEncodedHeight() {
	return _encodedHeight;
}


bool EncodedImageSize::IsValid() {
	return _isValid;
}


EncodedImageSize::EncodedImageSize(const std::vector<uchar>* jpegBuffer, const cv::Size& size) {
	_width = size.width;
	_height = size.height;
	_length = (int) jpegBuffer->size();

	std::pair<int, int> heightWidth = CalculateEncodedHeightWidth(jpegBuffer);
	_encodedWidth = heightWidth.first;
	_encodedHeight = heightWidth.second;

	_isValid = (_encodedWidth > 0 && _encodedHeight > 0);
}


std::pair<unsigned int, unsigned int> CalculateEncodedHeightWidth(const std::vector<uchar>* jpegBuffer) {
	std::vector<uchar> buffer(jpegBuffer->begin(), jpegBuffer->begin() + 24);
	long len = (int) jpegBuffer->size();

	if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF && buffer[3] == 0xE0 &&
		buffer[6] == 0x4A && buffer[7] == 0x46 && buffer[8] == 0x49 && buffer[9] == 0x46) {

		long pos = 2;
		while (buffer[2] == 0xFF)
		{
			if (buffer[3] == 0xC0 || buffer[3] == 0xC1 || buffer[3] == 0xC2 || buffer[3] == 0xC3 ||
				buffer[3] == 0xC9 || buffer[3] == 0xCA || buffer[3] == 0xCB) {
				break;
			}

			pos += 2 + (buffer[4] << 8) + buffer[5];
			if (pos + 12 > len) {
				break;
			}

			for (int i = (0 + 2); i < (12 + 2); i++) {
				buffer[i] = jpegBuffer->at(i);
			}
		}
	}

	if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF)
	{
		unsigned int height = (buffer[7] << 8) + buffer[8];
		unsigned int width = (buffer[9] << 8) + buffer[10];

		return std::pair<unsigned int, unsigned int>(height, width);
	}

	return std::pair<unsigned int, unsigned int>(0, 0);
}
