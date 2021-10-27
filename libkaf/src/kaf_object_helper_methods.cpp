#include "../libkaf.h"


namespace kaf_graphics
{
	void	object::kaf_parse_name(const string &line, string *name)
	{
		string			identifier;
		stringstream	data(line);

		data >> identifier >> *name;
	}

	void	object::kaf_parse_vertex(const string &line, vector<glm::vec3> &tmp_vectices)
	{
		string			identifier;
		float			vals[3];
		stringstream	data(line);

		data >> identifier >> vals[0] >> vals[1] >> vals[2];
		glm::vec3 v(vals[0], vals[1], vals[2]);
		tmp_vectices.push_back(v);
	}

	void	object::kaf_parse_texel(const string &line, vector<glm::vec2> &tmp_texels)
	{
		string			identifier;
		float			vals[2];
		stringstream	data(line);

		data >> identifier >> vals[0] >> vals[1];
		glm::vec2 t(vals[0], vals[1]);
		tmp_texels.push_back(t);
	}

	void	object::kaf_extract_int_data(string sub_string, int &v, int &vt, int &vn)
	{
		stringstream	data(sub_string);
		char			delim;

		data >> v;
		if (data.peek() == '/')
		{
			data >> delim;
			if (data.peek() == '/')
			{
				vt = 1;
				data >> delim >> vn;
			}
			else
			{
				data >> vt;
				if (data.peek() == '/')
					data >> delim >> vn;
			}
		}
	}

	void	object::kaf_parse_facing(string line, vector<unsigned int> &vectors,
				vector<unsigned int> &normals, vector<unsigned int> &texels)
	{
		char			identifier;
		stringstream	data(line);
		string			sub_str[3];
		int				v[3];
		int				vt[3];
		int				vn[3];

		data >> identifier >> sub_str[0] >> sub_str[1] >> sub_str[2];
		kaf_extract_int_data(sub_str[0], v[0], vt[0], vn[0]);
		kaf_extract_int_data(sub_str[1], v[1], vt[1], vn[1]);
		kaf_extract_int_data(sub_str[2], v[2], vt[2], vn[2]);
		vectors.push_back(v[0]);
		vectors.push_back(v[1]);
		vectors.push_back(v[2]);
		texels.push_back(vt[0]);
		texels.push_back(vt[1]);
		texels.push_back(vt[2]);
		normals.push_back(vn[0]);
		normals.push_back(vn[1]);
		normals.push_back(vn[2]);
	}

	void	object::kaf_index_object_data(t_object_temp *temp)
	{
		unsigned int i;
		unsigned int cur_vertex_idx;
		unsigned int cur_normal_idx;
		unsigned int cur_texel_idx;

		i = 0;
		while (i < temp->vertex_indices.size())
		{
			cur_vertex_idx = temp->vertex_indices[i];
			cur_normal_idx = temp->normal_indices[i];
			cur_texel_idx = temp->texel_indices[i];
			glm::vec3 vertex = temp->tmp_vertices[cur_vertex_idx - 1];
			glm::vec2 texel = temp->tmp_texels[cur_texel_idx - 1];
			glm::vec3 normal = temp->tmp_normals[cur_normal_idx - 1];
			vertices.push_back(vertex);
			texels.push_back(texel);
			normals.push_back(normal);
			i++;
		}
	}
}
