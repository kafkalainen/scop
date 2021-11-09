#ifndef MESH_HPP
# define MESH_HPP
# include "../glad/include/glad/glad.h"
# include "../libkaf/libkaf.h"
# include "shader.hpp"
# define MAX_BONE_INFLUENCE 4

typedef struct t_vertex
{
	glm::vec3	pos;
	glm::vec3	normal;
	glm::vec2	texel;
	glm::vec2	tangent;
	glm::vec2	bitangent;
	int			m_BoneIDs[MAX_BONE_INFLUENCE];
	float		m_Weights[MAX_BONE_INFLUENCE];
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
