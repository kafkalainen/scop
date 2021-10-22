#include <iostream>
using namespace std;

int	main(void)
{
	int	a;
	int	b;

	a = 0;
	b = 3;
	cout << (a < b) << endl;
	//Arithmetic operators are evaluated first.
	cout << (a + 4 < b) << endl;
	//=, +=, *=, /=, %=
	return (0);
}
