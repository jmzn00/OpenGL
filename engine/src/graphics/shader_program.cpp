#include <eng/graphics/shader_program.h>
#include <iostream>
#include <filesystem>

namespace eng
{
	ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath)
	{
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;

			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch(std::ifstream::failure e)
		{
			std::cout << "ERROR:SHADER::FILE_NOT_SUCCESFULLY_READ\n"
					  << e.what() << '\n';
			throw;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		unsigned int vertex;
		unsigned int fragment;

		int success;
		char infoLog[512];
		
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);

		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
				infoLog << std::endl;
		};

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, nullptr);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
				infoLog << std::endl;
		};

		m_id = glCreateProgram();
		glAttachShader(m_id, vertex);
		glAttachShader(m_id, fragment);
		glLinkProgram(m_id);

		glGetProgramiv(m_id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_id, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" <<
				infoLog << std::endl;
		}
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	ShaderProgram::~ShaderProgram()
	{
		if (m_id != 0)
		{
			glDeleteProgram(m_id);
		}
	}
	GLuint ShaderProgram::GetId() const
	{
		return m_id;
	}
	GLint ShaderProgram::GetUniform4f(const std::string& name) const
	{
		return glGetUniformLocation(m_id, name.c_str());
	}
	void ShaderProgram::SetUniform4f(GLint location, float x, float y, float z, float w) const
	{
		glUniform4f(location, x, y, z, w);
	}
}
