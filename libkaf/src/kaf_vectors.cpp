#include "../libkaf.h"

namespace kaf_graphics
{
	void	vec3::print(void)
	{
		cout << "x: " << this->x << " y: " << this->y << " z: "
		<< this->z << " w: " << this->w << endl;
	}
	vec3	vec3::dec(vec3 b)
	{
		vec3 c;

		c.x = this->x - b.x;
		c.y = this->y - b.y;
		c.z = this->z - b.z;
		return (c);
	}
	void	triangle::print(void)
	{
		cout << "triangle points:" << endl;
		this->p[0].print();
		this->p[1].print();
		this->p[2].print();
		cout << "triangle normal:" << endl;
		this->normal.print();
	}
}
