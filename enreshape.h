#ifndef ENRESHAPE_H
#define ENRESHAPE_H

#include <vector>
#include<opencv2/core/core.hpp>

using std::vector;
using cv::Mat;
using cv::Vec3b;

// 将三通道Mat图像转换为单通道
// param Mat 要转换的图像
// return 生成的单通道图像
vector<vector<int>> enreshape(Mat& img)
{
	// int t = img.cols * 3;
	// vector<vector<int>> vec(img.rows, vector<int>(t));
	// for (int i = 0; i < img.rows; ++i)
	// {
	// 	for (int j = 0; j < img.cols * 3; ++j)
	// 	{
	// 		vec[i][j] = img.at<Vec3b>(i, j / 3)[j % 3];
	// 	}
	// }
	// return vec;

	int t = img.cols * 3;
	vector<vector<int>> vec(img.rows, vector<int>(t));
	for (int i = 0; i < img.rows; ++i)
	{
		for (int j = 0; j < img.cols * 3; ++j)
		{
			vec[i][j] = img.at<Vec3b>(i, j / 3)[j % 3];
		}
	}
	return vec;

}

#endif // ENRESHAPE_H
