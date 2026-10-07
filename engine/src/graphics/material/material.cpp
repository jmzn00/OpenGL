#include <eng/graphics/material/material.h>
#include <iostream>
#include <eng/debug/assert.h>
namespace eng
{	
	Material::Material(MaterialProperties props)
	{
		m_vec3Params["material.ambient"] = props.ambient;
		m_vec3Params["material.diffuse"] = props.diffuse;
		m_vec3Params["material.specular"] = props.specular;
		m_floatParams["material.shininess"] = props.shininess;
	}
	void Material::SetShaderProgram(const std::shared_ptr<ShaderProgram>& shaderProgram)
	{
		m_shaderProgram = shaderProgram;
	}
	void Material::SetVec3(const std::string& name, const glm::vec3& value)
	{
		auto it = m_vec3Params.find(name);
		if (it == m_vec3Params.end())
		{
			std::cout << "MATERIAL::SETVEC3: PARAM: " << name << " NOT FOUND\n";
			return;
		}
		it->second = value;
	}
	void Material::SetFloat(const std::string& name, const float value)
	{
		auto it = m_floatParams.find(name);
		if (it == m_floatParams.end())
		{
			std::cout << "MATERIAL::SETFLOAT: PARAM: " << name << " NOT FOUND\n";
			return;
		}
		it->second = value;
	}
	ShaderProgram& Material::GetShaderProgram() const
	{
		ENG_ASSERT(m_shaderProgram, "MATERIAL::GET_SHADER_PROGRAM: NO SHADER_PROGRAM");
		return *m_shaderProgram;
	}
	void Material::Bind(GraphicsAPI& gapi) const
	{		
		ENG_ASSERT(m_shaderProgram, "MATERIAL::BIND: NO SHADER_PROGRAM");
		gapi.BindShaderProgram(m_shaderProgram.get());

		for (const auto& param : m_vec3Params)
		{
			m_shaderProgram->SetVec3(param.first, param.second);
		}
		for (const auto& param : m_floatParams)
		{
			m_shaderProgram->SetFloat(param.first, param.second);
		}
	}
}