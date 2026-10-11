#include <iostream>
#include <eng/core/engine.h>
#include <filesystem>
#include <eng/util/stb_image.h>
#include <eng/math/math.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <vector>

#include <eng/camera/camera.h>
#include <eng/graphics/light/light.h>

#include <eng/entity/entity.h>
#include <eng/renderer/vertex_layout.h>
#include <eng/renderer/mesh.h>

#include <eng/profiler/profiler.h>

namespace eng
{	void Engine::FrameBufferSizeCallback(GLFWwindow* window, int w, int h)
    {
        auto* engine =
            static_cast<Engine*>(glfwGetWindowUserPointer(window));

        if (!engine)
        {
            std::cout << "ENGINE::FRAME_BUFFER_SIZE_CALLBACK:: ENGINE NULL";
            return;
        }
        engine->m_window->SetSize(static_cast<uint32_t>(w), static_cast<uint32_t>(h));           

        engine->m_context->WindowResizeEvents().Publish(
            {
                static_cast<uint32_t>(w),
                static_cast<uint32_t>(h)
            });
    }
    void Engine::ScrollCallback(GLFWwindow* window, double xo, double yo)
    {
        auto* engine =
            static_cast<Engine*>(glfwGetWindowUserPointer(window));
        if (!engine)
        {
            std::cout << "ENGINE::SCROLL_CALLBACK:: ENGINE NULL";
            return;
        }
        engine->m_input.AddScroll(xo, yo);
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
            "ENG",
            nullptr,
            nullptr
        );
        if (!window)
        {
            std::cerr << "Failed to create GLFW window\n";
            return false;
        } 
        glfwMakeContextCurrent(window);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize GLAD\n";
            return false;
        } 
        glfwSetWindowUserPointer(window, this);

        m_window = std::make_unique<Window>
            (window, static_cast<uint32_t>(width), static_cast<uint32_t>(height));        
        
        glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
        glfwSetScrollCallback(window, ScrollCallback);

        if (!m_graphicsApi.Init())
        {
            return false;
        }
        if (!m_input.Init(window))
        {
            return false;
        }                

        m_shaderLibrary.Init();
        m_renderer = std::make_unique<Renderer>(m_graphicsApi);
        m_context = std::make_unique<EngineContext>
            (*m_window, m_logger, m_graphicsApi, m_input, *m_renderer);
        

        return m_application->Init(*m_context);
	}
	void Engine::Run()
	{                
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);        

        int width, height, nrChannels;
        unsigned char* data = stbi_load(ENGINE_ASSET_DIR "/textures/container.jpg"
            , &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }        
        else
        {
            std::cout << "Failed to load texture\n";
        }
        stbi_image_free(data);

        unsigned int texture2;
        glGenTextures(1, &texture2);
        glBindTexture(GL_TEXTURE_2D, texture2);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_set_flip_vertically_on_load(true);
        data = stbi_load(ENGINE_ASSET_DIR "/textures/awesomeface.png", &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture\n";
        }
        stbi_image_free(data);
        
        m_graphicsApi.SetClearColor(0.5, 0.5, 0.5, 1);        

        while (!m_application->NeedsToBeClosed())
        {                           
            Profiler::Get().BeginFrame();

            m_graphicsApi.ClearBuffers();
            glfwPollEvents();
            m_input.Update(m_window->GetNativeWindow());
            m_time.Update();
            m_application->Update(m_time.Delta());

            glfwSwapBuffers(m_window->GetNativeWindow());

            Profiler::Get().EndFrame();
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
            glfwDestroyWindow(m_window->GetNativeWindow());
            m_window = nullptr;
        }                
        glfwTerminate();
	}
	void Engine::SetApplication(std::unique_ptr<Application> app)
	{
		m_application = std::move(app);
	}
	Application* Engine::GetApplication()
	{
		return m_application.get();
	}
}