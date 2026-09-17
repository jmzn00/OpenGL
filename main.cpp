#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include "engine.h"

int main()
{
    eng::Engine& engine = eng::Engine::GetInstance();    
    if (engine.Init(800, 600))
    {
        engine.Run();
    }
    engine.Destroy();
    return 0;
}