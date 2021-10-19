#include "../libkaf.h"
using namespace kaf_graphics;

int	main(int argc, char **argv)
{
	if (argc == 4)
	{
		vec3 v0(stoi(argv[1]), stoi(argv[2]), stoi(argv[3]));
		vec3 v1(stoi(argv[1]), stoi(argv[2]), stoi(argv[3]));
		v0.print();
		vec3 v3 = v0.dec(v1);
		v3.print();
	}
	return (0);
}
