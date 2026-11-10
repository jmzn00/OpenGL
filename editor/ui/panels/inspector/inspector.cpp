#include "inspector.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>

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
				if (ImGui::MenuItem("Cube"))
				{
					m_executor.Submit("ent.create cube");
				}					
				if (ImGui::MenuItem("Pyramid"))
				{
					m_executor.Submit("ent.create pyramid");
				}
				if (ImGui::MenuItem("Window"))
				{
					m_executor.Submit("ent.create window");
				}
				if (ImGui::MenuItem("Backpack"))
				{
					m_executor.Submit("ent.create backpack");
				}
				if (ImGui::MenuItem("Grass"))
				{
					m_executor.Submit("ent.create grass");
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
			ImGui::PopID();
		}

		ImGui::End();
	}
	void Inspector::Update(float)
	{	
	}
}