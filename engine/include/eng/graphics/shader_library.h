#ifndef SHADER_LIBRARY_H
#define SHADER_LIBRARY_H

#include <memory>
#include <string>
#include <unordered_map>
#include <eng/graphics/shader_program.h>
#include <eng/debug/assert.h>

namespace eng
{
	class ShaderLibrary
	{
	public:
		ShaderLibrary()
		{
			ENG_ASSERT(m_instance == nullptr, "SHADER LIBRARY INSTANCE ALREADY EXISTS");
			m_instance = this;
		}
		void Init()
		{
			m_shaders["Default"] =
				std::make_shared<ShaderProgram>(
					ENGINE_ASSET_DIR "/shaders/vert.vert",
					ENGINE_ASSET_DIR "/shaders/frag.frag");

			m_shaders["Light"] =
				std::make_shared<ShaderProgram>(
					ENGINE_ASSET_DIR "/shaders/lightSource/lightSource.vert",
					ENGINE_ASSET_DIR "/shaders/lightSource/lightSource.frag");
		}
		static ShaderLibrary& Get()
		{
			return *m_instance;
		}
		std::shared_ptr<ShaderProgram> Get(const std::string& name)
		{
			return m_shaders.at(name);
		}
	private:
		std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> m_shaders;
		inline static ShaderLibrary* m_instance;
	};
}
#endif // !SHADER_LIBRARY_H
