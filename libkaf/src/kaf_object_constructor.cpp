
#include "../libkaf.h"

namespace kaf_graphics
{
	object::object(void)
	{
		initialized = false;
		indexed_VBO = false;
	}

	void	object::clear_tmp_vectors(t_object_temp *temp)
	{
		temp->tmp_vertices.clear();
		temp->tmp_texels.clear();
		temp->tmp_normals.clear();
		temp->vertex_indices.clear();
		temp->normal_indices.clear();
		temp->texel_indices.clear();
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

	bool	object::is_it_same_vertex(t_packed_vertex &one, t_packed_vertex &two)
	{
		if (kaf_memcmp((void*)&one, (void*)&two, sizeof(t_packed_vertex)) == 0)
			return (true);
		else
			return (false);
	}

	bool	object::get_similar_vertex_index_fast(
		t_packed_vertex &packed,
		map<t_packed_vertex, unsigned short> &vertex_to_out_index,
		unsigned short &result)
	{
		map<t_packed_vertex,unsigned short>::iterator it = vertex_to_out_index.find(packed);
		if (it == vertex_to_out_index.end())
			return (false);
		else
		{
			result = it->second;
			return (true);
		}
	}

	void	object::index_VBO()
	{
		if (!initialized || vertices.size() == 0)
			cout << "ERROR: Not initialized." << endl;
		if (indexed_VBO)
			cout << "ERROR: Already indexed." << endl;
		unsigned int	i;
		t_object_temp	temp;
		map<t_packed_vertex, unsigned short> vertex_to_out_index;

		i = 0;
		while (i < vertices.size())
		{
			t_packed_vertex	packed = {vertices[i], texels[i], normals[i]};
			unsigned short	index;
			bool found = get_similar_vertex_index_fast(packed, vertex_to_out_index, index);
			if (found)
				temp.VBO_indices.push_back(index);
			else
			{
				temp.tmp_vertices.push_back(vertices[i]);
				temp.tmp_texels.push_back(texels[i]);
				temp.tmp_normals.push_back(normals[i]);
				unsigned short new_index = (unsigned short)temp.tmp_vertices.size() - 1;
				temp.VBO_indices.push_back(new_index);
				vertex_to_out_index[packed] = new_index;
			}
			i++;
		}
		indices = temp.VBO_indices;
		vertices = temp.tmp_vertices;
		texels = temp.tmp_texels;
		normals = temp.tmp_normals;
		indexed_VBO = true;
	}
}
