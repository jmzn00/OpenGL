#ifndef OUTLINE_PASS_H
#define OUTLINE_PASS_H

#include <eng/renderer/render_pass.h>
#include <eng/profiler/profiler.h>
#include <eng/camera/camera.h>
#include <eng/graphics/shader_program.h>
#include <eng/graphics/graphics_api.h>
#include <eng/renderer/draw_command.h>

#include <editor_context.h>

#include <memory>

namespace eng
{
	class OutlinePass : public RenderPass
	{
	public:
		OutlinePass(EditorContext& editorContext)
			: m_editorContext(editorContext)
		{
		}

		void Init() override
		{
			m_outlineShader = std::make_unique<ShaderProgram>(
				EDITOR_ASSET_DIR "/shaders/outline/outline.vert",
				EDITOR_ASSET_DIR "/shaders/outline/outline.frag");
		}

		const char* Name() const override
		{
			return "Outline";
		}
		void Execute(RenderContext& context) override
		{
			const auto selectedId =
				m_editorContext.GetSelectedEntityId();

			GraphicsAPI::SetStencilFunc(GL_NOTEQUAL, 1, 0xFF);
			GraphicsAPI::SetStencilMask(0x00);
			GraphicsAPI::DisableTest(GL_DEPTH_TEST);

			for (auto& cmd : context.commands)
			{
				if (cmd.entity->GetID() != selectedId)
					continue;

				ShaderProgram* shader = m_outlineShader.get();				
				context.graphicsAPI.BindShaderProgram(shader);

				shader->SetVec3("outlineColor", glm::vec3(1.0f, 0.0f, 0.0f));

				auto model = cmd.transform->GetTransform();
				model = glm::scale(model, glm::vec3(1.1));
				shader->SetMat4(
					"view",
					context.camera.GetView());

				shader->SetMat4(
					"projection",
					context.camera.GetProjection());

				shader->SetMat4("model", model);

				cmd.mesh->Bind();
				cmd.mesh->Draw();

				Profiler::Get().IncrementDrawCalls();
				Profiler::Get().AddTriangles(cmd.mesh->GetVertexCount());
			}
			// restore the stencil mask
			// if the mask is 0x00 then the stencil buffer will not be cleared
			GraphicsAPI::SetStencilMask(0xFF);			
		}

	private:
		EditorContext& m_editorContext;
		std::unique_ptr<ShaderProgram> m_outlineShader;
	};
}

#endif