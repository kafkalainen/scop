
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
		t_object_temp			temp;
		if (!obj_file.is_open())
			throw ("ERROR: Couldn't open a file.");
		while (!obj_file.eof() && getline(obj_file, line))
		{
			if (line[0] == 'g')
				kaf_parse_name(line, &name);
			else if (line.find("v ") == 0)
				kaf_parse_vertex(line, temp.tmp_vertices);
			else if (line.find("vn") == 0)
				kaf_parse_vertex(line, temp.tmp_normals);
			else if (line.find("vt") == 0)
				kaf_parse_texel(line, temp.tmp_texels);
			else if (line[0] == 'f')
				kaf_parse_facing(line, temp.vertex_indices,
					temp.normal_indices, temp.texel_indices);
		}
		obj_file.close();
		kaf_index_object_data(&temp);
		initialized = true;
	}
}
