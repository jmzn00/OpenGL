#ifndef MASKED_PASS_H
#define MASKED_PASS_H

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
	class MaskedPass : public RenderPass
	{
	public:
		const char* Name() const override
		{
			return "Masked";
		}
		RenderStage Stage() const override
		{
			return RenderStage::Masked;
		}
		void Execute(RenderContext& context) override
		{
			ShaderProgram* currentShader = nullptr;

			for (auto& cmd : context.renderQueue.masked)
			{
				ENG_ASSERT(cmd.mesh != nullptr, "MESH NULL");
				ENG_ASSERT(cmd.transform != nullptr, "TRANSFORM NULL");

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

					shader->SetVec3(
						"viewPos",
						context.camera.GetPosition());
					
					RenderLights(*shader, context);
					currentShader = shader;
				}

				shader->SetMat4(
					"model",
					cmd.transform->GetTransform());

				cmd.mesh->Bind();
				cmd.mesh->Draw();

				Profiler::Get().IncrementDrawCalls();
				Profiler::Get().AddTriangles(cmd.mesh->GetVertexCount());
			}
		}
	private:
		void RenderLights(const ShaderProgram& shader, const RenderContext& context)
		{
			if (!context.pointLights.empty())
			{
				shader.SetPointLights(context.pointLights);
			}
			if (!context.directionalLights.empty())
			{
				shader.SetDirectionalLights(context.directionalLights);
			}
			if (!context.spotLights.empty())
			{
				shader.SetSpotLights(context.spotLights);
			}
		}
	};
}
#endif // !MASKED_PASS_H
