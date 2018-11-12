#ifndef DEMOS_H
#define DEMOS_H

#include "pch.h"

namespace Demos
{
	using namespace cv;

	// 维基百科关于索贝尔求导介绍页面上的一张示例图片，尽量做出那个效果
	Mat demo1(const Mat& img, int thres = 50);
	Mat demo1_plus(const Mat& img);
}

#endif // Demos.h
