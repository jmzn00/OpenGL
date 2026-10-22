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

target_link_libraries(Editor
    PRIVATE
        OpenGLEngine
)