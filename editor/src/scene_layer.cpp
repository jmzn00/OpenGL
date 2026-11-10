#include "scene_layer.h"

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
				m_cameraWidth = e.Width;
				m_cameraHeight = e.Height;
			});
	}
	void SceneLayer::Update(float dt)
	{		
		Viewport& viewport = m_editorContext.GetSceneViewport();

		UpdateCamera(dt, m_editorContext.GetSceneViewport());
		viewport.ApplyPendingResize();

		const uint32_t width = viewport.GetWidth();
		const uint32_t height = viewport.GetHeight();

		if (width != m_cameraWidth || height != m_cameraHeight)
		{
			m_editorCamera.SetViewportSize(width, height);
			m_cameraWidth = width;
			m_cameraHeight = height;
		}
		viewport.SetRenderArea();
		
		m_scene.Update(dt);
		m_scene.Render(m_editorCamera
			, viewport.GetSceneTarget(), viewport.GetOutputTarget());
	}
	void SceneLayer::UpdateCamera(float dt, Viewport& viewport)
	{	
		if (!viewport.GetFocused())
			return;

		const float cameraSpeed = 1.0f * dt;
		const float rotationSensitivity = 0.1f;

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

		const glm::vec2 mouseDelta = m_input->MouseDelta();

		m_editorCamera.Yaw +=
			mouseDelta.x * rotationSensitivity;

		m_editorCamera.Pitch -=
			mouseDelta.y * rotationSensitivity;

		m_editorCamera.Pitch = glm::clamp(
			m_editorCamera.Pitch,
			-89.0f,
			89.0f);

		m_editorCamera.Look(
			m_editorCamera.Pitch,
			m_editorCamera.Yaw);
	}
}