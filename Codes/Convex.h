#ifndef CONVEX_H
#define CONVEX_H

#include "pch.h"

using namespace std;
using namespace cv;

namespace Convex
{
	// �û���ͼ��������ѡ��һϵ�е㣬�������ѡ����ܹ���͹���ĵ㼯�������������걣�����ļ���
	// 2018-11-2 δ�����
	// 2018-11-4 �������
	void Get_Convex
	(
		const char* fname_in = "../User_Data/data0.in", 
		const char* fname_out = "../User_Data/data0.out", 
		bool store_img = false
	);
}

#endif // Convex.h