#ifndef SCENE_H
#define SCENE_H
#include <eng/entity/entity.h>
#include <eng/entity/components.h>
#include <eng/camera/camera.h>
#include <eng/core/engine_context.h>
#include <eng/renderer/render_queue.h>
#include <eng/graphics/framebuffer.h>

#include <vector>
#include <string>
#include <memory>

namespace eng
{
	class Scene
	{
	public:
		Scene(EngineContext& ctx, const std::string& name);
		Scene(const Scene&) = delete;
		Scene& operator=(const Scene&) = delete;

		void Update(float dt);
		void Render(Camera& camera, Framebuffer& scene, Framebuffer& output) const;

		Entity& CreateEntity();
		Entity& CreateEntity(const std::string& name);
		void ReplaceEntities(std::vector<std::unique_ptr<Entity>> entities);
		void ClearEntities();


		Entity* FindEntityByName(const std::string_view name) const;
		Entity* FindEntityById(const std::uint32_t id) const;

		bool SetParent(std::uint32_t childId, std::optional<std::uint32_t> parentId);
		glm::mat4 GetWorldTransform(const Entity& entity) const;

		Camera& GetMainCamera()
		{
			return m_mainCamera;
		}
		const std::string& GetName() const
		{
			return m_name;
		}
		void SetName(const std::string& name)
		{
			m_name = name;
		}
		
		const std::vector<std::unique_ptr<Entity>>& GetEntities() const;
	private:
		std::vector<std::unique_ptr<Entity>> m_entities{};
		RenderQueue m_renderQueue{ };
		EngineContext& m_engineContext;
		Camera m_mainCamera{};
		std::string m_name;
	};
}
#endif // !SCENE_H
