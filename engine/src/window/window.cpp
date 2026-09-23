#include <eng/window/window.h>
#include <iostream>
namespace eng
{
	Window::Window(GLFWwindow* window, uint32_t width, uint32_t height)
		: m_window {window}, m_width { width }, m_height { height }
		, m_aspect {static_cast<float>(width) / static_cast<float>(height)}
	{
		glViewport(0, 0, width, height);
	}
	void Window::Focus()
	{
		glfwFocusWindow(m_window);
	}
	void Window::SetSize(uint32_t width, uint32_t height)
	{
		m_width = width;
		m_height = height;
		m_aspect = (float)width / (float)height;

		glViewport(0, 0, width, height);
	}
	float Window::GetAspect() const
	{
		return m_aspect;
	}
	uint32_t Window::GetWidth() const
	{
		return m_width;
	}
	uint32_t Window::GetHeight() const
	{
		return m_height;
	}
	GLFWwindow* Window::GetNativeWindow() const
	{
		return m_window;
	}
}