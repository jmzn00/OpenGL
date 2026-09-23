#ifndef INPUT_H
#define INPUT_H

#include<array>
#include <GLFW/glfw3.h>
#include <vec2.hpp>

namespace eng
{
	class Input
	{
	public:
		bool Init(GLFWwindow* window);
		void Update(GLFWwindow* window);
		bool IsKeyPressed(int key);
		glm::vec2 MouseDelta() const;
		float Scroll() const;
		void AddScroll(float xOffset, float yOffset);
	private:		
		void SetKeyPressed(int key, bool pressed);		
		std::array<bool, GLFW_KEY_LAST + 1> m_keys = { false };
		std::array<bool, 16> m_mouseKeys{ false };

		// BAD BAD BAD
		float m_mouseLastX{ 960 };
		float m_mouseLastY{ 540 };

		glm::vec2 m_mouseDelta{};		

		bool m_firstMouse{ true };

		float m_scroll{45.0f};
	};
}
#endif // !INPUT_H
