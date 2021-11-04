#include "../headers/nerd.hpp"

int	run_main_loop(GLFWwindow *window, t_main *main, t_camera *cam)
{
	glm::vec3 headPositions[] = {
		glm::vec3( 0.0f,  0.0f,  0.0f),
		glm::vec3( 2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3( 2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3( 1.3f, -2.0f, -2.5f),
		glm::vec3( 1.5f,  2.0f, -2.5f),
		glm::vec3( 1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
		&& glfwWindowShouldClose(window) == 0)
	{
		toggle_transparency(&cam->inputs);
		toggle_wireframe(&cam->inputs);
		fps_timer(&cam->t);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		update_world(window, cam);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, main->texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, main->texture2);
		main->view_object.use();
		main->view_object.setMat4("view", cam->view_matrix);
		main->view_object.setMat4("projection", cam->projection_matrix);
		main->view_object.setFloat("LightPower", cam->light_power);
		glBindVertexArray(main->vertex_array_object);
		for(unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, headPositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			main->view_object.setMat4("model", model);
			glDrawElements(GL_TRIANGLES, main->box.indices.size(), GL_UNSIGNED_SHORT, (void*)0);
		}
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
