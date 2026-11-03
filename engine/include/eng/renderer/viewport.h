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
			m_width = width;
			m_height = height;

			return m_target.Create(width, height);
		}
		bool Resize(uint32_t width, uint32_t height);

		void RequestResize(uint32_t width, uint32_t height);
		void ApplyPendingResize();
		void SetRenderArea();

		void BindTarget() const;
		static void BindDefaultTarget();
		
		GLuint GetColorTexture() const;
		uint32_t GetWidth() const;
		uint32_t GetHeight() const;
	private:
		Framebuffer m_target;

		uint32_t m_width = 0;
		uint32_t m_height = 0;				

		uint32_t m_pendingWidth = 0;
		uint32_t m_pendingHeight = 0;
	};
}
#endif // !VIEWPORT_H
