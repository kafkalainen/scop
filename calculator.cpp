#include <iostream>
using namespace std;

int	main(void)
{
	float	a;
	float	b;
	char	operand;

	cout << "Enter the first variable" << endl;
	cin >> a >> operand >> b;
	switch (operand)
	{
	case ('+'):
		cout << a << " + " << b << " = " << a + b << endl;
		break;
	case ('-'):
		cout << a << " - " << b << " = " << a - b << endl;
		break;
	case ('*'):
		cout << a << " * " << b << " = " << a * b << endl;
		break;
	case ('/'):
		if (b != 0)
			cout << a << " / " << b << " = " << a / b << endl;
		else
			cout << "Division by zero." << endl;
		// Division by zero is evaluated to inf.
		break;
	case ('%'):
		bool	is_int_a;
		bool	is_int_b;

		is_int_a = ((int)a == a);
		is_int_b = ((int)b == b);
		if (is_int_a && is_int_b)
			cout << a << " % " << b << " = " << (int)a % (int)b << endl;
		else
			cout << a << " % " << b << " not a valid statement." << endl;
		break;
	default:
		break;
	}
	return (0);
}
