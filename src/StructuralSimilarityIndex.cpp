#include "StructuralSimilarityIndex.h"

// From https://docs.opencv.org/master/d5/dc4/tutorial_video_input_psnr_ssim.html
// and https://docs.opencv.org/master/dd/d3d/tutorial_gpu_basics_similarity.html
// Small changes for readability.

double MeanFromRGBAScalar(const cv::Scalar& scalar) {
    // Ignore alpha.
    return (scalar[0] + scalar[1] + scalar[2]) / 3;
}

#if GPU_SSIM

double StructuralSimilarityIndexMultichannelCUDA(const cv::Mat& i1, const cv::Mat& i2, BufferSSIM& b)
{
    constexpr float C1 = 6.5025f;
    constexpr float C2 = 58.5225f;

    b.gI1.upload(i1);
    b.gI2.upload(i2);

    cv::cuda::Stream stream;
    b.gI1.convertTo(b.t1, CV_32F, stream);
    b.gI2.convertTo(b.t2, CV_32F, stream);

    cv::cuda::split(b.t1, b.vI1, stream);
    cv::cuda::split(b.t2, b.vI2, stream);

    cv::Scalar mssim;
    cv::Ptr<cv::cuda::Filter> gauss = cv::cuda::createGaussianFilter(b.vI1[0].type(), -1, cv::Size(11, 11), 1.5);

    for (int i = 0; i < b.gI1.channels(); ++i)
    {
        // I2^2
        cv::cuda::multiply(b.vI2[i], b.vI2[i], b.I2_2, 1, -1, stream);

        // I1^2
        cv::cuda::multiply(b.vI1[i], b.vI1[i], b.I1_2, 1, -1, stream);

        // I1 * I2
        cv::cuda::multiply(b.vI1[i], b.vI2[i], b.I1_I2, 1, -1, stream);

        gauss->apply(b.vI1[i], b.mu1, stream);
        gauss->apply(b.vI2[i], b.mu2, stream);

        cv::cuda::multiply(b.mu1, b.mu1, b.mu1_2, 1, -1, stream);
        cv::cuda::multiply(b.mu2, b.mu2, b.mu2_2, 1, -1, stream);
        cv::cuda::multiply(b.mu1, b.mu2, b.mu1_mu2, 1, -1, stream);

        gauss->apply(b.I1_2, b.sigma1_2, stream);
        cv::cuda::subtract(b.sigma1_2, b.mu1_2, b.sigma1_2, cv::cuda::GpuMat(), -1, stream);
        // b.sigma1_2 -= b.mu1_2;  - This would result in an extra data transfer operation

        gauss->apply(b.I2_2, b.sigma2_2, stream);
        cv::cuda::subtract(b.sigma2_2, b.mu2_2, b.sigma2_2, cv::cuda::GpuMat(), -1, stream);
        // b.sigma2_2 -= b.mu2_2;

        gauss->apply(b.I1_I2, b.sigma12, stream);
        cv::cuda::subtract(b.sigma12, b.mu1_mu2, b.sigma12, cv::cuda::GpuMat(), -1, stream);
        // b.sigma12 -= b.mu1_mu2;

        // here too it would be an extra data transfer due to call of operator*(Scalar, Mat)
        // b.t1 = 2 * b.mu1_mu2 + C1;
        cv::cuda::multiply(b.mu1_mu2, 2, b.t1, 1, -1, stream);
        cv::cuda::add(b.t1, C1, b.t1, cv::cuda::GpuMat(), -1, stream);

        //b.t2 = 2 * b.sigma12 + C2;
        cv::cuda::multiply(b.sigma12, 2, b.t2, 1, -1, stream);
        cv::cuda::add(b.t2, C2, b.t2, cv::cuda::GpuMat(), -12, stream);

        // t3 = ((2*mu1_mu2 + C1).*(2*sigma12 + C2))
        cv::cuda::multiply(b.t1, b.t2, b.t3, 1, -1, stream);
        cv::cuda::add(b.mu1_2, b.mu2_2, b.t1, cv::cuda::GpuMat(), -1, stream);
        cv::cuda::add(b.t1, C1, b.t1, cv::cuda::GpuMat(), -1, stream);
        cv::cuda::add(b.sigma1_2, b.sigma2_2, b.t2, cv::cuda::GpuMat(), -1, stream);
        cv::cuda::add(b.t2, C2, b.t2, cv::cuda::GpuMat(), -1, stream);

        // t1 =((mu1_2 + mu2_2 + C1).*(sigma1_2 + sigma2_2 + C2))
        cv::cuda::multiply(b.t1, b.t2, b.t1, 1, -1, stream);

        // ssim_map =  t3./t1;
        cv::cuda::divide(b.t3, b.t1, b.ssim_map, 1, -1, stream);

        stream.waitForCompletion();
        cv::Scalar s = cv::cuda::sum(b.ssim_map, b.buf);
        mssim.val[i] = s.val[0] / (b.ssim_map.rows * b.ssim_map.cols);
    }
    return MeanFromRGBAScalar(mssim);
}

#else

double StructuralSimilarityIndexMultichannelCPU(const cv::Mat& img1_orig, const cv::Mat& img2_orig) {
    constexpr double C1 = 6.5025;
    constexpr double C2 = 58.5225;

    cv::Mat img1, img2;
    img1_orig.convertTo(img1, CV_32F);
    img2_orig.convertTo(img2, CV_32F);

    cv::Mat img2_squared = img2.mul(img2);
    cv::Mat img1_squared = img1.mul(img1);

    cv::Mat img1_img2_mul = img1.mul(img2);

    cv::Mat mu1, mu2;
    cv::GaussianBlur(img1, mu1, cv::Size(11, 11), 1.5);
    cv::GaussianBlur(img2, mu2, cv::Size(11, 11), 1.5);

    cv::Mat mu1_squared = mu1.mul(mu1);
    cv::Mat mu2_squared = mu2.mul(mu2);

    cv::Mat mu1_mu2_mul = mu1.mul(mu2);

    cv::Mat sigma1_squared, sigma2_squared, sigma_mul;
    cv::GaussianBlur(img1_squared, sigma1_squared, cv::Size(11, 11), 1.5);
    sigma1_squared -= mu1_squared;

    cv::GaussianBlur(img2_squared, sigma2_squared, cv::Size(11, 11), 1.5);
    sigma2_squared -= mu2_squared;

    cv::GaussianBlur(img1_img2_mul, sigma_mul, cv::Size(11, 11), 1.5);
    sigma_mul -= mu1_mu2_mul;

    cv::Mat t1, t2, t3;
    t1 = 2 * mu1_mu2_mul + C1;
    t2 = 2 * sigma_mul + C2;
    t3 = t1.mul(t2);
    t1 = mu1_squared + mu2_squared + C1;
    t2 = sigma1_squared + sigma2_squared + C2;
    t1 = t1.mul(t2);

    cv::Mat ssim_map;
    cv::divide(t3, t1, ssim_map);
    cv::Scalar mssim_channels = cv::mean(ssim_map);
    return MeanFromRGBAScalar(mssim_channels);
}

#endif
