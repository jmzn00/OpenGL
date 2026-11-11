#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <eng/graphics/texture/texture_library.h>
#include <eng/graphics/material/material_library.h>
#include <eng/graphics/shader_library.h>
#include <eng/renderer/mesh_library.h>

namespace eng
{	
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

		void Init();

		static AssetManager& Get();			

	private:
		inline static AssetManager* m_instance{nullptr};

		ShaderLibrary m_shaders{};
		TextureLibrary m_textures{};
		MeshLibrary m_meshes{};
      MaterialLibrary m_materials{ m_shaders, m_textures };
	};
}
#endif // !ASSET_MANAGER_H
