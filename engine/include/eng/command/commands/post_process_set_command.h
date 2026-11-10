#ifndef POST_PROCESS_SET_COMMAND_H
#define POST_PROCESS_SET_COMMAND_H

#include <eng/command/command.h>
#include <eng/renderer/passes/post_process_pass.h>

namespace eng
{
	class PostProcessSetCommand final : public ICommand
	{
	public:
		explicit PostProcessSetCommand(PostProcessPass& postProcess);

		std::string_view Name() const override;
		std::string_view Help() const override;

		CommandResult Execute(
			const std::vector<std::string_view>& arguments,
			CommandContext& context) override;
	private:
		PostProcessPass& m_postProcess;
	};
}

#endif // 
