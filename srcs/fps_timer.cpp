#include "../headers/nerd.hpp"

void	initialize_time(t_time *t)
{
	t->frame_count = 0;
	t->fps = 0;
	t->frame_time_last = glfwGetTime();
}

void	fps_timer(t_time *t)
{
	t_uint	time_index;
	double	current_time;
	t_uint	current_frame_amount;
	t_uint	i;

	i = 0;
	current_frame_amount = 10;
	current_time = glfwGetTime();
	time_index = t->frame_count % 10;
	t->frame_times[time_index] = current_time - t->frame_time_last;
	t->frame_time_last = current_time;
	t->frame_count = t->frame_count + 1;
	if (t->frame_count < 10)
		current_frame_amount = t->frame_count;
	t->fps = 0;
	while (i < current_frame_amount)
	{
		t->fps += t->frame_times[i];
		i++;
	}
	t->fps = 1.0f / (t->fps / current_frame_amount);
}
