#include <eng/scene/scene.h>
#include <eng/renderer/renderer.h>
#include <iostream>

#include <eng/profiler/profiler.h>

#include <algorithm>
#include <unordered_set>

namespace eng
{
    Scene::Scene(EngineContext& ctx, const std::string& name)
        : m_engineContext{ ctx }, m_name{ name }
    {
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
    void Scene::ReplaceEntities(std::vector<std::unique_ptr<Entity>> entities)
    {
        m_entities = std::move(entities);
    }
    void Scene::ClearEntities()
    {
        m_entities.clear();
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
    bool Scene::SetParent(std::uint32_t childId
        , std::optional<std::uint32_t> parentId)
    {
        Entity* child = FindEntityById(childId);
        if (child == nullptr)
            return false;

        Entity* parent = nullptr;
        if (parentId.has_value())
        {
            parent = FindEntityById(parentId.value());
            if (parent == nullptr)
                return false;

            std::unordered_set<std::uint32_t> visited;
            Entity* ancestor = parent;

            while (ancestor != nullptr)
            {
                const auto id = ancestor->GetID();
                if (id == childId || !visited.insert(id).second)
                    return false;

                const auto ancestorParent = ancestor->GetParent();
                if (!ancestorParent.has_value())
                    break;

                ancestor = FindEntityById(ancestorParent.value());
                if (!ancestor)
                    return false;
            }
        }    
        if (child->m_relationship.parent == parentId)
            return true;

        if (const auto oldParentId = child->m_relationship.parent)
        {
            if (Entity* oldParent = FindEntityById(oldParentId.value()))
            {
                auto& children = oldParent->m_relationship.children;
                children.erase(
                    std::remove(children.begin(), children.end(), childId),
                    children.end());
            }
        }
        child->m_relationship.parent = parentId;

        if (parent)
        {
            auto& children = parent->m_relationship.children;

            if (std::find(children.begin(), children.end(), childId)
                == children.end())
            {
                children.push_back(childId);
            }
        }
        return true;
    }
    glm::mat4 Scene::GetWorldTransform(const Entity& entity) const
    {
        const glm::mat4 local = entity.Transform().GetTransform();

        if (const auto parentId = entity.GetParent())
        {
            if (const Entity* parent = FindEntityById(*parentId))
                return GetWorldTransform(*parent) * local;
        }

        return local;
    }
    void Scene::Render(Camera& camera, Framebuffer& scene, Framebuffer& output) const
    {		
        Renderer::Get().BeginScene(camera);
        for (auto& entityPtr : m_entities)
        {
            Entity& entity = *entityPtr;
    
            if (entity.HasComponent<LightComponent>())
            {
                Renderer::Get().SubmitLight(entity);
            }
            if (entity.HasComponent<ModelComponent>())
            {
                auto& mc = entity.GetComponent<ModelComponent>();
                if (mc.model == nullptr)
                    break;

                for (auto& part : mc.model->GetParts())
                {
                    Renderer::Get().Submit(
                        {
                            part.mesh.get(),
                            part.material.get(),
                            GetWorldTransform(entity),
                            &entity
                        });
                }
            }
    
            if (!entity.HasComponent<MeshComponent>())
                continue;
    
            auto& meshComponent = entity.GetComponent<MeshComponent>();
            if (meshComponent.mesh == nullptr || meshComponent.material == nullptr)
                continue;
    
            Renderer::Get().Submit(
                { meshComponent.mesh.get()
                , meshComponent.material.get()
                , GetWorldTransform(entity)
                , &entity
                });
        }
        Renderer::Get().Render(scene, output);
        Renderer::Get().EndScene();                
    }
	void Scene::Update(float)
	{        
	}
    const std::vector<std::unique_ptr<Entity>>& Scene::GetEntities() const
    {
        return m_entities;
    }
}
