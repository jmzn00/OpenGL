#include <eng/graphics/texture/cubemap_texture.h>
#include <eng/util/stb_image.h>
#include <iostream>

namespace eng
{
	CubemapTexture::CubemapTexture(const std::vector<std::string>& faces)
	{
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);

		int width, height, nrChannels;
		unsigned char* data;
		for (std::size_t i = 0; i < faces.size(); i++)
		{
			data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);

			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + static_cast<GLenum>(i), 0, GL_RGB, width, height,
					0, GL_RGB, GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);
			}
			else
			{
				std::cerr << "CUBEMAP::FAILED TO LOAD AT PATH: " << faces[i] << '\n';
				stbi_image_free(data);
				return;
			}			
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	}
	CubemapTexture::~CubemapTexture()
	{
		if (m_id != 0)
			glDeleteTextures(1, &m_id);
	}
	void CubemapTexture::Bind(GLuint textureUnit) const
	{
		glActiveTexture(GL_TEXTURE0 + textureUnit);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
	}
}