#include <iostream>
using namespace std;

/*
**	When entering data using cin, you can press return or space as
**	much as you want to seperate your data.
*/
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
