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
    Entity* Scene::FindEntityByName(const std::string_view name) const
    {
        for (auto& entityPtr : m_entities)
        {
            if (entityPtr->GetName() == name)
                return entityPtr.get();
        }
        return nullptr;
    }
    Entity* Scene::FindEntityById(std::uint32_t id) const
    {
        for (auto& entityPtr : m_entities)
        {
            if (entityPtr->GetID() == id)
                return entityPtr.get();
        }
        return nullptr;
    }
    void Scene::Render(Camera& camera) const
    {
        if (m_entities.empty())
            return;
    
        Renderer::Get().BeginScene(camera);
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
	void Scene::Update(float dt)
	{        
	}
    const std::vector<std::unique_ptr<Entity>>& Scene::GetEntities() const
    {
        return m_entities;
    }
}