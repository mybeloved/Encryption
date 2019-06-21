#ifndef DECRYPTION_H
#define DECRYPTION_H

#include <iostream>
#include <vector>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

#include "makelogistic.h"
#include "bitxor.h"
#include "dereshape.h"
#include "dedeshape.h"

using std::string;
using std::vector;
using cv::Mat;
using cv::Vec3b;
using cv::imread;
using cv::imwrite;


// 图像解密
// param chg 要解密的文件，字符串
// param src 解密后的文件，字符串
// param x 密钥x，在(0, 1)范围内
bool decryption(string chg, string src, double x)
{
	Mat image = imread(chg);
	int row = image.rows, col = image.cols * 3; //获取图像的行和列
	int r, c;
	vector<vector<int>> v(row, vector<int>(col));
	//if (image.type() == CV_8UC3) {//如果是彩色图像，变换为二维矩阵
	v = dereshape(image);
	r = row - 1, c = col - 3;
	//}
	//else {
	//	return false;
	//}

	vector<double> chaosArri = makeLogistic(x, 500, r * c); // 返回Logistic从500项开始含有r*c个元素的数组
	vector<vector<int>> chaosArr(r, vector<int>(c)); // r*c个元素的二维矩阵

	//将数组chaosArri的元素填入二维矩阵chaosArr
	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			int t = i * c + j;
			chaosArr[i][j] = uint8_t(floor(chaosArri[t] * 255));
		}
	}

	vector<double> changeChaosC = makeLogistic(x, 10000, r); // 返回Logistic含有r个元素的数组
	vector<double> changeChaosR = makeLogistic(x, 10000 + r, c); // 返回Logistic含有c个元素的数组
	vector<double> changeRow = makeLogistic(x, 20000, r + 1); // 返回Logistic含有r + 1个元素的数组
	vector<double> changeCol = makeLogistic(x, 20000 + r + 1, c + 1); // 返回Logistic含有c + 1个元素的数组


	//对混沌加密的图片进行解密
	for (int i = c; i >= 0; --i)
	{
		int pos = floor(c * changeCol[i]) + 1;
		for (int j = r; j >= 0; --j)
		{
			int tmp = v[j][i];
			v[j][i] = v[j][pos];
			v[j][pos] = tmp;
		}
	}
	for (int i = r; i >= 0; --i)
	{
		int pos = floor(r * changeRow[i]) + 1;
		for (int j = c; j >= 0; --j)
		{
			int tmp = v[i][j];
			v[i][j] = v[pos][j];
			v[pos][j] = tmp;
		}
	}


	//将最下和最右侧的行列还原到图片中
	for (int i = 0; i < c; ++i)
	{
		int pos = floor(r * changeChaosR[i]) + 1;
		int tmp = v[r][i];
		v[r][i] = v[pos][i];
		v[pos][i] = tmp;
	}
	for (int i = 0; i < r; ++i)
	{
		int pos = floor(c * changeChaosC[i]) + 1;
		int tmp = v[i][c];
		v[i][c] = v[i][pos];
		v[i][pos] = tmp;
	}

	//取回最下和最右侧的行列值
	int r1 = r + 1, c1 = c + 1;
	vector<int> randArrR(r1), randArrC(c1);
	for (int i = 0; i <= r; ++i)
	{
		randArrR[i] = v[i][c];
	}
	for (int i = 0; i <= c; ++i)
	{
		randArrC[i] = v[r][i];
	}

	//还原二维矩阵大小
	v.pop_back();
	for (int i = 0; i < r; ++i)
	{
		v[i].pop_back();
		v[i].pop_back();
		v[i].pop_back();
	}


	vector<vector<int>> randR(r, vector<int>(c)), randC(r, vector<int>(c));
	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			randC[i][j] = randArrR[i];
		}
	}
	for (int i = 0; i < c; ++i)
	{
		for (int j = 0; j < r; ++j)
		{
			randR[j][i] = randArrC[i];
		}
	}
	v = bitxor(bitxor(bitxor(v, chaosArr, r, c), randR, r, c), randC, r, c);

	Mat img(r, c / 3, CV_8UC3);
	//将二维矩阵重新转换成图像
	if (image.type() == CV_8UC3)
	{
		img = dedeshape(v, r, c);
	}

	//写出图片
	imwrite(src, img);
	return true;
}


#endif // DECRYPTION_H
