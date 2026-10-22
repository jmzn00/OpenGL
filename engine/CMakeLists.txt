file(GLOB_RECURSE ENGINE_SOURCES
    CONFIGURE_DEPENDS
    "src/*.cpp"
)

add_library(OpenGLEngine
    ${ENGINE_SOURCES}
)

target_include_directories(OpenGLEngine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(OpenGLEngine
    PUBLIC
        cxx_std_20
)

target_compile_definitions(OpenGLEngine
    PUBLIC
        GLFW_INCLUDE_NONE
        ENGINE_ASSET_DIR="${CMAKE_SOURCE_DIR}/assets"
)

target_link_libraries(OpenGLEngine
    PUBLIC
        glad
        glfw
        glm
        imgui
        assimp
        opengl32
)