#ifndef EDITOR_UI_H
#define EDITOR_UI_H
#include "engine_context.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
namespace eng
{
	class EditorUI
	{
	public:
		EditorUI() = default;

		bool Init(EngineContext& ctx);
		void StartFrame();
		void UpdateFrame();
		void EndFrame();
		void Destroy();
	private:
		EngineContext* m_engine_context = nullptr;
	};
}
#endif // !EDITOR_UI_H
