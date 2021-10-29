#include "../libkaf.h"
using namespace kaf_graphics;

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		string file_name(argv[1]);
		if (file_name == "empty")
		{
			try
			{
				object test_object;
				test_object.load_from_file("");
				test_object.print_name();
			}
			catch (char const *result)
			{
				cout << result << endl;
			}
		}
		else
		{
			try
			{
				object test_object;
				test_object.load_from_file(file_name);
				test_object.print_name();
				test_object.print_vertices();
				test_object.print_texels();
				test_object.print_normals();
				test_object.index_VBO();
				test_object.print_indices();
			}
			catch (char const *result)
			{
				cout << result << endl;
			}
		}
	}
	return (0);
}
