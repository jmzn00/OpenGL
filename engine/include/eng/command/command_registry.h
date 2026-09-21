#ifndef COMMAND_REGISTRY_H
#define COMMAND_REGISTRY_H
#include <eng/command/command.h>

#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>

namespace eng
{
	class CommandRegistry
	{
	public:
		bool Register(std::unique_ptr<ICommand> command);

		CommandResult Execute(
			std::string_view input,
			CommandContext& context);
	private:
		std::unordered_map<std::string, std::unique_ptr<ICommand>> m_commands;
	};
}
#endif // !COMMAND_REGISTRY_H
