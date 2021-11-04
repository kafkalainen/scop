#include "../headers/nerd.hpp"

void	initialize_camera_position(t_camera *cam)
{
	cam->position = glm::vec3(0.0f, 0.0f, 5.0f);
	cam->direction = glm::vec3(0.0f, 0.0f, -1.0f);
	cam->up = glm::vec3(0.0f, 1.0f, 0.0f);
	cam->yaw = -1.57079633f;
	cam->pitch = 0.0f;
	cam->initial_fov = 45.0f;
	cam->speed = 3.0f;
	cam->mouse_speed = 0.005f;
	cam->middle = (t_screen_xy){512, 384};
	initialize_time(&cam->t);
	cam->model_matrix = mat4(1.0f);
	cam->view_matrix = mat4(1.0f);
	cam->projection_matrix = mat4(1.0f);
	compute_dir_right_up(cam);
	update_view_matrix(cam);
	update_projection_matrix(cam);
	cam->typewriting = glm::ortho(0.0f, 1024.0f, 0.0f, 768.0f);
}

void	compute_dir_right_up(t_camera *cam)
{
	cam->direction = glm::normalize(glm::vec3(
		cos(cam->yaw) * cos(cam->pitch),
		sin(cam->pitch),
		sin(cam->yaw) * cos(cam->pitch)
	));
	cam->up = glm::vec3(0.0f, 1.0f, 0.0f);
	cam->right = glm::normalize(glm::cross(cam->direction, cam->up));
	cam->up = glm::normalize(glm::cross(cam->right, cam->direction));
}

void	update_view_matrix(t_camera *cam)
{
	cam->view_matrix = glm::lookAt(cam->position,
		cam->position + cam->direction, cam->up);
}

void	update_projection_matrix(t_camera *cam)
{
	cam->projection_matrix = glm::perspective(
		glm::radians(cam->initial_fov), 4.0f / 3.0f, 0.1f, 100.0f);
}
