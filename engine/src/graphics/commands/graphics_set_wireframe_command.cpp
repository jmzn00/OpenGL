#include <eng/command/commands/graphics_set_wireframe_command.h>
#include <eng/command/command_context.h>
#include <eng/core/logger.h>
#include <eng/graphics/graphics_api.h>
#include <eng/util/util.h>
namespace eng
{
	GraphicsSetWireframeCommand::GraphicsSetWireframeCommand(GraphicsAPI& graphics)
		: m_graphicsApi(graphics)
	{
	}

	std::string_view GraphicsSetWireframeCommand::Name() const
	{
		return "graphics.wireframe";
	}
	std::string_view GraphicsSetWireframeCommand::Help() const
	{		
		return "Sets opengl to render wireframe";
	}
	CommandResult GraphicsSetWireframeCommand::Execute(
		const std::vector<std::string_view>& arguments
		,CommandContext& context)
	{
		if (arguments.size() != 1)
		{
			return { false, "Usage: graphics.wireframe <1/0/true/false>" };
		}
		bool value;
		if (!util::ParseBool(arguments[0], value)
			|| (value != 0 && value != 1))
		{
			return { false, "Usage: graphics.wireframe <1/0/true/false>" };
		}
		m_graphicsApi.ToggleWireframe(static_cast<bool>(value));
		
		std::string message{ "Wireframe toggled: " };
		if (value == 1)
			message += "true";
		else
			message += "false";

		return { true,  message};
	}
}
