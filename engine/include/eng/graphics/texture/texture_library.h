#ifndef TEXTURE_LIBRARY_H
#define TEXTURE_LIBRARY_H

#include <eng/graphics/texture/texture.h>
#include <eng/debug/assert.h>

#include <memory>
#include <array>
#include <cstdint>
#include <map>
#include <unordered_map>
#include <string>

namespace eng
{
	class TextureLibrary
	{
	public:
		using Color = std::array<std::uint8_t, 4>;

		TextureLibrary()
		{			
		}	
		std::shared_ptr<Texture2D> GetTexture(const Color& color)
		{
			auto texture = m_colorTextures.find(color);
			if (texture != m_colorTextures.end())
			{
				return texture->second;
			}
			auto newTexture = std::make_shared<Texture2D>(color);
			m_colorTextures.emplace(color, newTexture);

			return newTexture;
		}
		std::shared_ptr<Texture2D> GetTexture(const std::string& path)
		{
			auto texture = m_fileTextures.find(path);

			if (texture != m_fileTextures.end())
			{
				return texture->second;
			}

			auto newTexture =
				std::make_shared<Texture2D>(path);

			m_fileTextures.emplace(path, newTexture);

			return newTexture;
		}
		void Clear()
		{
			m_colorTextures.clear();
			m_fileTextures.clear();
		}
	private:
		std::map<Color, std::shared_ptr<Texture2D>> m_colorTextures;
		std::unordered_map<std::string, std::shared_ptr<Texture2D>> m_fileTextures;
	};
}

#endif // !TEXTURE_LIBRARY_H
