#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <eng/core/log.h>
#include <eng/core/engine_context.h>
#include <editor_component.h>

#include "editor_context.h"

#include <eng/command/command_executor.h>
#include <eng/scene/scene_serializer.h>
#include <eng/scene/scene.h>

namespace eng
{
	class Toolbar : public IEditorComponent
	{
	public:
		Toolbar(CommandExecutor& commandExecutor, SceneSerializer& sceneSerializer, Scene& scene);
		bool Init(EngineContext& ctx) override;
		void Update(float dt) override;
		void Draw() override;
		void Destroy() override;
	private:
		void DrawNewScenePopup();
		void DrawOpenScenePopup();

		CommandExecutor& m_commandExecutor;		
		SceneSerializer& m_sceneSerialzier;
		Scene& m_scene;

		bool m_showNewScenePopup = false;
		bool m_showOpenScenePopup = false;
		char m_newSceneName[128] = {};
		Logger* m_logger;
	};
}
#endif