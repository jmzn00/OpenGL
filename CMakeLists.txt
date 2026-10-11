cmake_minimum_required(VERSION 3.20)

project(OpenGL LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(dependencies/glfw-3.5.1)

add_library(glad
    dependencies/glad/src/glad.c
)

target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm
)

set(IMGUI_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui-docking
)

add_library(imgui
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp    
)

target_include_directories(imgui PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
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
    engine/apps/editor/src/editor.cpp
    engine/apps/editor/src/editor_layer.cpp

    engine/apps/editor/ui/panels/console/console.cpp
    engine/apps/editor/ui/panels/inspector/inspector.cpp
    engine/apps/editor/ui/panels/properties/properties_panel.cpp
    engine/apps/editor/ui/panels/toolbar/toolbar.cpp
    engine/apps/editor/ui/panels/profiler/profiler_panel.cpp

    engine/apps/editor/commands/application_quit_command.cpp

    engine/src/core/application.cpp
    engine/src/core/command_registry.cpp
    engine/src/core/engine.cpp
    engine/src/core/layer.cpp
    engine/src/core/layer_stack.cpp
    engine/src/core/logger.cpp

    engine/src/entity/commands/entity_create_command.cpp
    engine/src/entity/commands/entity_move_command.cpp

    engine/src/graphics/commands/graphics_set_clear_color_command.cpp
    engine/src/graphics/commands/graphics_set_wireframe_command.cpp
    engine/src/graphics/graphics_api.cpp
    engine/src/graphics/material/material.cpp
    engine/src/graphics/shader_program.cpp

    engine/src/imgui/imgui_layer.cpp
    engine/src/input/input.cpp
    engine/src/scene/scene.cpp
    engine/src/util/stb_image_implementation.cpp
    engine/src/window/window.cpp

    engine/src/scene/scene_layer.cpp
)

target_compile_definitions(OpenGL PRIVATE
    GLFW_INCLUDE_NONE
    ENGINE_ASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets"
)

target_include_directories(OpenGL PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/include
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/apps/editor/src
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/apps/editor/ui
)

target_link_libraries(OpenGL PRIVATE
    glad
    glfw
    imgui
    opengl32
)

set_property(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    PROPERTY VS_STARTUP_PROJECT OpenGL
)
