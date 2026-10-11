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
		ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
		ImGui::SetNextWindowSize(ImVec2(viewport->Size.x
			, viewport->Size.y / 10.0f));

		ImGui::Begin("Toolbar"
			, nullptr
			, ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoCollapse
		);

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