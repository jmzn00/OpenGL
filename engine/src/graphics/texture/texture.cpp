#include <eng/graphics/texture/texture.h>
#include <eng/debug/assert.h>
#include <eng/util/stb_image.h>
#include <iostream>


namespace eng
{
	Texture2D::Texture2D(const std::string& path)
	{
		int width = 0;
		int height = 0;
		int channels = 0;
		
		stbi_set_flip_vertically_on_load(true);

		unsigned char* data = stbi_load(
			path.c_str(),
			&width,
			&height,
			&channels,
			0);
		ENG_ASSERT(data, "TEXTURE2D: FAILED TO LOAD IMAGE");

		GLenum format = GL_RGB;
		if (channels == 1)
			format = GL_RED;
		else if (channels == 4)
			format = GL_RGBA;

		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			format,
			width,
			height,
			0,
			format,
			GL_UNSIGNED_BYTE,
			data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(data);
	}
	Texture2D::Texture2D(const Color& color)
	{
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			1,
			1,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			color.data());

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	Texture2D::~Texture2D()
	{
		if (m_id != 0)
		{
			glDeleteTextures(1, &m_id);
		}
	}
	void Texture2D::Bind(GLuint textureUnit) const
	{
		glActiveTexture(GL_TEXTURE0 + textureUnit);
		glBindTexture(GL_TEXTURE_2D, m_id);		
	}
}