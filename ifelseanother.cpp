#include <iostream>
using namespace std;

int	main()
{
	float	a, b, c;
	cout << "Enter the sides of the triangle" << endl;
	cin >> a >> b >> c;
	if (a == b && b == c)
	{
		cout << "Equilateral triangle." << endl;
	}
	else
	{
		if (a != b && a != c && b != c)
		{
			cout << "Scalene triangle." << endl;
		}
		else
		{
			cout << "Isosceles triangle." << endl;
		}
	}
	return (0);
}
