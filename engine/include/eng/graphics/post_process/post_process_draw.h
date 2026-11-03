#ifndef POST_PROCESS_DRAW_H
#define POST_PROCESS_DRAW_H

#include <eng/graphics/graphics_api.h>
#include <eng/graphics/framebuffer.h>
#include <eng/graphics/shader_program.h>
#include <eng/renderer/mesh.h>

#include <functional>
#include <memory>
#include <vector>
#include <cstdint>

namespace eng
{
	// Shared fullscreen-quad renderer used by all post-process effects.
	class PostProcessDraw final
	{
	public:
		void Init()
		{
			const std::vector<float> vertices = {
				-1.f,  1.f, 0.f, 1.f,
				-1.f, -1.f, 0.f, 0.f,
				 1.f, -1.f, 1.f, 0.f,
				 1.f,  1.f, 1.f, 1.f
			};
			const std::vector<uint32_t> indices = { 0, 1, 2, 0, 2, 3 };

			VertexLayout layout{};
			layout.stride = 4 * sizeof(float);
			layout.elements = {
				{ 0, 2, GL_FLOAT, 0 },
				{ 1, 2, GL_FLOAT, 2 * sizeof(float) }
			};
			m_quad = std::make_unique<Mesh>(layout, vertices, indices);
		}

		void Draw(
			GraphicsAPI& graphics,
			ShaderProgram& shader,
			GLuint inputTexture,
			Framebuffer& output,
			const std::function<void(ShaderProgram&)>& setUniforms = {}) const
		{
			if (!m_quad || output.GetWidth() == 0 || output.GetHeight() == 0)
				return;

			const GLboolean depthWasEnabled = glIsEnabled(GL_DEPTH_TEST);
			const GLboolean stencilWasEnabled = glIsEnabled(GL_STENCIL_TEST);
			const GLboolean blendWasEnabled = glIsEnabled(GL_BLEND);
			GLint previousProgram = 0;
			GLint previousVertexArray = 0;
			GLint previousActiveTexture = 0;
			GLint previousTexture0 = 0;
			glGetIntegerv(GL_CURRENT_PROGRAM, &previousProgram);
			glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &previousVertexArray);
			glGetIntegerv(GL_ACTIVE_TEXTURE, &previousActiveTexture);
			glActiveTexture(GL_TEXTURE0);
			glGetIntegerv(GL_TEXTURE_BINDING_2D, &previousTexture0);

			output.Bind();
			glViewport(0, 0, output.GetWidth(), output.GetHeight());
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_STENCIL_TEST);
			glDisable(GL_BLEND);

			graphics.BindShaderProgram(&shader);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, inputTexture);
			shader.SetInt("screenTexture", 0);
			if (setUniforms)
				setUniforms(shader);

			m_quad->Bind();
			m_quad->Draw();

			glBindVertexArray(static_cast<GLuint>(previousVertexArray));
			glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(previousTexture0));
			glActiveTexture(static_cast<GLenum>(previousActiveTexture));
			graphics.BindShaderProgram(nullptr);
			if (previousProgram != 0)
				glUseProgram(static_cast<GLuint>(previousProgram));

			if (depthWasEnabled) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
			if (stencilWasEnabled) glEnable(GL_STENCIL_TEST); else glDisable(GL_STENCIL_TEST);
			if (blendWasEnabled) glEnable(GL_BLEND); else glDisable(GL_BLEND);
		}

	private:
		std::unique_ptr<Mesh> m_quad;
	};
}

#endif // !POST_PROCESS_DRAW_H
