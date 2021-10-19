#include "../libkaf.h"
using namespace kaf_graphics;

int	main(int argc, char **argv)
{
	if (argc == 10)
	{
		vec3 p0(stoi(argv[1]), stoi(argv[2]), stoi(argv[3]));
		vec3 p1(stoi(argv[4]), stoi(argv[5]), stoi(argv[6]));
		vec3 p2(stoi(argv[7]), stoi(argv[8]), stoi(argv[9]));
		triangle tri(p0, p1, p2);
		tri.print();
	}
	return (0);
}
