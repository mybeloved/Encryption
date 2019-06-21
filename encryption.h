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


// ͼ�����
// param src Ҫ���ܵ��ļ����ַ���
// param chg ���ܺ���ļ����ַ���
// param x ��Կx����(0, 1)��Χ��
bool encryption(string src, string chg, double x)
{
	Mat image = imread(src);
	int r = image.rows, c = image.cols * 3; //��ȡͼ����к���
	vector<vector<int>> v(r, vector<int>(c));
	//if (image.type() == CV_8UC3) {//����ǲ�ɫͼ�񣬱任Ϊ��ά����
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
		randArrR[i] = uint8_t(random(0, 255)); //����ĺ���r��Ԫ�ص����飨0~255��
		for (int j = 0; j < c; ++j)
		{
			randC[i][j] = randArrR[i];
		}
	}
	//12.973s
	for (int i = 0; i < c; ++i)
	{
		randArrC[i] = uint8_t(random(0, 255)); //����ĺ���c��Ԫ�ص����飨0~255��
		for (int j = 0; j < r; ++j)
		{
			randR[j][i] = randArrC[i];
		}
	}
	//17s
	vector<double> chaosArr = makeLogistic(x, 500, r * c); // ����Logistic��500�ʼ����r*c��Ԫ�ص����� 
	vector<vector<int>> chaosArri(r, vector<int>(c));
	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			int k = i * c + j;
			chaosArri[i][j] = uint8_t(floor(chaosArr[k] * 255)); // ����Logistic����r*c��Ԫ�ص����飨1~255��
		}
	}
	//29.325s
	vector<double> changeChaosC = makeLogistic(x, 10000, r); // ����Logistic����r��Ԫ�ص�����
	vector<double> changeChaosR = makeLogistic(x, 10000 + r, c); // ����Logistic����c��Ԫ�ص�����
	vector<double> changeRow = makeLogistic(x, 20000, r + 1); // ����Logistic����r + 1��Ԫ�ص�����
	vector<double> changeCol = makeLogistic(x, 20000 + r + 1, c + 1); // ����Logistic����c + 1��Ԫ�ص�����
	//0.006s
	v = bitxor(bitxor(bitxor(v, chaosArri, r, c), randR, r, c), randC, r, c); //������
	//78.678s

	//�ڼ��ܺ��ͼ����һ�к���һ����Ӳ�����randArrR�к�randArrC��
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

	//�����º����Ҳ���������ص�ͼƬ��
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

	//��ͼƬ���л������
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
	//����ά��������ת����ͼ��
	if (image.type() == CV_8UC3)
	{
		img = endeshape(v, r + 1, c + 1);
	}
	//25.657s

	//д��ͼƬ
	imwrite(chg, img);
	return true; //5.625s
}


#endif // ENCRYPTION_H
