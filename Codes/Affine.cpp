#include "pch.h"
#include "Affine.h"

namespace Affine
{
	static Mat src;
	static Point2f from[3], to[3];
	static char win[20] = "Affine Demo";
	static int width, height;
	static const int radius = 12;
	static const int border = 20;

	static void mouse_callback(int event, int x, int y, int flags, void*);
	static float get_distance(const Point2f& a, const Point2f& b);
}

void Affine::Affine(const Mat& img)
{
	namedWindow(win);
	copyMakeBorder(img, src, border, border, border, border, BORDER_CONSTANT, CV_RGB(0, 0, 0));
	setMouseCallback(win, mouse_callback, NULL);

	width = img.cols;
	height = img.rows;

	from[0].x = to[0].x = border;
	from[0].y = to[0].y = border;

	from[1].x = to[1].x = border + width;
	from[1].y = to[1].y = border;

	from[2].x = to[2].x = border;
	from[2].y = to[2].y = border + height;

	while (waitKey(1) != esc)
	{
		Mat show, warp = getAffineTransform(from, to);
		warpAffine(src, show, warp, src.size());

		for (auto& p : to)
			circle
			(
				show,
				p,
				radius,
				CV_RGB(255, 0, 0),
				1,
				LINE_AA
			);

		imshow(win, show);
	}

	destroyWindow(win);
}

float Affine::get_distance(const Point2f& a, const Point2f& b)
{
	float dis1 = a.x - b.x;
	float dis2 = a.y - b.y;
	return sqrt(dis1 * dis1 + dis2 * dis2);
}

void Affine::mouse_callback(int event, int x, int y, int flags, void*)
{
	if (event == EVENT_LBUTTONDOWN ||
		flags == EVENT_FLAG_LBUTTON)
	{
		Point2f m(x, y);

		float dis1 = get_distance(m, to[0]);
		float dis2 = get_distance(m, to[1]);
		float dis3 = get_distance(m, to[2]);

		if (dis1 <= radius)
			to[0] = m;
		else if (dis2 <= radius)
			to[1] = m;
		else if (dis3 <= radius)
			to[2] = m;
	}
}
// end of file