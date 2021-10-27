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
#include "shader.hpp"
#include "camera.hpp"

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

int		init_glfw();
int		create_window(GLFWwindow **window);
GLuint	loadDDS(const char * imagepath);
void	update_world(GLFWwindow *window, t_camera *cam);
#endif
