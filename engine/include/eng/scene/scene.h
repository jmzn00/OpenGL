#ifndef SCENE_H
#define SCENE_H
#include <eng/entity/entity.h>
#include <eng/entity/components.h>
#include <eng/camera/camera.h>
#include <eng/core/engine_context.h>
#include <eng/renderer/render_queue.h>

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
		Camera& GetMainCamera();

		Entity& CreateEntity();
		Entity& CreateEntity(const std::string& name);

		Entity* FindEntityByName(const std::string_view name) const;
		Entity* FindEntityById(const std::uint32_t id) const;

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
