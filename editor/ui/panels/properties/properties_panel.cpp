#include "properties_panel.h"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <eng/graphics/material/material_library.h>

#include <string>

namespace eng
{
	PropertiesPanel::PropertiesPanel(Scene& scene, EditorContext& editorContext)
		: m_scene{scene}, m_editorContext{editorContext}
	{
	}
	bool PropertiesPanel::Init(EngineContext& engineContext)
	{
		m_log = &engineContext.GetLogger();

		return true;
	}
	void PropertiesPanel::Destroy()
	{
	}
	void PropertiesPanel::Update(float dt)
	{
	}
	void PropertiesPanel::Draw()
	{
		const float panelWidth = 200.0f;
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		//ImGui::SetNextWindowPos(ImVec2(viewport->Size.x - panelWidth
		//	, viewport->Size.y / 10.0f));
		ImGui::SetNextWindowSize(ImVec2(panelWidth
			, viewport->Size.y / 1.53f));

		ImGui::Begin(
			"Properties"
			, nullptr,
			ImGuiWindowFlags_NoCollapse
		);
		float width = ImGui::GetContentRegionAvail().x;

		Entity* ent = m_scene.FindEntityById(m_editorContext.GetSelectedEntityId());
		if (ent)
		{
			TransformComponent& tc = ent->Transform();
			ImGui::SeparatorText("Transform");

			ImGui::DragFloat3("Position", &tc.Translation.x, 0.1f);
			ImGui::DragFloat3("Rotation", &tc.Rotation.x, 0.1f);
			ImGui::DragFloat3("Scale", &tc.Scale.x, 0.1f);			
						
			if (ent->HasComponent<LightComponent>())
			{
				ImGui::SeparatorText("Light");			
				auto& lc = ent->GetComponent<LightComponent>();
				
				if (ImGui::Button("Type"))
				{
					ImGui::OpenPopup("LightTypePopup");
				}
				if (ImGui::BeginPopup("LightTypePopup"))
				{					
					for (int i = 0; i < static_cast<int>(LightType::Count); i++)
					{
						LightType type = static_cast<LightType>(i);
						if (ImGui::MenuItem(Light::ToString(type)))
						{
							lc.type = type;
						}									
					}					
					ImGui::EndPopup();
				}
				if (lc.type == LightType::Spot)
				{
					ImGui::DragFloat("Inner Cutoff", &lc.innerCutoff, 0.01);
					ImGui::DragFloat("Outer Cutoff", &lc.outerCutoff, 0.01);
				}				
			}
		}
		ImGui::End();
	}
}