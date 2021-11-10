#include "../headers/nerd.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"

GLuint	load_image(const char *path, const string &directory, bool gamma)
{
	t_bitmap	img;
	string 		filename = string(path);

	(void)gamma;
	stbi_set_flip_vertically_on_load(true);
	filename = directory + '/' + filename;
	img.data = stbi_load(filename.c_str(), &img.width, &img.height,
					&img.channel_count, 0);
	if (!img.data)
	{
		std::cout << "ERROR: Couldn't load texture." << std::endl;
		return (0);
	}
	GLuint		texture_ID;
	GLenum		format;
	if (img.channel_count == 1)
		format = GL_RED;
	else if (img.channel_count == 3)
		format = GL_RGB;
	else if (img.channel_count == 4)
		format = GL_RGBA;
	glGenTextures(1, &texture_ID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexImage2D(GL_TEXTURE_2D, 0, format, img.width,
			img.height, 0, format, GL_UNSIGNED_BYTE, img.data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_image_free(img.data);
	return (texture_ID);
}
