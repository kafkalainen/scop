#include "../libkaf.h"

namespace kaf_graphics
{
	vec3::vec3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 1.0f;
	}
	vec3::vec3(float a, float b, float c)
	{
		x = a;
		y = b;
		z = c;
		w = 1.0f;
	}
	void	vec3::print(void)
	{
		cout << "x: " << this->x << " y: " << this->y << " z: "
		<< this->z << " w: " << this->w << endl;
	}
	vec3	vec3::dec(vec3 b)
	{
		vec3 c(0.0f, 0.0f, 0.0f);

		c.x = this->x - b.x;
		c.y = this->y - b.y;
		c.z = this->z - b.z;
		return (c);
	}
	//Constructor defined outside the class, since vec3 defaults to vec3(0.0f, 0.0f, 0.0f),
	//object can be created just calling triangle()
	triangle::triangle(vec3 p0, vec3 p1, vec3 p2)
	{
		p[0] = p0;
		p[1] = p1;
		p[2] = p2;
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
