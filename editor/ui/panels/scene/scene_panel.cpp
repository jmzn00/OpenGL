#include "scene_panel.h"
#include <imgui.h>
#include <algorithm>
#include <cmath>
#include <cstdint>

namespace eng
{
	bool ScenePanel::Init(EngineContext& ctx)
	{		
		return true;
	}

	void ScenePanel::Update(float dt)
	{		
	}

	void ScenePanel::UpdateCamera(float dt)
	{
		
	}

	void ScenePanel::Draw()
	{
		if (ImGui::Begin("Scene"))
		{
			const ImVec2 size = ImGui::GetContentRegionAvail();

			const auto width = static_cast<uint32_t>(
				std::max(1.0f, std::floor(size.x)));
			const auto height = static_cast<uint32_t>(
				std::max(1.0f, std::floor(size.y)));

			m_viewport.RequestResize(width, height);

			ImGui::Image(
				static_cast<ImTextureID>(m_viewport.GetColorTexture()),
				size,
				ImVec2(0, 1),
				ImVec2(1, 0));
		}
		ImGui::End();
	}
}
