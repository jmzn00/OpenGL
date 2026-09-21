#include <eng/command/commands/graphics_set_clear_color_command.h>
#include <charconv>
#include <system_error>

#include <eng/command/command_context.h>
#include <eng/core/logger.h>
#include <eng/graphics/graphics_api.h>

#include <eng/util/util.h>
namespace eng
{
	GraphicsSetClearColorCommand::GraphicsSetClearColorCommand(GraphicsAPI& graphics)
		: m_graphicsApi {graphics}
	{
	}
	std::string_view GraphicsSetClearColorCommand::Name() const
	{
		return "graphics.setclear";
	}
	std::string_view GraphicsSetClearColorCommand::Help() const
	{
		return "Sets clear color for the GraphicsAPI";
	}
	CommandResult GraphicsSetClearColorCommand::Execute(
		const std::vector<std::string_view>& arguments,
		CommandContext& context)
	{
        if (arguments.size() != 4)
        {
            return {
                false,
                "Usage: graphics.setclear <red> <green> <blue> <alpha>"
            };
        }

        float red;
        float green;
        float blue;
        float alpha;

        if (!util::ParseFloat(arguments[0], red) ||
            !util::ParseFloat(arguments[1], green) ||
            !util::ParseFloat(arguments[2], blue) ||
            !util::ParseFloat(arguments[3], alpha))
        {
            return {
                false,
                "All clear-color values must be numbers."
            };
        }

        if (red < 0.0f || red > 1.0f ||
            green < 0.0f || green > 1.0f ||
            blue < 0.0f || blue > 1.0f ||
            alpha < 0.0f || alpha > 1.0f)
        {
            return {
                false,
                "Clear-color values must be between 0 and 1."
            };
        }

        m_graphicsApi.SetClearColor(red, green, blue, alpha);

		return { true, "Clear color set" };
	}
	
}