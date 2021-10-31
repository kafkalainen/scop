
#include "../headers/nerd.hpp"
#include "../glew/include/GL/glew.h"
#include "../glfw/include/GLFW/glfw3.h"

int	init_glfw()
{
	if( !glfwInit() )
	{
		cout << "Failed to initialize GLFW" << endl;
		return (EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	return (EXIT_SUCCESS);
}

int	create_window(GLFWwindow **window)
{
	*window = glfwCreateWindow( 1024, 768, "Particles", NULL, NULL);
	if( *window == NULL ){
		cout << "Failed to open GLFW window." << endl;
		glfwTerminate();
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	initialize_buffers(t_main *main)
{
	glGenBuffers(1, &main->vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, main->vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, main->box.vertices.size() * sizeof(glm::vec3), &main->box.vertices[0], GL_STATIC_DRAW);
	glGenBuffers(1, &main->texel_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, main->texel_buffer);
	glBufferData(GL_ARRAY_BUFFER, main->box.texels.size() * sizeof(glm::vec2), &main->box.texels[0], GL_STATIC_DRAW);
	glGenBuffers(1, &main->normal_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, main->normal_buffer);
	glBufferData(GL_ARRAY_BUFFER, main->box.normals.size() * sizeof(glm::vec3), &main->box.normals[0], GL_STATIC_DRAW);
	glGenBuffers(1, &main->element_buffer);
 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, main->element_buffer);
 	glBufferData(GL_ELEMENT_ARRAY_BUFFER, main->box.indices.size() * sizeof(unsigned short), &main->box.indices[0], GL_STATIC_DRAW);
}
