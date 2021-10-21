#include "../libkaf.h"


namespace kaf_graphics
{
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

	triangle	object::kaf_parse_facing(string line, vector<vec3> &vectors,
				vector<vec3> &normals, vector<uv> &texels)
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
		triangle tri(vectors.at(v[0] - 1), vectors.at(v[1] - 1), vectors.at(v[2] - 1));
		if (!texels.empty())
		{
			tri.set_texel(0, texels.at(vt[0] - 1));
			tri.set_texel(1, texels.at(vt[1] - 1));
			tri.set_texel(2, texels.at(vt[2] - 1));
		}
		if (!normals.empty())
		{
			tri.set_normal(0, normals.at(vn[0] - 1));
			tri.set_normal(1, normals.at(vn[1] - 1));
			tri.set_normal(2, normals.at(vn[2] - 1));
		}
		return (tri);
	}
}
