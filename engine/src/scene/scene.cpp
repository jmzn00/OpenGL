#include <eng/scene/scene.h>
#include <eng/renderer/renderer.h>
#include <eng/renderer/default_meshes.h>
#include <iostream>

namespace eng
{
    Scene::Scene(EngineContext& ctx, const std::string& name)
        : m_engineContext{ ctx }, m_name{ name }
    {
        Window& window{ ctx.GetWindow() };

        m_mainCamera.SetViewportSize(window.GetWidth(), window.GetHeight());
    }
    Entity& Scene::CreateEntity(const std::string& name)
    {
        m_entities.emplace_back(std::make_unique<Entity>(name));
       
        return *m_entities.back();
    }
    Entity& Scene::CreateEntity()
    {
        return CreateEntity("Unnamed");
    }
    Entity* Scene::FindEntityByName(const std::string_view name)
    {
        for (auto& entityPtr : m_entities)
        {
            if (entityPtr->GetName() == name)
                return entityPtr.get();
        }
        return nullptr;
    }
	void Scene::Update(float dt)
	{
        if (m_entities.empty())
            return;

        Renderer::Get().BeginScene(m_mainCamera);
		for (auto& entityPtr : m_entities)
        {
            Entity& entity = *entityPtr;

            if (entity.HasComponent<LightComponent>())
            {
                Renderer::Get().SubmitLight(entity);
            }

            if (!entity.HasComponent<MeshComponent>())
                continue;

            auto& meshComponent = entity.GetComponent<MeshComponent>();    

            Renderer::Get().Submit(
                { meshComponent.mesh.get()
                , meshComponent.material.get()
                , &entity.Transform()
                });
        }
        Renderer::Get().Render();

        Renderer::Get().EndScene();
	}
	Camera& Scene::GetMainCamera()
	{
		return m_mainCamera;
	}
}