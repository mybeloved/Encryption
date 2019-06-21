#ifndef BITXOR_H
#define BITXOR_H

#include <vector>

using std::vector;

// 2个二维数组进行异或
// param m 第一个二维数组
// param n 第二个二维数组
// param r 数组的行
// param c 数组的列
// return 返回的异或数组
vector<vector<int>> bitxor(const vector<vector<int>> m, const vector<vector<int>> n, int r, int c)
{
	vector<vector<int>> tmp(r, vector<int>(c));
	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			tmp[i][j] = m[i][j] ^ n[i][j];
		}
	}
	return tmp;
}

#endif // BITXOR_H
