#ifndef NERD_H
# define NERD_H

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

int	init_glfw();
int	create_window(GLFWwindow **window);
#endif
