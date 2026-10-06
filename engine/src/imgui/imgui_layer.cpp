#include <eng/imgui/imgui_layer.h>
#include <iostream>
namespace eng
{
	ImGuiLayer::ImGuiLayer(GLFWwindow* window, const std::string& name)
		: m_window{ window }, Layer(name)
	{
	}
	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();

		if (!ImGui_ImplGlfw_InitForOpenGL(m_window, true))
		{
			std::cerr << "ImGui GLFW initialization failed\n";
		}
		if (!ImGui_ImplOpenGL3_Init("#version 460"))
		{
			std::cerr << "ImGui OpenGL3 initialization failed\n";
		}
	}
	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}
	void ImGuiLayer::End()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}	
}