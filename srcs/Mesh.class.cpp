#include "../headers/nerd.hpp"

namespace kaf_mesh
{

	Mesh::Mesh(vector<t_vertex> vertices, vector<unsigned int> indices, vector<t_texture> textures)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;
		setupMesh();
	}

	/*
	**	glGenVertexarrays generates vertex array object (VAO), that stores
	**	necessary buffers to render image on the screen.
	**	Vertex buffer object stores vertex data, which have vertex information
	**	texel, and normal to vertex. These are stored tightly in t_vertex struct.
	**	so data is copied to vertex buffer object as it is.
	**	Element buffer object (EBO) has the indices to tell to the drawing function which
	**	vertex to render to user. Vertex attribute arrays are then used to inform
	**	OpenGL how the data is stored in the vertex buffer object (VBO),
	**	and what the offset they reside in memory buffer.
	**	Finally, vertex array object is bound to zero, to release current
	**	vertex array object in focus.
	*/
	void Mesh::setupMesh()
	{
		glGenVertexArrays(1, &vertex_array_object);
		glGenBuffers(1, &vertex_buffer_object);
		glGenBuffers(1, &element_buffer_object);
		glBindVertexArray(vertex_array_object);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(t_vertex),
			&vertices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()
			* sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex),
			(void*)offsetof(t_vertex, normal));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(t_vertex),
			(void*)offsetof(t_vertex, texel));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex),
			(void*)offsetof(t_vertex, tangent));
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex),
			(void*)offsetof(t_vertex, tangent));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, MAX_BONE_INFLUENCE, GL_INT, GL_FALSE, sizeof(t_vertex),
			(void*)offsetof(t_vertex, m_BoneIDs));
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, MAX_BONE_INFLUENCE, GL_FLOAT, GL_FALSE, sizeof(t_vertex),
			(void*)offsetof(t_vertex, m_Weights));
		glBindVertexArray(0);
	}

	void Mesh::Draw(kaf_shader::Shader &shader)
	{
		unsigned int diffuse_textures = 1;
		unsigned int specular_textures = 1;
		unsigned int normal_textures = 1;
		unsigned int height_textures = 1;
		for(unsigned int i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			string number;
			string name = textures[i].type;
			if(name == "texture_diffuse")
				number = std::to_string(diffuse_textures++);
			else if(name == "texture_specular")
				number = std::to_string(specular_textures++);
			else if(name == "texture_normal")
				number = std::to_string(normal_textures++);
			else if(name == "texture_height")
				number = std::to_string(height_textures++);
			shader.setInt(("material." + name + number).c_str(), i);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}
		glBindVertexArray(vertex_array_object);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0); //NOTE: It's good practice to set vertex array object to zero.
		glActiveTexture(GL_TEXTURE0); //NOTE: Also, it's good to set texture to default.
	}
}
