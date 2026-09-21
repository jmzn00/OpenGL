#ifndef GRAPHICS_SET_WIREFRAME_COMMAND
#define GRAPHICS_SET_WIREFRAME_COMMAND
#include <eng/command/command.h>

namespace eng
{
	class GraphicsAPI;

    class GraphicsSetWireframeCommand final : public ICommand
    {
    public:
        explicit GraphicsSetWireframeCommand(GraphicsAPI& graphics);

        std::string_view Name() const override;
        std::string_view Help() const override;

        CommandResult Execute(
            const std::vector<std::string_view>& arguments,
            CommandContext& context) override;
    private:
        GraphicsAPI& m_graphicsApi;
    };
}
#endif // !GRAPHICS_SET_WIREFRAME_COMMAND
