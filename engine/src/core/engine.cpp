#include <eng/core/engine.h>
#include <eng/core/engine_context.h>
#include <iostream>

namespace eng
{	
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
        EngineContext ctx{ m_window , m_logger};
        return m_application->Init(ctx);
	}
	void Engine::Run()
	{        
        while (!m_application->NeedsToBeClosed())
        {            
            glClear(GL_COLOR_BUFFER_BIT);

            glfwPollEvents();

            m_application->Update(0);

            glfwSwapBuffers(m_window);
        }
	}
	void Engine::Destroy()
	{
        if (m_application)
        {
            m_application->Destroy();
            m_application.reset();
        }
        if (m_window)
        {
            glfwDestroyWindow(m_window);
            m_window = nullptr;
        }                
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