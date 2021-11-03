#include "../headers/nerd.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"


GLuint	load_image(const char *path)
{
	t_bitmap	img;
	GLuint		texture;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	img.data = stbi_load(path, &img.width, &img.height,
					&img.channel_count, 0);
	if (!img.data)
	{
		std::cout << "ERROR: Couldn't load texture." << std::endl;
		return (0);
	}
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.width,
		img.height, 0, GL_RGB, GL_UNSIGNED_BYTE, img.data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(img.data);
	return (texture);
}
