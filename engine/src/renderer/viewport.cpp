#include <eng/renderer/viewport.h>

namespace eng
{
	bool Viewport::Resize(uint32_t width, uint32_t height)
	{
		if (width == 0 || height == 0)
			return false;

		if (width == m_width && height == m_height)
			return true;

		if (!m_target.Resize(width, height))
			return false;

		m_width = width;
		m_height = height;

		return true;
	}
	void Viewport::SetRenderArea()
	{
		glViewport(0, 0, m_width, m_height);
	}
	void Viewport::RequestResize(uint32_t width, uint32_t height)
	{
		m_pendingWidth = width;
		m_pendingHeight = height;
	}
	void Viewport::ApplyPendingResize()
	{
		if (m_pendingWidth == 0 || m_pendingHeight == 0)
			return;

		if (Resize(m_pendingWidth, m_pendingHeight))
		{
			m_pendingHeight = 0;
			m_pendingWidth = 0;
		}				
	}
	void Viewport::BindTarget() const
	{
		m_target.Bind();
	}
	void Viewport::BindDefaultTarget()
	{
		Framebuffer::BindDefault();
	}

	GLuint Viewport::GetColorTexture() const
	{
		return m_target.GetColorTexture();
	}
	uint32_t Viewport::GetWidth() const
	{
		return m_width;
	}
	uint32_t Viewport::GetHeight() const
	{
		return m_height;
	}
}