#include <iostream>
using namespace std;

int	sum(int a, int b);
double	sum(double a, double b);
float	sum(float a, float b, float c);


int	sum(int a, int b)
{
	return (a + b);
}

float	sum(float a, float b)
{
	return (a + b);
}

double	sum(double a, double b)
{
	return (a + b);
}

float	sum(float a, float b, float c)
{
	return (a + b + c);
}

//In C++, you can create functions with the same name,
//which is called overloading. The compiler chooses
//which function to use in that case. But does compiler choose
//float or double? If you use suffix notation f, the compiler
//knows to use float version of the overloaded method.
int	main(void)
{
	cout << sum(4, 3) << endl;
	cout << sum(4.4, 3.3) << endl;
	cout << sum(4.4f, 3.3f) << endl;
	cout << sum(4.4, 3.3, 2.2) << endl;
	return (0);
}
