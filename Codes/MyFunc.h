#ifndef MYFUNC_H
#define MYFUNC_H

#include "pch.h"

// ������ѧϰOpenCV3��ԭ��1-11�����漰�Ĳ��ֺ�����������

using namespace std;

// Canny��Ե��⺯����ʹ��
void Canny_Demo();

// ��չͼ���Ե�ĺ���
void Make_Border_Demo(const char* fname);

// ��ֵ�������˻Ҷ�ͼ
void Threshold_Demo(const char* fname);

// ����Ӧ��ֵ���������ڻҶ�ͼ
void AdaptiveThreshold_Demo(const char* fname);

// ����Ӧ��ֵ������������Ƶ
void AdaptiveThreshold_VideoDemo();

// ƽ��ֵ�˲�����ֵ�˲�
void Blur_MedianBlur(const char* fname);

// ��˹�˲���sigma��Ч����Ӱ�죨�˴�СΪ15 * 15��
void Gaussian_Sigma_Effect(const char* fname);

// ˫���˲�����ʹ��
void Bilateral_Filter_Demo(const char* fname);

// ����������������
void Sobel_Demo(const char* fname);

// Scharr�˲���ʵ��
void Scharr_Demo(const char* fname, bool gray = false);

// ������˹�任
void Laplacian_Demo(const char* fname, bool gray = false);

// ͼ������Ͳ���
void Dilate_Demo(const char* fname, bool gray = false);

// ͼ��ĸ�ʴ����
void Erode_Demo(const char* fname, bool gray = false);

// ͨ����̬ѧ�������������� ��������ʱͼ��
void MorphologyEx_Open_Demo(const char* fname);

// ͨ����̬ѧ���������ղ��� ��������ʱͼ��
void MorphologyEx_Close_Demo(const char* fname);

// ͨ����̬ѧ����������̬ѧ�ݶ� ����Ҫ��ʱͼ��
void MorphologyEx_Gradient_Demo(const char* fname);

// ͨ����̬ѧ����������ñ���� ���͵ص��ã�
void MorphologyEx_Tophat_Demo(const char* fname);

// ͨ����̬ѧ����������ñ���� ���͵ص��ã�
void MorphologyEx_Blackhat_Demo(const char* fname);

// ͼ��任-resize
void Resize_Demo(const char* fname);

// ����任����warpaffine
void WarpAffine_Demo(const char* fname);

// ������ת������LogPolar
void LogPolar_Demo(const char* fname);

// ����ӳ�䡪��remap
void Remap_Demo(const char* fname);

// ͼ���޸�����inpaint
cv::Mat Inpaint_Demo(const cv::Mat& to_fix, const cv::Mat& trace);

// ���ٷǾֲ���ֵȥ�롪��Fast Non-Local Means Denoising
// һ��ʼ��֪�������������������ô������Ϊ����ֱ��ʵʱ������Ƶ������һ��
void FNLMD_Demo(int cam = 0);

// ���ٷǾֲ���ֵȥ�롪���Ҷ�ͼ
// ͬ��
void FNLMD_Gray_Demo(int cam = 0);

// FNLMD_Multi�������ٶȼ���
// ���Ĭ������ͷ��0��ץȡ6��ͼƬ��֮��ʹ��fastNlMeansDenoisingColoredMulti()���н���
void FNLMD_Multi_Demo(int cam = 0);

// ֱ��ͼ���⻯����equalizeHist
void EqualizeHist_Demo(int cam = 0);

#endif // MyFunc.h