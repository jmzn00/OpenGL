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
			throw;
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
			throw;
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
			throw;
		}
		glDeleteShader(vertex);
		glDeleteShader(fragment);

		GLint uniformCount{ 0 };
		glGetProgramiv(m_id, GL_ACTIVE_UNIFORMS, &uniformCount);

		for (GLint i = 0; i < uniformCount; i++)
		{
			char name[256];
			GLsizei length;
			GLint size;
			GLenum type;

			glGetActiveUniform(
				m_id,
				i,
				sizeof(name),
				&length,
				&size,
				&type,
				name
			);
			GLint location = glGetUniformLocation(m_id, name);
			m_uniforms[name] = location;			
		}
	}
	void ShaderProgram::SetFloat(const char* name, float x) const
	{
		auto it = m_uniforms.find(name);

		if (it == m_uniforms.end())
		{
			//std::cout << "Uniform not found: " << name << '\n';
			return;			
		}
		glUniform1f(it->second, x);
	}
	void ShaderProgram::SetMat4(const std::string& name, glm::mat4 value) const
	{
		auto it = m_uniforms.find(name);

		if (it == m_uniforms.end())
		{
			std::cout << "SHADER_PROGRAM::SETMAT4 UNIFORM: " << name << " NOT FOUND\n";
			return;
		}
		glUniformMatrix4fv(it->second, 1, GL_FALSE, glm::value_ptr(value));
	}
	void ShaderProgram::SetVec3(const std::string& name, glm::vec3 value) const
	{
		auto it = m_uniforms.find(name);

		if (it == m_uniforms.end())
		{
			//std::cout << "Uniform not found: " << name << '\n';
			return;
		}
		glUniform3f(it->second, value.x, value.y, value.z);
	}
	void ShaderProgram::SetInt(const std::string& name, int value) const
	{
		auto it = m_uniforms.find(name);
		
		if (it == m_uniforms.end())
		{
			return;
		}
		glUniform1i(it->second, value);
	}
	void ShaderProgram::SetFloat(const std::string& name, float value) const
	{
		auto it = m_uniforms.find(name);

		if (it == m_uniforms.end())
		{
			//std::cout << "Uniform not found: " << name << '\n';
			return;
		}
		glUniform1f(it->second, value);
	}
	void ShaderProgram::SetLight(const RenderLight& light) const
	{
		switch (light.type)
		{
		case LightType::Point:
			std::cout << "point light" << '\n';

			SetVec3("pointLights[0].position", light.position);
			SetVec3("pointLights[0].ambient", light.ambient);
			SetVec3("pointLights[0].diffuse", light.diffuse);
			SetVec3("pointLights[0].specular", light.specular);

			SetFloat("pointLights[0].constant", light.constant);
			SetFloat("pointLights[0].linear", light.linear);
			SetFloat("pointLights[0].quadratic", light.quadratic);
			break;
		case LightType::Direction:
			break;

		}
		//SetInt("light.type", static_cast<int>(light.type));
		//
		//SetVec3("light.position", light.position);
		//SetVec3("light.direction", light.direction);
		//
		//SetVec3("light.ambient", light.ambient);
		//SetVec3("light.diffuse", light.diffuse);
		//SetVec3("light.specular", light.specular);
		//
		//SetFloat("light.constant", light.constant);
		//SetFloat("light.linear", light.linear);
		//SetFloat("light.quadratic", light.quadratic);
		//
		//SetFloat("light.innerCutoff", light.innerCutoff);
		//SetFloat("light.outerCutoff", light.outerCutoff);
	}
	void ShaderProgram::SetPointLights(const std::vector<RenderLight>& lights) const
	{
		constexpr std::size_t maxPointLights = 32;
		const std::size_t count = std::min(lights.size(), maxPointLights);

		SetInt("pointLightCount", static_cast<int>(count));

		for (std::size_t i = 0; i < count; i++)
		{
			const std::string prefix{
				"pointLights[" + std::to_string(i) + "]."
			};

			SetVec3(prefix + "position", lights[i].position);
			SetVec3(prefix + "ambient", lights[i].ambient);
			SetVec3(prefix + "diffuse", lights[i].diffuse);
			SetVec3(prefix + "specular", lights[i].specular);

			SetFloat(prefix + "constant", lights[i].constant);
			SetFloat(prefix + "linear", lights[i].linear);
			SetFloat(prefix + "quadratic", lights[i].quadratic);
		}
	}
	void ShaderProgram::SetDirectionalLights(const std::vector<RenderLight>& lights) const
	{
		constexpr std::size_t maxDirectionalLights = 4;
		const std::size_t count = std::min(lights.size(), maxDirectionalLights);

		SetInt("directionalLightCount", static_cast<int>(count));
		for (std::size_t i = 0; i < count; i++)
		{
			const std::string prefix{
				"directionalLights[" + std::to_string(i) + "]."
			};

			SetVec3(prefix + "direction", lights[i].direction);
			SetVec3(prefix + "ambient", lights[i].ambient);
			SetVec3(prefix + "diffuse", lights[i].diffuse);
			SetVec3(prefix + "specular", lights[i].specular);
		}
	}
	void ShaderProgram::SetSpotLights(const std::vector<RenderLight>& lights) const
	{
		constexpr std::size_t maxSpotLights = 32;
		const std::size_t count = std::min(lights.size(), maxSpotLights);

		SetInt("spotLightCount", static_cast<int>(count));

		for (std::size_t i = 0; i < count; i++)
		{
			const std::string prefix{
				"spotLights[" + std::to_string(i) + "]."
			};

			SetFloat(prefix + "innerCutoff", lights[i].innerCutoff);
			SetFloat(prefix + "outerCutoff", lights[i].outerCutoff);
			SetFloat(prefix + "constant", lights[i].constant);
			SetFloat(prefix + "linear", lights[i].linear);
			SetFloat(prefix + "quadratic", lights[i].quadratic);


			SetVec3(prefix + "position", lights[i].position);
			SetVec3(prefix + "direction", lights[i].direction);
			SetVec3(prefix + "ambient", lights[i].ambient);
			SetVec3(prefix + "diffuse", lights[i].diffuse);
			SetVec3(prefix + "specular", lights[i].specular);


		}
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
	GLint ShaderProgram::GetUniform(const std::string& name) const
	{
		auto it = m_uniforms.find(name);

		if (it == m_uniforms.end())
			return -1;

		return it->second;
	}
}
