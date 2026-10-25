#ifndef MATERIAL_LIBRARY_H
#define MATERIAL_LIBRARY_H

#include <eng/graphics/material/material.h>
#include <eng/debug/assert.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <eng/graphics/shader_library.h>

namespace eng
{
	class MaterialLibrary
	{
	public:
		MaterialLibrary()
		{
			ENG_ASSERT(m_instance == nullptr, "MATERIAL LIBRARY INSTANCE ALREADY EXISTS");
			m_instance = this;
		}

		void Init()
		{
			m_materials["Default"] = std::make_shared<Material>(
				MaterialProperties{
					glm::vec3(0.1f, 0.1f, 0.1f),
					glm::vec3(0.5f, 0.5f, 0.5f),
					glm::vec3(1.0f, 1.0f, 1.0f),
					32.0f
				});

			m_materials["Emerald"] = std::make_shared<Material>(
				MaterialProperties{
					glm::vec3(0.0215f, 0.1745f, 0.0215f),
					glm::vec3(0.07568f, 0.61424f, 0.07568f),
					glm::vec3(0.633f, 0.727811f, 0.633f),
					76.8f
				});

			m_materials["Jade"] = std::make_shared<Material>(
				MaterialProperties{
					glm::vec3(0.135f, 0.2225f, 0.1575f),
					glm::vec3(0.54f, 0.89f, 0.63f),
					glm::vec3(0.316228f, 0.316228f, 0.316228f),
					12.8f
				});

			m_materials["Obsidian"] = std::make_shared<Material>(
				MaterialProperties{
					glm::vec3(0.05375f, 0.05f, 0.06625f),
					glm::vec3(0.18275f, 0.17f, 0.22525f),
					glm::vec3(0.332741f, 0.328634f, 0.346435f),
					38.4f
				});

			m_materials["Pearl"] = std::make_shared<Material>(
				MaterialProperties{
					glm::vec3(0.25f, 0.20725f, 0.20725f),
					glm::vec3(1.0f, 0.829f, 0.829f),
					glm::vec3(0.296648f, 0.296648f, 0.296648f),
					11.264f
				});

			m_materials["Ruby"] = std::make_shared<Material>(
				MaterialProperties{
					glm::vec3(0.1745f, 0.01175f, 0.01175f),
					glm::vec3(0.61424f, 0.04136f, 0.04136f),
					glm::vec3(0.727811f, 0.626959f, 0.626959f),
					76.8f
				});

			m_materials["Gold"] = std::make_shared<Material>(
				MaterialProperties{
					glm::vec3(0.24725f, 0.1995f, 0.0745f),
					glm::vec3(0.75164f, 0.60648f, 0.22648f),
					glm::vec3(0.628281f, 0.555802f, 0.366065f),
					51.2f
				});

			m_materials["Silver"] = std::make_shared<Material>(
				MaterialProperties{
					glm::vec3(0.19225f, 0.19225f, 0.19225f),
					glm::vec3(0.50754f, 0.50754f, 0.50754f),
					glm::vec3(0.508273f, 0.508273f, 0.508273f),
					51.2f
				});

			m_materials["Bronze"] = std::make_shared<Material>(
				MaterialProperties{
					glm::vec3(0.2125f, 0.1275f, 0.054f),
					glm::vec3(0.714f, 0.4284f, 0.18144f),
					glm::vec3(0.393548f, 0.271906f, 0.166721f),
					25.6f
				});

			for (auto& mat : m_materials)
			{
				mat.second->SetShaderProgram(ShaderLibrary::Get("Default"));
			}
		}
		static MaterialLibrary& Instance()
		{
			return *m_instance;
		}
		static std::shared_ptr<Material> Get(const std::string& name)
		{
			ENG_ASSERT(m_instance != nullptr, "MATERIAL_LIBRARY:Get: INSTANCE IS NULL");
			return Instance().GetMaterial(name);
		}
		static std::unordered_map<std::string, std::shared_ptr<Material>>& GetAllMaterials()
		{
			ENG_ASSERT(m_instance != nullptr, "MATERIAL_LIBRARY:GetAll: INSTANCE IS NULL");
			return Instance().GetAll();
		}
	private:
		std::shared_ptr<Material> GetMaterial(const std::string& name)
		{
			auto material = m_materials.find(name);

			ENG_ASSERT(
				material != m_materials.end(),
				"MATERIAL DOES NOT EXIST");

			return material->second;
		}
		std::unordered_map<std::string, std::shared_ptr<Material>>& GetAll()
		{
			return m_materials;
		}
		std::unordered_map<std::string, std::shared_ptr<Material>> m_materials;
		inline static MaterialLibrary* m_instance;
	};
}
#endif // !MATERIAL_LIBRARY_H


