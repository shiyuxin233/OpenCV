#ifndef MYFUNC_H
#define MYFUNC_H

#include "pch.h"

// 包含《学习OpenCV3》原书1-11章所涉及的部分函数的样例。

using namespace std;

// Canny边缘检测函数的使用
void Canny_Demo();

// 扩展图像边缘的函数
void Make_Border_Demo(const char* fname);

// 阈值函数过滤灰度图
void Threshold_Demo(const char* fname);

// 自适应阈值函数作用于灰度图
void AdaptiveThreshold_Demo(const char* fname);

// 自适应阈值函数作用于视频
void AdaptiveThreshold_VideoDemo();

// 平均值滤波与中值滤波
void Blur_MedianBlur(const char* fname);

// 高斯滤波中sigma对效果的影响（核大小为15 * 15）
void Gaussian_Sigma_Effect(const char* fname);

// 双边滤波器的使用
void Bilateral_Filter_Demo(const char* fname);

// 索贝尔导数的例子
void Sobel_Demo(const char* fname);

// Scharr滤波器实例
void Scharr_Demo(const char* fname, bool gray = false);

// 拉普拉斯变换
void Laplacian_Demo(const char* fname, bool gray = false);

// 图像的膨胀操作
void Dilate_Demo(const char* fname, bool gray = false);

// 图像的腐蚀操作
void Erode_Demo(const char* fname, bool gray = false);

// 通用形态学函数——开操作 （无需临时图像）
void MorphologyEx_Open_Demo(const char* fname);

// 通用形态学函数——闭操作 （无需临时图像）
void MorphologyEx_Close_Demo(const char* fname);

// 通用形态学函数——形态学梯度 （需要临时图像）
void MorphologyEx_Gradient_Demo(const char* fname);

// 通用形态学函数——顶帽操作 （就地调用）
void MorphologyEx_Tophat_Demo(const char* fname);

// 通用形态学函数——黑帽操作 （就地调用）
void MorphologyEx_Blackhat_Demo(const char* fname);

// 图像变换-resize
void Resize_Demo(const char* fname);

// 仿射变换——warpaffine
void WarpAffine_Demo(const char* fname);

// 极坐标转换——LogPolar
void LogPolar_Demo(const char* fname);

// 任意映射——remap
void Remap_Demo(const char* fname);

// 图像修复——inpaint
cv::Mat Inpaint_Demo(const cv::Mat& to_fix, const cv::Mat& trace);

// 快速非局部均值去噪——Fast Non-Local Means Denoising
// 一开始不知道这个函数处理起来这么慢，以为可以直接实时处理视频，将就一下
void FNLMD_Demo(int cam = 0);

// 快速非局部均值去噪——灰度图
// 同上
void FNLMD_Gray_Demo(int cam = 0);

// FNLMD_Multi，计算速度极慢
// 会从默认摄像头（0）抓取6张图片，之后使用fastNlMeansDenoisingColoredMulti()进行降噪
void FNLMD_Multi_Demo(int cam = 0);

// 直方图均衡化——equalizeHist
void EqualizeHist_Demo(int cam = 0);

#endif // MyFunc.h