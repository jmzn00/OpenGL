file(GLOB_RECURSE EDITOR_SOURCES
    CONFIGURE_DEPENDS
    "*.cpp"
)

add_executable(Editor
    ${EDITOR_SOURCES}
)

target_include_directories(Editor
    PRIVATE
        src
        ui
    PUBLIC
        include
)
target_compile_definitions(Editor
    PRIVATE
        EDITOR_ASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets"
)

target_link_libraries(Editor
    PRIVATE
        OpenGLEngine
)

if (MSVC)
    target_compile_options(Editor PRIVATE /W4 /WX)
else()
    target_compile_options(Editor PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()