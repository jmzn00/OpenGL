#ifndef IMGUI_LAYER_H
#define IMGUI_LAYER_H
#include <eng/core/layer.h>
#include <eng/core/engine_context.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"
namespace eng
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer(GLFWwindow* window, const std::string& name);
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();
	private:
		GLFWwindow* m_window;
	};
}
#endif // !IMGUI_LAYER_H