#include "pch.h"
#include "MyFunc.h"
#include "Affine.h"
#include "Perspective.h"
#include "Paint_1.h"
#include "Convex.h"
#include "Demos.h"

using namespace std;

const char* videos[]
{
	"../input/video-test.mp4"
};

const char* images[]
{
	"../input/pic1.jpg", // 本贾尼
	"../input/pic2.jpg", // 树莓派logo
	"../input/pic3.jpg", // Ubuntu Mate Logo
	"../input/pic4.jpg", // ACO截图1
	"../input/pic5.jpg", // ACO截图2
	"../input/pic6.jpg", // Python他爹
	"../input/pic7.jpg", // Aorus Logo
	"../input/pic8.jpg", // ROG Logo
	"../input/pic9.jpg", // 老黄
	"../input/pic10.jpg", // OpenCV Logo
	"../input/pic11.jpg" // 网上找的图
};

int main()
{
	using namespace cv;
	
	setNumThreads(4);

	/***********************
	  * Begin of user code.*
	  **********************
	  */
#if 1

	Mat src = imread(images[10]), dst;

	int thres = 50;
	namedWindow("demo");
	createTrackbar("threshold", "demo", &thres, 255);

	while (waitKey(300) != esc)
	{
		dst = Demos::demo1(src, thres);
		imshow("demo", dst);
	}

#elif 1

	Mat src = imread(images[10]), dst;

	dst = Demos::demo1_plus(src);

	imshow("demo plus", dst);

	while (waitKey(0) != esc);

#endif

	

	/*********************
	  * End of user code.*
	  ********************
	  */

	destroyAllWindows();
	system("pause");
	return 0;
}