#ifndef VIEWPORT_PANEL_H
#define VIEWPORT_PANEL_H

#include <editor_component.h>
#include <eng/scene/scene.h>
#include <eng/camera/camera.h>
#include <eng/renderer/viewport.h>

namespace eng
{
	class ViewportPanel final : public IEditorComponent
	{
	public:
		explicit ViewportPanel(Scene& scene, Viewport& viewport) : m_scene(scene), m_viewport(viewport) {}
		bool Init(EngineContext& ctx) override;
		void Update(float dt) override;
		void Draw() override;
		void Destroy() override {}

	private:
		void UpdateCamera(float dt);
		EngineContext* m_engine = nullptr;
		Scene& m_scene;
		Viewport& m_viewport;

		bool m_focused = false;
	};
}
#endif
