#ifndef MAKELOGISTIC_H
#define MAKELOGISTIC_H

#include <vector>

#include "logistic.h"

using std::vector;

// 创建Logistic项
// param x0 初始key
// param t 从第t项开始
// param n 返回的项数
// return 返回的n个Logistic项
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
