#ifndef ENTITY_CREATE_COMMAND
#define ENTITY_CREATE_COMMAND

#include <eng/command/command.h>

#include <eng/scene/scene.h>
#include <eng/entity/entity.h>
#include <eng/entity/components.h>

#include <eng/renderer/mesh_library.h>
#include <eng/graphics/shader_library.h>

#include <string_view>
namespace eng
{
	class EntityCreateCommand final : public ICommand
	{
	public:
		explicit EntityCreateCommand(Scene& scene);

		std::string_view Name() const override;
		std::string_view Help() const override;

		CommandResult Execute(
			const std::vector<std::string_view>& arguments,
				  CommandContext& context) override;
	private:
		Scene& m_scene;
	};
}
#endif // !ENTITY_CREATE_COMMAND
