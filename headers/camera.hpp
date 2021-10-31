#ifndef CAMERA_HPP
#define CAMERA_HPP

typedef unsigned int t_uint;

typedef struct s_time
{
	double	frame_times[11];
	double	frame_time_last;
	t_uint	frame_count;
	float	fps;
}				t_time;

typedef struct	t_screen_xy
{
	double		x;
	double		y;
}				s_screen_xy;

typedef struct	t_camera
{
	glm::mat4	model;
	glm::mat4	view_matrix;
	glm::mat4	projection_matrix;
	glm::vec3	position;
	glm::vec3	direction;
	glm::vec3	right;
	glm::vec3	up;
	t_time		t;
	t_screen_xy	mouse;
	t_screen_xy	middle;
	double		last_time;
	double		current_time;
	double		delta_time;
	float		yaw;
	float		pitch;
	float		initial_fov;
	float		speed;
	float		mouse_speed;
	int			win_width;
	int			win_height;
}				s_camera;


void		initialize_camera_position(t_camera *cam);
void		compute_dir_right_up(t_camera *cam);
void 		update_view_matrix(t_camera *cam);
void		update_projection_matrix(t_camera *cam);

#endif
