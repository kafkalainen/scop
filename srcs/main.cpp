#include "../headers/nerd.h"
using namespace glm;
using namespace kaf_graphics;

int	main(int argc, char **argv)
{
	if (argc != 2)
		cout << "ERROR: Incorrect number of arguments." << endl;
	GLFWwindow *window;

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
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "srcs/shaders/TransformVertexShader.vertexshader", "srcs/shaders/TextureFragmentShader.fragmentshader" );
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	mat4 Projection = perspective(radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	mat4 View = lookAt(
								glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
								glm::vec3(0,0,0), // and looks at the origin
								glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
	mat4 Model = mat4(1.0f);
	mat4 MVP = Projection * View * Model;
	GLuint Texture = loadDDS("srcs/textures/uvtemplate.DDS");
	GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");
	object box;
	try
	{
		box.load_from_file(argv[1]);
		box.print_vertices();
	}
	catch (char const *str)
	{
		cout << str << endl;
		return (EXIT_FAILURE);
	}
	// UV buffer data generated in blender.
	static const GLfloat g_uv_buffer_data[] = {
		0.000059f, 1.0f-0.000004f,
		0.000103f, 1.0f-0.336048f,
		0.335973f, 1.0f-0.335903f,
		1.000023f, 1.0f-0.000013f,
		0.667979f, 1.0f-0.335851f,
		0.999958f, 1.0f-0.336064f,
		0.667979f, 1.0f-0.335851f,
		0.336024f, 1.0f-0.671877f,
		0.667969f, 1.0f-0.671889f,
		1.000023f, 1.0f-0.000013f,
		0.668104f, 1.0f-0.000013f,
		0.667979f, 1.0f-0.335851f,
		0.000059f, 1.0f-0.000004f,
		0.335973f, 1.0f-0.335903f,
		0.336098f, 1.0f-0.000071f,
		0.667979f, 1.0f-0.335851f,
		0.335973f, 1.0f-0.335903f,
		0.336024f, 1.0f-0.671877f,
		1.000004f, 1.0f-0.671847f,
		0.999958f, 1.0f-0.336064f,
		0.667979f, 1.0f-0.335851f,
		0.668104f, 1.0f-0.000013f,
		0.335973f, 1.0f-0.335903f,
		0.667979f, 1.0f-0.335851f,
		0.335973f, 1.0f-0.335903f,
		0.668104f, 1.0f-0.000013f,
		0.336098f, 1.0f-0.000071f,
		0.000103f, 1.0f-0.336048f,
		0.000004f, 1.0f-0.671870f,
		0.336024f, 1.0f-0.671877f,
		0.000103f, 1.0f-0.336048f,
		0.336024f, 1.0f-0.671877f,
		0.335973f, 1.0f-0.335903f,
		0.667969f, 1.0f-0.671889f,
		1.000004f, 1.0f-0.671847f,
		0.667979f, 1.0f-0.335851f
	};
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, box.vertices.size() * sizeof(glm::vec3), &box.vertices[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
		&& glfwWindowShouldClose(window) == 0)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		glUniform1i(TextureID, 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			2,                                // size : U+V => 2
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);
	glfwTerminate();
	return (EXIT_SUCCESS);
}
