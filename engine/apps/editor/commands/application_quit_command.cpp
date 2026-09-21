#include <eng/command/commands/application_quit_command.h>
#include <eng/core/application.h>

#include <iostream>

namespace eng
{
    ApplicationQuitCommand::ApplicationQuitCommand(Application& application)
        : m_application(application)
    {
    }

    std::string_view ApplicationQuitCommand::Name() const
    {
        return "quit";
    }

    std::string_view ApplicationQuitCommand::Help() const
    {
        return "Closes the application.";
    }

    CommandResult ApplicationQuitCommand::Execute(
        const std::vector<std::string_view>& arguments,
        CommandContext& context)
    {
        if (!arguments.empty())
        {
            return { false, "Usage: application.quit" };
        }

        m_application.SetNeedsToBeClosed(true);
        context.logger.Info("Application close requested.");

        return { true, "Closing application." };
    }
}