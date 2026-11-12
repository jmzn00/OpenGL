#include "inspector.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <algorithm>
#include <cstring>

namespace eng
{
	Inspector::Inspector(Scene& scene, EditorContext& editorContext, CommandExecutor& executor)
		: m_scene {scene}, m_editorContext {editorContext}
		, m_executor {executor}
	{		
	}
	bool Inspector::Init(EngineContext& ctx)
	{	
		m_log = &ctx.GetLogger();
		return true;
	}
	void Inspector::Destroy()
	{
	}
	void Inspector::Draw()
	{
		ImGui::Begin(
			"Inspector"
			,nullptr,
			ImGuiWindowFlags_NoCollapse
			);

		if(ImGui::Button("Create"))
		{
			ImGui::OpenPopup("CreateEntityPopup");
		}
		if (ImGui::BeginPopup("CreateEntityPopup"))
		{
			if (ImGui::BeginMenu("Entity"))
			{
				if (ImGui::MenuItem("New"))
				{
					m_executor.Submit("ent.create empty");
				}				

				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Lights"))
			{
				if (ImGui::MenuItem("Light"))
				{
					m_executor.Submit("ent.create light");
				}					
				ImGui::EndMenu();
			}
			ImGui::EndPopup();
		}		

		auto& entities = m_scene.GetEntities();

		for (auto& entity : entities)
		{
			ImGui::PushID(static_cast<int>(entity->GetID()));

			if (ImGui::Selectable(entity->GetName().c_str()))
			{
				m_editorContext.SetSelectedEntityId(entity->GetID());
			}

			// Must follow Selectable so the popup belongs to that row.
			if (ImGui::BeginPopupContextItem("EntityContext"))
			{
				if (ImGui::IsWindowAppearing())
				{
					m_editorContext.SetSelectedEntityId(entity->GetID());

					const auto& name = entity->GetName();
					const auto length =
						std::min(name.size(), sizeof(m_renameBuffer) - 1);

					std::memcpy(m_renameBuffer, name.data(), length);
					m_renameBuffer[length] = '\0';

					ImGui::SetKeyboardFocusHere();
				}

				const bool enter = ImGui::InputText(
					"Name",
					m_renameBuffer,
					sizeof(m_renameBuffer),
					ImGuiInputTextFlags_EnterReturnsTrue |
					ImGuiInputTextFlags_AutoSelectAll);

				const bool valid =
					std::string_view(m_renameBuffer).find_first_not_of(" \t\r\n")
					!= std::string_view::npos;

				ImGui::BeginDisabled(!valid);
				const bool save = ImGui::Button("Rename");
				ImGui::EndDisabled();

				if (valid && (enter || save))
				{
					entity->SetName(m_renameBuffer);
					ImGui::CloseCurrentPopup();
				}

				ImGui::SameLine();
				if (ImGui::Button("Cancel"))
				{
					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}

			ImGui::PopID();
		}

		ImGui::End();
	}
	void Inspector::Update(float)
	{	
	}
}