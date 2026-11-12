#include "properties_panel.h"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <eng/graphics/material/material_library.h>

#include <string>

namespace eng
{
	PropertiesPanel::PropertiesPanel(Scene& scene, EditorContext& editorContext
		, EntityComponentRegistry& components)
		: m_scene{scene}, m_editorContext{editorContext}, m_components {components}
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
	void PropertiesPanel::Update(float)
	{
	}
	void PropertiesPanel::Draw()
	{
		const float panelWidth = 200.0f;
		ImGuiViewport* viewport = ImGui::GetMainViewport();		
		ImGui::SetNextWindowSize(ImVec2(panelWidth
			, viewport->Size.y / 1.53f));
		ImGui::Begin(
			"Properties"
			, nullptr,
			ImGuiWindowFlags_NoCollapse
		);
		Entity* ent = m_scene.FindEntityById(m_editorContext.GetSelectedEntityId());
		if (ent)
		{
			for (const auto& entry : m_components.Entries())
			{
				if (!entry.has(*ent))
					continue;
				
				ImGui::PushID(entry.id.c_str());
				const bool expanded = ImGui::CollapsingHeader(entry.label.c_str(),
					ImGuiTreeNodeFlags_DefaultOpen);
				bool remove = false;
				if (entry.remove && ImGui::BeginPopupContextItem("ComponentContext"))
				{
					remove = ImGui::MenuItem("Remove Component");
					ImGui::EndPopup();
				}
				if (expanded && !remove)
				{
					ImGui::PushID("properties");
					entry.draw(*ent, m_editorContext);
					ImGui::PopID();
				}
				if (remove)
					entry.remove(*ent);
				ImGui::PopID();				
			}

			if (ImGui::Button("Add Component"))
			{
				ImGui::OpenPopup("AddComponentPopup");
			}
			if (ImGui::BeginPopup("AddComponentPopup"))
			{
				bool available = false;

				for (const auto& entry : m_components.Entries())
				{
					if (!entry.add || entry.has(*ent))
						continue;

					available = true;
					ImGui::PushID(entry.id.c_str());
					if (ImGui::MenuItem(entry.label.c_str()))
					{
						entry.add(*ent);
					}
					ImGui::PopID();
				}
				if (!available)
				{
					ImGui::TextDisabled("All components already added");
				}
				ImGui::EndPopup();
			}			
		}
		ImGui::End();
	}
}
