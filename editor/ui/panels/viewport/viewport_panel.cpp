#include "viewport_panel.h"
#include <imgui.h>
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>

namespace eng
{
	bool ViewportPanel::Init(EngineContext& ctx)
	{		
		return true;
	}

	void ViewportPanel::Update(float dt)
	{		
	}

	void ViewportPanel::UpdateCamera(float dt)
	{
		
	}

	void ViewportPanel::Draw()
	{
		if (ImGui::Begin("Viewport"))
		{
			const ImVec2 size = ImGui::GetContentRegionAvail();

			const auto width = static_cast<uint32_t>(
				std::max(1.0f, std::floor(size.x)));
			const auto height = static_cast<uint32_t>(
				std::max(1.0f, std::floor(size.y)));

			m_viewport.RequestResize(width, height);

			ImGui::Image(
				static_cast<ImTextureID>(m_viewport.GetOutputTexture()),
				size,
				ImVec2(0, 1),
				ImVec2(1, 0));

			bool hovered = ImGui::IsWindowHovered();	
			bool rmbHeld = ImGui::IsMouseDown(ImGuiMouseButton_Right);

			if (hovered && rmbHeld)
				m_focused = true;

			if (!rmbHeld && m_focused)
				m_focused = false;
			
			m_viewport.SetFocused(m_focused);
		}
		ImGui::End();
	}
}
