
#include "../libkaf.h"

namespace kaf_graphics
{
	object::object(string file)
	{
		try
		{
			if (file.empty())
				throw (1);
			string				line;
			ifstream			obj_file(file);
			vector <vec3>		vertices;
			vector <vec3>		normals;
			vector <uv>			texels;
			if (!obj_file.is_open())
				throw (2);
			while (!obj_file.eof() && getline(obj_file, line))
			{
				string			identifier;
				stringstream	data(line);
				float			vals[3];
				string			name;

				if (line[0] == 'g')
					data >> identifier >> name;
				if (line.find("v ") == 0)
				{
					data >> identifier >> vals[0] >> vals[1] >> vals[2];
					vec3 v(vals[0], vals[1], vals[2]);
					vertices.push_back(v);
				}
				if (line.find("vn") == 0)
				{
					data >> identifier >> vals[0] >> vals[1] >> vals[2];
					vec3 v(vals[0], vals[1], vals[2]);
					normals.push_back(v);
				}
				if (line.find("vt") == 0)
				{
					data >> identifier >> vals[0] >> vals[1];
					uv t(vals[0], vals[1]);
					texels.push_back(t);
				}
				if (line[0] == 'f')
				{
					triangles.push_back(kaf_parse_facing(line, vertices, normals, texels));
				}
			}
			obj_file.close();
		}
		catch (int result)
		{
			if (result == 1)
				cout << "ERROR: Invalid obj file." << endl;
			else if (result == 2)
				cout << "ERROR: Couldn't open a file." << endl;
		}
	}
}
