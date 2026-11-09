#ifndef SCENE_SERIALIZER_H
#define SCENE_SERIALIZER_H

#include <filesystem>
#include <nlohmann/json.hpp>
namespace eng
{
	class Scene;
	class Material;

	class SceneSerializer
	{
	public:
		explicit SceneSerializer(Scene& scene);

		bool Save(const std::filesystem::path& path) const;
		bool Load(const std::filesystem::path& path);

	private:
		Scene& m_scene;

		nlohmann::json SerializeMaterial(const Material& material) const;
	};
}

#endif // !SCENE_SERIALIZER_H
