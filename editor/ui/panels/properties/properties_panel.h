#ifndef PROPERTIES_PANEL_H
#define PROPERTIES_PANEL_H

#include <eng/core/log.h>
#include <eng/scene/scene.h>

#include "editor_component.h"
#include "editor_context.h"

#include "entity_component_registry.h"

namespace eng
{
	class PropertiesPanel : public IEditorComponent
	{
	public:
		PropertiesPanel(Scene& scene, EditorContext& editorContext,
			EntityComponentRegistry& components);
		bool Init(EngineContext& engineContext) override;
		void Update(float dt) override;
		void Draw() override;
		void Destroy() override;
	private:
		EditorContext& m_editorContext;
		Scene& m_scene;

		Logger* m_log = nullptr;

		EntityComponentRegistry& m_components;
	};
}
#endif // !PROPERTIES_PANEL_H
