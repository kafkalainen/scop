#include "../headers/nerd.hpp"

namespace kaf_typewriter
{
	typewriter::typewriter(void)
	{
		initialized = false;
	}

	int	typewriter::initialize_typeface(const char *path)
	{
		if (FT_Init_FreeType(&writer.ft))
		{
			std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
			return (EXIT_FAILURE);
		}
		if (FT_New_Face(writer.ft, path, 0, &writer.face))
		{
			std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
			return (EXIT_FAILURE);
		}
		FT_Set_Pixel_Sizes(writer.face, 0, 48);
		load_characters();
		FT_Done_Face(writer.face);
		FT_Done_FreeType(writer.ft);
		glGenVertexArrays(1, &typewriter_VAO);
		glGenBuffers(1, &typewriter_buffer);
		glBindVertexArray(typewriter_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, typewriter_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		initialized = true;
		return (EXIT_SUCCESS);
	}

	void	typewriter::load_characters(void)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		for (unsigned char c = 0; c < 128; c++)
		{
			if (FT_Load_Char(writer.face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue ;
			}
			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				writer.face->glyph->bitmap.width,
				writer.face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				writer.face->glyph->bitmap.buffer
			);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			t_character character = {
				texture,
				glm::ivec2(writer.face->glyph->bitmap.width, writer.face->glyph->bitmap.rows),
				glm::ivec2(writer.face->glyph->bitmap_left, writer.face->glyph->bitmap_top),
				(t_uint)writer.face->glyph->advance.x
			};
			writer.characters.insert(std::pair<char, t_character>(c, character));
		}
	}

	void	typewriter::render_text(kaf_shader::shader &s, std::string text, t_text_mod mod)
	{
		s.use();
		glUniform3f(glGetUniformLocation(s.program_id, "textColor"), mod.color.x, mod.color.y, mod.color.z);
		glActiveTexture(GL_TEXTURE1);
		glBindVertexArray(typewriter_VAO);
		std::string::const_iterator c;
		for (c = text.begin(); c != text.end(); c++)
		{
			t_character ch = writer.characters[*c];
			float xpos = mod.x + ch.bearing.x * mod.scale;
			float ypos = mod.y - (ch.size.y - ch.bearing.y) * mod.scale;
			float w = ch.size.x * mod.scale;
			float h = ch.size.y * mod.scale;
			float vertices[6][4] = {
				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos,     ypos,       0.0f, 1.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },
				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },
				{ xpos + w, ypos + h,   1.0f, 0.0f }
			};
			glBindTexture(GL_TEXTURE_2D, ch.texture_ID);
			glBindBuffer(GL_ARRAY_BUFFER, typewriter_buffer);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			mod.x += (ch.advance >> 6) * mod.scale;
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
