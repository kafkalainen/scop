#include "../headers/nerd.hpp"
using namespace glm;

void	initialize_input(GLFWwindow **window, t_camera *cam)
{
	glfwSetInputMode(*window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwPollEvents();
	glfwSetCursorPos(*window, cam->middle.x, cam->middle.y);
	cam->inputs.transparency = false;
	cam->inputs.wireframe = false;
	cam->inputs.transparency_toggle = false;
	cam->inputs.wireframe_toggle = false;
	cam->inputs.w_currently_active = false;
	cam->inputs.t_currently_active = false;
}

void	handle_mouse_movement(GLFWwindow *window, t_camera *cam)
{
	glfwGetCursorPos(window, &cam->mouse.x, &cam->mouse.y);
	glfwSetCursorPos(window, cam->middle.x, cam->middle.y);
	cam->yaw += cam->mouse_speed * float(512 - cam->mouse.x);
	cam->pitch += cam->mouse_speed * float(384 - cam->mouse.y);
}

void	handle_key_input(GLFWwindow *window, t_camera *cam, float delta_time)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cam->position += cam->direction * delta_time * cam->speed;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cam->position -= cam->direction * delta_time * cam->speed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cam->position += cam->right * delta_time * cam->speed;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cam->position -= cam->right * delta_time * cam->speed;
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		cam->light_power -= 0.1f;
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		cam->light_power += 0.1f;
	cam->inputs.t_currently_active = glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS;
	cam->inputs.w_currently_active = glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS;
	if (!cam->inputs.transparency_toggle && cam->inputs.t_currently_active)
		cam->inputs.transparency = !cam->inputs.transparency;
	if (!cam->inputs.wireframe_toggle && cam->inputs.w_currently_active)
		cam->inputs.wireframe = !cam->inputs.wireframe;
	cam->inputs.transparency_toggle = cam->inputs.t_currently_active;
	cam->inputs.wireframe_toggle = cam->inputs.w_currently_active;
}

void	clean_up_gl(t_main *main)
{
	glDeleteBuffers(1, &main->vertex_buffer_object);
	glDeleteBuffers(1, &main->texel_buffer_object);
	glDeleteBuffers(1, &main->normal_buffer_object);
	glDeleteBuffers(1, &main->element_buffer_object);
	glDeleteVertexArrays(1, &main->vertex_array_object);
	glDeleteTextures(1, &main->texture1);
	glDeleteTextures(1, &main->texture2);
}
