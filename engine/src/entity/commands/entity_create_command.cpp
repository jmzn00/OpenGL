#include <eng/command/commands/entity_create_command.h>
#include <eng/graphics/material/material.h>
#include <eng/graphics/material/material_library.h>
#include <eng/debug/assert.h>
#include <eng/graphics/texture/texture.h>

namespace eng
{
	EntityCreateCommand::EntityCreateCommand(Scene& scene)
		: m_scene {scene}
	{
	}
	std::string_view EntityCreateCommand::Name() const
	{
		return "ent.create";
	}
	std::string_view EntityCreateCommand::Help() const
	{
		return "Usage: ent.create <cube / light>";
	}

	CommandResult EntityCreateCommand::Execute(
		const std::vector<std::string_view>& arguments,
		CommandContext& context)
	{		
		if (arguments.empty())
		{
			return { false, "Usage: ent.create <cube / light>" };
		}
		if (arguments[0] == "cube")
		{
			std::string name = arguments.size() > 1 ? std::string(arguments[1]) : "CubeEnt";

			Entity& ent = m_scene.CreateEntity(name);

			auto mat = std::make_shared<Material>(*MaterialLibrary::Get("Silver"));
			std::shared_ptr<Texture2D> texture =
				std::make_shared<Texture2D>(ENGINE_ASSET_DIR "/textures/container.jpg");


			mat->SetShaderProgram(ShaderLibrary::Get("Default"));
			mat->SetDiffuseTexture(texture);

			ent.AddComponent<MeshComponent>(
				CubeMesh(),mat);

			return { true, "Created ent: " + ent.GetName() + ' ' + std::to_string(ent.GetID()) };
		}
		if (arguments[0] == "light")
		{
			std::string name = arguments.size() > 1 ? std::string(arguments[1]) : "LightEnt";
			Entity& ent = m_scene.CreateEntity(name);

			auto mat = MaterialLibrary::Get("Default");
			
			mat->SetShaderProgram(ShaderLibrary::Get("Light"));
			ent.AddComponent<MeshComponent>(
				CubeMesh(), mat);
			ent.AddComponent<LightComponent>();
			ent.Transform().SetScale(glm::vec3(0.5f));

			return { true, "Created ent: " + ent.GetName() + ' ' + std::to_string(ent.GetID())};
			
		}
		if (arguments[0] == "pyramid")
		{
			std::string name = arguments.size() > 1 ? std::string(arguments[1]) : "PyramidEnt";

			Entity& ent = m_scene.CreateEntity(name);

			auto mat = std::make_shared<Material>(*MaterialLibrary::Get("Silver"));
			std::shared_ptr<Texture2D> texture =
				std::make_shared<Texture2D>(ENGINE_ASSET_DIR "/textures/awesomeface.png");

			mat->SetDiffuseTexture(texture);
			mat->SetShaderProgram(ShaderLibrary::Get("Default"));
			ent.AddComponent<MeshComponent>(
				PyramidMesh(), mat);
			return { true, "Created ent: " + ent.GetName() + ' ' + std::to_string(ent.GetID()) };
		}
		return { false, "Usage: ent.create <cube / light>" };
	}
}