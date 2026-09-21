#include "editor.h"
#include "panels/console/console.h"
#include <eng/command/commands/application_quit_command.h>
#include <eng/command/commands/graphics_set_clear_color_command.h>
#include <eng/command/commands/graphics_set_wireframe_command.h>

#include <iostream>

namespace eng
{
	bool Editor::Init(EngineContext& ctx)
	{
		if (!m_ui.Init(ctx))
		{
			std::cerr << "EDITOR::UI: FAILED TO INIT";
			return false;
		}			
	
		ctx.GetLogger().Info("[Editor] Initialized");	


		m_commandContext = std::make_unique<CommandContext>(
			CommandContext{ ctx.GetLogger() }
		);

		m_commands.Register(
			std::make_unique<ApplicationQuitCommand>(*this)
		);
		m_commands.Register(
			std::make_unique<GraphicsSetClearColorCommand>(ctx.GetGraphicsAPI())
		);
		m_commands.Register(
			std::make_unique<GraphicsSetWireframeCommand>(ctx.GetGraphicsAPI())
		);

		m_components.push_back(std::make_unique<Console>(m_commands, *m_commandContext));
		for (auto& component : m_components)
		{
			if (!component->Init(ctx))
			{
				ctx.GetLogger().Error("[Editor] Component failed to init");
				std::cerr << "EDITOR::COMPONENT: FAILED TO INIT";
				return false;
			}
		}

		return true;
	}
	void Editor::Update(float dt)
	{		
		m_ui.StartFrame();
		for (auto& component : m_components)
		{
			component->Draw();
		}
		m_ui.EndFrame();
	}
	void Editor::Destroy()
	{
		for (auto& component : m_components)
		{
			component->Destroy();
		}
		m_components.clear();
		m_ui.Destroy();
	}
}