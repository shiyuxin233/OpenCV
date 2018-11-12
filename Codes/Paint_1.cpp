#include "pch.h"
#include "Paint_1.h"

namespace Paint_1
{
	static int R = 0, G = 0, B = 0;
	static const int radius = 1;
	static queue <Point> points;
	static const char win[] = "Paint with mouse";

	static float distance(Point a, Point b);
	static void mouse_callback(int event, int x, int y, int flags, void*);
}

Mat Paint_1::Paint(const Mat& img, Mat& track, bool with_track)
{
	Mat src = img, ret = img;
	Point from(-1, -1), to(-1, -1);
	track.create(img.size(), CV_8UC1);
	namedWindow(win);

	for (int i = 0; i < img.cols; ++i)
		for (int j = 0; j < img.rows; ++j)
			track.at<unsigned char>(j, i) = 0;

	setMouseCallback(win, mouse_callback);

	createTrackbar("R", win, &R, 255);
	createTrackbar("G", win, &G, 255);
	createTrackbar("B", win, &B, 255);

	imshow(win, ret);
	if (with_track)
		imshow("track", track);

	while (waitKey(1) != esc)
	{
		if (points.size() > 1)
		{
			from = points.front(), to;
			points.pop();

			while (!points.empty())
			{
				to = points.front();
				points.pop();

				line(ret, from, to, CV_RGB(R, G, B), 2, LINE_AA);
				line(track, from, to, CV_RGB(255, 255, 255), 2, LINE_AA);

				from = to;
			}
			imshow(win, ret);
			if (with_track)
				imshow("track", track);
		}
		else if (points.size() == 1 && from.x != -1 && from.y != -1)
		{
			to = points.front();
			points.pop();

			float dis = distance(from, to);

			if (dis <= 10)
			{
				line(ret, from, to, CV_RGB(R, G, B), 2, LINE_AA);
				imshow(win, ret);
			}
		}
	}

	while (!points.empty()) 
		points.pop();

	destroyWindow(win);
	if (with_track)
		destroyWindow("track");
	return ret;
}

static void Paint_1::mouse_callback(int event, int x, int y, int flags, void*)
{
	if (event == EVENT_LBUTTONDOWN || flags == EVENT_FLAG_LBUTTON)
	{
		points.push(Point(x, y));
	}
}

static float Paint_1::distance(Point a, Point b)
{
	int dis1 = a.x - b.x;
	int dis2 = a.y - b.y;
	return sqrt(dis1 * dis1 + dis2 * dis2);
}
// end of file