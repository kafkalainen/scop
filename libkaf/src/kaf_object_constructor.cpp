
#include "../libkaf.h"

namespace kaf_graphics
{
	object::object(void)
	{
		initialized = false;
	}

	void	object::load_from_file(string file)
	{
		if (file.empty())
			throw ("ERROR: Invalid obj file.");
		string					line;
		ifstream				obj_file(file);
		vector <unsigned int>	vertex_indices;
		vector <unsigned int>	texel_indices;
		vector <unsigned int>	normal_indices;
		vector <glm::vec3>		tmp_vertices;
		vector <glm::vec3>		tmp_normals;
		vector <glm::vec2>		tmp_texels;
		if (!obj_file.is_open())
			throw ("ERROR: Couldn't open a file.");
		while (!obj_file.eof() && getline(obj_file, line))
		{
			if (line[0] == 'g')
				kaf_parse_name(line, &name);
			else if (line.find("v ") == 0)
				kaf_parse_vertex(line, tmp_vertices);
			else if (line.find("vn") == 0)
				kaf_parse_vertex(line, tmp_normals);
			else if (line.find("vt") == 0)
				kaf_parse_texel(line, tmp_texels);
			else if (line[0] == 'f')
				kaf_parse_facing(line, vertex_indices, normal_indices, texel_indices);
		}
		obj_file.close();
		kaf_copy_vertices(vertex_indices, tmp_vertices);
		initialized = true;
	}
}
