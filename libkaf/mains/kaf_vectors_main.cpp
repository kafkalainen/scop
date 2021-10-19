#include "../libkaf.h"
#include <iostream>
#include <fstream>
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
		cout << v0.get_x() << endl;
		cout << v3.get_x() << endl;
		v0.set_x(4);
		v3.set_x(2);
		cout << v0.get_x() << endl;
		cout << v3.get_x() << endl;
		ofstream vec3_output("your_answers/vec3.txt");
		vec3_output << v0.get_x() << endl;
		vec3_output << v3.get_x() << endl;
		vec3_output.close();
	}
	return (0);
}
