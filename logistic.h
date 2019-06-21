#ifndef LOGISTIC_H
#define LOGISTIC_H

// 逻辑回归函数
// param n 第i - 1项，实数
// param u Logistic映射的参数，u > 3.569945672...
// return  第i项的值，实数
double logistic(double n, double u)
{
	return u * n * (1 - n);
}

#endif // LOGISTIC_H
