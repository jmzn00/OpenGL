#ifndef EDITOR_LAYER_H
#define EDITOR_LAYER_H

#include "eng/core/layer.h"
#include <eng/core/engine_context.h>
#include "editor_component.h"

#include <eng/command/command.h>
#include <eng/command/command_registry.h>

#include "panels/console/console.h"
#include "panels/inspector/inspector.h"
#include "panels/properties/properties_panel.h"

#include <eng/scene/scene.h>

#include <eng/graphics/shader_library.h>

#include <memory>
#include <vector>

#include "editor_context.h"

namespace eng
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer(EngineContext& ctx);
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Update(float dt) override;
		virtual void OnImGuiRender() override;
	private:
		EngineContext& m_ctx;
		EditorContext m_editorContext{};

		std::vector<std::unique_ptr<IEditorComponent>> m_components;

		CommandRegistry m_commands;		
		std::unique_ptr<CommandContext> m_commandContext;
		std::unique_ptr<Scene> m_currentScene;

		ShaderLibrary m_shaderLibrary{};
	};
}
#endif // !EDITOR_LAYER_H

