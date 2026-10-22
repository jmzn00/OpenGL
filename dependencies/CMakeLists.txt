add_subdirectory(glfw-3.5.1)

set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

add_subdirectory(assimp)

add_library(glad
    glad/src/glad.c
)

target_include_directories(glad PUBLIC
    glad/include
)

add_library(glm INTERFACE)

target_include_directories(glm INTERFACE
    glm
)

set(IMGUI_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui-docking
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

target_link_libraries(imgui PUBLIC
    glfw
    opengl32
)