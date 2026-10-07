#include "editor_layer.h"
#include <eng/core/application.h>

namespace eng
{
	EditorLayer::EditorLayer(EngineContext& ctx)
		: Layer("EditorLayer"), m_ctx(ctx)
	{
		ctx.GetLogger().Info("[EditorLayer] Initialized");
	}
	void EditorLayer::OnAttach()
	{	
		m_currentScene = std::make_unique<Scene>(m_ctx, "Test Scene");

		m_shaderLibrary.Init();

		m_commands.RegisterAll(m_ctx, *m_currentScene);
		m_commandContext = std::make_unique<CommandContext>(m_ctx.GetLogger(), *m_currentScene);		

		m_components.push_back(std::make_unique<Console>(m_commands, *m_commandContext));
		m_components.push_back(std::make_unique<Inspector>(*m_currentScene, m_editorContext));
		m_components.push_back(std::make_unique<PropertiesPanel>(*m_currentScene, m_editorContext));

		for (auto& component : m_components)
		{
			if (!component->Init(m_ctx))
			{
				m_ctx.GetLogger().Error("[Editor] Component failed to init");
			}
		}		
	}
	void EditorLayer::OnDetach()
	{
		for (auto& component : m_components)
		{
			component->Destroy();
		}
		m_components.clear();
	}
	void EditorLayer::Update(float dt)
	{
		for (auto& component : m_components)
		{
			component->Update(dt);
		}	
		m_currentScene->Update(dt);
	}
	void EditorLayer::OnImGuiRender()
	{
		for (auto& component : m_components)
		{
			component->Draw();
		}
	}	
}