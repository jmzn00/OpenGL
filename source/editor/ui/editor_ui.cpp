#include "editor/ui/editor_ui.h"
#include <iostream>
namespace eng
{
	bool EditorUI::Init(EngineContext& ctx)
	{		
		m_engine_context = &ctx;

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();

		if (!ImGui_ImplGlfw_InitForOpenGL(ctx.GetWindow(), true))
		{
			std::cerr << "ImGui GLFW initialization failed\n";
			return false;
		}

		if (!ImGui_ImplOpenGL3_Init("#version 460"))
		{
			std::cerr << "ImGui OpenGL3 initialization failed\n";
			return false;
		}

		return true;
	}
	void EditorUI::StartFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();				
	}
	void EditorUI::UpdateFrame()
	{
		//ImGui::Begin("My name is window, ImGUI window");
		//ImGui::Text("Hello there");
		//ImGui::Text("this is text 2");
		//ImGui::End();
	}
	void EditorUI::EndFrame()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	void EditorUI::Destroy()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		m_engine_context = nullptr;
	}
}