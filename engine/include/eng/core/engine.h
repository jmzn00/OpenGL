#ifndef ENGINE_H
#define ENGINE_H
#include <memory>
#include <eng/core/engine_context.h>
#include <eng/core/application.h>
#include <eng/graphics/graphics_api.h>
#include <eng/graphics/shader_program.h>
#include <eng/core/logger.h>
#include <glad/glad.h>
#include <eng/input/input.h>
#include <eng/time/time.h>
#include <eng/window/window.h>
#include <eng/renderer/renderer.h>

namespace eng
{
	class Engine
	{
	public:		
		Engine()
		{
		
		}
	private:		
		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;
		Engine& operator=(const Engine&) = delete;
		Engine& operator=(Engine&&) = delete;

		static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
		static void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
	public:
		bool Init(int width, int height);
		void Run();
		void Destroy();
		void SetApplication(std::unique_ptr<Application> app);
		Application* GetApplication();
	private:

		std::unique_ptr<EngineContext> m_context;
		std::unique_ptr<Application> m_application;
		std::unique_ptr<Renderer> m_renderer;
		std::unique_ptr<Window> m_window;

		Time m_time{};
		Input m_input{};
		GraphicsAPI m_graphicsApi;
		Logger m_logger;
	};
}
#endif // !ENGINE_H