#include "pch.h"
#include "MyFunc.h"

void Canny_Demo()
{
	using namespace cv;

	VideoCapture cap(0);

	constexpr char win_name1[] = "origin footage";
	constexpr char win_name2[] = "edge detect";

	if (cap.isOpened())
	{
		int t1 = 40, t2 = 20;
		Mat frame, edge;
		auto time = getTickCount();

		namedWindow(win_name1);
		namedWindow(win_name2);

		createTrackbar("ãÐÖµ1", win_name2, &t1, 150);
		createTrackbar("ãÐÖµ2", win_name2, &t2, 150);

		while (cap.read(frame))
		{
			double fps = 1.0 / ((getTickCount() - time) / getTickFrequency());
			ostringstream os;
			os << "fps at: " << fps;

			Canny(frame, edge, t1, t2, 3, true);
			displayOverlay(win_name1, os.str(), 0);
			displayStatusBar(win_name2, os.str(), 0);

			imshow(win_name1, frame);
			imshow(win_name2, edge);

			if (waitKey(1) == esc)
				break;

			time = getTickCount();
		}
	}

	destroyWindow(win_name1);
	destroyWindow(win_name2);
}

void Make_Border_Demo(const char* fname)
{
	using namespace cv;

	int type[] =
	{
		BORDER_CONSTANT,
		BORDER_REPLICATE,
		BORDER_REFLECT,
		BORDER_WRAP,
		BORDER_REFLECT_101
	}, index = 0, last = 1;

	const char* name[] =
	{
		"border constant",
		"border replicate",
		"border reflect",
		"border wrap",
		"border reflect 101"
	};

	Mat img = imread(fname);
	Mat out;

	namedWindow("extended");
	createTrackbar("mode", "extended", &index, 4);

	while (waitKey(30) != esc)
	{
		if (last != index)
		{
			copyMakeBorder(
				img, out,
				100, 100, 100, 100,
				type[index],
				CV_RGB(100, 50, 0)
			);

			rectangle(
				out,
				Point(100, 100),
				Point(100 + img.cols, 100 + img.rows),
				CV_RGB(255, 0, 0),
				1,
				LINE_AA);

			imshow("extended", out);
			displayOverlay("extended", name[index]);

			last = index;
		}
	}

	destroyWindow("extended");
}

void Threshold_Demo(const char* fname)
{
	using namespace cv;

	int val = 100, last = 101;
	Mat img = imread(fname);
	Mat gry, out;
	cvtColor(img, gry, CV_BGR2GRAY);

	namedWindow("threshold");
	createTrackbar("threshold", "threshold", &val, 256);

	while (waitKey(30) != esc)
	{
		if (val != last)
		{
			if (val == 256)
				threshold(gry, out, THRESH_OTSU, 255, THRESH_TOZERO);
			else
				threshold(gry, out, val, 255, THRESH_TOZERO);
			imshow("threshold", out);
			last = val;
		}
	}

	destroyWindow("threshold");
}

void AdaptiveThreshold_Demo(const char* fname)
{
	using namespace cv;

	namedWindow("adaptive threshold");
	Mat img = imread(fname);
	Mat out, gry;

	cvtColor(img, gry, CV_BGR2GRAY);

	adaptiveThreshold(
		gry,
		out,
		255,
		ADAPTIVE_THRESH_GAUSSIAN_C,
		THRESH_BINARY,
		13,
		0
	);

	imshow("adaptive threshold", out);
	displayOverlay("adaptive threshold", "paused", 100000);
	while (waitKey(100) != esc);

	destroyWindow("adaptive threshold");
}

void AdaptiveThreshold_VideoDemo()
{
	using namespace cv;

	VideoCapture src(0);
	char winName[] = "adaptive threshold in video";

	if (src.isOpened())
	{
		Mat raw, gry, thr;

		auto time = clock();
		while (src.read(raw) && waitKey(1) != esc)
		{
			double fps = (clock() - (double)time) / CLOCKS_PER_SEC;
			fps = 1.0 / fps;
			ostringstream os;
			os << "fps at: " << fps;

			cvtColor(raw, gry, CV_BGR2GRAY);
			adaptiveThreshold(
				gry,
				thr,
				255,
				ADAPTIVE_THRESH_GAUSSIAN_C,
				THRESH_BINARY,
				15,
				0
			);
			imshow(winName, thr);
			displayOverlay(winName, os.str(), 0);

			time = clock();
		}
	}

	destroyWindow(winName);
}

void Blur_MedianBlur(const char* fname)
{
	using namespace cv;

	Mat src = imread(fname);
	Mat out_blur, out_median;

	char win1[] = "mean blur";
	char win2[] = "median blur";

	int ks1 = 1, ks2 = 1, last1 = 0, last2 = 0;

	namedWindow(win1);
	namedWindow(win2);
	createTrackbar("kernal size", win1, &ks1, 30);
	createTrackbar("kernal size", win2, &ks2, 30);

	while (waitKey(30) != esc)
	{
		if (ks1 != last1)
		{
			last1 = ks1;

			ostringstream os;
			os << "kernal size: " << 2 * ks1 + 1;
			displayOverlay(win1, os.str(), 0);

			blur(src, out_blur, {2 * ks1 + 1, 2 * ks1 + 1});

			imshow(win1, out_blur);
		}

		if (ks2 != last2)
		{
			last2 = ks2;

			ostringstream os;
			os << "kernal size: " << 2 * ks2 + 1;
			displayOverlay(win2, os.str(), 0);

			medianBlur(src, out_median, 2 * ks2 + 1);

			imshow(win2, out_median);
		}
	}

	destroyWindow(win1);
	destroyWindow(win2);
}

void Gaussian_Sigma_Effect(const char* fname)
{
	using namespace cv;

	Mat src = imread(fname);
	Mat out;

	char win[] = "Gaussian Blur";

	int sigma = 1, last = 2;

	namedWindow(win);
	createTrackbar("sigma value", win, &sigma, 10);

	while (waitKey(100) != esc)
	{
		if (last != sigma)
		{
			last = sigma;

			GaussianBlur(src, out, { 15, 15 }, sigma, sigma, BORDER_REFLECT_101);

			ostringstream os;
			os << "current sigma value: " << sigma;

			displayOverlay(win, os.str(), 0);

			imshow(win, out);
		}
	}

	destroyWindow(win);
}

void Bilateral_Filter_Demo(const char* fname)
{
	using namespace cv;

	Mat img = imread(fname);
	Mat noise(img.rows, img.cols, CV_8UC3);
	Mat out, src;

	randu(noise, 0, 255);
	addWeighted(img, 0.7, noise, 0.3, 0.0, src);
	imshow("source", src);

	int sigma_color = 1, sigma_space = 1, last_color = 2, last_space = 2;

	char win[] = "bilateral blur demo";

	namedWindow(win);
	createTrackbar("sigmaColor", win, &sigma_color, 500);
	createTrackbar("sigmaSpace", win, &sigma_space, 500);

	while (waitKey(100) != esc)
	{
		if (last_color != sigma_color || last_space != sigma_space)
		{
			last_color = sigma_color;
			last_space = sigma_space;

			ostringstream os;
			os << "sigmaColor: " << sigma_color / 10.0 << " sigmaSpace: " << sigma_space / 10.0;
			displayOverlay(win, os.str(), 0);

			bilateralFilter(src, out, 9, sigma_color / 10.0, sigma_space / 10.0, BORDER_REFLECT_101);

			imshow(win, out);
		}
	}

	destroyWindow(win);
	destroyWindow("source");
}

void Sobel_Demo(const char* fname)
{
	using namespace cv;

	Mat src = imread(fname);
	Mat out, show;

	char win[] = "Sobel operator";

	int x = 1, y = 0, last_x = -1, last_y = -1;

	namedWindow(win);
	createTrackbar("Derivative - X", win, &x, 2);
	createTrackbar("Derivative - Y", win, &y, 2);

	while (waitKey(200) != esc)
	{
		if (last_x != x)
		{
			last_x = x;

			if (x == 0 && y == 0)
			{
				setTrackbarPos("Derivative - X", win, 1);
				x = 1;
			}
			else
			{
				Sobel(src, out, CV_16S, x, y, 3, 1, 0, BORDER_REFLECT_101);
				convertScaleAbs(out, show);

				imshow(win, show);
			}
		}

		if (last_y != y)
		{
			last_y = y;

			if (x == 0 && y == 0)
			{
				setTrackbarPos("Derivative - Y", win, 1);
				y = 1;
			}
			else
			{
				Sobel(src, out, CV_16S, x, y, 3, 1, 0, BORDER_REFLECT_101);
				convertScaleAbs(out, show);

				imshow(win, show);
			}
		}
	}

	destroyWindow(win);
}

void Scharr_Demo(const char* fname, bool gray)
{
	using namespace cv;

	Mat img = imread(fname);
	Mat out_x, out_y, convert_x, convert_y, show, src;

	char win1[] = "X-derivative";
	char win2[] = "Y-derivative";
	char win3[] = "Result";

	if (gray)
		cvtColor(img, src, CV_BGR2GRAY);
	else
		src = img;

	Scharr(src, out_x, CV_16S, 1, 0);
	Scharr(src, out_y, CV_16S, 0, 1);

	convertScaleAbs(out_x, convert_x);
	convertScaleAbs(out_y, convert_y);

	addWeighted(convert_x, 0.5, convert_y, 0.5, 0.0, show);

	imshow(win1, convert_x);
	imshow(win2, convert_y);
	imshow(win3, show);

	if (gray)
	{
		displayOverlay(win1, "gray-X", 0);
		displayOverlay(win2, "gray-y", 0);
		displayOverlay(win3, "gray-result", 0);
	}
	else
	{
		displayOverlay(win1, "BGR-x", 0);
		displayOverlay(win2, "BGR-y", 0);
		displayOverlay(win3, "BGR-result", 0);
	}

	while (waitKey(300) != esc);

	destroyWindow(win1);
	destroyWindow(win2);
	destroyWindow(win3);
}

void Laplacian_Demo(const char* fname, bool gray)
{
	using namespace cv;

	Mat img, src, converted, show;
	int ks = 0, last = -1;
	char win[] = "Laplacian operate Demo";

	img = imread(fname);
	if (gray)
		cvtColor(img, src, CV_BGR2GRAY);
	else
		src = img;

	namedWindow(win);
	createTrackbar("kernal size value:", win, &ks, 3);

	while (waitKey(300) != esc)
	{
		if (ks != last)
		{
			ostringstream os;
			last = ks;

			os << "kernal size: " << 2 * ks + 1;
			Laplacian(src, converted, CV_16S, 2 * ks + 1, 1, 0, BORDER_REFLECT_101);
			convertScaleAbs(converted, show);

			displayOverlay(win, os.str(), 0);
			imshow(win, show);

			os.clear();
		}
	}

	destroyWindow(win);
}

void Dilate_Demo(const char* fname, bool gray)
{
	using namespace cv;

	Mat img, src, show;
	char win[] = "Dilate operate";
	int time = 1, last = -1;

	namedWindow(win);
	createTrackbar("iteration time", win, &time, 10);
	img = imread(fname);

	if (gray)
		cvtColor(img, src, CV_BGR2GRAY);
	else
		src = img;

	while (waitKey(300) != esc)
	{
		if (last != time)
		{
			ostringstream os;
			last = time;
			os << "current iteration time: " << time;

			dilate
			(
				src, 
				show, 
				getStructuringElement(MORPH_ELLIPSE, {3, 3}),
				{ -1, -1 }, 
				time, 
				BORDER_REFLECT_101
			);
			imshow(win, show);
			displayOverlay(win, os.str(), 0);
		}
	}

	destroyWindow(win);
}

void Erode_Demo(const char* fname, bool gray)
{
	using namespace cv;

	Mat img, src, show;
	char win[] = "Dilate operate";
	int time = 1, last = -1;

	namedWindow(win);
	createTrackbar("iteration time", win, &time, 10);
	img = imread(fname);

	if (gray)
		cvtColor(img, src, CV_BGR2GRAY);
	else
		src = img;

	while (waitKey(300) != esc)
	{
		if (last != time)
		{
			ostringstream os;
			last = time;
			os << "current iteration time: " << time;

			erode
			(
				src,
				show,
				getStructuringElement(MORPH_ELLIPSE, { 3, 3 }),
				{ -1, -1 },
				time,
				BORDER_REFLECT_101
			);
			imshow(win, show);
			displayOverlay(win, os.str(), 0);

			os.clear();
		}
	}

	destroyWindow(win);
}

void MorphologyEx_Open_Demo(const char* fname)
{
	using namespace cv;

	Mat src, show;
	char win[] = "morphology open";
	int time = 1, last = -1;

	namedWindow(win);
	createTrackbar("iteration: ", win, &time, 5);
	src = imread(fname);

	while (waitKey(300) != esc)
	{
		if (last != time)
		{
			ostringstream os;
			last = time;
			os << "iteration time: " << time;

			morphologyEx(src, show, MORPH_OPEN, Mat(), { -1, -1 }, time);
			displayOverlay(win, os.str(), 0);
			imshow(win, show);
		}
	}

	destroyWindow(win);
}

void MorphologyEx_Close_Demo(const char* fname)
{
	using namespace cv;

	Mat src, show;
	char win[] = "morphology open";
	int time = 1, last = -1;

	namedWindow(win);
	createTrackbar("iteration: ", win, &time, 5);
	src = imread(fname);

	while (waitKey(300) != esc)
	{
		if (last != time)
		{
			ostringstream os;
			last = time;
			os << "iteration time: " << time;

			morphologyEx(src, show, MORPH_CLOSE, Mat(), { -1, -1 }, time);
			displayOverlay(win, os.str(), 0);
			imshow(win, show);
		}
	}

	destroyWindow(win);
}

void MorphologyEx_Gradient_Demo(const char* fname)
{
	using namespace cv;

	Mat src, show;
	int time = 1, last = -1;
	char win[] = "morphology gradient";

	src = imread(fname);
	namedWindow(win);
	createTrackbar("iteration: ", win, &time, 5);

	while (waitKey(300) != esc)
	{
		if (last != time)
		{
			ostringstream os;
			last = time;
			os << "iteration: " << time;

			morphologyEx(src, show, MORPH_GRADIENT, Mat(), { -1, -1 }, time, BORDER_REFLECT_101);
			displayOverlay(win, os.str(), 0);
			imshow(win, show);
		}
	}

	destroyWindow(win);
}

void MorphologyEx_Tophat_Demo(const char* fname)
{
	using namespace cv;

	Mat src, show;
	int time = 1, last = -1;
	char win[] = "morphology tophat";

	src = imread(fname);
	namedWindow(win);
	createTrackbar("iteration:", win, &time, 10);

	while (waitKey(300) != esc)
	{
		if (last != time)
		{
			ostringstream os;
			last = time;
			os << "iteration: " << time;

			morphologyEx
			(
				src, 
				show, 
				MORPH_TOPHAT, 
				getStructuringElement
				(
					MORPH_ELLIPSE,
					{ 3, 3 }, 
					{ -1, -1 }
				), 
				{ -1, -1 }, 
				time, 
				BORDER_REFLECT_101
			);

			if (!time)
			{
				imshow(win, src);
				displayOverlay(win, "original image", 0);
			}
			else
			{
				imshow(win, show);
				displayOverlay(win, os.str(), 0);
			}
		}
	}

	destroyWindow(win);
}

void MorphologyEx_Blackhat_Demo(const char* fname)
{
	using namespace cv;

	Mat src, show;
	int time = 1, last = -1;
	char win[] = "morphology blackhat";

	src = imread(fname);
	namedWindow(win);
	createTrackbar("iteration:", win, &time, 10);

	while (waitKey(300) != esc)
	{
		if (last != time)
		{
			ostringstream os;
			last = time;
			os << "iteration: " << time;

			morphologyEx
			(
				src,
				show,
				MORPH_BLACKHAT,
				getStructuringElement
				(
					MORPH_ELLIPSE,
					{ 3, 3 },
					{ -1, -1 }
				),
				{ -1, -1 },
				time,
				BORDER_REFLECT_101
			);

			if (!time)
			{
				imshow(win, src);
				displayOverlay(win, "original image", 0);
			}
			else
			{
				imshow(win, show);
				displayOverlay(win, os.str(), 0);
			}
		}
	}

	destroyWindow(win);
}

void Resize_Demo(const char* fname)
{
	using namespace cv;

	Mat src = imread(fname), out;
	int fx = 50, fy = 50, mode = 1;
	const int Mode[] = {
		INTER_NEAREST,
		INTER_LINEAR,
		INTER_CUBIC,
		INTER_AREA,
		INTER_LANCZOS4,
		INTER_LINEAR_EXACT
	};
	const char* ModeName[] = {
		"INTER_NEAREST",
		"INTER_LINEAR",
		"INTER_CUBIC",
		"INTER_AREA",
		"INTER_LANCZOS4",
		"INTER_LINEAR_EXACT"
	};
	const char win1[] = "original";
	const char win2[] = "resized";

	namedWindow(win1);
	namedWindow(win2);

	createTrackbar("Fx: ", win1, &fx, 200);
	createTrackbar("Fy: ", win1, &fy, 200);
	createTrackbar("Mode: ", win1, &mode, 5);

	while (waitKey(300) != esc)
	{
		if (fx == 0) fx++;
		if (fy == 0) fy++;

		resize(src, out, Size(), fx / 100.0, fy / 100.0, Mode[mode]);

		imshow(win1, src);
		imshow(win2, out);
		displayOverlay(win1, ModeName[mode], 0);
	}

	destroyWindow(win1);
	destroyWindow(win2);
}

void WarpAffine_Demo(const char* fname)
{
	using namespace cv;

	Mat src = imread(fname), img, tmp, show;

	char win[] = "affine";

	int width = src.cols;
	int height = src.rows;

	int scale = 100, last_s = -1;
	int angle = 0, last_a = -1;

	namedWindow(win);

	createTrackbar("SCALE", win, &scale, 200);
	createTrackbar("ANGLE", win, &angle, 360);

	while (waitKey(300) != esc)
	{
		if (last_s != scale || last_a != angle)
		{
			last_s = scale;
			last_a = angle;

			copyMakeBorder
			(
				src,
				img,
				abs(width - height) / 2,
				abs(width - height) / 2,
				abs(width - height) / 2,
				abs(width - height) / 2,
				BORDER_CONSTANT,
				CV_RGB(0, 0, 0)
			);

			Mat warp = getRotationMatrix2D
			(
				Point { img.cols / 2, img.rows / 2 },
				angle,
				1.0
			);

			warpAffine
			(
				img,
				tmp,
				warp,
				img.size()
			);

			warp = getRotationMatrix2D
			(
				Point {tmp.cols / 2, tmp.rows / 2},
				0,
				scale / 100.0
			);

			warpAffine
			(
				tmp,
				show,
				warp,
				tmp.size()
			);

			imshow(win, show);
		}
	}

	destroyWindow(win);
}

void LogPolar_Demo(const char* fname)
{
	using namespace cv;

	Mat src = imread(fname), log;
	int m = 1, x_percent = 50, y_percent = 50;
	const char win1[] = "log polar";
	const char win2[] = "source image";

	namedWindow(win1);
	namedWindow(win2);
	createTrackbar("m val", win1, &m, 100);
	createTrackbar("x per", win1, &x_percent, 100);
	createTrackbar("y per", win1, &y_percent, 100);

	while (waitKey(500) != esc)
	{
		if (x_percent == 0) x_percent++;
		if (y_percent == 0) y_percent++;

		logPolar
		(
			src, 
			log, 
			Point2f
			(
				src.cols * (x_percent / 100.0), 
				src.rows * (y_percent / 100.0)
			), 
			m, 
			WARP_POLAR_LINEAR | INTER_CUBIC
		);

		imshow(win1, log);
		imshow(win2, src);
		log.release();
	}

	destroyWindow(win1);
	destroyWindow(win2);
}

void Remap_Demo(const char* fname)
{
	using namespace cv;

	Mat src = imread(fname), dst, map_x, map_y;

	dst.create(src.size(), src.type());
	map_x.create(src.size(), CV_32FC1);
	map_y.create(src.size(), CV_32FC1);

	for (int i = 0; i < src.cols; ++i)
	{
		for (int j = 0; j < src.rows; ++j)
		{
			map_x.at<float>(j, i) = src.cols - i;
			map_y.at<float>(j, i) = src.rows - j;
		}
	}

	remap
	(
		src,
		dst,
		map_x,
		map_y,
		CV_INTER_LINEAR,
		BORDER_CONSTANT,
		CV_RGB(255, 0, 0)
	);

	imshow("original", src);
	imshow("remapped", dst);

	while (waitKey(0) != esc);

	destroyWindow("original");
	destroyWindow("remapped");
}

cv::Mat Inpaint_Demo(const cv::Mat& to_fix, const cv::Mat& trace)
{
	using namespace cv;

	if (to_fix.size() != trace.size() || trace.type() != CV_8UC1)
		abort();

	Mat ret;
	int radius = 5, last = 0;
	const char win1[] = "origin";
	const char win2[] = "fixed";

	namedWindow(win1);
	namedWindow(win2);

	createTrackbar("radius", win2, &radius, 20);

	imshow(win1, to_fix);
	while (waitKey(200) != esc)
	{
		if (last != radius)
		{
			if (radius == 0)
				radius = last = 1;

			last = radius;

			inpaint(to_fix, trace, ret, radius, INPAINT_TELEA);
			imshow(win2, ret);
		}
	}

	destroyWindow(win1);
	destroyWindow(win2);
	return ret;
}

void FNLMD_Demo(int cam)
{
	using namespace cv;

	Mat src, img, dst;
	VideoCapture cap(cam);

	int templateWindowSize = 7;
	int searchWindowSize = 21;
	int h_luminance = 3;
	int h_color = 3;

	const char win1[] = "Raw Stream";
	const char win2[] = "FNLMD";

	if (cap.isOpened())
	{
		namedWindow(win1);
		namedWindow(win2);

		createTrackbar("template win size", win1, &templateWindowSize, 42);
		createTrackbar("search win size", win1, &searchWindowSize, 126);
		createTrackbar("h luminance", win1, &h_luminance, 21);
		createTrackbar("h color", win1, &h_color, 21);
		displayOverlay(win1, "press any key to continue, esc top qiut", 0);

		while (cap.read(src) && waitKey(0) != esc)
		{
			if (templateWindowSize == 0) templateWindowSize++;
			if (searchWindowSize == 0) searchWindowSize++;
			if (h_luminance == 0) h_luminance++;
			if (h_color == 0) h_color++;

			pyrDown(src, img, Size(), BORDER_REFLECT_101);

			fastNlMeansDenoisingColored
			(
				img, 
				dst, 
				h_luminance, 
				h_color, 
				templateWindowSize, 
				searchWindowSize
			);
			imshow(win1, img);
			imshow(win2, dst);
		}
		destroyWindow(win1);
		destroyWindow(win2);
		cap.release();
	}
}

void FNLMD_Gray_Demo(int cam)
{
	using namespace cv;

	Mat src, img, dst;
	VideoCapture cap(cam);

	int h = 3;
	int templateWindowSize = 7;
	int searchWindowSize = 21;

	const char win1[] = "raw stream";
	const char win2[] = "FNLMD";

	if (cap.isOpened())
	{
		namedWindow(win1);
		namedWindow(win2);

		createTrackbar("h luminance", win1, &h, 21);
		createTrackbar("template window size", win1, &templateWindowSize, 42);
		createTrackbar("search window size", win1, &searchWindowSize, 126);

		while (cap.read(src) && waitKey(1) != esc)
		{
			if (h == 0) h++;
			if (templateWindowSize == 0) templateWindowSize++;
			if (searchWindowSize == 0) searchWindowSize++;

			cvtColor(src, src, CV_BGR2GRAY);
			resize(src, img, Size(), 0.8, 0.8, INTER_CUBIC);

			fastNlMeansDenoising
			(
				img, 
				dst, 
				h,
				templateWindowSize,
				searchWindowSize
			);

			imshow(win1, img);
			imshow(win2, dst);
		}
		destroyWindow(win1);
		destroyWindow(win2);
		cap.release();
	}
}

void FNLMD_Multi_Demo(int cam)
{
	using namespace cv;

	vector <Mat> imgs;
	VideoCapture cap(cam);

	if (cap.isOpened())
	{
		Mat dst;
		const int num = 6;
		const char win1[] = "origin";
		const char win2[] = "FNLMD";

		for (int i = 0; i < num; ++i)
		{
			cap.read(dst);
			if (!dst.empty())
				imgs.emplace_back(dst);
			else
				i--;
		}

		cap.release();
		namedWindow(win1);
		namedWindow(win2);

		int img_to_process = 3;
		int img_to_refer = 5;
		float h_luminance = 5.0;
		float h_color = 3.0;
		int templaeWindowSize = 7;
		int searchWindowSize = 21;

		imshow(win1, imgs[img_to_process]);

		auto begin_time = getTickCount();
		fastNlMeansDenoisingColoredMulti
		(
			imgs,
			dst,
			img_to_process,
			img_to_refer,
			h_luminance,
			h_color,
			templaeWindowSize,
			searchWindowSize
		);
		auto end_time = getTickCount();

		imshow(win2, dst);
		cout << "Time Consumption: " << (end_time - begin_time) / getTickFrequency() << endl;

		while (waitKey(0) != esc);
	}
}

void EqualizeHist_Demo(int cam)
{
	using namespace cv;

	VideoCapture cap(cam);

	if (cap.isOpened())
	{
		Mat src, dst;

		const char win1[] = "cam raw";
		const char win2[] = "equalize hist";

		namedWindow(win1);
		namedWindow(win2);

		auto time = getTickCount();

		while (cap.read(src) && waitKey(1) != esc)
		{
			Mat tmp1[3], tmp2[3];
			split(src, tmp1);

			for (int i = 0; i < 3; ++i)
			{
				equalizeHist(tmp1[i], tmp2[i]);
			}

			merge(tmp2, 3, dst);

			imshow(win1, src);
			imshow(win2, dst);

			cout << "FPS: " << 1.0 / ((getTickCount() - time) / getTickFrequency()) << endl;
			time = getTickCount();
		}

		cap.release();
		destroyWindow(win1);
		destroyWindow(win2);
	}
	else
	{
		cout << "Fail to access cam " << cam << ", exit." << endl;
	}
}
// end of MyFunc.cpp