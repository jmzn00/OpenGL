#include <eng/scene/scene.h>
#include <eng/renderer/renderer.h>
#include <eng/renderer/default_meshes.h>

namespace eng
{
    std::vector<float> vertices =
    {
        // positions              // normals           // tex coords

        // Front face (+Z)
        -0.5f, -0.5f,  0.5f,      0,0,1,              0,0,
         0.5f, -0.5f,  0.5f,      0,0,1,              1,0,
         0.5f,  0.5f,  0.5f,      0,0,1,              1,1,
        -0.5f,  0.5f,  0.5f,      0,0,1,              0,1,

        // Back face (-Z)
         0.5f, -0.5f, -0.5f,      0,0,-1,             0,0,
        -0.5f, -0.5f, -0.5f,      0,0,-1,             1,0,
        -0.5f,  0.5f, -0.5f,      0,0,-1,             1,1,
         0.5f,  0.5f, -0.5f,      0,0,-1,             0,1,

         // Left face (-X)
         -0.5f, -0.5f, -0.5f,     -1,0,0,              0,0,
         -0.5f, -0.5f,  0.5f,     -1,0,0,              1,0,
         -0.5f,  0.5f,  0.5f,     -1,0,0,              1,1,
         -0.5f,  0.5f, -0.5f,     -1,0,0,              0,1,

         // Right face (+X)
          0.5f, -0.5f,  0.5f,      1,0,0,              0,0,
          0.5f, -0.5f, -0.5f,      1,0,0,              1,0,
          0.5f,  0.5f, -0.5f,      1,0,0,              1,1,
          0.5f,  0.5f,  0.5f,      1,0,0,              0,1,

          // Top face (+Y)
          -0.5f,  0.5f,  0.5f,      0,1,0,              0,0,
           0.5f,  0.5f,  0.5f,      0,1,0,              1,0,
           0.5f,  0.5f, -0.5f,      0,1,0,              1,1,
          -0.5f,  0.5f, -0.5f,      0,1,0,              0,1,

          // Bottom face (-Y)
          -0.5f, -0.5f, -0.5f,      0,-1,0,             0,0,
           0.5f, -0.5f, -0.5f,      0,-1,0,             1,0,
           0.5f, -0.5f,  0.5f,      0,-1,0,             1,1,
          -0.5f, -0.5f,  0.5f,      0,-1,0,             0,1,
    };
    std::vector<unsigned int> indices =
    {
        // Front
        0, 1, 2,
        2, 3, 0,

        // Back
        4, 5, 6,
        6, 7, 4,

        // Left
        8, 9, 10,
        10, 11, 8,

        // Right
        12, 13, 14,
        14, 15, 12,

        // Top
        16, 17, 18,
        18, 19, 16,

        // Bottom
        20, 21, 22,
        22, 23, 20

    };

	Scene::Scene(EngineContext& ctx, const std::string& name)
		: m_engineContext {ctx}, m_name {name}
	{	
        Window& window{ ctx.GetWindow() };

        m_mainCamera.SetViewportSize(window.GetWidth(), window.GetHeight());        

        //auto shader = std::make_shared<ShaderProgram>(ENGINE_ASSET_DIR "/shaders/vert.vert",
        //    ENGINE_ASSET_DIR "/shaders/frag.frag");
        //
        //Entity e{ Primitives::CubeEnt(shader) };
        //e.Transform().Translate(glm::vec3(-2.0f, 0.0f, -5.0f));
        //
        //Entity e2{ Primitives::CubeEnt(shader) };
        //e2.Transform().Translate(glm::vec3(2.0f, 0.0f, -5.0f));
        //
        //m_entities.push_back(e);
        //m_entities.push_back(e2);
	}
	//Entity Scene::CreateEntity()
	//{
	//	
	//}
	//void Scene::DestroyEntity(Entity* entity)
	//{
	//
	//}
    Entity& Scene::CreateEntity()
    {
        m_entities.emplace_back();

        m_entities.back().Transform().Translate(glm::vec3(1.0f, 0.0f, -3.0f));

        return m_entities.back();
    }
    Entity& Scene::CreateEntity(const std::string& name)
    {
        m_entities.emplace_back(name);

        m_entities.back().Transform().Translate(glm::vec3(1.0f, 0.0f, -3.0f));

        return m_entities.back();
    }
    Entity* Scene::FindEntityByName(const std::string_view name)
    {
        for (auto& entity : m_entities)
        {
            if (entity.GetName() == name)
                return &entity;
        }
        return nullptr;
    }
	void Scene::Update(float dt)
	{
        if (m_entities.empty())
            return;

        Renderer::Get().BeginScene(m_mainCamera);
		for (auto& entity : m_entities)
        {
            if (!entity.HasComponent<MeshComponent>())
                continue;

            auto& meshComponent = entity.GetComponent<MeshComponent>();    

            Renderer::Get().Submit(
                { meshComponent.mesh.get()
                , meshComponent.shader.get()
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