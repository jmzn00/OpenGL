#include <eng/command/command_registry.h>
#include <eng/core/application.h>

#include <cctype>
#include <vector>
#include <memory>

// command headers
#include <eng/command/commands/application_quit_command.h>
#include <eng/command/commands/graphics_set_clear_color_command.h>
#include <eng/command/commands/graphics_set_wireframe_command.h>
#include <eng/command/commands/entity_create_command.h>
#include <eng/command/commands/entity_move_command.h>

namespace eng
{
	void CommandRegistry::RegisterAll(EngineContext& ctx, Scene& scene)
	{
		Register(
			std::make_unique<ApplicationQuitCommand>(Application::Get())
		);
		Register(
			std::make_unique<GraphicsSetClearColorCommand>(ctx.GetGraphicsAPI())
		);
		Register(
			std::make_unique<GraphicsSetWireframeCommand>(ctx.GetGraphicsAPI())
		);
		Register(
			std::make_unique<EntityCreateCommand>(scene)
		);
		Register(
			std::make_unique<EntityMoveCommand>(scene)
		);
	}
	bool CommandRegistry::Register(std::unique_ptr<ICommand> command)
	{
		if (!command)
			return false;

		const std::string name(command->Name().data(),
							command->Name().size());

		return m_commands.emplace(name, std::move(command)).second;
	}
	CommandResult CommandRegistry::Execute(
		std::string_view input,
		CommandContext& context)
	{

		std::vector<std::string_view> tokens;
		std::size_t position = 0;

		while (position < input.size())
		{
			while (position < input.size() &&
				std::isspace(static_cast<unsigned char>(input[position])))
			{
				++position;
			}

			const std::size_t start = position;
			while (position < input.size() &&
				!std::isspace(static_cast<unsigned char>(input[position])))
			{
				++position;
			}
			if (start != position)
			{
				tokens.push_back(input.substr(start, position - start));
			}
		}
		if (tokens.empty())
		{
			return { false, "Enter a command." };
		}

		const std::string commandName(
			tokens[0].data(),
			tokens[0].size()
		);

		const auto command = m_commands.find(commandName);
		if (command == m_commands.end())
		{
			return { false, "Unknown command: " + std::string(tokens[0]) };
		}
		std::vector <std::string_view> arguments(
			tokens.begin() + 1,
			tokens.end()
		);
		return command->second->Execute(arguments, context);
	}

}