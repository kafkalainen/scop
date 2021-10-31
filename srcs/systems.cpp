#include "../headers/nerd.h"

int	run_main_loop(GLFWwindow *window, t_main *main, t_camera *cam)
{
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
		&& glfwWindowShouldClose(window) == 0)
	{
		fps_timer(&cam->t);
		// cout << cam->t.fps << endl;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(main->program_id);
		update_world(window, cam);
		mat4 MVP = cam->projection_matrix * cam->view_matrix * cam->model;
		glUniformMatrix4fv(main->matrix_id, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(main->model_matrix_id, 1, GL_FALSE, &cam->model[0][0]);
		glUniformMatrix4fv(main->view_matrix_id, 1, GL_FALSE, &cam->view_matrix[0][0]);
		glm::vec3 lightPos = glm::vec3(4,4,4);
		glUniform3f(main->light_id, lightPos.x, lightPos.y, lightPos.z);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, main->texture);
		glUniform1i(main->texture_id, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, main->element_buffer);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, main->vertex_buffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, main->texel_buffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, main->normal_buffer);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glDrawElements(GL_TRIANGLES, main->box.indices.size(), GL_UNSIGNED_SHORT, (void*)0);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return (EXIT_SUCCESS);
}
