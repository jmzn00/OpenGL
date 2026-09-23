#ifndef CAMERA_H
#define CAMERA_H
#include <eng/window/window.h>
#include <vec3.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>
namespace eng
{
	class Camera
	{
	public:
		explicit Camera()
		{
		}
		Camera(const Camera&) = delete;
		Camera(Camera&&) = delete;
		Camera& operator=(const Camera&) = delete;
		Camera& operator=(Camera&&) = delete;
		
		void SetViewportSize(uint32_t w, uint32_t h)
		{
			m_projection = glm::perspective(glm::radians(m_fov)
				, static_cast<float>(w) / h, 0.1f, 100.0f);
		}
		glm::vec3 GetPosition() const
		{
			return m_position;
		}

		glm::mat4 GetProjection() const
		{
			return m_projection;
		}
		glm::mat4 GetView() const
		{
			return m_view;
		}
		glm::vec3 GetUp() const
		{
			return m_up;
		}
		glm::vec3 GetForward() const
		{
			return m_forward;
		}
		glm::vec3 GetFlatForward() const
		{
			return m_flatForward;
		}
		glm::vec3 GetRight() const
		{
			return m_right;
		}
		void Look(float pitch, float yaw)
		{
 			glm::vec3 direction;
			direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			direction.y = sin(glm::radians(pitch));
			direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

			m_forward = glm::normalize(direction);
			RecalculateView();
		}
		void MoveTo(glm::vec3 position)
		{
			m_position = position;
			RecalculateView();
		}
	private:
		void RecalculateView()
		{
			m_view = glm::lookAt(
				m_position,
				m_position + m_forward,
				m_up);

			RecalculateFlatForwarward();
			RecalculateRight();
		}
		void RecalculateRight()
		{
			m_right = glm::normalize(
				glm::cross(m_flatForward,
					m_up));
		}
		void RecalculateFlatForwarward()
		{
			m_flatForward = glm::normalize(
				glm::vec3(m_forward.x, 0.0f, m_forward.z));
		}
		glm::vec3 m_position {0.0, 0.0, 3.0};
		glm::vec3 m_forward {0.0, 0.0, -1.0};
		glm::vec3 m_flatForward{};
		glm::vec3 m_up {0.0, 1.0, 0.0};
		glm::vec3 m_right{};

		glm::mat4 m_projection{1.0};
		glm::mat4 m_view{ 1.0 };

		float m_fov{ 45.0f };
	};
}
#endif // !CAMERA_H
