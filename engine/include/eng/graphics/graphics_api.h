#ifndef GRAPHICS_API_H
#define GRAPHICS_API_H
#include <memory>
#include <string>
#include <vector>
#include <glad/glad.h>
#include <cstdint>

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
		void BindFramebuffer(GLuint frameBufferId);

		void ToggleWireframe(bool isWireframe);

		static void SetBlendFunc(GLenum sfactor, GLenum dfactor);

		static void SetStencilFunc(
			GLenum func,
			GLint ref,
			GLuint mask);
		static void SetStencilOp(
			GLenum sfail,
			GLenum dpfail,
			GLenum dppass);
		static void SetStencilMask(GLuint mask);
		static void SetColorMask(GLboolean r, GLboolean g, GLboolean b, GLboolean a);

		static void EnableTest(GLenum test);
		static void DisableTest(GLenum test);
	};
}
#endif // !GRAPHICS_API_H
