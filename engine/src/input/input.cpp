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

		if (m_firstMouse)
		{
			m_mouseLastX = static_cast<float>(x);
			m_mouseLastY = static_cast<float>(y);
			m_firstMouse = false;
		}

		m_mouseDelta.x = static_cast<float>(x) - m_mouseLastX;
		m_mouseDelta.y = static_cast<float>(y) - m_mouseLastY;

		m_mouseLastX = static_cast<float>(x);
		m_mouseLastY = static_cast<float>(y);
	}
	void Input::AddScroll(float, float yOffset)
	{				
		m_scroll -= yOffset;
		m_scroll = math::clamp(m_scroll, 1.0f, 45.0f);
	}
	void Input::SetKeyPressed(int key, bool isPressed)
	{
		if (key < 0 || key >= static_cast<int>(m_keys.size()))
		{
			return;
		}
		m_keys[key] = isPressed;
	}
	bool Input::IsKeyPressed(int key)
	{
		if (key < 0 || key >= static_cast<int>(m_keys.size()))
		{
			return false;
		}
		return m_keys[key];
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