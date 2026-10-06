#include <eng/command/commands/entity_create_command.h>

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
		return "Creates an entity";
	}

	CommandResult EntityCreateCommand::Execute(
		const std::vector<std::string_view>& arguments,
		CommandContext& context)
	{
		if (arguments.empty())
		{
			return { false, "Usage: ent.create cube" };
		}
		if (arguments[0] == "cube")
		{
			std::string name = arguments.size() > 1 ? std::string(arguments[1]) : "Cube Ent";

			Entity& ent = m_scene.CreateEntity(name);
			ent.AddComponent<MeshComponent>(
				CubeMesh(),
				ShaderLibrary::Get().Get("Default")
			);

			return { true, "Created ent: " + ent.GetName()};
		}
		return { false, "Usage: ent.create cube" };
	}
}