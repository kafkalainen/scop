#include "../headers/nerd.hpp"
using namespace glm;
using namespace kaf_graphics;

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		cout << "ERROR: Incorrect number of arguments." << endl;
		cout << argv[0] << endl;
		return (EXIT_FAILURE);
	}
	GLFWwindow *window;
	t_camera	cam;

	if (init_glfw() || create_window(&window))
		return (EXIT_FAILURE);
	initialize_camera_position(&cam);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return (EXIT_FAILURE);
	}
	initialize_input(&window, &cam);
	glClearColor(0.0f, 0.0f, 0.2f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	t_main	main;
	glGenVertexArrays(1, &main.vertex_array_id);
	glBindVertexArray(main.vertex_array_id);
	main.mod.x = 200;
	main.mod.y = 200;
	main.mod.scale = 1.0f;
	main.mod.color = glm::vec3(1.0f, 0.0f, 0.0f);
	main.view_object.load_from_file(
		"assets/shaders/StandardShading.vertexshader",
		"assets/shaders/StandardShading.fragmentshader");
	main.text.load_from_file(
		"assets/shaders/Typewriter.vertexshader",
		"assets/shaders/Typewriter.fragmentshader");
	main.text.use();
	glUniformMatrix4fv(glGetUniformLocation(main.text.program_id, "typewriting"), 1, GL_FALSE, glm::value_ptr(cam.typewriting));
	main.writer.initialize_typeface(
		"assets/fonts/Crumbled-Pixels.ttf");
	main.matrix_id = glGetUniformLocation(main.view_object.program_id, "MVP");
	main.view_matrix_id = glGetUniformLocation(main.view_object.program_id, "V");
	main.model_matrix_id = glGetUniformLocation(main.view_object.program_id, "M");
	main.texture = loadDDS("assets/textures/suzanne_uvmap.DDS");
	main.texture_id  = glGetUniformLocation(main.view_object.program_id, "myTextureSampler");
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
	initialize_buffers(&main);
	main.view_object.use();
	main.light_id = glGetUniformLocation(main.view_object.program_id, "LightPosition_worldspace");
	run_main_loop(window, &main, &cam);
	clean_up_gl(&main);
	glfwTerminate();
	return (EXIT_SUCCESS);
}
