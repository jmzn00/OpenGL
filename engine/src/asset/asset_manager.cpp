#include <eng/asset/asset_manager.h>

#include <eng/debug/assert.h>

namespace eng
{
	AssetManager::AssetManager()
	{
		ENG_ASSERT(m_instance == nullptr, "ASSET_MANAGER: INSTANCE ALREADY EXISTS");
		m_instance = this;		
	}
	AssetManager::~AssetManager()
	{		
		if (m_instance == this)
			m_instance = nullptr;

		m_shaders.Clear();
		m_materials.Clear();
		m_textures.Clear();
		m_meshes.Clear();
	}
	void AssetManager::Init()
	{
		m_shaders.Init();
		m_materials.Init();
	}
	AssetManager& AssetManager::Get()
	{
		ENG_ASSERT(m_instance != nullptr, "ASSET_MANAGER: INSTANCE NOT INITIALIZED");

		return *m_instance;
	}
	ShaderLibrary& AssetManager::Shaders()
	{
		return m_shaders;
	}
	MaterialLibrary& AssetManager::Materials()
	{
		return m_materials;
	}
	MeshLibrary& AssetManager::Meshes()
	{
		return m_meshes;
	}
	TextureLibrary& AssetManager::Textures()
	{		
		return m_textures;
	}
}