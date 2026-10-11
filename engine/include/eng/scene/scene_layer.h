#ifndef SCENE_LAYER_H
#define SCENE_LAYER_H

#include "editor_context.h"
#include <eng/core/engine_context.h>
#include <eng/core/layer.h>
#include <eng/camera/camera.h>
#include <eng/scene/scene.h>

namespace eng
{
	class SceneLayer final : public Layer
	{
	public:
		SceneLayer(
			EngineContext& ctx,
			Scene& scene,
			EditorContext& editorContext);

		void OnAttach() override;
		void Update(float dt) override;

	private:
		void UpdateCamera(float dt);
		
		EngineContext& m_engineContext;
		Scene& m_scene;
		EditorContext& m_editorContext;

		Camera m_editorCamera{};
		Input* m_input = nullptr;
	};
}

#endif // !SCENE_LAYER_H
