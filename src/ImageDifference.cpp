#include "ImageDifference.h"


bool ImageDifference::PassDifferenceTest(const cv::Mat& img1, const cv::Mat& img2) {
	return ImageDifference::PassRawDifferenceTest(img1, img2) && ImageDifference::PassSSIMDifferenceTest(img1, img2);
}


bool ImageDifference::PassRawDifferenceTest(const cv::Mat& img1, const cv::Mat& img2) {
	cv::Mat result;
	cv::absdiff(img1, img2, result);
	cv::compare(result, _floatingMargin, result, cv::CMP_LT);
	cv::Scalar mean = cv::mean(result);
	double pctEqual = (mean[0] + mean[1] + mean[2]) / 3 / 255;  // true's are set to 255, so divide by it.
	return pctEqual < _rawThreshold;
}


bool ImageDifference::PassSSIMDifferenceTest(const cv::Mat& img1, const cv::Mat& img2) {
	double ssmi = StructuralSimilarityIndexMultichannelCUDA(img1, img2, _bufferSSIM);
	return ssmi < _ssmiThreshold;
}
