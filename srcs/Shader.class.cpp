#include "../headers/nerd.hpp"

using namespace std;

namespace kaf_shader
{
	Shader::Shader(void)
	{
		initialized = false;
	}

	void	Shader::load_from_file(const char* vertex_file_path, const char* fragment_file_path)
	{
		t_temp_loader	tmp;

		tmp.vertex_shader_file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
		tmp.fragment_shader_file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			tmp.vertex_shader_file.open(vertex_file_path);
			tmp.fragment_shader_file.open(fragment_file_path);
			tmp.vertex_shader_stream << tmp.vertex_shader_file.rdbuf();
			tmp.fragment_shader_stream << tmp.fragment_shader_file.rdbuf();
			tmp.vertex_shader_file.close();
			tmp.fragment_shader_file.close();
			tmp.vertex_code = tmp.vertex_shader_stream.str();
			tmp.fragment_code = tmp.fragment_shader_stream.str();
		}
		catch (std::ifstream::failure &e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		const char* vShaderCode = tmp.vertex_code.c_str();
		const char* fShaderCode = tmp.fragment_code.c_str();

		tmp.vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(tmp.vertex, 1, &vShaderCode, NULL);
		glCompileShader(tmp.vertex);
		check_compiling_errors(tmp.vertex, "SHADER");
		tmp.fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(tmp.fragment, 1, &fShaderCode, NULL);
		glCompileShader(tmp.fragment);
		check_compiling_errors(tmp.fragment, "VERTEX");
		program_id = glCreateProgram();
		glAttachShader(program_id, tmp.vertex);
		glAttachShader(program_id, tmp.fragment);
		glLinkProgram(program_id);
		check_compiling_errors(program_id, "PROGRAM");
		glDeleteShader(tmp.vertex);
		glDeleteShader(tmp.fragment);
		initialized = true;
	}
	void Shader::use()
	{
		glUseProgram(program_id);
	}
	void Shader::setBool(const std::string &name, bool value) const
	{
		glUniform1i(glGetUniformLocation(program_id, name.c_str()), (int)value);
	}
	void Shader::setInt(const std::string &name, int value) const
	{
		glUniform1i(glGetUniformLocation(program_id, name.c_str()), value);
	}
	void Shader::setFloat(const std::string &name, float value) const
	{
		glUniform1f(glGetUniformLocation(program_id, name.c_str()), value);
	}

	void Shader::setVec3(const std::string &name, glm::vec3 &v)
	{
		glUniform3f(glGetUniformLocation(program_id, name.c_str()), v.x, v.y, v.z);
	}

	void Shader::setVec3(const std::string &name, float x, float y, float z)
	{
		glUniform3f(glGetUniformLocation(program_id, name.c_str()), x, y, z);
	}

	void Shader::setMat4(const std::string &name, glm::mat4 &m)
	{
		glUniformMatrix4fv(glGetUniformLocation(program_id, name.c_str()),
			1, GL_FALSE, &m[0][0]);
	}

	void Shader::check_compiling_errors(GLuint type, const char *msg)
	{
		GLint	success;
		char	infoLog[1024];

		glGetShaderiv(type, GL_COMPILE_STATUS, &success);
		if (kaf_strncmp(msg,"PROGRAM", 8))
		{
			glGetShaderiv(type, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(type, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: "
					<< type << "\n" << infoLog
					<< "\n -- --------------------------------------------------- --"
					<< std::endl;
			}
		}
		else
		{
			glGetProgramiv(type, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(type, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog
				<< "\n -- --------------------------------------------------- -- "
				<< std::endl;
			}
		}
	}
}
