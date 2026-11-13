#include <eng/scene/scene_serializer.h>
#include <eng/scene/scene.h>
#include <eng/entity/components.h>
#include <eng/graphics/material/material.h>
#include <eng/asset/asset_manager.h>
#include <eng/renderer/model.h>
#include <eng/core/logger.h>

#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <optional>
#include <cstdint>

namespace
{
	glm::vec3 ReadVec3(const nlohmann::json& value)
	{
		if (!value.is_array() || value.size() != 3)
			throw std::runtime_error("Expected a vec3 array");
		return { value.at(0).get<float>(), value.at(1).get<float>(), value.at(2).get<float>() };
	}

	void ReadTransformVec3(const nlohmann::json& transform, const char* name, glm::vec3& output)
	{
		output = ReadVec3(transform.at(name));
	}
}

namespace eng
{
	SceneSerializer::SceneSerializer(Scene& scene)
		: m_scene{ scene }
	{
	}

	bool SceneSerializer::Save(const std::filesystem::path& path) const
	{
		using nlohmann::json;
		std::error_code filesystemError;
		if (!path.parent_path().empty())
			std::filesystem::create_directories(path.parent_path(), filesystemError);
		if (filesystemError)
			return false;

		json root;
		root["version"] = 2;
		root["sceneName"] = m_scene.GetName();
		root["entities"] = json::array();

		for (const auto& entityPtr : m_scene.GetEntities())
		{
			const Entity& entity = *entityPtr;
			const TransformComponent& transform = entity.Transform();

			json entityJson;
			entityJson["id"] = entity.GetID();
			entityJson["parent"] = entity.GetParent()
				? json(*entity.GetParent()) : json(nullptr);
			entityJson["name"] = entity.GetName();
			entityJson["transform"] = {
				{ "translation", {
					transform.Translation.x,
					transform.Translation.y,
					transform.Translation.z
				}},
				{ "rotation", {
					transform.Rotation.x,
					transform.Rotation.y,
					transform.Rotation.z
				}},
				{ "scale", {
					transform.Scale.x,
					transform.Scale.y,
					transform.Scale.z
				}}
			};

			if (entity.HasComponent<MeshComponent>())
			{
				MeshComponent& meshComponent = entity.GetComponent<MeshComponent>();
				Mesh& mesh = *meshComponent.mesh;
				Material& material = *meshComponent.material;

				entityJson["mesh"] = mesh.GetKey();
				entityJson["material"] = SerializeMaterial(material);
			}
			else if (entity.HasComponent<ModelComponent>())
			{
				ModelComponent& model = entity.GetComponent<ModelComponent>();
				entityJson["model"] = model.model->GetKey();
			}
			if (entity.HasComponent<LightComponent>())
			{
				LightComponent& light = entity.GetComponent<LightComponent>();

				entityJson["light"] = {
					{"type", static_cast<int>(light.type)},
					{"ambient", {light.ambient.x, light.ambient.y, light.ambient.z}},
					{ "diffuse", {light.diffuse.x, light.diffuse.y, light.diffuse.z}
				},
					{ "specular", {light.specular.x, light.specular.y, light.specular.z}
				},
					{ "constant", light.constant},
					{ "linear", light.linear},
					{ "quadratic", light.quadratic},
					{ "innerCutoff", light.innerCutoff},
					{ "outerCutoff", light.outerCutoff}
				};
			}

			root["entities"].push_back(entityJson);
		}

		std::ofstream file(path);
		if (!file)
			return false;

		file << root.dump(4);
		return file.good();
	}
	nlohmann::json SceneSerializer::SerializeMaterial(const Material& material) const
	{
		using nlohmann::json;

		json root;

		root["shader"] = material.GetShaderProgram().GetKey();
		root["alphamode"] = static_cast<int>(material.GetAlphaMode());

		root["textures"] = {
			{ "diffuse", material.GetDiffuseTextureKey()},
			{ "specular", material.GetSpecularTextureKey()},
			{ "emission", material.GetEmissionTextureKey()},
			{ "reflection", material.GetReflectionTextureKey()}
		};
		root["vec3Params"] = json::object();
		for (const auto& [name, value] : material.GetVec3Params())
			root["vec3Params"][name] = { value.x, value.y, value.z };
		root["floatParams"] = json::object();
		for (const auto& [name, value] : material.GetFloatParams())
			root["floatParams"][name] = value;

		return root;		
	}
	bool SceneSerializer::Load(const std::filesystem::path& path)
	{
		using nlohmann::json;
		Logger& log = Logger::Instance();
		ShaderLibrary& shaders = AssetManager::Get().Shaders();
		TextureLibrary& textureLibrary = AssetManager::Get().Textures();
		MeshLibrary& meshes = AssetManager::Get().Meshes();
		MaterialLibrary& materials = AssetManager::Get().Materials();
		
		try
		{
			std::ifstream file(path);
			if (!file)
			{
				log.Error("[SCENE SERIALIZER] FILE OPEN FAILED");
				return false;
			}				

			json root;
			file >> root;
			const int version = root.at("version").get<int>();
			if ((version != 1 && version != 2) || !root.at("entities").is_array())
			{
				log.Error("[SCENE SERIALIZER] ROOT FAILED");
				return false;
			}

			std::vector<std::unique_ptr<Entity>> loadedEntities;
			loadedEntities.reserve(root.at("entities").size());
			std::unordered_map<std::uint32_t, Entity*> savedEntities;
			std::unordered_map<std::uint32_t, std::optional<std::uint32_t>> parents;
			auto readId = [](const json& value) -> std::uint32_t
			{
				if (!value.is_number_integer() || value.get<std::int64_t>() < 0 ||
					value.get<std::uint64_t>() > UINT32_MAX)
					throw std::runtime_error("Invalid entity ID");
				return value.get<std::uint32_t>();
			};

			for (const json& entityJson : root.at("entities"))
			{
				auto entity = std::make_unique<Entity>(entityJson.at("name").get<std::string>());
				if (version == 2)
				{
					const auto savedId = readId(entityJson.at("id"));
					if (!savedEntities.emplace(savedId, entity.get()).second)
						throw std::runtime_error("Duplicate entity ID");
					const auto& parent = entityJson.at("parent");
					parents.emplace(savedId, parent.is_null()
						? std::nullopt : std::optional<std::uint32_t>(readId(parent)));
				}
				const json& transformJson = entityJson.at("transform");
				ReadTransformVec3(transformJson, "translation", entity->Transform().Translation);
				ReadTransformVec3(transformJson, "rotation", entity->Transform().Rotation);
				ReadTransformVec3(transformJson, "scale", entity->Transform().Scale);

				if (entityJson.contains("mesh"))
				{
					auto mesh = meshes.Create(entityJson.at("mesh").get<std::string>());
					if (!mesh)
					{
						log.Error("[SCENE SERIALIZER] MESH CREATION FAILED");
						return false;
					}						

					const json& materialJson = entityJson.at("material");
					auto material = std::make_shared<Material>(*materials.GetMaterial("Default"));
					material->SetShaderProgram(shaders.GetShader(materialJson.at("shader").get<std::string>()));

					const int alphaMode = materialJson.at("alphamode").get<int>();
					if (alphaMode < static_cast<int>(AlphaMode::Opaque) ||
						alphaMode > static_cast<int>(AlphaMode::Blend))
					{
						log.Error("[SCENE SERIALIZER] ALPHA MODE INVALID");
						return false;
					}						
					material->SetAlphaMode(static_cast<AlphaMode>(alphaMode));

					const json& textures = materialJson.at("textures");
					const std::string diffuse = textures.at("diffuse").get<std::string>();
					const std::string specular = textures.at("specular").get<std::string>();
					const std::string emission = textures.at("emission").get<std::string>();
					const std::string reflection = textures.at("reflection").get<std::string>();
					if (!diffuse.empty())
						material->SetDiffuseTexture(textureLibrary.GetTexture(diffuse));
					if (!specular.empty())
						material->SetSpecularMap(textureLibrary.GetTexture(specular));
					if (!emission.empty())
						material->SetEmissionMap(textureLibrary.GetTexture(emission));
					if (!reflection.empty())
						material->SetReflectionMap(textureLibrary.GetTexture(reflection));

					for (auto it = materialJson.at("vec3Params").begin(); it != materialJson.at("vec3Params").end(); ++it)
						material->SetVec3(it.key(), ReadVec3(it.value()));
					for (auto it = materialJson.at("floatParams").begin(); it != materialJson.at("floatParams").end(); ++it)
						material->SetFloat(it.key(), it.value().get<float>());

					entity->AddComponent<MeshComponent>(std::move(mesh), std::move(material));
				}
				else if (entityJson.contains("model"))
				{
					const std::string assetPath = entityJson.at("model").get<std::string>();
					auto& model = entity->AddComponent<ModelComponent>();					
					model.model = std::make_shared<Model>(assetPath);
				}

				if (entityJson.contains("light"))
				{
					const json& lightJson = entityJson.at("light");
					auto& light = entity->AddComponent<LightComponent>();
					const int type = lightJson.at("type").get<int>();
					if (type < static_cast<int>(LightType::Point) || type >= static_cast<int>(LightType::Count))
					{
						log.Error("[SCENE SERIALIZER] LIGHT TYPE INVALID");
						return false;
					}						
					light.type = static_cast<LightType>(type);
					light.ambient = ReadVec3(lightJson.at("ambient"));
					light.diffuse = ReadVec3(lightJson.at("diffuse"));
					light.specular = ReadVec3(lightJson.at("specular"));
					light.constant = lightJson.at("constant").get<float>();
					light.linear = lightJson.at("linear").get<float>();
					light.quadratic = lightJson.at("quadratic").get<float>();
					light.innerCutoff = lightJson.at("innerCutoff").get<float>();
					light.outerCutoff = lightJson.at("outerCutoff").get<float>();
				}

				loadedEntities.push_back(std::move(entity));
			}

			std::unordered_set<std::uint32_t> validated;
			for (const auto& [savedId, parentId] : parents)
			{
				std::unordered_set<std::uint32_t> chain;
				std::optional<std::uint32_t> current = savedId;
				while (current && !validated.count(*current))
				{
					if (!chain.insert(*current).second)
						throw std::runtime_error("Cycle in entity hierarchy");
					const auto it = parents.find(*current);
					if (it == parents.end())
						throw std::runtime_error("Missing parent entity");
					current = it->second;
				}
				validated.insert(chain.begin(), chain.end());
			}

			if (version == 2)
			{
				for (const json& entityJson : root.at("entities"))
				{
					const auto savedId = readId(entityJson.at("id"));
					if (const auto parentId = parents.at(savedId))
					{
						Entity* child = savedEntities.at(savedId);
						Entity* parent = savedEntities.at(*parentId);
						child->SetParent(parent->GetID());
						parent->AddChild(child->GetID());
					}
				}
			}

			const auto sceneName = root.at("sceneName").get<std::string>();
			m_scene.ReplaceEntities(std::move(loadedEntities));

			std::string msg{"[SCENE SERIALIZER] LOADED "};
			msg += sceneName;

			log.Info(msg);
			return true;
		}
		catch (const std::exception& e)
		{
			std::string msg{ "[SCENE SERIALZIER] LOAD FAILED: " };
			msg += e.what();
			log.Error(msg);
			return false;
		}
	}
}
