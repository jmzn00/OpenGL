#ifndef GEOMETRY_PASS_H
#define GEOMETRY_PASS_H
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

#include <vector>
#include <iostream>


namespace eng
{
	class GeometryPass : public RenderPass
	{
	public:
		const char* Name() const override
		{
			return "Geometry";
		}
		void Execute(RenderContext& context) override
		{			
			ShaderProgram* currentShader = nullptr;
			
			GraphicsAPI::EnableTest(GL_DEPTH_TEST);
			GraphicsAPI::SetStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
			GraphicsAPI::SetStencilFunc(GL_ALWAYS, 1, 0xFF);
			GraphicsAPI::SetStencilMask(0xFF);

			for (auto& cmd : context.commands)
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
#endif // !GEOMETRY_PASS_H
