#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <iostream>
#include <vector>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <ctime>

#include "random.h"
#include "makelogistic.h"
#include "bitxor.h"
#include "enreshape.h"
#include "endeshape.h"

using std::string;
using std::vector;
using cv::Mat;
using cv::Vec3b;
using cv::imread;
using cv::imwrite;


// 图像加密
// param src 要加密的文件，字符串
// param chg 加密后的文件，字符串
// param x 密钥x，在(0, 1)范围内
bool encryption(string src, string chg, double x)
{
	Mat image = imread(src);
	int r = image.rows, c = image.cols * 3; //获取图像的行和列
	vector<vector<int>> v(r, vector<int>(c));
	//if (image.type() == CV_8UC3) {//如果是彩色图像，变换为二维矩阵
	v = enreshape(image);//23.92s
	//}//26.78s
	//else {
	//	return false;
	//}

	srand(time(nullptr)); 
	vector<int> randArrR(r), randArrC(c);
	vector<vector<int>> randR(r, vector<int>(c)), randC(r, vector<int>(c));
	for (int i = 0; i < r; ++i)
	{
		randArrR[i] = uint8_t(random(0, 255)); //随机的含有r个元素的数组（0~255）
		for (int j = 0; j < c; ++j)
		{
			randC[i][j] = randArrR[i];
		}
	}
	//12.973s
	for (int i = 0; i < c; ++i)
	{
		randArrC[i] = uint8_t(random(0, 255)); //随机的含有c个元素的数组（0~255）
		for (int j = 0; j < r; ++j)
		{
			randR[j][i] = randArrC[i];
		}
	}
	//17s
	vector<double> chaosArr = makeLogistic(x, 500, r * c); // 返回Logistic从500项开始含有r*c个元素的数组 
	vector<vector<int>> chaosArri(r, vector<int>(c));
	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			int k = i * c + j;
			chaosArri[i][j] = uint8_t(floor(chaosArr[k] * 255)); // 返回Logistic含有r*c个元素的数组（1~255）
		}
	}
	//29.325s
	vector<double> changeChaosC = makeLogistic(x, 10000, r); // 返回Logistic含有r个元素的数组
	vector<double> changeChaosR = makeLogistic(x, 10000 + r, c); // 返回Logistic含有c个元素的数组
	vector<double> changeRow = makeLogistic(x, 20000, r + 1); // 返回Logistic含有r + 1个元素的数组
	vector<double> changeCol = makeLogistic(x, 20000 + r + 1, c + 1); // 返回Logistic含有c + 1个元素的数组
	//0.006s
	v = bitxor(bitxor(bitxor(v, chaosArri, r, c), randR, r, c), randC, r, c); //异或加密
	//78.678s

	//在加密后的图像下一行和右一行添加产生的randArrR行和randArrC列
	v.push_back(vector<int>(c));
	for (int i = 0; i < c; ++i)
	{
		v[r][i] = randArrC[i];
	}
	//0.009s
	randArrR.insert(randArrR.end(), random(0, 255));
	for (int i = 0; i <= r; ++i)
	{
		v[i].insert(v[i].end(), randArrR[i]);
	}
	//0.602s

	//将最下和最右侧的行列隐藏到图片中
	for (int i = 0; i < r; ++i)
	{
		int pos = floor(c * changeChaosC[i]) + 1;
		int tmp = v[i][c];
		v[i][c] = v[i][pos];
		v[i][pos] = tmp;
	}
	//0.004s
	for (int i = 0; i < c; ++i)
	{
		int pos = floor(r * changeChaosR[i]) + 1;
		int tmp = v[r][i];
		v[r][i] = v[pos][i];
		v[pos][i] = tmp;
	}
	//0.012s

	//对图片进行混沌加密
	for (int i = 0; i <= r; ++i)
	{
		int pos = floor(r * changeRow[i]) + 1;
		for (int j = 0; j <= c; ++j)
		{
			int tmp = v[i][j];
			v[i][j] = v[pos][j];
			v[pos][j] = tmp;
		}
	}
	//32.504s
	for (int i = 0; i <= c; ++i)
	{
		int pos = floor(c * changeCol[i]) + 1;
		for (int j = 0; j <= r; ++j)
		{
			int tmp = v[j][i];
			v[j][i] = v[j][pos];
			v[j][pos] = tmp;
		}
	}
	//61.683s
	Mat img(image.rows + 1, image.cols + 1, CV_8UC3);
	//0.076s
	//将二维矩阵重新转换成图像
	if (image.type() == CV_8UC3)
	{
		img = endeshape(v, r + 1, c + 1);
	}
	//25.657s

	//写出图片
	imwrite(chg, img);
	return true; //5.625s
}


#endif // ENCRYPTION_H
