#include "editor.h"
#include "panels/console/console.h"
#include <eng/command/commands/application_quit_command.h>
#include <eng/command/commands/graphics_set_clear_color_command.h>
#include <eng/command/commands/graphics_set_wireframe_command.h>

#include <iostream>
#include "editor_layer.h"

namespace eng
{
	bool Editor::Init(EngineContext& ctx)
	{		
		m_imguiLayer = new ImGuiLayer(ctx.GetNativeWindow(), "ImGuiLayer");		

		PushOverlay(m_imguiLayer);
		PushLayer(new EditorLayer(ctx));

		return true;
	}
	void Editor::Destroy()
	{
	}
}