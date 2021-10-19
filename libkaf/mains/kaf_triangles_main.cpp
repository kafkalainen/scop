#include "../libkaf.h"
using namespace kaf_graphics;

int	main(int argc, char **argv)
{
	if (argc == 10)
	{
		//Constructor with arguments.
		vec3 p0(stoi(argv[1]), stoi(argv[2]), stoi(argv[3]));
		vec3 p1(stoi(argv[4]), stoi(argv[5]), stoi(argv[6]));
		vec3 p2(stoi(argv[7]), stoi(argv[8]), stoi(argv[9]));
		//Constructor with no arguments
		vec3 p3;
		vec3 p4;
		vec3 p5;
		triangle tri(p0, p1, p2);
		triangle tri2(p3, p4, p5);
		tri.print();
		tri2.print();
	}
	return (0);
}
