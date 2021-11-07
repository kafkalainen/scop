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
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
			&indices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex),
			(void*)offsetof(t_vertex, normal));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(t_vertex),
			(void*)offsetof(t_vertex, texel));
		glBindVertexArray(0);
	}

	void Mesh::Draw(kaf_shader::Shader &shader)
	{
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		for(unsigned int i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			string number;
			string name = textures[i].type;
			if(name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if(name == "texture_specular")
				number = std::to_string(specularNr++);
			shader.setFloat(("material." + name + number).c_str(), i);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(vertex_array_object);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}
