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
            "cmde",
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
        m_window = new Window{ window, static_cast<uint32_t>(width)
            , static_cast<uint32_t>(height) };
        
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
        EngineContext ctx{ window , m_logger, m_graphicsApi, m_input};

        return m_application->Init(ctx);
	}
	void Engine::Run()
	{        
        float vertices[] =
        {
            // positions              // normals           // tex coords

            // Front face (+Z)
            -0.5f, -0.5f,  0.5f,      0,0,1,              0,0,
             0.5f, -0.5f,  0.5f,      0,0,1,              1,0,
             0.5f,  0.5f,  0.5f,      0,0,1,              1,1,
            -0.5f,  0.5f,  0.5f,      0,0,1,              0,1,

            // Back face (-Z)
             0.5f, -0.5f, -0.5f,      0,0,-1,             0,0,
            -0.5f, -0.5f, -0.5f,      0,0,-1,             1,0,
            -0.5f,  0.5f, -0.5f,      0,0,-1,             1,1,
             0.5f,  0.5f, -0.5f,      0,0,-1,             0,1,

             // Left face (-X)
             -0.5f, -0.5f, -0.5f,     -1,0,0,              0,0,
             -0.5f, -0.5f,  0.5f,     -1,0,0,              1,0,
             -0.5f,  0.5f,  0.5f,     -1,0,0,              1,1,
             -0.5f,  0.5f, -0.5f,     -1,0,0,              0,1,

             // Right face (+X)
              0.5f, -0.5f,  0.5f,      1,0,0,              0,0,
              0.5f, -0.5f, -0.5f,      1,0,0,              1,0,
              0.5f,  0.5f, -0.5f,      1,0,0,              1,1,
              0.5f,  0.5f,  0.5f,      1,0,0,              0,1,

              // Top face (+Y)
              -0.5f,  0.5f,  0.5f,      0,1,0,              0,0,
               0.5f,  0.5f,  0.5f,      0,1,0,              1,0,
               0.5f,  0.5f, -0.5f,      0,1,0,              1,1,
              -0.5f,  0.5f, -0.5f,      0,1,0,              0,1,

              // Bottom face (-Y)
              -0.5f, -0.5f, -0.5f,      0,-1,0,             0,0,
               0.5f, -0.5f, -0.5f,      0,-1,0,             1,0,
               0.5f, -0.5f,  0.5f,      0,-1,0,             1,1,
              -0.5f, -0.5f,  0.5f,      0,-1,0,             0,1,
        };
        unsigned int indices[] =
        {
            // Front
            0, 1, 2,
            2, 3, 0,

            // Back
            4, 5, 6,
            6, 7, 4,

            // Left
            8, 9, 10,
            10, 11, 8,

            // Right
            12, 13, 14,
            14, 15, 12,

            // Top
            16, 17, 18,
            18, 19, 16,

            // Bottom
            20, 21, 22,
            22, 23, 20
        };
        std::vector<glm::vec3> cubes
        {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(2.0f, 5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f, -3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f, 2.0f, -2.5f),
            glm::vec3(1.5f, 0.2f, -1.5f),
            glm::vec3(-1.3f, 1.0f, -1.5f),
        };
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

        Camera camera{};
        camera.SetViewportSize(m_window->GetWidth(), m_window->GetHeight());
                                
        unsigned int VAO, VBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float)
            , (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float)
            , (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        unsigned int EBO;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        ShaderProgram shaderProgram(ENGINE_ASSET_DIR "/shaders/vert.vert", 
                                    ENGINE_ASSET_DIR "/shaders/frag.frag"); 

        unsigned int lightVAO;
        glGenVertexArrays(1, &lightVAO);
        glBindVertexArray(lightVAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindVertexArray(0);

        ShaderProgram lightShader(ENGINE_ASSET_DIR "/shaders/lightSource/lightSource.vert",
                                  ENGINE_ASSET_DIR "/shaders/lightSource/lightSource.frag");

        m_graphicsApi.BindShaderProgram(&lightShader);

        unsigned int lightModelLoc = lightShader.GetUniform("model");
        unsigned int lightViewLoc = lightShader.GetUniform("view");
        unsigned int lightProjectionLoc = lightShader.GetUniform("projection");

        glm::mat4 lightModel{ 1.0 };
        glm::vec3 lightPos{ 2.0f, 0.0f, 0.0f };
        lightModel = glm::translate(lightModel, lightPos);
        lightModel = glm::scale(lightModel, glm::vec3(0.5f, 0.5f, 0.5));

        glUniformMatrix4fv(lightModelLoc, 1, GL_FALSE, glm::value_ptr(lightModel));
        glUniformMatrix4fv(lightViewLoc, 1, GL_FALSE, glm::value_ptr(camera.GetView()));
        glUniformMatrix4fv(lightProjectionLoc, 1, GL_FALSE, glm::value_ptr(camera.GetProjection()));

        m_graphicsApi.BindShaderProgram(&shaderProgram);

        shaderProgram.SetVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
        shaderProgram.SetVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

        glUniform1i(glGetUniformLocation(shaderProgram.GetId(), "texture1"), 0);
        glUniform1i(glGetUniformLocation(shaderProgram.GetId(), "texture2"), 1);        
        
        unsigned int modelLoc = shaderProgram.GetUniform("model");
        unsigned int viewLoc = shaderProgram.GetUniform("view");
        unsigned int projectionLoc = shaderProgram.GetUniform("projection");               

        glm::vec3 cameraPos = camera.GetPosition();
        glm::vec3 cameraFront = camera.GetForward();
        glm::vec3 cameraUp = camera.GetUp();

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 projection = camera.GetProjection();
        glm::mat4 view = camera.GetView();

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.GetView()));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera.GetProjection()));

        float mixAmount = 0.5f;

        const float sensitivity = 0.1;
        float yaw = -90.0f;
        float pitch = 0.0f;
        
        m_graphicsApi.SetClearColor(0, 0, 0, 1);

        while (!m_application->NeedsToBeClosed())
        {                           
            glm::vec2 delta = m_input.MouseDelta();
            yaw += delta.x * sensitivity;
            pitch -= delta.y * sensitivity;
            pitch = math::clamp(pitch, -89.0f, 89.0f);
                       
            float cameraSpeed = 1 * m_time.Delta();;
            glm::vec3 cameraPos = camera.GetPosition();

            if (m_input.IsKeyPressed(GLFW_KEY_W))
                cameraPos += cameraSpeed * camera.GetFlatForward();
            if (m_input.IsKeyPressed(GLFW_KEY_S))
                cameraPos -= cameraSpeed * camera.GetFlatForward();
            if (m_input.IsKeyPressed(GLFW_KEY_A))
                cameraPos -= cameraSpeed * camera.GetRight();
            if (m_input.IsKeyPressed(GLFW_KEY_D))
                cameraPos += cameraSpeed * camera.GetRight();

            camera.Look(pitch, yaw);
            camera.MoveTo(cameraPos);
            

            view = camera.GetView();
            projection = camera.GetProjection();

            //for (int i = 0; i < cubes.size(); i++)
            //{
            //    glm::mat4 model = glm::mat4(1.0f);
            //    model = glm::translate(model, cubes[i]);
            //
            //    float angle = 20.0f * i;
            //    if (i % 3 == 0)
            //    {
            //        angle = m_time.Elapsed() * 25.0f;
            //    }
            //    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3, 0.5f));
            //    
            //    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            //    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            //}   

            //if (m_input.IsKeyPressed(GLFW_KEY_UP))
            //{
            //    mixAmount += m_time.Delta() * 2.0f;
            //}
            //else if (m_input.IsKeyPressed(GLFW_KEY_DOWN))
            //{
            //    mixAmount -= m_time.Delta() * 2.0f;
            //}
            //mixAmount = math::clamp(mixAmount, 0.0f, 1.0f);
            //shaderProgram.SetFloat("mixAmount", mixAmount);            

            float radius = 5.0f;
            lightPos.x = cos(m_time.Elapsed()) * radius;
            lightPos.z = sin(m_time.Elapsed()) * radius;
            lightModel = glm::mat4(1.0);
            lightModel = glm::translate(lightModel, lightPos);
            lightModel = glm::scale(lightModel, glm::vec3(0.5, 0.5, 0.5));

            m_graphicsApi.ClearBuffers();
            m_graphicsApi.BindShaderProgram(&shaderProgram);

            shaderProgram.SetVec3("viewPos", camera.GetPosition());
            shaderProgram.SetVec3("lightPos", lightPos);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture2);

            glBindVertexArray(VAO);
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);

            m_graphicsApi.BindShaderProgram(&lightShader);  

            glBindVertexArray(lightVAO);
            glUniformMatrix4fv(lightModelLoc, 1, GL_FALSE, glm::value_ptr(lightModel));
            glUniformMatrix4fv(lightViewLoc, 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(lightProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);

            glfwPollEvents();
            m_input.Update(m_window->GetNativeWindow());
            m_time.Update();
            m_application->Update(m_time.Delta());

            glfwSwapBuffers(m_window->GetNativeWindow());
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
	void Engine::SetApplication(Application* app)
	{
		m_application.reset(app);
	}
	Application* Engine::GetApplication()
	{
		return m_application.get();
	}
}