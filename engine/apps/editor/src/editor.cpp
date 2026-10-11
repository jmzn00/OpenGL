#include "editor.h"

#include "editor_layer.h"
#include <eng/scene/scene_layer.h>

#include <iostream>

namespace eng
{
	bool Editor::Init(EngineContext& ctx)
	{			
		m_engineContext = &ctx;
		m_imguiLayer = new ImGuiLayer(ctx.GetNativeWindow(), "ImGuiLayer");		
		m_currentScene = std::make_unique<Scene>(ctx, "DefaultScene");		
		
		m_commands.RegisterAll(*m_engineContext, *m_currentScene);
		m_commandContext = std::make_unique<CommandContext>(m_engineContext->GetLogger(), *m_currentScene);
		m_commandExecutor = std::make_unique<CommandExecutor>(m_commands, *m_commandContext);

		m_editorContext = std::make_unique<EditorContext>(*m_commandExecutor, *m_currentScene);		

		PushOverlay(m_imguiLayer);
		PushLayer(new SceneLayer(ctx, *m_currentScene, *m_editorContext));
		PushLayer(new EditorLayer(ctx, *m_editorContext));		
				
		return true;
	}
	void Editor::Destroy()
	{
		m_editorContext.reset();
		m_commandExecutor.reset();
		m_commandContext.reset();
		m_currentScene.reset();

		m_imguiLayer = nullptr;
		m_engineContext = nullptr;
	}
}