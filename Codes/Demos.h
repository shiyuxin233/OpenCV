#ifndef DEMOS_H
#define DEMOS_H

#include "pch.h"

namespace Demos
{
	using namespace cv;

	// ά���ٿƹ����������󵼽���ҳ���ϵ�һ��ʾ��ͼƬ�����������Ǹ�Ч��
	Mat demo1(const Mat& img, int thres = 50);
	Mat demo1_plus(const Mat& img);
}

#endif // Demos.h
