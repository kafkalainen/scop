#include "../headers/nerd.h"
using namespace glm;
using namespace kaf_graphics;

int	main(int argc, char **argv)
{
	if (argc != 2)
		cout << "ERROR: Incorrect number of arguments." << endl;
	GLFWwindow *window;
	t_camera	cam;

	initialize_camera_position(&cam);
	if (init_glfw())
		return (EXIT_FAILURE);
	if (create_window(&window))
		return (EXIT_FAILURE);
	glfwMakeContextCurrent(window);
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK)
	{
		cout << "Failed to initialize GLEW" << endl;
		glfwTerminate();
		return (EXIT_FAILURE);
	}
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0.0f, 0.0f, 0.5f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	GLuint program_id = LoadShaders( "srcs/shaders/TransformVertexShader.vertexshader", "srcs/shaders/TextureFragmentShader.fragmentshader" );
	GLuint matrix_id = glGetUniformLocation(program_id, "MVP");
	GLuint texture = loadDDS("srcs/textures/uvmap.DDS");
	GLuint texture_id  = glGetUniformLocation(program_id, "myTextureSampler");
	object box;
	try
	{
		box.load_from_file(argv[1]);
	}
	catch (char const *str)
	{
		cout << str << endl;
		return (EXIT_FAILURE);
	}
	GLuint vertex_buffer;
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, box.vertices.size() * sizeof(glm::vec3), &box.vertices[0], GL_STATIC_DRAW);

	GLuint uv_buffer;
	glGenBuffers(1, &uv_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
	glBufferData(GL_ARRAY_BUFFER, box.texels.size() * sizeof(glm::vec2), &box.texels[0], GL_STATIC_DRAW);
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
		&& glfwWindowShouldClose(window) == 0)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(program_id);
		update_world(window, &cam);
		mat4 MVP = cam.projection_matrix * cam.view_matrix * cam.model;
		glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &MVP[0][0]);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(texture_id, 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glDrawArrays(GL_TRIANGLES, 0, box.vertices.size());
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteBuffers(1, &vertex_buffer);
	glDeleteBuffers(1, &uv_buffer);
	glDeleteProgram(program_id);
	glDeleteTextures(1, &texture);
	glDeleteVertexArrays(1, &VertexArrayID);
	glfwTerminate();
	return (EXIT_SUCCESS);
}
