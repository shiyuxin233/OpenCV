#ifndef CONVEX_H
#define CONVEX_H

#include "pch.h"

using namespace std;
using namespace cv;

namespace Convex
{
	// 用户在图像上自由选区一系列点，程序从中选择出能构成凸包的点集，并将横纵坐标保存在文件中
	// 2018-11-2 未完待续
	// 2018-11-4 基本完成
	void Get_Convex
	(
		const char* fname_in = "../User_Data/data0.in", 
		const char* fname_out = "../User_Data/data0.out", 
		bool store_img = false
	);
}

#endif // Convex.h