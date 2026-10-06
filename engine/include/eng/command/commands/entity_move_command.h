#ifndef ENTITY_MOVE_COMMAND
#define ENTITY_MOVE_COMMAND

#include <eng/command/command.h>

#include <eng/scene/scene.h>
#include <eng/entity/entity.h>
#include <eng/entity/components.h>

namespace eng
{
	class EntityMoveCommand final : public ICommand
	{
	public:
		explicit EntityMoveCommand(Scene& scene);

		std::string_view Name() const override;
		std::string_view Help() const override;

		CommandResult Execute(
			const std::vector<std::string_view>& arguments,
			CommandContext& context) override;
	private:
		Scene& m_scene;
	};
}
#endif // !ENTITY_MOVE_COMMAND
