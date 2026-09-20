#include "console.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <string>
#include <cstring>
namespace eng
{
	bool Console::Init(EngineContext& ctx)
	{		
		return true;
	}
	void Console::Destroy()
	{
	
	}
	void Console::Write(const Message& message)
	{        
		m_messages.push_back(message);

        m_scroll_to_bottom = true;
	}
    void Console::Draw()
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();

        float height = viewport->Size.y * 0.25f;

        ImGui::SetNextWindowPos(
            ImVec2(
                viewport->Pos.x,
                viewport->Pos.y + viewport->Size.y - height
            )
        );

        ImGui::SetNextWindowSize(
            ImVec2(viewport->Size.x, height)
        );

        ImGui::Begin(
            "Console",
            nullptr,
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoCollapse
        );

        // Message area
        ImGui::BeginChild(
            "ConsoleMessages",
            ImVec2(0, -ImGui::GetFrameHeightWithSpacing()),
            ImGuiChildFlags_Borders,
            ImGuiWindowFlags_HorizontalScrollbar
        );

        for (const Message& message : m_messages)
        {
            switch (message.level)
            {
            case Level::Info:
                ImGui::PushStyleColor(
                    ImGuiCol_Text,
                    ImVec4(1.0f, 1.0f, 1.0f, 1.0f)
                );
                break;

            case Level::Warning:
                ImGui::PushStyleColor(
                    ImGuiCol_Text,
                    ImVec4(1.0f, 1.0f, 0.0f, 1.0f)
                );
                break;

            case Level::Error:
                ImGui::PushStyleColor(
                    ImGuiCol_Text,
                    ImVec4(1.0f, 0.3f, 0.3f, 1.0f)
                );
                break;
            }

            ImGui::TextUnformatted(message.text.c_str());

            ImGui::PopStyleColor();
        }
        if (m_scroll_to_bottom)
        {
            ImGui::SetScrollHereY(1.0f);
            m_scroll_to_bottom = false;
        }
        ImGui::EndChild();

        static bool focus_input = true;

        if (focus_input)
        {
            ImGui::SetKeyboardFocusHere();
            focus_input = false;
        }

        if (ImGui::InputText(
            "##ConsoleInput",
            m_input,
            IM_ARRAYSIZE(m_input),
            ImGuiInputTextFlags_EnterReturnsTrue))
        {
            std::cout << m_input << '\n';

            if (std::strcmp(m_input, "warning") == 0)
            {
                Write(Message{ Level::Warning, m_input });
            }
            else if (std::strcmp(m_input, "error") == 0)
            {
                Write(Message{ Level::Error, m_input });
            }
            else
            {
                Write(Message{ Level::Info, m_input });
            }            
            m_input[0] = '\0';
            focus_input = true;
        }

        ImGui::End();
    }
	void Console::Update(float dt)
	{
	
	}
}