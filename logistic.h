#ifndef LOGISTIC_H
#define LOGISTIC_H

// �߼��ع麯��
// param n ��i - 1�ʵ��
// param u Logisticӳ��Ĳ�����u > 3.569945672...
// return  ��i���ֵ��ʵ��
double logistic(double n, double u)
{
	return u * n * (1 - n);
}

#endif // LOGISTIC_H
