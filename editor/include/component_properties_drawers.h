#ifndef COMPONENT_PROPERTIES_DRAWERS_H
#define COMPONENT_PROPERTIES_DRAWERS_H

#include "editor_context.h"
#include <eng/entity/components.h>
#include <imgui.h>
#include <eng/asset/asset_manager.h>

namespace eng
{
	class ComponentPropertiesDrawers
	{
	public:
		explicit ComponentPropertiesDrawers(EditorContext& context)
			: m_editorContext{ context }
		{
		}
		void DrawTransform(TransformComponent& transform)
		{
			ImGui::DragFloat3("Position", &transform.Translation.x, 0.1f);
			ImGui::DragFloat3("Rotation", &transform.Rotation.x, 0.1f);
			ImGui::DragFloat3("Scale", &transform.Scale.x, 0.1f);
		}
		void DrawModel(ModelComponent& component)
		{
			auto& assets = AssetManager::Get();
			auto& models = assets.Models();

			const char* preview = component.model
				? component.model->GetKey().c_str()
				: "None";

			if (ImGui::BeginCombo("Model", preview))
			{
				for (const auto& asset : models)
				{
					ImGui::PushID(asset.relativePath.c_str());

					if (ImGui::Selectable(asset.name.c_str()))
					{
						component.model = assets.LoadModel(asset.relativePath);
					}
					ImGui::PopID();
				}
				ImGui::EndCombo();
			}
		}
		void DrawLight(LightComponent& light)
		{
			if (ImGui::BeginCombo("Type", Light::ToString(light.type)))
			{
				for (int i = 0; i < static_cast<int>(LightType::Count); ++i)
				{
					const auto type = static_cast<LightType>(i);
					const bool selected = light.type == type;
					if (ImGui::Selectable(Light::ToString(type), selected))
						light.type = type;
					if (selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}

			ImGui::ColorEdit3("Ambient", &light.ambient.x);
			ImGui::ColorEdit3("Diffuse", &light.diffuse.x);
			ImGui::ColorEdit3("Specular", &light.specular.x);

			if (light.type != LightType::Direction)
			{
				ImGui::SeparatorText("Attenuation");
				ImGui::DragFloat("Constant", &light.constant, 0.01f,
					0.001f, 100.0f, "%.3f", ImGuiSliderFlags_AlwaysClamp);
				ImGui::DragFloat("Linear", &light.linear, 0.001f,
					0.0f, 100.0f, "%.3f", ImGuiSliderFlags_AlwaysClamp);
				ImGui::DragFloat("Quadratic", &light.quadratic, 0.001f,
					0.0f, 100.0f, "%.3f", ImGuiSliderFlags_AlwaysClamp);
			}

			if (light.type == LightType::Spot)
			{
				float inner = glm::degrees(glm::acos(glm::clamp(light.innerCutoff, -1.0f, 1.0f)));
				float outer = glm::degrees(glm::acos(glm::clamp(light.outerCutoff, -1.0f, 1.0f)));
				ImGui::SeparatorText("Spot Cone");
				if (ImGui::SliderFloat("Inner Angle", &inner, 0.0f,
					glm::max(0.0f, outer - 0.1f), "%.1f deg", ImGuiSliderFlags_AlwaysClamp))
					light.innerCutoff = glm::cos(glm::radians(inner));
				if (ImGui::SliderFloat("Outer Angle", &outer, inner + 0.1f,
					89.9f, "%.1f deg", ImGuiSliderFlags_AlwaysClamp))
					light.outerCutoff = glm::cos(glm::radians(outer));
			}
		}
	private:
		EditorContext& m_editorContext;
	};
}
#endif // COMPONENT_PROPERTIES_DRAWERS_H
