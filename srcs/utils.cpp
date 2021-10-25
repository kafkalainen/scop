
#include "../headers/nerd.h"
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
	*window = glfwCreateWindow( 1024, 768, "Tutorial 02 - Red triangle", NULL, NULL);
	if( *window == NULL ){
		cout << "Failed to open GLFW window." << endl;
		glfwTerminate();
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
