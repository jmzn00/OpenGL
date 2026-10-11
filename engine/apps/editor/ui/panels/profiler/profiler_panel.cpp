#include "profiler_panel.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace eng
{
	ProfilerPanel::ProfilerPanel()
	{	
	}
	bool ProfilerPanel::Init(EngineContext& engineContext)
	{
		return true;		
	}
	void ProfilerPanel::Destroy()
	{
	}
	void ProfilerPanel::Draw()
	{
		if (ImGui::Begin("Profiler"))
		{
			auto sampleOpt = Profiler::Get().GetLatestSample();
			if (sampleOpt)
			{
				const auto& s = *sampleOpt;
				float fps = s.FrameMs > 0.0 ? (1000.0f / static_cast<float>(s.FrameMs)) : 0.0f;
				ImGui::Text("FPS: %.1f", fps);
				ImGui::Text("Frame: %.2f ms", s.FrameMs);
				ImGui::Text("CPU Render: %.2f ms", s.CpuRenderMs);
				ImGui::Text("CPU Update: %.2f ms", s.CpuUpdateMs);
				ImGui::Text("GPU: %.2f ms", s.GpuMs);
				ImGui::Text("Draw Calls: %u", s.drawCalls);
				ImGui::Text("Triangles: %u", s.triangles);

				const auto& hist = Profiler::Get().GetHistoryRef();
				if (!hist.empty())
				{
					static std::vector<float> values;
					values.resize(hist.size());
					for (size_t i = 0; i < hist.size(); ++i)
						values[i] = static_cast<float>(hist[i].FrameMs);
					ImGui::PlotLines("Frame ms", values.data(), (int)values.size());
				}
			}
			else
			{
				ImGui::TextDisabled("No profiler data yet");
			}			
		}
		ImGui::End();
	}
	void ProfilerPanel::Update(float dt)
	{
	}
}