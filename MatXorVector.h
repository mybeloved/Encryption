#ifndef MATXORVECTOR_H
#define MATXORVECTOR_H

#include <vector>
#include<opencv2/core/core.hpp>

using std::vector;
using cv::Mat;
using cv::Vec3b;

// ͼ����vector����������
// param img Ҫ����ͼ��Ϊ
// param vec ��������vector
// param type �������ͣ�1������ƽ�̣�2��һ��һ���
// return ���������ͼ��
Mat MatXorVector(Mat& img, const vector<int> vec, int ,)
{
	Mat tmp;
	if (1 == type)
	{
	}
	if (2 == type)
	{
		for (int i = 0; i < img.rows; ++i)
		{
			for (int j = 0; j < img.cols * 3; ++j)
			{
				tmp[i][j] = m[i][j] ^ n[i][j];
			}
		}
	}

	return tmp;
}

#endif // MATXORVECTOR_H
