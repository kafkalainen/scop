#include <iostream>
using namespace std;

int	main(void)
{
	int	year;
	int	month;

	cout << "Enter year and month" << endl;
	cin >> year >> month;
	switch (month)
	{
		case (2):
		{
			if ((year % 4 == 0 && (year % 100 != 0)) || year % 400 == 0)
				cout << "29 days month.";
			else
				cout << "28 days month.";
			break;
		}
		// All of these will fire 30 days month,
		// since break is at row 29.
		case (4):
		case (6):
		case (9):
		case (11):
		{
			cout << "30 days month.";
			break;
		}
		// All of these will fire 31 days month.
		case (1):
		case (3):
		case (5):
		case (7):
		case (8):
		case (10):
		case (12):
		{
			cout << "31 days month.";
			break;
		}
		default:
		{
			cout << "Not valid.";
			break;
		}
	}
}
