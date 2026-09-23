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
    dependencies/glm/
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
    engine/apps/editor/ui/panels/console/console.cpp
    engine/src/core/logger.cpp    
    engine/src/core/command_registry.cpp
    engine/apps/editor/commands/application_quit_command.cpp
    engine/src/graphics/graphics_api.cpp
    engine/src/graphics/commands/graphics_set_clear_color_command.cpp
    engine/src/graphics/commands/graphics_set_wireframe_command.cpp
    engine/src/graphics/shader_program.cpp
    engine/src/util/stb_image_implementation.cpp
    engine/src/input/input.cpp
    engine/src/window/window.cpp
    
)
target_compile_definitions(OpenGL PRIVATE
    GLFW_INCLUDE_NONE
    ENGINE_ASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets"
)
target_include_directories(OpenGL PRIVATE
    engine/include
    engine/apps/editor/src
    engine/apps/editor/ui
)

target_link_libraries(OpenGL PRIVATE
    glad
    glfw
    opengl32
    imgui
)
