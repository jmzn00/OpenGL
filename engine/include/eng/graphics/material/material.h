#ifndef MATERIAL_H
#define MATERIAL_H
#include "vec3.hpp"
#include <memory>
#include <unordered_map>
#include <string>
#include <eng/graphics/shader_program.h>
#include <eng/graphics/graphics_api.h>

namespace eng
{	
	struct MaterialProperties
	{
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float shininess;
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
	private:
		std::shared_ptr<ShaderProgram> m_shaderProgram;
		std::unordered_map<std::string, glm::vec3> m_vec3Params;
		std::unordered_map<std::string, float> m_floatParams;
	};
}
#endif // !MATERIAL_H
