#ifndef ENRESHAPE_H
#define ENRESHAPE_H

#include <vector>
#include<opencv2/core/core.hpp>

using std::vector;
using cv::Mat;
using cv::Vec3b;

// ����ͨ��Matͼ��ת��Ϊ��ͨ��
// param Mat Ҫת����ͼ��
// return ���ɵĵ�ͨ��ͼ��
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
