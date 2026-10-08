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
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
		ImGui::SetNextWindowSize(ImVec2(viewport->Size.x / 6.0f, viewport->Size.y / 1.33f));

		ImGui::Begin(
			"Inspector"
			,nullptr,
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoResize |
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
	void Inspector::Update(float dt)
	{	
	}
}