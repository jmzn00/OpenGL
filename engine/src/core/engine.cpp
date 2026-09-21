#include <iostream>
#include <eng/core/engine.h>
#include <filesystem>

namespace eng
{	
    static std::filesystem::path shaderDirectory =
        std::filesystem::path(ENGINE_ASSET_DIR) / "shaders";

    void framebuffer_size_callback(GLFWwindow* window, int w, int h)
    {
        glViewport(0, 0, w, h);
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
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
        glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);


        GLFWwindow* window = glfwCreateWindow(
            width,
            height,
            "cmde",
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
        glfwFocusWindow(m_window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize GLAD\n";
            glfwTerminate();
            return false;
        }
        glViewport(0, 0, width, height);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        //std::cout << "OpenGL version: "
        //    << glGetString(GL_VERSION)
        //    << '\n';        
        EngineContext ctx{ m_window , m_logger, m_graphicsApi};
        return m_application->Init(ctx);
	}
	void Engine::Run()
	{        
        float vertices[] =
        {    //positions        // colors
            -1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
             0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
            -0.5f,0.75f, 0.0f,  0.0f, 0.0f, 1.0f
        };
        unsigned int indices[] = 
        {
            0, 1, 2,                
        };        

        unsigned int VAO, VBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float)
            , (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        unsigned int EBO;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        ShaderProgram shaderProgram(ENGINE_ASSET_DIR "/shaders/vert.vert", 
                                    ENGINE_ASSET_DIR "/shaders/frag.frag");
        
        m_graphicsApi.SetClearColor(0.5, 0.5, 0.5, 1);
        
        while (!m_application->NeedsToBeClosed())
        {            
            m_graphicsApi.ClearBuffers();                        
            m_graphicsApi.BindShaderProgram(&shaderProgram);
            
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);

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