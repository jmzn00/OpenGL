#ifndef APPLICATION_QUIT_COMMAND_H
#define APPLICATION_QUIT_COMMAND_H

#include <eng/command/command.h>
namespace eng
{
    class Application;

    class ApplicationQuitCommand final : public ICommand
    {
    public:
        explicit ApplicationQuitCommand(Application& application);

        std::string_view Name() const override;
        std::string_view Help() const override;

        CommandResult Execute(
            const std::vector<std::string_view>& arguments,
            CommandContext& context) override;
    private:
        Application& m_application;
    };

}
#endif // !


