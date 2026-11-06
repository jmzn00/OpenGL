#include <eng/command/commands/post_process_set_command.h>
#include <eng/renderer/renderer.h>
#include <eng/util/util.h>

namespace eng
{
	PostProcessSetCommand::PostProcessSetCommand()
	{	
		
	}
	std::string_view PostProcessSetCommand::Name() const
	{
		return "postprocess.set";
	}
	std::string_view PostProcessSetCommand::Help() const
	{
		return "sets post process effects";
	}
	CommandResult PostProcessSetCommand::Execute(
		const std::vector<std::string_view>& arguments
		,CommandContext& context)
	{		
		if (arguments.size() < 2)
		{
			return { false, "Usage: postprocess.set <name> <true/false>" };
		}		
		bool value;
		if (!util::ParseBool(arguments[1], value))
		{
			return { false, "Usage: postprocess.set <name> <true/false>" };
		}

		auto* postProcess = Renderer::Get().GetPass<PostProcessPass>();
		if (!postProcess)
		{
			return { false, "PostProcess NULL" };
		}
		if (!postProcess->ToggleEffect(std::string(arguments[0]), value))
		{
			return { false, "Invalid effect name" };
		}
		else
		{
			std::string op = value ? "true" : "false";

			return { true, "Set " + std::string(arguments[0]) + " " + op};
		}
		
	}

}