#include "pch.h"
#include "Demos.h"

namespace Demos
{
	Mat demo1(const Mat& img, int thres)
	{
		Mat src = img, x, y, res, ret;

		Scharr(src, x, CV_16S, 1, 0);
		Scharr(src, y, CV_16S, 0, 1);
		addWeighted(x, 0.5, y, 0.5, 0.0, res);
		convertScaleAbs(res, res);
		cvtColor(res, res, CV_BGR2GRAY);

		threshold(res, ret, thres, 255, THRESH_TOZERO);

		return ret;
	}

	Mat demo1_plus(const Mat& img)
	{
		Mat src = demo1(img, 0), dst;
		bilateralFilter(src, dst, 10, 5, 3, BORDER_REFLECT_101);
		return dst;
	}
}