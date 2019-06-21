#ifndef MATXORVECTOR_H
#define MATXORVECTOR_H

#include <vector>
#include<opencv2/core/core.hpp>

using std::vector;
using cv::Mat;
using cv::Vec3b;

// 图像与vector数组进行异或
// param img 要异或的图像为
// param vec 进行异或的vector
// param type 数组类型：1：数组平铺，2：一对一异或
// return 返回异或后的图像
Mat MatXorVector(Mat& img, const vector<int> vec, int ,)
{
	Mat tmp;
	if (1 == type)
	{
	}
	if (2 == type)
	{
		for (int i = 0; i < img.rows; ++i)
		{
			for (int j = 0; j < img.cols * 3; ++j)
			{
				tmp[i][j] = m[i][j] ^ n[i][j];
			}
		}
	}

	return tmp;
}

#endif // MATXORVECTOR_H
