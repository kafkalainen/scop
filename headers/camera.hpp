#ifndef CONTROLS_HPP
#define CONTROLS_HPP

typedef struct	t_screen_xy
{
	double		x;
	double		y;
}				s_screen_xy;

typedef struct	t_camera
{
	glm::mat4	view_matrix;
	glm::mat4	projection_matrix;
	glm::vec3	position;
	glm::vec3	direction;
	glm::vec3	right;
	glm::vec3	up;
	double		last_time;
	double		current_time;
	double		delta_time;
	t_screen_xy	mouse;
	float		yaw;
	float		pitch;
	float		initial_fov;
	float		speed;
	float		mouse_speed;
	int			win_width;
	int			win_height;
	t_screen_xy	middle;
}				s_camera;


void		initialize_camera_position(t_camera *cam);
void		compute_dir_right_up(t_camera *cam);
void 		update_view_matrix(t_camera *cam);
void		update_projection_matrix(t_camera *cam);

#endif
