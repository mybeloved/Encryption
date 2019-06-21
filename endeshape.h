#ifndef ENDESHAPE_H
#define ENDESHAPE_H

#include <vector>
#include<opencv2/core/core.hpp>
#include "random.h"

using std::vector;
using cv::Mat;
using cv::Vec3b;

// 将二维矩阵转换为三通道Mat图像
// param Mat 二维矩阵
// return 生成的图像
Mat endeshape(vector<vector<int>> vec, int row, int col)
{
	Mat img(row, (col + 2) / 3, CV_8UC3);
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			img.at<Vec3b>(i, j / 3)[j % 3] = vec[i][j];
		}
	}
	for (int i = 0; i < row; ++i)
	{
		img.at<Vec3b>(i, col / 3)[(col % 3)] = random(0, 255);
		img.at<Vec3b>(i, col / 3)[(col % 3) + 1] = random(0, 255);
	}
	return img;
}

#endif // ENDESHAPE_H
