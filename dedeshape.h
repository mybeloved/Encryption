#ifndef DEDESHAPE_H
#define DEDESHAPE_H

#include <vector>
#include<opencv2/core/core.hpp>

using std::vector;
using cv::Mat;
using cv::Vec3b;

// 将二维矩阵转换为三通道Mat图像
// param Mat 二维矩阵
// return 生成的图像
Mat dedeshape(vector<vector<int>> vec, int row, int col)
{
	Mat img(row, col / 3, CV_8UC3);
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			img.at<Vec3b>(i, j / 3)[j % 3] = vec[i][j];
		}
	}
	return img;
}

#endif // DEDESHAPE_H
