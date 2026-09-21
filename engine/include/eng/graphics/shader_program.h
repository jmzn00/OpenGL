#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>

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
		GLint GetUniform4f(const std::string& name) const;
		void SetUniform4f(GLint location, float x, float y, float z, float w) const;
	private:
		GLuint m_id{0};
	};
}
#endif // !SHADER_PROGRAM_H
