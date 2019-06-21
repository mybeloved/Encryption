#ifndef RANDOM_H
#define RANDOM_H

//产生随机数，其中范围为min~max  
int random(int min, int max)
{
	const int r = rand() % (max - min + 1) + min;
	return r;
}

#endif // RANDOM_H
