#ifndef GRAPHICS_API_H
#define GRAPHICS_API_H
#include <memory>
#include <string>
#include <vector>
#include <glad/glad.h>

namespace eng
{
	class ShaderProgram;
	class Material;
	class Mesh;

	class GraphicsAPI
	{
	public:
		bool Init();

		void SetClearColor(float r, float g, float b, float a);
		void ClearBuffers();

		void BindShaderProgram(ShaderProgram* shaderProgram);

		void ToggleWireframe(bool isWireframe);

		static void SetStencilFunc(
			GLenum func,
			GLint ref,
			GLuint mask);
		static void SetStencilOp(
			GLenum sfail,
			GLenum dpfail,
			GLenum dppass);
		static void SetStencilMask(GLuint mask);
		static void SetColorMask(GLenum a, GLenum b, GLenum c, GLenum d);

		static void EnableTest(GLenum test);
		static void DisableTest(GLenum test);

	};
}
#endif // !GRAPHICS_API_H
