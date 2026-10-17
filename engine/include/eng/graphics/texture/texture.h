#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <string>

#include <array>
#include <cstdint>

namespace eng
{
	class Texture2D
	{
	public:
		using Color = std::array<std::uint8_t, 4>;

		explicit Texture2D(const std::string& path);
		explicit Texture2D(const Color& color);

		~Texture2D();
		Texture2D(const Texture2D&) = delete;
		Texture2D& operator=(const Texture2D&) = delete;
		void Bind(GLuint textureUnit) const;

		GLuint GetId() const
		{
			return m_id;
		}
	private:
		GLuint m_id{0};
	};
}
#endif // !TEXTURE_H
