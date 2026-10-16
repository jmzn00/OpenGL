#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <string>

namespace eng
{
	class Texture2D
	{
	public:
		explicit Texture2D(const std::string& path);
		~Texture2D()
		{
			if (m_id != 0)
			{
				glDeleteTextures(1, &m_id);
			}
		}
		Texture2D(const Texture2D&) = delete;
		Texture2D& operator=(const Texture2D&) = delete;

		void Bind(GLuint textureUnit) const
		{
			glActiveTexture(GL_TEXTURE0 + textureUnit);
			glBindTexture(GL_TEXTURE_2D, m_id);
		}
		GLuint GetId() const
		{
			return m_id;
		}
	private:
		GLuint m_id{0};
	};
}
#endif // !TEXTURE_H
