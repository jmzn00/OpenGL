#include "engine.h"
#include "engine_context.h"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>

namespace eng
{
	Engine& Engine::GetInstance()
	{
		static Engine instance;
		return instance;
	}
	bool Engine::Init(int width, int height)
	{
        if (!m_application)
        {
            std::cerr << "ENGINE::INIT: NO APPLICATION";
            return false;
        }

        if (!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW\n";
            return false;
        }

        GLFWwindow* window = glfwCreateWindow(
            width,
            height,
            "OpenGL",
            nullptr,
            nullptr
        );

        if (!window)
        {
            std::cerr << "Failed to create GLFW window\n";
            glfwTerminate();
            return false;
        }
        m_window = window;
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize GLAD\n";
            glfwTerminate();
            return false;
        }
        //std::cout << "OpenGL version: "
        //    << glGetString(GL_VERSION)
        //    << '\n';
        EngineContext ctx{ m_window };
        return m_application->Init(ctx);
	}
	void Engine::Run()
	{        
        while (!glfwWindowShouldClose(m_window))
        {
            glClear(GL_COLOR_BUFFER_BIT);

            glfwPollEvents();

            m_application->Update(0);

            glfwSwapBuffers(m_window);
        }
	}
	void Engine::Destroy()
	{
        m_application->Destroy();
        SetApplication(nullptr);

        glfwDestroyWindow(m_window);
        glfwTerminate();
	}
	void Engine::SetApplication(Application* app)
	{
		m_application.reset(app);
	}
	Application* Engine::GetApplication()
	{
		return m_application.get();
	}
}