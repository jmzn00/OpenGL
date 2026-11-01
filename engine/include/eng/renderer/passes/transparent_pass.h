#ifndef TRANSPARENT_PASS_H
#define TRANSPARENT_PASS_H

#include <eng/renderer/render_pass.h>
#include <eng/profiler/profiler.h>
#include <eng/camera/camera.h>
#include <eng/graphics/shader_program.h>
#include <eng/debug/assert.h>
#include <eng/graphics/graphics_api.h>
#include <eng/renderer/draw_command.h>

#include <eng/renderer/mesh.h>
#include <eng/graphics/material/material.h>
#include <eng/entity/components.h>
#include <eng/renderer/render_queue.h>

#include <vector>
#include <iostream>

namespace eng
{
	class TransparentPass : public RenderPass
	{
	public:
		const char* Name() const override
		{
			return "Transparent";
		}
		RenderStage Stage() const override
		{
			return RenderStage::Transparent;
		}
		void Execute(RenderContext& context) override
		{			
			ShaderProgram* currentShader = nullptr;
			for (auto& cmd : context.renderQueue.transparent)
			{
				ENG_ASSERT(cmd.mesh != nullptr, "MESH NULL");
				ENG_ASSERT(cmd.material != nullptr, "Material null");
				ENG_ASSERT(cmd.transform != nullptr, "Transform null");

				ShaderProgram* shader = &cmd.material->GetShaderProgram();
				cmd.material->Bind(context.graphicsAPI);
				if (shader != currentShader)
				{
					shader->SetMat4(
						"view",
						context.camera.GetView());
					shader->SetMat4(
						"projection",
						context.camera.GetProjection());
					currentShader = shader;
				}
				shader->SetMat4(
					"model",
					cmd.transform->GetTransform());

				cmd.mesh->Bind();
				cmd.mesh->Draw();
			}
		}
	private:
		
	};
}
#endif // !TRANSPARENT_PASS_H
