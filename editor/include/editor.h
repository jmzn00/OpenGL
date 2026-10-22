#ifndef EDITOR_H
#define EDITOR_H

#include <eng/core/application.h>

#include <eng/command/command_executor.h>
#include <eng/command/command_context.h>
#include <eng/command/command_registry.h>

#include <eng/scene/scene.h>

#include "editor_component.h"
#include "editor_context.h"

#include <memory>
#include <vector>

namespace eng
{
	class Editor : public Application
	{
	public:		
		Editor() = default;

		bool Init(EngineContext& ctx) override;
		void Destroy() override;		

		static Editor& Get() { return *static_cast<Editor*>(m_instance); }
	private:
		EngineContext* m_engineContext;
		std::unique_ptr<EditorContext> m_editorContext;

		CommandRegistry m_commands;
		std::unique_ptr<CommandContext> m_commandContext;
		std::unique_ptr<CommandExecutor> m_commandExecutor;

		std::unique_ptr<Scene> m_currentScene;					
	};
}
#endif // !EDITOR_H
