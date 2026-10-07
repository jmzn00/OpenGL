#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <eng/core/log.h>
#include <eng/scene/scene.h>
#include "editor_component.h"
#include "editor_context.h"


#include <vector>
#include <memory>

namespace eng
{
	class Inspector : public IEditorComponent
	{
	public:
		Inspector(Scene& scene, EditorContext& editorContext);
		bool Init(EngineContext& ctx) override;
		void Update(float dt) override;
		void Draw() override;
		void Destroy() override;
	private:
		EditorContext& m_editorContext;
		Scene* m_scene;
		Entity* m_selectedEntity = nullptr;
		Logger* m_log = nullptr;
	};
}
#endif // !INSPECTOR_H
