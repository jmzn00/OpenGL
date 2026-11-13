#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <eng/core/log.h>
#include <eng/scene/scene.h>
#include "editor_component.h"
#include "editor_context.h"

#include <eng/command/command_executor.h>


#include <vector>
#include <memory>

namespace eng
{
	class Entity;
	struct ParentChange
	{
		std::uint32_t child;
		std::optional<std::uint32_t> parent;
	};
	class Inspector : public IEditorComponent
	{
	public:
		Inspector(Scene& scene, EditorContext& editorContext, CommandExecutor& executor);
		bool Init(EngineContext& ctx) override;
		void Update(float dt) override;
		void Draw() override;
		void Destroy() override;
	private:
		void DrawEntityNode(Entity& entity);
		EditorContext& m_editorContext;
		Scene& m_scene;
		Logger* m_log = nullptr;

		CommandExecutor& m_executor;
		char m_renameBuffer[256]{};

		std::optional<ParentChange> m_pendingParentChange;
	};
}
#endif // !INSPECTOR_H
