
#ifndef LIBKAF_H
# define LIBKAF_H
# include <iostream>
# include <fstream>
# include "src/kaf_swap.tpp"
  using namespace std;

namespace kaf_swapping
{
	template <typename T>
	class swap
	{
		public:
			void	kaf_swap(T &a, T &b);
	};
}

namespace kaf_math
{
	class math
	{
		public:
			static double	add(double a, double b);
			static float	add(float a, float b);
			static int		add(int a, int b);
			static double	dec(double a, double b);
			static float	dec(float a, float b);
			static int		dec(int a, int b);
			static double	mul(double a, double b);
			static float	mul(float a, float b);
			static int		mul(int a, int b);
			static double	div(double a, double b);
			static float	div(float a, float b);
			static int		div(int a, int b);
			static int		mod(int a, int b);
	};
}

namespace kaf_graphics
{
	class vec3
	{
		//Private keyword defines methods and variables that can't be accessed without using class methods.
		private:
			float	x;
			float	y;
			float	z;
			float	w;
		//Public defines methods and variables that are accessable outside of the scope of the function.
		public:
			//Variables of the class.
			//Class constructor, named as the class, definiton of the constructor is in kaf_vectors.cpp
			vec3();
			vec3(float a, float b, float c);
			//Class method declaration, when the class methods are defined, you will have to use :: notation.
			//I have three getters, and three setters for the variables.
			float	get_x();
			float	get_y();
			float	get_z();
			void	set_x(float a);
			void	set_y(float b);
			void	set_z(float c);
			void	print(void);
			vec3	dec(vec3 b);
	};

	class uv
	{
		//Private keyword defines methods and variables that can't be accessed without using class methods.
		private:
			float	u;
			float	v;
			float	w;
		//Public defines methods and variables that are accessable outside of the scope of the function.
		public:
			//Variables of the class.
			//Class constructor, named as the class, definiton of the constructor is in kaf_vectors.cpp
			uv();
			uv(float a, float b);
			//Class method declaration, when the class methods are defined, you will have to use :: notation.
			//I have three getters, and three setters for the variables.
			float	get_u();
			float	get_v();
			void	set_u(float a);
			void	set_v(float b);
			void	print(void);
	};

	class triangle
	{
		private:
			vec3	p[3];
			vec3 	normal;
		public:
			//Class method declaration, when the class methods are defined, you will have to use :: notation.
			triangle(vec3 p0, vec3 p1, vec3 p2);
			void	print(void);
	};

	class object
	{
		private:
			int			vertex_indices;
			int			uv_indices;
			int			normal_indices;
		public:
			object(string file);
			void	print(void);
	};

	//inheritance in c++ is done with : notation.
	//class arithmetic: public vec3
	//In C++, class can inherit multiple classes.
	//Ie. class FinnishStudent: public Finnish, public Student
	class arithmetic: public vec3
	{
		public:
			vec3	dec(vec3 a, vec3 b);
	};
}


int		kaf_open(const char *name);
void	kaf_putendl(const string str);
void	kaf_putstr(const string str);
int		kaf_nblen(int nb);
// T		kaf_swap(T &a, T &b);
void	kaf_swapi(int &a, int &b);
void	kaf_swapf(float &a, float &b);
void	kaf_swapd(double &a, double &b);
#endif
