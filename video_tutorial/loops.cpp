#include <iostream>
#include <stdio.h>

int	main(void)
{
	int counter;

	counter = 100;
	while (counter < 501)
	{
		if (counter % 3 == 0 || counter % 5 == 0)
			printf("%d is divisible.\n", counter);
		counter++;
	}
	return (0);
}
