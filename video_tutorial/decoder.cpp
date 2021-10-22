#include <iostream>
using namespace std;

/*
**	You can create multiple variables by entering those on a single line,
**	but they must be same datatype.
**	cout is character output, cin is character input.
**	cin cannot capture space.
*/
int	main()
{
	char	c1, c2, c3, c4, c5;
	char	c6;
	char	c7;

	cout << "Enter 5 letters: ";
	cin >> c1 >> c2 >> c3 >> c4 >> c5;
	cout << "ASCII message: " << int(c1) << " " << int(c2) << " " << int(c3)
	<<  " " << int(c4) << " " << int(c5);


	return (0);
}
