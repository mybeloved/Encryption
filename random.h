#ifndef RANDOM_H
#define RANDOM_H

//��������������з�ΧΪmin~max  
int random(int min, int max)
{
	const int r = rand() % (max - min + 1) + min;
	return r;
}

#endif // RANDOM_H
