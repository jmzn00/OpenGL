#include <eng/scene/scene_layer.h>

namespace eng
{
	SceneLayer::SceneLayer(
		EngineContext& ctx, Scene& scene, EditorContext& editorContext)
		: Layer("SceneLayer"), m_engineContext { ctx }
		, m_scene{scene}, m_editorContext{editorContext}
	{		
		ctx.GetLogger().Info("[SceneLayer] Initialized");

		m_input = &ctx.GetInput();
	}
	void SceneLayer::OnAttach()
	{	
		Window& window = m_engineContext.GetWindow();

		m_editorCamera.SetViewportSize(window.GetWidth(), window.GetHeight());
		m_editorCamera.Pitch = -90.0f;
		m_editorCamera.Yaw = 0.0f;

		m_engineContext.WindowResizeEvents().Subscribe(
			[this]
			(const WindowResizeEvent& e)
			{				
				m_editorCamera
					.SetViewportSize(
						e.Width,
						e.Height
					);
			});
	}
	void SceneLayer::Update(float dt)
	{
		UpdateCamera(dt);

		m_scene.Update(dt);
		m_scene.Render(m_editorCamera);
	}
	void SceneLayer::UpdateCamera(float dt)
	{	
		const float cameraSpeed = 1.0f * dt;
		glm::vec3 cameraPosition = m_editorCamera.GetPosition();

		if (m_input->IsKeyPressed(GLFW_KEY_W))
		{
			cameraPosition +=
				cameraSpeed * m_editorCamera.GetFlatForward();
		}

		if (m_input->IsKeyPressed(GLFW_KEY_S))
		{
			cameraPosition -=
				cameraSpeed * m_editorCamera.GetFlatForward();
		}

		if (m_input->IsKeyPressed(GLFW_KEY_D))
		{
			cameraPosition +=
				cameraSpeed * m_editorCamera.GetRight();
		}

		if (m_input->IsKeyPressed(GLFW_KEY_A))
		{
			cameraPosition -=
				cameraSpeed * m_editorCamera.GetRight();
		}

		m_editorCamera.MoveTo(cameraPosition);
	}
}