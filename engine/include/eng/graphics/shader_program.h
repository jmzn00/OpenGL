#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vec3.hpp>

#include <unordered_map>

namespace eng
{
	class ShaderProgram
	{
	public:		
		explicit ShaderProgram(const char* vertexPath, const char* fragmentPath);
		ShaderProgram(const ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;
		explicit ShaderProgram(GLuint shaderProgramID);
		~ShaderProgram();
		GLuint GetId() const;
		GLint GetUniform(const std::string& name) const;

		void SetFloat(const char* name, float x) const;
		void SetVec3(const std::string& name, glm::vec3 value) const;

	private:
		GLuint m_id{0};
		[[maybe_unused]]std::unordered_map<std::string, GLuint> m_uniforms;
	};
}
#endif // !SHADER_PROGRAM_H
