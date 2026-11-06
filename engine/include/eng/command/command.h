#ifndef COMMAND_H
#define COMMAND_H

#include <eng/command/command_context.h>

#include <string>
#include <string_view>
#include <vector>

namespace eng
{
    struct CommandResult
    {
        bool succeeded;
        std::string message;
    }; // required semicolon

    class ICommand
    {
    public:
        virtual ~ICommand() = default;

        virtual std::string_view Name() const = 0;
        virtual std::string_view Help() const = 0;

        virtual CommandResult Execute(
            const std::vector<std::string_view>& arguments,
            CommandContext& context) = 0;
    };
}

#endif // !COMMAND_H