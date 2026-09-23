#ifndef WINDOW_H
#define WINDOW_H
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <cstdint>

namespace eng
{
	class Window
	{
	public:		
		explicit Window(GLFWwindow* window, uint32_t width, uint32_t height);
		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) = delete;

		void Focus();
		void SetSize(uint32_t width, uint32_t height);
		uint32_t GetWidth() const;
		uint32_t GetHeight() const;
		float GetAspect() const;

		GLFWwindow* GetNativeWindow() const;
	private:
		GLFWwindow* m_window;
		uint32_t m_width;
		uint32_t m_height;
		float m_aspect;
	};
}
#endif // !WINDOW_H
