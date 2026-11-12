#include <eng/asset/asset_manager.h>

#include <eng/debug/assert.h>
#include <eng/renderer/model.h>

namespace eng
{
	AssetManager::AssetManager()
	{
		ENG_ASSERT(m_instance == nullptr, "ASSET_MANAGER: INSTANCE ALREADY EXISTS");
		m_instance = this;		

		m_models.push_back({ "Planet", ENGINE_ASSET_DIR"/models/planet/planet.obj" });
		m_models.push_back({ "Rock", ENGINE_ASSET_DIR"/models/rock/rock.obj" });
		m_models.push_back({ "Backpack", ENGINE_ASSET_DIR"/models/backpack/backpack.obj" });
		m_models.push_back({ "Sponza", ENGINE_ASSET_DIR"/models/sponza/sponza.obj" });
		m_models.push_back({ "Camera", ENGINE_ASSET_DIR"/models/camera/Camera.fbx" });
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
	std::vector<ModelAsset>& AssetManager::Models()
	{
		return m_models;
	}
	std::shared_ptr<eng::Model> AssetManager::LoadModel(const std::string& relativePath)
	{
		return std::make_shared<Model>(relativePath);
	}
}