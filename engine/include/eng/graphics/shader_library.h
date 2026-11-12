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
		}
		void Init()
		{
			m_shaders["Default"] =
				std::make_shared<ShaderProgram>(
					ENGINE_ASSET_DIR "/shaders/vert.vert",
					ENGINE_ASSET_DIR "/shaders/frag.frag");
			m_shaders["Default"]->SetKey("Default");

			m_shaders["Light"] =
				std::make_shared<ShaderProgram>(
					ENGINE_ASSET_DIR "/shaders/lightSource/lightSource.vert",
					ENGINE_ASSET_DIR "/shaders/lightSource/lightSource.frag");			
			m_shaders["Light"]->SetKey("Light");

			m_shaders["Debug"] = 
				std::make_shared<ShaderProgram>(
					ENGINE_ASSET_DIR "/shaders/vert.vert",
					ENGINE_ASSET_DIR "/shaders/debug/debug.frag");
			m_shaders["Debug"]->SetKey("Debug");

			m_shaders["Line"] =
				std::make_shared<ShaderProgram>(
					ENGINE_ASSET_DIR "/shaders/line/line.vert",
					ENGINE_ASSET_DIR "/shaders/line/line.frag",
					ENGINE_ASSET_DIR "/shaders/line/line.geom");
			m_shaders["Line"]->SetKey("Line");
		}				
		void Clear()
		{
			m_shaders.clear();			
		}
		std::shared_ptr<ShaderProgram> GetShader(const std::string& name)
		{
			return m_shaders.at(name);
		}
	private:		
		std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> m_shaders;		
	};
}
#endif // !SHADER_LIBRARY_H
