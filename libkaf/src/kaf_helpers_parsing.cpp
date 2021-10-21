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
}
