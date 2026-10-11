#include <eng/imgui/imgui_layer.h>
#include <iostream>
namespace eng
{
	ImGuiLayer::ImGuiLayer(GLFWwindow* window, const std::string& name)
		: m_window{ window }, Layer(name)
	{
	}
    void ImGuiLayer::SetEditorStyle(ImGuiStyle& style)
    {
        const ImColor cream(254, 243, 226);
        const ImColor lightOrange(244, 174, 82);
        const ImColor darkOrange(212, 98, 26);
        const ImColor brown(42, 26, 14);
        const ImColor black(0, 0, 0);
        const ImColor mutedBrown(92, 62, 38);
        const ImColor white(255, 255, 255);

        style.WindowRounding = 0.0f;
        style.ChildRounding = 0.0f;
        style.FrameRounding = 5.0f;
        style.PopupRounding = 5.0f;
        style.ScrollbarRounding = 5.0f;
        style.GrabRounding = 0.0f;
        style.TabRounding = 5.0f;

        style.WindowBorderSize = 1.0f;
        style.ChildBorderSize = 1.0f;
        style.FrameBorderSize = 1.0f;
        style.PopupBorderSize = 1.0f;

        style.WindowPadding = ImVec2(10.0f, 8.0f);
        style.FramePadding = ImVec2(8.0f, 5.0f);
        style.ItemSpacing = ImVec2(8.0f, 6.0f);
        style.ItemInnerSpacing = ImVec2(6.0f, 4.0f);
        style.ScrollbarSize = 14.0f;
        style.GrabMinSize = 10.0f;

        style.Colors[ImGuiCol_Text] = brown;
        style.Colors[ImGuiCol_TextDisabled] = mutedBrown;

        style.Colors[ImGuiCol_WindowBg] = cream;
        style.Colors[ImGuiCol_ChildBg] = cream;
        style.Colors[ImGuiCol_PopupBg] = cream;

        style.Colors[ImGuiCol_Border] = mutedBrown;
        style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.10f);

        style.Colors[ImGuiCol_FrameBg] = ImColor(255, 232, 196);
        style.Colors[ImGuiCol_FrameBgHovered] = ImColor(255, 215, 158);
        style.Colors[ImGuiCol_FrameBgActive] = lightOrange;

        style.Colors[ImGuiCol_TitleBg] = lightOrange;
        style.Colors[ImGuiCol_TitleBgActive] = darkOrange;
        style.Colors[ImGuiCol_TitleBgCollapsed] = mutedBrown;

        style.Colors[ImGuiCol_MenuBarBg] = ImColor(255, 226, 181);

        style.Colors[ImGuiCol_Button] = lightOrange;
        style.Colors[ImGuiCol_ButtonHovered] = darkOrange;
        style.Colors[ImGuiCol_ButtonActive] = brown;

        style.Colors[ImGuiCol_Header] = lightOrange;
        style.Colors[ImGuiCol_HeaderHovered] = darkOrange;
        style.Colors[ImGuiCol_HeaderActive] = brown;

        style.Colors[ImGuiCol_Separator] = mutedBrown;
        style.Colors[ImGuiCol_SeparatorHovered] = darkOrange;
        style.Colors[ImGuiCol_SeparatorActive] = brown;

        style.Colors[ImGuiCol_CheckMark] = darkOrange;
        style.Colors[ImGuiCol_SliderGrab] = darkOrange;
        style.Colors[ImGuiCol_SliderGrabActive] = brown;

        style.Colors[ImGuiCol_Tab] = lightOrange;
        style.Colors[ImGuiCol_TabHovered] = darkOrange;
        style.Colors[ImGuiCol_TabSelected] = cream;
        style.Colors[ImGuiCol_TabSelectedOverline] = darkOrange;
        style.Colors[ImGuiCol_TabDimmed] = mutedBrown;
        style.Colors[ImGuiCol_TabDimmedSelected] = lightOrange;

        style.Colors[ImGuiCol_DockingPreview] =
            ImVec4(0.83f, 0.38f, 0.10f, 0.70f);

        style.Colors[ImGuiCol_DockingEmptyBg] =
            ImVec4(0.65f, 0.42f, 0.22f, 0.35f);

        style.Colors[ImGuiCol_ScrollbarBg] = ImColor(255, 226, 181);
        style.Colors[ImGuiCol_ScrollbarGrab] = lightOrange;
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = darkOrange;
        style.Colors[ImGuiCol_ScrollbarGrabActive] = brown;

        style.Colors[ImGuiCol_TextSelectedBg] =
            ImVec4(0.83f, 0.38f, 0.10f, 0.35f);

        style.Colors[ImGuiCol_NavHighlight] = darkOrange;
        style.Colors[ImGuiCol_ModalWindowDimBg] =
            ImVec4(0.16f, 0.10f, 0.05f, 0.35f);
    }

	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();

        ImGuiStyle& style = ImGui::GetStyle();
        SetEditorStyle(style);
        			
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.IniFilename = "editor_layout.ini";

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