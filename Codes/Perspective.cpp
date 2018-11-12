#include "pch.h"
#include "Perspective.h"

namespace Perspective
{
	static Mat src;
	static Point2f from[4], to[4];
	static const char win[20] = "Perspective";
	static const int border = 50, radius = 12;
	static int width, height;
	static bool changed = true;

	static float distance(const Point2f& a, const Point2f& b);
	static void callback(int event, int x, int y, int flags, void*);
}

void Perspective::Perspective(const Mat& img)
{
	namedWindow(win);
	setMouseCallback(win, callback, NULL);
	copyMakeBorder
	(
		img, src, 
		border, border, border, border, 
		BORDER_CONSTANT, 
		CV_RGB(0, 0, 0)
	);

	width = img.cols;
	height = img.rows;

	from[0].x = to[0].x = border;
	from[0].y = to[0].y = border;

	from[1].x = to[1].x = border + width;
	from[1].y = to[1].y = border;

	from[2].x = to[2].x = border + width;
	from[2].y = to[2].y = border + height;

	from[3].x = to[3].x = border;
	from[3].y = to[3].y = border + height;

	changed = true;

	Mat show;
	while (waitKey(1) != esc)
	{
		if (changed)
		{
			Mat warp = getPerspectiveTransform(from, to);
			warpPerspective(src, show, warp, src.size());

			for (auto& p : to)
				circle
				(
					show,
					p,
					radius,
					CV_RGB(50, 100, 80),
					1,
					LINE_AA
				);

			imshow(win, show);
		}
	}

	destroyWindow(win);
}

static float Perspective::distance(const Point2f& a, const Point2f& b)
{
	float dis1 = a.x - b.x;
	float dis2 = a.y - b.y;
	return sqrt(dis1 * dis1 + dis2 * dis2);
}

static void Perspective::callback(int event, int x, int y, int flags, void*)
{
	Point2f m(x, y);

	if (event == EVENT_LBUTTONDOWN || 
		flags == EVENT_FLAG_LBUTTON)
	{
		float dis0 = distance(m, to[0]);
		float dis1 = distance(m, to[1]);
		float dis2 = distance(m, to[2]);
		float dis3 = distance(m, to[3]);

		if (dis0 <= radius)
		{
			to[0] = m;
			changed = true;
		}
		else if (dis1 <= radius)
		{
			to[1] = m;
			changed = true;
		}
		else if (dis2 <= radius)
		{
			to[2] = m;
			changed = true;
		}
		else if (dis3 <= radius)
		{
			to[3] = m;
			changed = true;
		}
		else
			changed = false;
	}
	else
		changed = false;
}
// end of file