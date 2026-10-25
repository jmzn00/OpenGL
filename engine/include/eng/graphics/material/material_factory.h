#ifndef MATERIAL_FACTORY_H
#define MATERIAL_FACTORY_H

#include <eng/graphics/material/material.h>
#include <eng/graphics/texture/texture_library.h>
#include <eng/debug/assert.h>

#include <memory>
#include <vector>
#include <string>

#include <assimp/postprocess.h>
#include <assimp/scene.h>

namespace eng
{
	class MaterialFactory
	{
	public:
		MaterialFactory()
		{
			ENG_ASSERT(m_instance == nullptr, "MATERIAL FACTORY INSTANCE ALREADY EXISTS");
			m_instance = this;
		}
		static MaterialFactory& Instance()
		{
			return *m_instance;
		}
		static std::shared_ptr<Material> CreateFromAssimp(aiMaterial* aiMat, const std::string& directory)
		{
			return Instance().CreateFromAssimpInternal(aiMat, directory);
		}	
	private:
		std::shared_ptr<Material> CreateFromAssimpInternal(aiMaterial* aiMat, const std::string& directory)
		{
			MaterialProperties props{};

			aiColor3D color;

			if (aiMat->Get(AI_MATKEY_COLOR_AMBIENT, color) == AI_SUCCESS)
				props.ambient = { color.r, color.g, color.b };
			if (aiMat->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS)
				props.diffuse = { color.r, color.g, color.b };
			if (aiMat->Get(AI_MATKEY_COLOR_SPECULAR, color) == AI_SUCCESS)
				props.specular = { color.r, color.g, color.b };

			float shininess;
			if (aiMat->Get(AI_MATKEY_SHININESS, shininess) == AI_SUCCESS)
				props.shininess = shininess;

			auto material = std::make_shared<Material>(props);

			if (auto tex =
				LoadMaterialTexture(
					aiMat,
					aiTextureType_DIFFUSE,
					directory))
			{
				material->SetDiffuseTexture(tex);
			}

			if (auto tex =
				LoadMaterialTexture(
					aiMat,
					aiTextureType_SPECULAR,
					directory))
			{
				material->SetSpecularMap(tex);
			}

			if (auto tex =
				LoadMaterialTexture(
					aiMat,
					aiTextureType_EMISSIVE,
					directory))
			{
				material->SetEmissionMap(tex);
			}

			return material;
		}
		std::shared_ptr<Texture2D> LoadMaterialTexture(aiMaterial* aiMat, aiTextureType type
			, const std::string& directory)
		{
			if (aiMat->GetTextureCount(type) == 0)
				return nullptr;

			aiString path;
			aiMat->GetTexture(type, 0, &path);

			std::string texturePath =
				directory + "/" + path.C_Str();

			//return std::make_shared<Texture2D>(texturePath);
			return TextureLibrary::GetTexture(texturePath);
		}
		inline static MaterialFactory* m_instance;
	};
}
#endif // !MATERIAL_FACTORY_H
