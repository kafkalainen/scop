#include <iostream>
#include <map>
#include <bits/stdc++.h>
#include "../freetype/include/freetype2/ft2build.h"
#include FT_FREETYPE_H
using namespace std;

namespace kaf_typewriter
{
	class typewriter
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
			typewriter(void);
			int				initialize_typeface(const char *path);
	};
}
