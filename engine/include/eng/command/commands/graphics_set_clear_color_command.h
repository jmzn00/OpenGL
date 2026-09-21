#ifndef GRAPHICS_SET_CLEAR_COLOR_COMMAND
#define GRAPHICS_SET_CLEAR_COLOR_COMMAND

#include <eng/command/command.h>
namespace eng
{
    class GraphicsAPI;

    class GraphicsSetClearColorCommand final : public ICommand
    {
    public:
        explicit GraphicsSetClearColorCommand(GraphicsAPI& graphics);

        std::string_view Name() const override;
        std::string_view Help() const override;

        CommandResult Execute(
            const std::vector<std::string_view>& arguments,
            CommandContext& context) override;
    private:
        GraphicsAPI& m_graphicsApi;
    };
}
#endif // !GRAPHICS_SET_CLEAR_COLOR_COMMAND
