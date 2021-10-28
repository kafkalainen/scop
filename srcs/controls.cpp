#include "../headers/nerd.h"
using namespace glm;

void	initialize_input(GLFWwindow *window, t_screen_xy middle)
{
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwPollEvents();
    glfwSetCursorPos(window, middle.x, middle.y);
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
}

void	update_world(GLFWwindow *window, t_camera *cam)
{
	cam->current_time = glfwGetTime();
	cam->delta_time = float(cam->current_time - cam->last_time);
	handle_mouse_movement(window, cam);
	handle_key_input(window, cam, cam->delta_time);
	compute_dir_right_up(cam);
	update_projection_matrix(cam);
	update_view_matrix(cam);
	cam->last_time = cam->current_time;
}

void	clean_up_gl(t_main *main)
{
	glDeleteBuffers(1, &main->vertex_buffer);
	glDeleteBuffers(1, &main->texel_buffer);
	glDeleteProgram(main->program_id);
	glDeleteTextures(1, &main->texture);
	glDeleteVertexArrays(1, &main->vertex_array_id);
}
