#ifndef ENGINE_H
#define ENGINE_H
#include <memory>

#include "application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace eng
{
	class Engine
	{
	public:
		static Engine& GetInstance();
	private:
		Engine() = default;
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
		GLFWwindow* m_window;
		std::unique_ptr<Application> m_application;
	};
}
#endif // !ENGINE_H