#include <iostream>
using namespace std;

/*
**	Integers overflow in c++ to other side, not a random number.
*/
int	main()
{
	int	intMax = INT32_MAX;

	cout << intMax << endl;
	cout << intMax + 1 << endl;
	return (0);
}
