#include <stdio.h>
#include <iostream>
#include <string>
#include "../libkaf.h"
using namespace std;

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		printf("%d\n", kaf_nblen(stoi(argv[1])));
	}
	return (0);
}
