#include "../headers/nerd.hpp"

int	run_main_loop(GLFWwindow *window, t_main *main, t_camera *cam)
{
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
		&& glfwWindowShouldClose(window) == 0)
	{
		toggle_transparency(&cam->inputs);
		toggle_wireframe(&cam->inputs);
		fps_timer(&cam->t);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		update_world(window, cam);
		main->view_object.use();
		main->view_object.setMat4("view", cam->view_matrix);
		main->view_object.setMat4("projection", cam->projection_matrix);
		main->view_object.setVec3("viewPos", cam->position);
		main->view_object.setMat4("model", cam->model_matrix);
		main->model.Draw(main->view_object);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return (EXIT_SUCCESS);
}

		//DRAW HUD SEPERATELY
		// glEnableVertexAttribArray(0);
		// glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		// glBindBuffer(GL_ARRAY_BUFFER, 0);
		// glBindVertexArray(0);
		// main->writer.render_text(main->text, "Hello", main->mod);
