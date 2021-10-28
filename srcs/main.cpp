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
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		cout << "Failed to initialize GLEW" << endl;
		glfwTerminate();
		return (EXIT_FAILURE);
	}
	initialize_input(window, cam.middle);
	t_main	main;
	glClearColor(0.0f, 0.0f, 0.2f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glGenVertexArrays(1, &main.vertex_array_id);
	glBindVertexArray(main.vertex_array_id);
	main.program_id = LoadShaders( "srcs/shaders/TransformVertexShader.vertexshader", "srcs/shaders/TextureFragmentShader.fragmentshader" );
	main.matrix_id = glGetUniformLocation(main.program_id, "MVP");
	main.texture = loadDDS("srcs/textures/uvmap.DDS");
	main.texture_id  = glGetUniformLocation(main.program_id, "myTextureSampler");
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
	glGenBuffers(1, &main.vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, main.vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, box.vertices.size() * sizeof(glm::vec3), &box.vertices[0], GL_STATIC_DRAW);
	glGenBuffers(1, &main.texel_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, main.texel_buffer);
	glBufferData(GL_ARRAY_BUFFER, box.texels.size() * sizeof(glm::vec2), &box.texels[0], GL_STATIC_DRAW);
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
		&& glfwWindowShouldClose(window) == 0)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(main.program_id);
		update_world(window, &cam);
		mat4 MVP = cam.projection_matrix * cam.view_matrix * cam.model;
		glUniformMatrix4fv(main.matrix_id, 1, GL_FALSE, &MVP[0][0]);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, main.texture);
		glUniform1i(main.texture_id, 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, main.vertex_buffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, main.texel_buffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glDrawArrays(GL_TRIANGLES, 0, box.vertices.size());
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	clean_up_gl(&main);
	glfwTerminate();
	return (EXIT_SUCCESS);
}
