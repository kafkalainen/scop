#ifndef TYPEWRITER_HPP
#define TYPEWRITER_HPP
#include <iostream>
#include <map>
#include "../glad/include/glad/glad.h"
#include "../glfw/include/GLFW/glfw3.h"
#include "../libkaf/libkaf.h"
#include <bits/stdc++.h>
#include "../freetype/include/freetype2/ft2build.h"
#include FT_FREETYPE_H
using namespace std;


typedef struct s_text_mod
{
	float		x;
	float		y;
	float		scale;
	glm::vec3	color;
}				t_text_mod;

namespace kaf_typewriter
{
	class Typewriter
	{
		typedef struct s_character
		{
			unsigned int	texture_ID;
			glm::ivec2		size;
			glm::ivec2		bearing;
			unsigned int	advance;
		}				t_character;

		typedef struct s_typewriter
		{
			FT_Library	ft;
			FT_Face		face;
			std::map<char, t_character> characters;
		}				t_typewriter;

		private:
			bool			initialized;
			t_typewriter	writer;
			void			load_characters(void);
		public:
			GLuint			typewriter_buffer;
			GLuint			typewriter_VAO;
			Typewriter(void);
			int				initialize_typeface(const char *path);
			void			render_text(kaf_shader::Shader &s, std::string text, t_text_mod mod);
	};
}
#endif
