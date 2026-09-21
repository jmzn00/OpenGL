#ifndef ENGINE_H
#define ENGINE_H
#include <memory>

#include <eng/core/application.h>
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
		Logger m_logger;
		GLFWwindow* m_window = nullptr;
		std::unique_ptr<Application> m_application;
	};
}
#endif // !ENGINE_H