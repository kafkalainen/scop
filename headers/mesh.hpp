#ifndef MESH_HPP
# define MESH_HPP
# include "../glad/include/glad/glad.h"
# include "../libkaf/libkaf.h"
# include "shader.hpp"

typedef struct t_vertex
{
	glm::vec3	pos;
	glm::vec3	normal;
	glm::vec2	texel;
}			s_vertex;

typedef struct t_texture
{
	GLuint		id;
	string		type;
	string		path;
}				s_texture;

namespace kaf_mesh
{
	class Mesh
	{
		public:
			vector<t_vertex>		vertices;
			vector<unsigned int>	indices;
			vector<t_texture>		textures;

			Mesh(vector<t_vertex> vertices, vector<unsigned int> indices, vector<t_texture> textures);
			void Draw(kaf_shader::Shader &shader);
		private:
			GLuint	vertex_array_object;
			GLuint	vertex_buffer_object;
			GLuint	element_buffer_object;
			void setupMesh();
	};
}
#endif
