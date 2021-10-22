#include <iostream>
using namespace std;


/*
**	Even or odd
**	cin doesn't need typecasting, c++ can parse together that number.
**	endl: Inserts a new-line character and flushes the stream.
*/
int	main()
{
	int	nb;

	cout << "Enter a number:" << endl;
	cin >> nb;
	if (nb % 2)
	{
		cout << "Odd." << endl;
	}
	else
	{
		cout << "Even." << endl;
	}
	cout << "Thanks a lot. Bye." << endl;
	return (0);
}
