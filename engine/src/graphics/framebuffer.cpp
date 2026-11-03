#include <eng/graphics/framebuffer.h>

#include <iostream>

namespace eng
{
	Framebuffer::~Framebuffer()
	{
		Destroy();
	}
	bool Framebuffer::Create(uint32_t width, uint32_t height)
	{
		if (m_framebuffer == 0)
		{
			glGenFramebuffers(1, &m_framebuffer);
			glGenTextures(1, &m_colorTexture);
			glGenRenderbuffers(1, &m_depthStencil);
		}
		return Resize(width, height);
	}
	void Framebuffer::Destroy()
	{
		if (m_depthStencil)
			glDeleteRenderbuffers(1, &m_depthStencil);
		if (m_colorTexture)
			glDeleteTextures(1, &m_colorTexture);
		if (m_framebuffer)
			glDeleteFramebuffers(1, &m_framebuffer);

		m_depthStencil = 0;
		m_colorTexture = 0;
		m_framebuffer = 0;
		m_width = 0;
		m_height = 0;
	}
	void Framebuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
	}	
	bool Framebuffer::Resize(uint32_t width, uint32_t height)
	{
		if (width == 0 || height == 0)
			return false;

		if (m_framebuffer == 0)
			return false;

		if (width == m_width && height == m_height)
			return true;

		GLint previousFramebuffer = 0;
		GLint previousTexture = 0;
		GLint previousRenderbuffer = 0;

		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &previousFramebuffer);
		glGetIntegerv(GL_TEXTURE_BINDING_2D, &previousTexture);
		glGetIntegerv(GL_RENDERBUFFER_BINDING, &previousRenderbuffer);

		glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

		// color attachment
		glBindTexture(GL_TEXTURE_2D, m_colorTexture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA8,
			width,
			height,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			nullptr
		);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0
			, GL_TEXTURE_2D, m_colorTexture, 0);

		// depth and stencil storage
		glBindRenderbuffer(GL_RENDERBUFFER, m_depthStencil);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT
			, GL_RENDERBUFFER, m_depthStencil);

		const bool complete = 
			glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;

		glBindFramebuffer(GL_FRAMEBUFFER, previousFramebuffer);
		glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(previousTexture));
		glBindRenderbuffer(GL_RENDERBUFFER, static_cast<GLuint>(previousRenderbuffer));

		if (!complete)
		{
			std::cerr << "FRAMEBUFFER NOT COMPLETE\n";
			return false;
		}

		m_width = width;
		m_height = height;

		return true;


		return true;
	}	
	GLuint Framebuffer::GetID() const
	{
		return m_framebuffer;
	}
	GLuint Framebuffer::GetColorTexture() const
	{
		return m_colorTexture;
	}

}
