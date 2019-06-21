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


// ͼ�����
// param chg Ҫ���ܵ��ļ����ַ���
// param src ���ܺ���ļ����ַ���
// param x ��Կx����(0, 1)��Χ��
bool decryption(string chg, string src, double x)
{
	Mat image = imread(chg);
	int row = image.rows, col = image.cols * 3; //��ȡͼ����к���
	int r, c;
	vector<vector<int>> v(row, vector<int>(col));
	//if (image.type() == CV_8UC3) {//����ǲ�ɫͼ�񣬱任Ϊ��ά����
	v = dereshape(image);
	r = row - 1, c = col - 3;
	//}
	//else {
	//	return false;
	//}

	vector<double> chaosArri = makeLogistic(x, 500, r * c); // ����Logistic��500�ʼ����r*c��Ԫ�ص�����
	vector<vector<int>> chaosArr(r, vector<int>(c)); // r*c��Ԫ�صĶ�ά����

	//������chaosArri��Ԫ�������ά����chaosArr
	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			int t = i * c + j;
			chaosArr[i][j] = uint8_t(floor(chaosArri[t] * 255));
		}
	}

	vector<double> changeChaosC = makeLogistic(x, 10000, r); // ����Logistic����r��Ԫ�ص�����
	vector<double> changeChaosR = makeLogistic(x, 10000 + r, c); // ����Logistic����c��Ԫ�ص�����
	vector<double> changeRow = makeLogistic(x, 20000, r + 1); // ����Logistic����r + 1��Ԫ�ص�����
	vector<double> changeCol = makeLogistic(x, 20000 + r + 1, c + 1); // ����Logistic����c + 1��Ԫ�ص�����


	//�Ի�����ܵ�ͼƬ���н���
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


	//�����º����Ҳ�����л�ԭ��ͼƬ��
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

	//ȡ�����º����Ҳ������ֵ
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

	//��ԭ��ά�����С
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
	//����ά��������ת����ͼ��
	if (image.type() == CV_8UC3)
	{
		img = dedeshape(v, r, c);
	}

	//д��ͼƬ
	imwrite(src, img);
	return true;
}


#endif // DECRYPTION_H
