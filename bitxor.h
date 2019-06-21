#ifndef BITXOR_H
#define BITXOR_H

#include <vector>

using std::vector;

// 2����ά����������
// param m ��һ����ά����
// param n �ڶ�����ά����
// param r �������
// param c �������
// return ���ص��������
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
