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
	main.program_id = LoadShaders( "srcs/shaders/StandardShading.vertexshader", "srcs/shaders/StandardShading.fragmentshader" );
	main.matrix_id = glGetUniformLocation(main.program_id, "MVP");
	main.view_matrix_id = glGetUniformLocation(main.program_id, "V");
	main.model_matrix_id = glGetUniformLocation(main.program_id, "M");
	main.texture = loadDDS("srcs/textures/suzanne_uvmap.DDS");
	main.texture_id  = glGetUniformLocation(main.program_id, "myTextureSampler");
	try
	{
		main.box.load_from_file(argv[1]);
		main.box.index_VBO();
	}
	catch (char const *str)
	{
		cout << str << endl;
		clean_up_gl(&main);
		return (EXIT_FAILURE);
	}
	glGenBuffers(1, &main.vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, main.vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, main.box.vertices.size() * sizeof(glm::vec3), &main.box.vertices[0], GL_STATIC_DRAW);
	glGenBuffers(1, &main.texel_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, main.texel_buffer);
	glBufferData(GL_ARRAY_BUFFER, main.box.texels.size() * sizeof(glm::vec2), &main.box.texels[0], GL_STATIC_DRAW);
	glGenBuffers(1, &main.normal_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, main.normal_buffer);
	glBufferData(GL_ARRAY_BUFFER, main.box.normals.size() * sizeof(glm::vec3), &main.box.normals[0], GL_STATIC_DRAW);
	glGenBuffers(1, &main.element_buffer);
 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, main.element_buffer);
 	glBufferData(GL_ELEMENT_ARRAY_BUFFER, main.box.indices.size() * sizeof(unsigned short), &main.box.indices[0], GL_STATIC_DRAW);
	glUseProgram(main.program_id);
	main.light_id = glGetUniformLocation(main.program_id, "LightPosition_worldspace");
	run_main_loop(window, &main, &cam);
	clean_up_gl(&main);
	glfwTerminate();
	return (EXIT_SUCCESS);
}
