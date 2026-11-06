#ifndef POST_PROCESS_PANEL_H
#define POST_PROCESS_PANEL_H

#include <editor_component.h>
#include <eng/renderer/renderer.h>
#include <eng/renderer/passes/post_process_pass.h>
#include <eng/command/command_executor.h>
namespace eng
{
	class PostProcessPanel final : public IEditorComponent
	{
	public:
		PostProcessPanel(CommandExecutor& commandExecutor);

		bool Init(EngineContext& context);
		void Update(float dt) override;
		void Draw() override;
		void Destroy() override;

	private:
		PostProcessPass* m_postProcess;
		CommandExecutor& m_executor;
	};
}
#endif // !
