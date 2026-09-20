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

# Our program
add_executable(OpenGL
    main.cpp
    source/engine.cpp
    source/application/application.cpp
    source/render/render_queue.cpp
    source/editor/editor.cpp
    source/editor/ui/editor_ui.cpp
    source/editor/tools/console/console.cpp
    
)
target_compile_definitions(OpenGL PRIVATE GLFW_INCLUDE_NONE)
target_include_directories(OpenGL PRIVATE
    source
)

target_link_libraries(OpenGL PRIVATE
    glad
    glfw
    opengl32
    imgui
)