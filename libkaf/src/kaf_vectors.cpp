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
	float	vec3::get_x()
	{
		return (x);
	}
	float	vec3::get_y()
	{
		return (y);
	}
	float	vec3::get_z()
	{
		return (z);
	}
	void	vec3::set_x(float a)
	{
		this->x = a;
	}
	void	vec3::set_y(float b)
	{
		this->y = b;
	}
	void	vec3::set_z(float c)
	{
		this->z = c;
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
	uv::uv()
	{
		u = 0.0f;
		v = 0.0f;
		w = 1.0f;
	}
	uv::uv(float a, float b)
	{
		u = a;
		v = b;
		w = 1.0f;
	}
	float	uv::get_u()
	{
		return (this->u);
	}
	float	uv::get_v()
	{
		return (this->v);
	}
	void	uv::set_u(float a)
	{
		this->u = a;
	}
	void	uv::set_v(float a)
	{
		this->v = a;
	}
	void	uv::print(void)
	{
		cout << "u: " << this->u << " v: " << this->v
			<< " w: " << this->w << endl;
	}
	//Constructor defined outside the class, since vec3 defaults to vec3(0.0f, 0.0f, 0.0f),
	//object can be created just calling triangle()
	triangle::triangle()
	{
		p[0] = vec3();
		p[1] = vec3();
		p[2] = vec3();
		n[0] = vec3();
		n[1] = vec3();
		n[2] = vec3();
		t[0] = uv();
		t[1] = uv();
	}
	triangle::triangle(vec3 p0, vec3 p1, vec3 p2)
	{
		p[0] = p0;
		p[1] = p1;
		p[2] = p2;
		n[0] = vec3();
		n[1] = vec3();
		n[2] = vec3();
		t[0] = uv();
		t[1] = uv();
	}
	void	triangle::set_texel(int idx, float x, float y)
	{
		t[idx].set_u(x);
		t[idx].set_v(y);
	}
	void	triangle::set_texel(int idx, uv texel)
	{
		t[idx] = texel;
	}
	uv		triangle::get_texel(int idx)
	{
		return (t[idx]);
	}
	void	triangle::set_normal(int idx, float a, float b, float c)
	{
		n[idx].set_x(a);
		n[idx].set_y(b);
		n[idx].set_z(c);
	}
	void	triangle::set_normal(int idx, vec3 a)
	{
		n[idx] = a;
	}
	vec3	triangle::get_normal(int idx)
	{
		return (n[idx]);
	}
	void	triangle::print(void)
	{
		cout << "triangle points:" << endl;
		this->p[0].print();
		this->p[1].print();
		this->p[2].print();
		cout << "triangle normal:" << endl;
		this->n[0].print();
	}
}
