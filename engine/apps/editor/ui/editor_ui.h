#ifndef EDITOR_UI_H
#define EDITOR_UI_H
#include <eng/core/engine_context.h>
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
	};
}
#endif // !EDITOR_UI_H
