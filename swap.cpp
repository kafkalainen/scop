#include <iostream>
using namespace std;

void	swap(int a, int b)
{
	int	temp;

	temp = a;
	a = b;
	b = temp;
}

void	swap(int a, int b)
{
	a = a + b;
	b = a - b;
	a = a - b;
}

int	main(void)
{
	int	a;
	int	b;

	a = 0;
	b = 1;
	cout << " jee jee jee " << a << " huu " << endl;
	cout << " jee jee jee " << b << " huu " << endl;
	return (0);
}
