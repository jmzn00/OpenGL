#ifndef MATERIAL_H
#define MATERIAL_H
#include "vec3.hpp"
#include <memory>
#include <unordered_map>
#include <string>
#include <eng/graphics/shader_program.h>
#include <eng/graphics/graphics_api.h>
#include <eng/graphics/texture/texture.h>

namespace eng
{	
	struct MaterialProperties
	{
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float shininess;
	};
	enum class AlphaMode {
		Opaque,
		Mask,
		Blend
	};
	class Material
	{
	public:
		Material(MaterialProperties props);
		void SetShaderProgram(const std::shared_ptr<ShaderProgram>& shaderProgram);
		void SetVec3(const std::string& name, const glm::vec3& value);
		void SetFloat(const std::string& name, const float value);		
		ShaderProgram& GetShaderProgram() const;
		void Bind(GraphicsAPI& gapi) const;

		void SetDiffuseTexture(const std::shared_ptr<Texture2D>& texture);
		void SetSpecularMap(const std::shared_ptr<Texture2D>& specular);
		void SetEmissionMap(const std::shared_ptr<Texture2D>& emission);
		void SetReflectionMap(const std::shared_ptr<Texture2D>& reflection);

		void SetAlphaMode(AlphaMode mode)
		{
			m_alphaMode = mode;
		}
		AlphaMode GetAlphaMode() const { return m_alphaMode; }

		const std::string& GetDiffuseTextureKey() const
		{
			return m_diffuseTextureKey;
		}
		const std::string& GetSpecularTextureKey() const
		{
			return m_specularTextureKey;
		}
		const std::string& GetEmissionTextureKey() const
		{
			return m_emissionTextureKey;
		}
		const std::string& GetReflectionTextureKey() const
		{
			return m_reflectionTextureKey;
		}
		const std::unordered_map<std::string, glm::vec3>& GetVec3Params() const
		{
			return m_vec3Params;
		}
		const std::unordered_map<std::string, float>& GetFloatParams() const
		{
			return m_floatParams;
		}

	private:
		std::shared_ptr<ShaderProgram> m_shaderProgram;

		std::unordered_map<std::string, glm::vec3> m_vec3Params;
		std::unordered_map<std::string, float> m_floatParams;

		std::shared_ptr<Texture2D> m_diffuseTexture;
		std::shared_ptr<Texture2D> m_specularMap;
		std::shared_ptr<Texture2D> m_emissionMap;
		std::shared_ptr<Texture2D> m_reflectionMap;

		AlphaMode m_alphaMode = AlphaMode::Opaque;

		std::string m_diffuseTextureKey;
		std::string m_specularTextureKey;
		std::string m_emissionTextureKey;
		std::string m_reflectionTextureKey;
	};
}
#endif // !MATERIAL_H
