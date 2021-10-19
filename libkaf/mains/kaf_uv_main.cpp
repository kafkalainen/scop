#include "../libkaf.h"
#include <iostream>
#include <fstream>
using namespace kaf_graphics;

int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		uv v0(stoi(argv[1]), stoi(argv[2]));
		uv v1(stoi(argv[1]), stoi(argv[2]));
		v0.print();
		v1.print();
		cout << v0.get_u() << endl;
		cout << v1.get_v() << endl;
		v0.set_u(4);
		v1.set_u(2);
		cout << v0.get_u() << endl;
		cout << v1.get_v() << endl;
		ofstream vec3_output("your_answers/uv.txt");
		vec3_output << v0.get_u() << endl;
		vec3_output << v1.get_v() << endl;
		vec3_output.close();
	}
	return (0);
}
