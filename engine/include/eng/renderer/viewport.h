#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <cstdint>
#include <eng/graphics/framebuffer.h>

namespace eng
{
	class Viewport
	{
	public:
		bool Create(uint32_t width, uint32_t height)
		{			
			bool complete = m_sceneTarget.Create(width, height)
				&& m_outputTarget.Create(width, height);

			if (complete)
			{
				m_width = width;
				m_height = height;
			}

			return complete;
		}
		bool Resize(uint32_t width, uint32_t height);

		void RequestResize(uint32_t width, uint32_t height);
		void ApplyPendingResize();
		void SetRenderArea();

		void BindSceneTarget() const;
		void BindOutputTarget() const;

		Framebuffer& GetSceneTarget()
		{
			return m_sceneTarget;
		}
		Framebuffer& GetOutputTarget()
		{
			return m_outputTarget;
		}

		static void BindDefaultTarget();
		
		GLuint GetOutputTexture() const;
		GLuint GetSceneTexture() const;

		uint32_t GetWidth() const;
		uint32_t GetHeight() const;

		bool GetFocused() const
		{
			return m_focused;
		}
		void SetFocused(bool value)
		{
			m_focused = value;
		}
	private:
		Framebuffer m_sceneTarget;
		Framebuffer m_outputTarget;

		uint32_t m_width = 0;
		uint32_t m_height = 0;				

		uint32_t m_pendingWidth = 0;
		uint32_t m_pendingHeight = 0;

		bool m_focused = false;
	};
}
#endif // !VIEWPORT_H
