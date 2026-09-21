cmake_minimum_required(VERSION 3.20)

project(OpenGL LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GLFW
add_subdirectory(dependencies/glfw-3.5.1)

# GLAD
add_library(glad
    dependencies/glad/src/glad.c
)

target_include_directories(glad PUBLIC
    dependencies/glad/include
)

add_library(imgui
    dependencies/imgui/imgui.cpp
    dependencies/imgui/imgui_draw.cpp
    dependencies/imgui/imgui_tables.cpp
    dependencies/imgui/imgui_widgets.cpp
    dependencies/imgui/imgui_impl_glfw.cpp
    dependencies/imgui/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
    dependencies/imgui
)

target_compile_definitions(imgui PRIVATE
    GLFW_INCLUDE_NONE
)

target_link_libraries(imgui PRIVATE
    glfw
    opengl32
)

add_executable(OpenGL
    engine/apps/editor/src/main.cpp
    engine/src/core/engine.cpp
    engine/src/core/application.cpp
    engine/src/render/render_queue.cpp
    engine/apps/editor/src/editor.cpp
    engine/apps/editor/ui/editor_ui.cpp
    engine/apps/editor/panels/console/console.cpp
    engine/src/core/logger.cpp    
    engine/src/command/command_registry.cpp
    engine/src/command/application_quit_command.cpp
)
target_compile_definitions(OpenGL PRIVATE GLFW_INCLUDE_NONE)
target_include_directories(OpenGL PRIVATE
    engine/include
    engine/apps/editor/src
    engine/apps/editor/ui
    engine/apps/editor/panels
)

target_link_libraries(OpenGL PRIVATE
    glad
    glfw
    opengl32
    imgui
)