#ifndef TEXTURE_LIBRARY_H
#define TEXTURE_LIBRARY_H

#include <eng/graphics/texture/texture.h>
#include <eng/debug/assert.h>

#include <memory>
#include <array>
#include <cstdint>
#include <map>

namespace eng
{
	class TextureLibrary
	{
	public:
		using Color = std::array<std::uint8_t, 4>;

		TextureLibrary()
		{
			ENG_ASSERT(
				m_instance == nullptr,
				"TEXTURE_LIBRARY: INSTANCE ALREADY EXISTS");

			m_instance = this;
		}
		static TextureLibrary& Instance()
		{
			ENG_ASSERT(
				m_instance != nullptr,
				"TEXTURE_LIBRARY: INSTANCE NOT INITIALIZED");

			return *m_instance;
		}
		static std::shared_ptr<Texture2D> GetTexture(const Color& color)
		{
			return Instance().GetTextureInternal(color);
		}
	private:
		std::shared_ptr<Texture2D> GetTextureInternal(const Color& color)
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

		inline static TextureLibrary* m_instance{ nullptr };
		std::map<Color, std::shared_ptr<Texture2D>> m_colorTextures;
	};
}

#endif // !TEXTURE_LIBRARY_H
