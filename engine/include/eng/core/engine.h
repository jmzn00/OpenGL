#ifndef ENGINE_H
#define ENGINE_H
#include <memory>

#include <eng/core/engine.h>
#include <eng/core/engine_context.h>
#include <eng/core/application.h>
#include <eng/graphics/graphics_api.h>
#include <eng/graphics/shader_program.h>
#include <eng/core/logger.h>
#include <glad/glad.h>

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
	public:
		bool Init(int width, int height);
		void Run();
		void Destroy();

		void SetApplication(Application* app);
		Application* GetApplication();
	private:
		GLFWwindow* m_window = nullptr;

		GraphicsAPI m_graphicsApi;
		Logger m_logger;
		std::unique_ptr<Application> m_application;
	};
}
#endif // !ENGINE_H