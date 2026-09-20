#include "editor.h"
#include "editor/tools/console/console.h"
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

		m_components.push_back(std::make_unique<Console>());
		for (auto& component : m_components)
		{
			if (!component->Init(ctx))
			{
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

	}
}