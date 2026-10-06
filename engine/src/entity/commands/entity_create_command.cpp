#include <eng/command/commands/entity_create_command.h>
#include <eng/graphics/material/material.h>
#include <eng/debug/assert.h>

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

			Material mat{ MaterialProperties
				{
					glm::vec3(0.2, 0.2, 0.2),
					glm::vec3(0.5, 0.5, 0.5),
					glm::vec3(0.2, 0.2, 0.2),
					32.0f} };

			mat.SetShaderProgram(ShaderLibrary::Get().Get("Default"));
			ent.AddComponent<MeshComponent>(
				CubeMesh(),std::make_shared<Material>(mat));
			return { true, "Created ent: " + ent.GetName() + ' ' + std::to_string(ent.GetID()) };
		}
		if (arguments[0] == "light")
		{
			std::string name = arguments.size() > 1 ? std::string(arguments[1]) : "LightEnt";
			Entity& ent = m_scene.CreateEntity(name);

			Material mat{ MaterialProperties
				{
					glm::vec3(0.2, 0.2, 0.2),
					glm::vec3(0.2, 0.2, 0.2),
					glm::vec3(0.2, 0.2, 0.2),
					32.0f} };

			mat.SetShaderProgram(ShaderLibrary::Get().Get("Light"));
			ent.AddComponent<MeshComponent>(
				CubeMesh(), std::make_shared<Material>(mat));
			ent.AddComponent<LightComponent>();
			ent.Transform().SetScale(glm::vec3(0.5f));

			return { true, "Created ent: " + ent.GetName() + ' ' + std::to_string(ent.GetID())};
			
		}
		return { false, "Usage: ent.create <cube / light>" };
	}
}