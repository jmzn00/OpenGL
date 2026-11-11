#include <eng/command/commands/entity_create_command.h>
#include <eng/graphics/material/material.h>
#include <eng/debug/assert.h>
#include <eng/graphics/texture/texture.h>
#include <eng/renderer/model.h>

#include <eng/asset/asset_manager.h>

namespace eng
{
	EntityCreateCommand::EntityCreateCommand(Scene& scene)
		: m_scene {scene}
	{
	}
	std::string_view EntityCreateCommand::Name() const
	{
		return "ent.create";
	}
	std::string_view EntityCreateCommand::Help() const
	{
		return "Usage: ent.create <cube / light>";
	}

	CommandResult EntityCreateCommand::Execute(
		const std::vector<std::string_view>& arguments,
		CommandContext&)
	{		
		ShaderLibrary& shaders = AssetManager::Get().Shaders();
		MeshLibrary& meshes = AssetManager::Get().Meshes();
		MaterialLibrary& materials = AssetManager::Get().Materials();

		if (arguments.empty())
		{
			return { false, "Usage: ent.create <cube / light>" };
		}
		if (arguments[0] == "cube")
		{
			std::string name = arguments.size() > 1 ? std::string(arguments[1]) : "CubeEnt";

			Entity& ent = m_scene.CreateEntity(name);

			auto mat = std::make_shared<Material>(*materials.GetMaterial("Silver"));
			std::shared_ptr<Texture2D> texture =
				std::make_shared<Texture2D>(ENGINE_ASSET_DIR "/textures/container2/container2.png");
			std::shared_ptr<Texture2D> specular =
				std::make_shared<Texture2D>(ENGINE_ASSET_DIR "/textures/container2/container2_specular.png");
			std::shared_ptr<Texture2D> reflection =
				std::make_shared<Texture2D>(ENGINE_ASSET_DIR "/textures/container2/container2_specular.png");

			mat->SetShaderProgram(shaders.GetShader("Default"));
			mat->SetDiffuseTexture(texture);
			mat->SetSpecularMap(specular);
			mat->SetReflectionMap(reflection);
						
			ent.AddComponent<MeshComponent>(meshes.Create("primitives::cube"), mat);

			return { true, "Created ent: " + ent.GetName() + ' ' + std::to_string(ent.GetID()) };
		}
		if (arguments[0] == "light")
		{
			std::string name = arguments.size() > 1 ? std::string(arguments[1]) : "LightEnt";
			Entity& ent = m_scene.CreateEntity(name);

			auto mat = std::make_shared<Material>(*materials.GetMaterial("Default"));
			
			mat->SetShaderProgram(shaders.GetShader("Light"));
			ent.AddComponent<LightComponent>();
			ent.Transform().SetScale(glm::vec3(0.5f));

			ent.AddComponent<MeshComponent>(meshes.Create("primitives::cube"), mat);

			return { true, "Created ent: " + ent.GetName() + ' ' + std::to_string(ent.GetID())};
			
		}
		if (arguments[0] == "pyramid")
		{
			std::string name = arguments.size() > 1 ? std::string(arguments[1]) : "PyramidEnt";

			Entity& ent = m_scene.CreateEntity(name);

			auto mat = std::make_shared<Material>(*materials.GetMaterial("Silver"));

			mat->SetShaderProgram(shaders.GetShader("Default"));
			ent.AddComponent<MeshComponent>(meshes.Create("primitives::pyramid"), mat);

			return { true, "Created ent: " + ent.GetName() + ' ' + std::to_string(ent.GetID()) };
		}
		if (arguments[0] == "backpack")
		{
			std::string name = arguments.size() > 1 ? std::string(arguments[1]) : "BackpackEnt";

			Entity& ent = m_scene.CreateEntity(name);

			auto& modelComp = ent.AddComponent<ModelComponent>();
			modelComp.model = std::make_shared<Model>(ENGINE_ASSET_DIR "/models/backpack/backpack.obj");

			return { true, "Created ent: " + ent.GetName() + ' ' + std::to_string(ent.GetID()) };
		}
		if (arguments[0] == "sponza")
		{
			std::string name = arguments.size() > 1 ? std::string(arguments[1]) : "SponzaEnt";

			Entity& ent = m_scene.CreateEntity(name);

			ent.Transform().SetScale(glm::vec3(0.1, 0.1, 0.1));

			auto& modelComp = ent.AddComponent<ModelComponent>();
			modelComp.model = std::make_shared<Model>(ENGINE_ASSET_DIR "/models/sponza/sponza.obj");

			return { true, "Created ent: " + ent.GetName() + ' ' + std::to_string(ent.GetID()) };
		}
		if (arguments[0] == "grass")
		{
			std::string name = arguments.size() > 1 ? std::string(arguments[1]) : "GrassEnt";

			Entity& ent = m_scene.CreateEntity(name);
           auto mat = std::make_shared<Material>(*materials.GetMaterial("Default"));
			mat->SetDiffuseTexture(std::make_shared<Texture2D>(ENGINE_ASSET_DIR "/textures/grass.png"));
			mat->SetAlphaMode(AlphaMode::Mask);

			ent.AddComponent<MeshComponent>(meshes.Create("primitives::quad"), mat);

			return { true, "Created ent: " + ent.GetName() + ' ' + std::to_string(ent.GetID()) };
		}
		if (arguments[0] == "window")
		{
			std::string name = arguments.size() > 1 ? std::string(arguments[1]) : "WindowEnt";

			Entity& ent = m_scene.CreateEntity(name);
           auto mat = std::make_shared<Material>(*materials.GetMaterial("Default"));
			mat->SetDiffuseTexture(std::make_shared<Texture2D>(ENGINE_ASSET_DIR "/textures/window.png"));
			mat->SetAlphaMode(AlphaMode::Blend);
			ent.AddComponent<MeshComponent>(meshes.Create("primitives::quad"), mat);

			return { true, "Created ent: " + ent.GetName() + ' ' + std::to_string(ent.GetID()) };
		}
		if (arguments[0] == "cwindow")
		{
			std::string name = arguments.size() > 1 ? std::string(arguments[1]) : "CWindowEnt";

			Entity& ent = m_scene.CreateEntity(name);
           auto mat = std::make_shared<Material>(*materials.GetMaterial("Default"));
			mat->SetDiffuseTexture(std::make_shared<Texture2D>(ENGINE_ASSET_DIR "/textures/container_window.png"));
			mat->SetSpecularMap(std::make_shared<Texture2D>(ENGINE_ASSET_DIR "/textures/container2/container2_specular.png"));
			mat->SetAlphaMode(AlphaMode::Blend);
			ent.AddComponent<MeshComponent>(meshes.Create("primitives::quad"), mat);

			return { true, "Created ent: " + ent.GetName() + ' ' + std::to_string(ent.GetID()) };
		}
		return { false, "Usage: ent.create <cube / light>" };
	}
}
