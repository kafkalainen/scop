#include "../headers/nerd.hpp"

static unsigned int	compress_dxt_value(int four_cc)
{
	unsigned int	format;

	if (four_cc == FOURCC_DXT1)
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
	else if (four_cc == FOURCC_DXT3)
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
	else if (four_cc == FOURCC_DXT5)
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
	else
		format = 0;
	return (format);
}

static size_t		calculate_bufsize(unsigned int mip_map_count, unsigned int	linear_size)
{
	if (mip_map_count > 1)
		return (linear_size * 2);
	else
		return (linear_size);
}

static GLuint		create_texture(t_DDS *properties, vector<unsigned char> &buffer)
{
	GLuint textureID;
    glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	unsigned int	block_size = (properties->format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	unsigned int	offset = 0;
	for (unsigned int level = 0; level < properties->mip_map_count && (properties->width || properties->height); ++level)
	{
		unsigned int size = ((properties->width + 3) / 4)*((properties->height + 3) / 4) * block_size;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, properties->format, properties->width, properties->height,
			0, size, (void *)(&buffer[offset]));
		offset += size;
		properties->width  /= 2;
		properties->height /= 2;
		if(properties->width < 1) properties->width = 1;
		if(properties->height < 1) properties->height = 1;
	}
	return (textureID);
}

static void			read_header(ifstream &image, t_DDS *properties)
{
	image.ignore(8);
	image.read((char *)&properties->height, sizeof(unsigned int));
	image.read((char *)&properties->width, sizeof(unsigned int));
	image.read((char *)&properties->linear_size, sizeof(unsigned int));
	image.ignore(4);
	image.read((char *)&properties->mip_map_count, sizeof(unsigned int));
	image.ignore(52);
	image.read((char *)&properties->four_cc, sizeof(unsigned int));
	image.ignore(40);
}

GLuint				loadDDS(const char *imagepath)
{
	if (imagepath == NULL)
		return (0);
	ifstream image(imagepath, ios::binary);
	if (!image.is_open())
		return (0);
	char	filecode[4];
	image.read(filecode, 4);
	if (kaf_strncmp(filecode, "DDS ", 4) != 0)
	{
		image.close();
		return (0);
	}
	t_DDS	properties;
	read_header(image, &properties);
	size_t bufsize = calculate_bufsize(properties.mip_map_count, properties.linear_size);
	vector<unsigned char> buffer(bufsize);
	image.read((char *)(&buffer[0]), bufsize);
	image.close();
	properties.format = compress_dxt_value(properties.four_cc);
	return (create_texture(&properties, buffer));
}
