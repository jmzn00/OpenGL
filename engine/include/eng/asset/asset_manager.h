#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <eng/graphics/texture/texture_library.h>
#include <eng/graphics/material/material_library.h>
#include <eng/graphics/shader_library.h>
#include <eng/renderer/mesh_library.h>

#include <string>
#include <vector>

namespace eng
{	
	struct ModelAsset
	{
		std::string name;
		std::string relativePath;
	};
	class Model;
	class AssetManager
	{
	public:
		AssetManager();
		~AssetManager();
		AssetManager(const AssetManager&) = delete;
		AssetManager(AssetManager&&) = delete;
		AssetManager& operator=(const AssetManager&) = delete;
		AssetManager& operator=(AssetManager&&) = delete;		

		MeshLibrary& Meshes();
		TextureLibrary& Textures();
		ShaderLibrary& Shaders();
		MaterialLibrary& Materials();
		std::vector<ModelAsset>& Models();

		std::shared_ptr<eng::Model> LoadModel(const std::string& relativePath);

		void Init();
		static AssetManager& Get();			

	private:
		inline static AssetManager* m_instance{nullptr};

		ShaderLibrary m_shaders{};
		TextureLibrary m_textures{};
		MeshLibrary m_meshes{};
		MaterialLibrary m_materials{ m_shaders, m_textures };

		std::vector<ModelAsset> m_models;
	};
}
#endif // !ASSET_MANAGER_H
