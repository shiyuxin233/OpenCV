#ifndef PAINT_1
#define PAINT_1

#include "pch.h"

using namespace std;
using namespace cv;

// һ���Ƚ�ʧ�ܵĻ�ͼ����

namespace Paint_1
{
	Mat Paint(const Mat& img, Mat& track, bool show_track = false);
}

#endif // Paint_1.h