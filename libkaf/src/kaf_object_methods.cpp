#include "../libkaf.h"

namespace kaf_graphics
{
	void	object::print_name(void)
	{
		if (initialized)
			cout << name << endl;
	}

	void	object::print_vertices(void)
	{
		unsigned int	i;
		glm::vec3		v;

		i = 0;
		while (i < vertices.size())
		{
			v = vertices.at(i);
			cout << "x: " << v.x << " y: " << v.y << " z: " << v.z << endl;
			i++;
		}
	}

	void	object::print_texels(void)
	{
		unsigned int	i;
		glm::vec2		v;

		i = 0;
		while (i < texels.size())
		{
			v = texels[i];
			cout << "x: " << v.x << " y: " << v.y << endl;
			i++;
		}
	}

	void	object::print_normals(void)
	{
		unsigned int	i;
		glm::vec3		v;

		i = 0;
		while (i < normals.size())
		{
			v = normals[i];
			cout << "x: " << v.x << " y: " << v.y << " z: " << v.z << endl;
			i++;
		}
	}

	void	object::print_indices(void)
	{
		unsigned int	i;

		i = 0;
		while (i < indices.size())
		{
			cout << "idx: " << indices[i] << endl;
			i++;
		}
	}
}
