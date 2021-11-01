#ifndef NERD_H
# define NERD_H
# define FOURCC_DXT1 0x31545844
# define FOURCC_DXT3 0x33545844
# define FOURCC_DXT5 0x35545844

# include <iostream>
using namespace std;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;
#include "../glew/include/GL/glew.h"

// Include GLFW
#include "../glfw/include/GLFW/glfw3.h"

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
#include "../libkaf/libkaf.h"
using namespace kaf_graphics;
#include "controls.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include "typewriter.hpp"
using namespace kaf_typewriter;
using namespace kaf_shader;

typedef struct	t_DDS
{
	unsigned int	height;
	unsigned int	width;
	unsigned int	linear_size;
	unsigned int	mip_map_count;
	unsigned int	four_cc;
	unsigned int	block_size;
	unsigned int	format;
}				s_DDS;

typedef struct	t_main
{
	GLuint						vertex_array_id;
	GLuint						matrix_id;
	GLuint						view_matrix_id;
	GLuint						model_matrix_id;
	GLuint						texture;
	GLuint						texture_id;
	vector<unsigned int>		indices;
	GLuint						vertex_buffer;
	GLuint						texel_buffer;
	GLuint						normal_buffer;
	GLuint						element_buffer;
	GLuint						light_id;
	object						box;
	kaf_shader::shader			view_object;
}				s_main;
// typewriter					writer;

void	clean_up_gl(t_main *main);
void	fps_timer(t_time *t);
int		init_glfw();
void	initialize_buffers(t_main *main);
void	initialize_input(GLFWwindow *window, t_camera *cam);
void	initialize_time(t_time *t);
void	handle_key_input(GLFWwindow *window, t_camera *cam, float delta_time);
void	handle_mouse_movement(GLFWwindow *window, t_camera *cam);
int		create_window(GLFWwindow **window);
GLuint	loadDDS(const char * imagepath);
int		run_main_loop(GLFWwindow *window, t_main *main, t_camera *cam);
void	toggle_transparency(t_inputs *input);
void	update_world(GLFWwindow *window, t_camera *cam);

#endif
