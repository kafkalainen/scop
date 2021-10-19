
#ifndef LIBKAF_H
# define LIBKAF_H
# include <iostream>
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
			//Class constructor, named as the class
			vec3()
			{
				x = 0.0f;
				y = 0.0f;
				z = 0.0f;
				w = 1.0f;
			}
			vec3(float a, float b, float c)
			{
				x = a;
				y = b;
				z = c;
				w = 1.0f;
			}
			//Class method.
			void	print(void);
			vec3	dec(vec3 b);
	};

	class triangle
	{
		private:
			vec3	p[3];
			vec3 	normal;
		public:
			triangle(vec3 p0, vec3 p1, vec3 p2)
			{
				p[0] = p0;
				p[1] = p1;
				p[2] = p2;
			}
			void	print(void);
	};

	//inheritance in c++ is done with : notation.
	//class arithmetic: public vec3
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
