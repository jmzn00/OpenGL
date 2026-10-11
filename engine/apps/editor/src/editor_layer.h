#ifndef EDITOR_LAYER_H
#define EDITOR_LAYER_H


#include "eng/core/layer.h"
#include <eng/core/engine_context.h>
#include "editor_component.h"
#include "editor_context.h"

#include <eng/command/command_executor.h>

#include "panels/console/console.h"
#include "panels/inspector/inspector.h"
#include "panels/properties/properties_panel.h"
#include "panels/toolbar/toolbar.h"
#include "panels/profiler/profiler_panel.h"

#include <memory>
#include <vector>

#include <imgui.h>
#include <imgui_internal.h>

namespace eng
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer(EngineContext& ctx, EditorContext& editorContext);
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Update(float dt) override;
		virtual void OnImGuiRender() override;		
	private:		
		void BuildDefaultDockLayout(ImGuiID dockspaceId, const ImVec2& dockspaceSize);
		bool m_dockLayoutBuilt = false;

		EditorContext& m_editorContext;
		EngineContext& m_engineContext;

		std::vector<std::unique_ptr<IEditorComponent>> m_components;
	};
}
#endif // !EDITOR_LAYER_H

