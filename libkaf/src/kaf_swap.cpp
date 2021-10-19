#include "../libkaf.h"

void	kaf_swapi(int &a, int &b)
{
	int	temp;

	temp = a;
	a = b;
	b = temp;
}

void	kaf_swapf(float &a, float &b)
{
	float	temp;

	temp = a;
	a = b;
	b = temp;
}

void	kaf_swapd(double &a, double &b)
{
	double	temp;

	temp = a;
	a = b;
	b = temp;
}
