#include "post_process_panel.h"
#include <imgui.h>

namespace eng
{
	PostProcessPanel::PostProcessPanel(CommandExecutor& commandExecutor)
		: m_executor {commandExecutor}
	{
	}
	void PostProcessPanel::Update(float dt)
	{
	}
	bool PostProcessPanel::Init(EngineContext& context)
	{
		Renderer& renderer = Renderer::Get();
		PostProcessPass* pass = renderer.GetPass<PostProcessPass>();

		if (pass == nullptr)
			return false;
		
		m_postProcess = pass;

		return true;
	}
	void PostProcessPanel::Draw()
	{
		ImGui::Begin(
			"PostProcess"
			, nullptr,
			ImGuiWindowFlags_NoCollapse
		);

		ImGui::SeparatorText("Inversion");
		bool inversion = m_postProcess->IsActive("inversion");
		if (ImGui::Checkbox("Enabled##inversion", &inversion))
		{
			m_postProcess->ToggleEffect("inversion", inversion);
		}

		ImGui::SeparatorText("Grayscale");
		bool grayscale = m_postProcess->IsActive("grayscale");
		if(ImGui::Checkbox("Enabled##grayscale", &grayscale))
		{
			m_postProcess->ToggleEffect("grayscale", grayscale);
		}

		ImGui::SeparatorText("Kernel");
		bool kernel = m_postProcess->IsActive("kernel");
		if (ImGui::Checkbox("Enabled##kernel", &kernel))
		{
			m_postProcess->ToggleEffect("kernel", kernel);
		}

		ImGui::End();
	}
	void PostProcessPanel::Destroy()
	{
		m_postProcess = nullptr;
	}
}