#ifndef EDITOR_H
#define EDITOR_H

#include <eng/command/command_context.h>
#include <eng/command/command_registry.h>
#include <eng/core/application.h>
#include "editor_ui.h"
#include "editor_component.h"
#include <memory>
#include <vector>
namespace eng
{
	class Editor : public Application
	{
	public:		
		Editor() = default;

		bool Editor::Init(EngineContext& ctx);
		void Editor::Update(float dt);
		void Editor::Destroy();
	private:
		EditorUI m_ui;
		std::vector<std::unique_ptr<IEditorComponent>> m_components;		

		CommandRegistry m_commands;
		std::unique_ptr<CommandContext> m_commandContext;
	};
}
#endif // !EDITOR_H
