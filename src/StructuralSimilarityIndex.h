#pragma once

// From https://docs.opencv.org/master/d5/dc4/tutorial_video_input_psnr_ssim.html
// and https://docs.opencv.org/master/dd/d3d/tutorial_gpu_basics_similarity.html
// Small changes for readability.

#include <opencv2/core.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/cuda.hpp>
#include <vector>

#if GPU_SSIM

#include <opencv2/cudaarithm.hpp>
#include <opencv2/cudafilters.hpp>

struct BufferSSIM {
    // Data allocations are very expensive on CUDA. Use a buffer to solve: allocate once reuse later.
    cv::cuda::GpuMat gI1, gI2, gs, t1, t2;
    cv::cuda::GpuMat I1_2, I2_2, I1_I2;
    std::vector<cv::cuda::GpuMat> vI1, vI2;
    cv::cuda::GpuMat mu1, mu2;
    cv::cuda::GpuMat mu1_2, mu2_2, mu1_mu2;
    cv::cuda::GpuMat sigma1_2, sigma2_2, sigma12;
    cv::cuda::GpuMat t3;
    cv::cuda::GpuMat ssim_map;
    cv::cuda::GpuMat buf;
};

double StructuralSimilarityIndexMultichannelCUDA(const cv::Mat& i1, const cv::Mat& i2, BufferSSIM& b);

#else

#include <opencv2/imgproc.hpp>

double StructuralSimilarityIndexMultichannelCPU(const cv::Mat& img1_orig, const cv::Mat& img2_orig);

#endif

double MeanFromRGBAScalar(const cv::Scalar& scalar);
