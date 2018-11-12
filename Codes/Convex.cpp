#include "pch.h"
#include "Convex.h"

#define endl '\n'

namespace Convex
{
	static vector <Point> points, result;
	static queue <Point> to_show;
	static const char win[] = "click to select";
	static const int width = 1000, height = 1000, min_dis = 30, radius = 2;

	// 闲的蛋疼写的Lambda
	static auto cmp = [](Point a, Point b) -> bool 
	{
		a.x -= points[0].x;
		a.y -= points[0].y;
		b.x -= points[0].x;
		b.y -= points[0].y;

		int x_plus = a.x * b.y - a.y * b.x;

		if (x_plus == 0)
		{
			if (a.x == b.x)
				return a.y < b.y;
			else
				return a.x < b.x;
		}
		else
			return x_plus > 0;
	};

	// 获取两个点之间的距离，返回整数
	static int dis(Point a, Point b)
	{
		int dis_x = a.x - b.x;
		int dis_y = a.y - b.y;

		return (int)sqrt(dis_x * dis_x + dis_y * dis_y);
	}

	// 获取两个点之间的距离，返回double
	static double dis_f(Point a, Point b)
	{
		double dis_x = a.x - b.x;
		double dis_y = a.y - b.y;

		return sqrt(dis_x * dis_x + dis_y * dis_y);
	}

	// 利用三个点的坐标计算一个三角形的面积，未对共线情况特殊处理
	static double Get_Triangle_Aera(Point A, Point B, Point C)
	{
		double a = dis_f(B, C);
		double b = dis_f(A, C);
		double c = dis_f(A, B);
		double p = (a + b + c) / 2.0;

		return sqrt(p * (p - a) * (p - b) * (p - c));
	}

	// OpenCV鼠标回调函数
	static void mouse_callback(int event, int x, int y, int flags, void*)
	{
		if (event == EVENT_LBUTTONDOWN || flags == EVENT_FLAG_LBUTTON)
		{
			if (points.empty())
			{
				points.emplace_back(Point(x, y));
				to_show.push(Point(x, y));

				cout << "Add: " << x << ' ' << y << endl;
			}
			else
			{
				Point now(x, y);
				int MIN = INT_MAX;

				for (auto& p : points)
				{
					MIN = min(MIN, dis(now, p));
				}

				if (MIN > min_dis)
				{
					points.emplace_back(now);
					to_show.push(now);

					cout << "Add: " << x << ' ' << y << endl;
				}
			}
		}
	}

	// 对用户鼠标点击选择的点集生成凸包
	static void Get_Result()
	{
		int num = points.size(), index = 0;
		auto tmp = new Point[points.size()];

		for (int i = 1; i < num; ++i)
		{
			if (points[i].x <= points[index].x && points[i].y <= points[index].y)
				index = i;
		}
		swap(points[0], points[index]);

		sort(points.begin() + 1, points.end(), cmp);

		index = 1;
		tmp[0] = points[0];
		tmp[1] = points[1];
		for (int i = 2; i < num; ++i)
		{
			Point a(tmp[index].x - tmp[index - 1].x, tmp[index].y - tmp[index - 1].y);
			Point b(points[i].x - tmp[index - 1].x, points[i].y - tmp[index - 1].y);

			int plus = a.x * b.y - a.y * b.x;

			if (plus >= 0)
			{
				index++;
				tmp[index] = points[i];
			}
			else
			{
				i--;
				index--;
			}
		}

		for (int i = 0; i <= index; ++i)
		{
			result.emplace_back(tmp[i]);
		}
		delete[] tmp;
	}

	// 把生成的凸包结果显示在图像上（生成结果之后）
	static void Show_Result(Mat& img)
	{
		for (auto& p : result)
		{
			circle
			(
				img,
				p,
				radius * 5,
				CV_RGB(255, 255, 255),
				1,
				LINE_AA
			);
		}

		int num = result.size();
		for (int i = 1; i < num; ++i)
		{
			line
			(
				img,
				result[i],
				result[i - 1],
				CV_RGB(255, 255, 255),
				1,
				LINE_AA
			);
		}
		line
		(
			img,
			result[0],
			result[num - 1],
			CV_RGB(255, 255, 255),
			1,
			LINE_AA
		);
	}

	// 对一个凸包求面积（生成结果之后）
	static double Get_Convex_Aera()
	{
		int num = result.size();
		double ans = 0;

		Point origin = result[0];

		for (int i = 2; i < num; ++i)
		{
			ans += Get_Triangle_Aera(origin, result[i], result[i - 1]);
		}
		return ans;
	}

	// 对一个凸包求周长（生成结果之后）
	static double Get_Convex_Perimeter()
	{
		int num = result.size();
		double ans = 0;

		for (int i = 1; i < num; ++i)
		{
			ans += dis_f(result[i], result[i - 1]);
		}
		ans += dis_f(result[0], result[num - 1]);

		return ans;
	}

	// 储存原始点集（生成结果之后）
	static void Store_Raw_Data(const char* fname)
	{
		ofstream of(fname);

		of << points.size() << endl;
		for (auto& p : points)
		{
			of << p.x << ' ' << p.y << endl;
		}
		of.close();
	}

	// 储存最终构成凸包的点集，并求面积和周长（生成结果）
	static void Store_Result_Data(const char* fname)
	{
#ifdef ACM
		ofstream of(fname);

		of << fixed << setprecision(0) << Get_Convex_Perimeter() << endl;
#else
		ofstream of(fname);

		of << result.size() << endl;
		for (auto& p : result)
		{
			of << p.x << ' ' << p.y << endl;
		}
		of << "Perimeter: " << Get_Convex_Perimeter() << endl;
		of << "Aera: " << Get_Convex_Aera() << endl;
		of.close();
#endif
	}
}

void Convex::Get_Convex(const char* fname_in, const char* fname_out, bool store_img)
{
	Mat img(height, width, CV_8UC1, CV_RGB(0 ,0, 0));

	points.clear();
	result.clear();
	while (!to_show.empty())
		to_show.pop();

	namedWindow(win);
	setMouseCallback(win, mouse_callback);
	imshow(win, img);

	while (waitKey(50) != esc)
	{
		if (!to_show.empty())
		{
			while (!to_show.empty())
			{
				circle
				(
					img,
					to_show.front(),
					radius,
					CV_RGB(255, 255, 255),
					radius,
					LINE_AA
				);

				cout << "Draw: " << to_show.front().x << ' ' << to_show.front().y << endl;

				to_show.pop();
			}
			imshow(win, img);
		}
	}

	destroyWindow(win);

	if (points.size() < 3)
		return;

	if (store_img)
	{
		imwrite("../User_Data/hint_input.png", img);
	}

	Get_Result();

	Show_Result(img);

	if (store_img)
	{
		imwrite("../User_Data/hint_output.png", img);
	}

	imshow("CONVEX", img);
	while (waitKey(0) != esc);
	destroyWindow("CONVEX");

	Store_Raw_Data(fname_in);
	Store_Result_Data(fname_out);
}
// end of convex.cpp