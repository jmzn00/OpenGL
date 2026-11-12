#ifndef DEBUG_PASS_H
#define DEBUG_PASS_H
#include <eng/renderer/render_pass.h>
#include <eng/renderer/render_queue.h>
#include <eng/renderer/draw_command.h>
#include <eng/graphics/material/material.h>
#include <eng/graphics/shader_program.h>
#include <eng/entity/components.h>
#include <eng/entity/entity.h>

#include <eng/debug/assert.h>
#include <eng/profiler/profiler.h>

#include <memory>
#include <iostream>

namespace eng
{
	class DebugPass : public RenderPass
	{
	public:
		const char* Name() const override
		{
			return "Debug";
		}
		RenderStage Stage() const override
		{
			return RenderStage::PrePostProcess;
		}
		void Init() override
		{
			m_shader = std::make_unique<ShaderProgram>
				(ENGINE_ASSET_DIR "/shaders/debug/debug.vert",
					ENGINE_ASSET_DIR "/shaders/debug/debug.frag",
					ENGINE_ASSET_DIR "/shaders/debug/debug.geom");
		}
		void Execute(RenderContext& context) override
		{
			context.graphicsAPI.BindShaderProgram(m_shader.get());

			m_shader->SetMat4("projection", context.camera.GetProjection());
			m_shader->SetMat4("view", context.camera.GetView());

			for (auto& cmd : context.renderQueue.commands)
			{
				ENG_ASSERT(cmd.mesh != nullptr, "MESH NULL");
				ENG_ASSERT(cmd.transform != nullptr, "TRANSFORM NULL");

				m_shader->SetMat4("model", cmd.transform->GetTransform());				
				cmd.mesh->Bind();
				cmd.mesh->Draw();

				Profiler::Get().IncrementDrawCalls();
				Profiler::Get().AddTriangles(static_cast<uint32_t>(cmd.mesh->GetVertexCount()));
			}
		}
	private:
		std::unique_ptr<ShaderProgram> m_shader;
	};
}
#endif // !DEBUG_PASS_H
