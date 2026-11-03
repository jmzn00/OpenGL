#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <glad/glad.h>
#include <cstdint>

namespace eng
{
	class Framebuffer final
	{
	public:
		Framebuffer() = default;
		~Framebuffer();

		Framebuffer(const Framebuffer&) = delete;
		Framebuffer& operator=(const Framebuffer&) = delete;

		bool Create(uint32_t width, uint32_t height);
		void Destroy();
		bool Resize(uint32_t width, uint32_t height);
		void Bind() const;
		static void BindDefault()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		GLuint GetID() const;

		GLuint GetColorTexture() const;
		uint32_t GetWidth() const { return m_width; }
		uint32_t GetHeight() const { return m_height; }
	private:
		GLuint m_framebuffer = 0;
		GLuint m_colorTexture = 0;
		GLuint m_depthStencil = 0;

		uint32_t m_width = 0;
		uint32_t m_height = 0;
	};
}

#endif // !FRAMEBUFFER_H
