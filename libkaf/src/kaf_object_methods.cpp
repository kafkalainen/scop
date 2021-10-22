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
}
