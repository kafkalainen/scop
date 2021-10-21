
#include "../libkaf.h"

namespace kaf_graphics
{
	object::object(string file)
	{
		try
		{
			if (file.empty())
				throw (1);
			string					line;
			ifstream				obj_file(file);
			vector <unsigned int>	vertex_indices;
			vector <unsigned int>	texel_indices;
			vector <unsigned int>	normal_indices;
			vector <glm::vec3>		tmp_vertices;
			vector <glm::vec3>		tmp_normals;
			vector <glm::vec2>		tmp_texels;
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
					glm::vec3 v(vals[0], vals[1], vals[2]);
					tmp_vertices.push_back(v);
				}
				if (line.find("vn") == 0)
				{
					data >> identifier >> vals[0] >> vals[1] >> vals[2];
					glm::vec3 v(vals[0], vals[1], vals[2]);
					tmp_normals.push_back(v);
				}
				if (line.find("vt") == 0)
				{
					data >> identifier >> vals[0] >> vals[1];
					glm::vec2 t(vals[0], vals[1]);
					tmp_texels.push_back(t);
				}
				if (line[0] == 'f')
				{
					kaf_parse_facing(line, vertex_indices, normal_indices, texel_indices);
				}
			}
			obj_file.close();
			unsigned int i;
			unsigned int cur_idx;
			i = 0;
			while (i < vertex_indices.size())
			{
				cur_idx = vertex_indices[i];
				glm::vec3 vertex = tmp_vertices[cur_idx - 1];
				vertices.push_back(vertex);
				i++;
			}
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
