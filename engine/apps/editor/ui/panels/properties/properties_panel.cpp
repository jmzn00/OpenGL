#include "properties_panel.h"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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
		ImGui::SetNextWindowPos(ImVec2(viewport->Size.x - panelWidth, 0.0f));
		ImGui::SetNextWindowSize(ImVec2(panelWidth, viewport->Size.y / 1.33f));

		ImGui::Begin(
			"Properties"
			, nullptr,
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoCollapse
		);

		Entity* ent = m_scene.FindEntityById(m_editorContext.GetSelectedEntityId());
		if (ent)
		{
			TransformComponent& tc = ent->Transform();
			ImGui::SeparatorText("Transform");

			ImGui::DragFloat3("Position", &tc.Translation.x, 0.1f);
			ImGui::DragFloat3("Rotation", &tc.Rotation.x, 0.1f);
			ImGui::DragFloat3("Scale", &tc.Scale.x, 0.1f);
			
		}
		ImGui::End();
	}
}