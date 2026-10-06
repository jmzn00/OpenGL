#include <eng/command/commands/entity_move_command.h>
#include <eng/util/util.h>

namespace eng
{
	EntityMoveCommand::EntityMoveCommand(Scene& scene)
		: m_scene {scene}
	{
	}
	std::string_view EntityMoveCommand::Name() const
	{
		return "ent.move";
	}
	std::string_view EntityMoveCommand::Help() const
	{
		return "Moves an entity to the position";
	}
	CommandResult EntityMoveCommand::Execute(
		const std::vector<std::string_view>& arguments,
		CommandContext& context)
	{
		if (arguments.empty())
		{
			return { false, "Usage: ent.move <name> <position>" };
		}
		if (arguments.size() < 4)
		{
			return { false, "Usage: ent.move <name> <position / 1 2 3>" };
		}
		Entity* ent = m_scene.FindEntityByName(arguments[0]);
		if (ent == nullptr)
		{
			std::string msg{ "Ent: " };
			msg += arguments[0];
			msg += " Not Found";
			return { false, msg};
		}
		float x, y, z;

		if (!util::ParseFloat(arguments[1], x))
		{
			return { false, "Usage: ent.move <name> <position / 1 2 3>" };
		}
		if (!util::ParseFloat(arguments[2], y))
		{
			return { false, "Usage: ent.move <name> <position / 1 2 3>" };
		}
		if (!util::ParseFloat(arguments[3], z))
		{
			return { false, "Usage: ent.move <name> <position / 1 2 3>" };
		}
		ent->Transform().MoveTo(glm::vec3(x, y, z));

		std::string msg =
			"Moved " +
			ent->GetName() +
			" to: " +
			std::string(arguments[1]) + " " +
			std::string(arguments[2]) + " " +
			std::string(arguments[3]);

		return { true, msg };
	}
}