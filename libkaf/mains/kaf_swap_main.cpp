#include <stdio.h>
#include <iostream>
#include <string>
#include "../libkaf.h"
using namespace std;

int	main(int argc, char **argv)
{
	int	a;
	int	b;
	if (argc == 3)
	{
		a = stoi(argv[1]);
		b = stoi(argv[2]);
		kaf_swapi(a, b);
		printf("%d %d\n", a, b);
	}
	return (0);
}
