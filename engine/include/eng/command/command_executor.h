#ifndef COMMAND_EXECUTOR_H
#define COMMAND_EXECUTOR_H

#include <eng/command/command_context.h>
#include <eng/command/command_registry.h>

#include <string>

namespace eng
{
	class CommandExecutor
	{
	public:
		CommandExecutor(CommandRegistry& registry, CommandContext& context)
			: m_context {context}, m_registry {registry}
		{		
		}
		CommandResult Submit(const std::string& command)
		{
			return m_registry.Execute(command, m_context);
		}
	private:
		CommandContext& m_context;
		CommandRegistry& m_registry;
	};
}
#endif // !COMMAND_EXECUTOR_H
