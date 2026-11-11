#include <eng/input/input.h>
#include <iostream>
#include <eng/math/math.h>
namespace eng
{
	bool Input::Init(GLFWwindow*)
	{
		return true;
	}
	void Input::Update(GLFWwindow* window)
	{
		for (int i = 0; i < GLFW_KEY_LAST; i++)
		{
			m_keys[i] = glfwGetKey(window, i) == GLFW_PRESS;
		}

		for (int i = 0; i <= GLFW_MOUSE_BUTTON_LAST; i++)
		{
			m_mouseKeys[i] =
				glfwGetMouseButton(window, i) == GLFW_PRESS;
		}

		double x;
		double y;
		glfwGetCursorPos(window, &x, &y);

		float xf = static_cast<float>(x);
		float yf = static_cast<float>(y);

		if (m_firstMouse)
		{
			m_mouseLastX = xf;
			m_mouseLastY = yf;
			m_firstMouse = false;
		}

		m_mouseDelta.x = xf - m_mouseLastX;
		m_mouseDelta.y = yf - m_mouseLastY;

		m_mouseLastX = xf;
		m_mouseLastY = yf;
	}
	void Input::AddScroll(float, float yOffset)
	{				
		m_scroll -= yOffset;
		m_scroll = math::clamp(m_scroll, 1.0f, 45.0f);
	}
	bool Input::IsKeyPressed(int key)
	{
		int max = static_cast<int>(m_keys.size());
		if (key < 0 || key >= max)
		{
			return false;
		}
		return m_keys[key];
	}
	bool Input::IsMouseKeyPressed(int key)
	{
		int max = static_cast<int>(m_mouseKeys.size());
		if (key < 0 || key >= max)
		{
			return false;
		}
		return m_mouseKeys[key];
	}
	glm::vec2 Input::MouseDelta() const
	{
		return m_mouseDelta;
	}
	float Input::Scroll() const
	{
		return m_scroll;
	}

}