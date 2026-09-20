#ifndef EDITOR_H
#define EDITOR_H

#include "application/application.h"
#include "editor/ui/editor_ui.h"
#include "editor/tools/editor_component.h"
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
	};
}
#endif // !EDITOR_H
