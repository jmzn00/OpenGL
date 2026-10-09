#ifndef EDITOR_LAYER_H
#define EDITOR_LAYER_H

#include "eng/core/layer.h"
#include <eng/core/engine_context.h>
#include "editor_component.h"
#include "editor_context.h"

#include <eng/command/command_registry.h>
#include <eng/command/command_executor.h>

#include "panels/console/console.h"
#include "panels/inspector/inspector.h"
#include "panels/properties/properties_panel.h"

#include <eng/camera/camera.h>
#include <eng/scene/scene.h>
#include <eng/graphics/shader_library.h>

#include <memory>
#include <vector>




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
		Camera m_editorCamera{};
		EditorContext m_editorContext{};
		CommandRegistry m_commands;
		ShaderLibrary m_shaderLibrary{};

		std::vector<std::unique_ptr<IEditorComponent>> m_components;
		std::unique_ptr<CommandContext> m_commandContext;
		std::unique_ptr<CommandExecutor> m_commandExecutor;
		std::unique_ptr<Scene> m_currentScene;

		EngineContext& m_engineContext;		
		Input* m_input;
	};
}
#endif // !EDITOR_LAYER_H

