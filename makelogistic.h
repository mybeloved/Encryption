#ifndef MAKELOGISTIC_H
#define MAKELOGISTIC_H

#include <vector>

#include "logistic.h"

using std::vector;

// ����Logistic��
// param x0 ��ʼkey
// param t �ӵ�t�ʼ
// param n ���ص�����
// return ���ص�n��Logistic��
vector<double> makeLogistic(double x0, int t, int n)
{
	vector<double> vec(n);
	for (int i = 0; i < t; ++i)
	{
		x0 = logistic(x0, 3.99);
	}
	vec[0] = x0;
	for (int i = 1; i < n; ++i)
	{
		int j = i - 1;
		vec[i] = logistic(vec[j], 3.99);
	}
	return vec;
}


#endif // MAKELOGISTIC_H
