#include "toolbar.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>

namespace eng
{
	Toolbar::Toolbar(CommandExecutor& commandExecutor)
		: m_commandExecutor{commandExecutor}
	{
	}
	bool Toolbar::Init(EngineContext& engineContext)
	{
		return true;
	}
	void Toolbar::Destroy()
	{
	}
	void Toolbar::Draw()
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();

		const float toolbarHeight = 48.0f;

		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, toolbarHeight));

		ImGuiWindowFlags flags =
			ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoCollapse
			| ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_NoDocking;

		ImGui::Begin("Toolbar", nullptr, flags);

		if (ImGui::Button("File"))
		{	
			ImGui::OpenPopup("FileOpenPopup");
		}
		if (ImGui::BeginPopup("FileOpenPopup"))
		{
			if (ImGui::BeginMenu("Scene"))
			{
				if (ImGui::MenuItem("Save"))
				{
				}
				if (ImGui::MenuItem("Load"))
				{
				}
				ImGui::EndMenu();
			}
			ImGui::EndPopup();
		}

		ImGui::SameLine();
		if (ImGui::Button("Edit"))
		{
			ImGui::OpenPopup("EditOpenPopup");
		}
		if (ImGui::BeginPopup("EditOpenPopup"))
		{

			ImGui::EndPopup();
		}

		ImGui::End();

	}
	void Toolbar::Update(float dt)
	{
	}
}