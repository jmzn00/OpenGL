#include "inspector.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>

namespace eng
{
	Inspector::Inspector(Scene& scene, EditorContext& editorContext)
		: m_scene {&scene}, m_editorContext {editorContext}
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

		auto& entities = m_scene->GetEntities();
		for (auto& entity : entities)
		{
			if (ImGui::Selectable(entity->GetName().c_str()))
			{
				m_selectedEntity = entity.get();
				m_log->Info("[Inspector] selected: " + entity->GetName());

				m_editorContext.SetSelectedEntityId(entity->GetID());
			}
		}

		ImGui::End();
	}
	void Inspector::Update(float dt)
	{	
	}
}