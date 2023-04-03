#[[
    # Example of usage

    Add into your CMakeLists.txt the next lines:

    # --------------------------------------------------------------------------

    # Add 'gl_wrap' into modules search path - to find this file (gl_wrap.cmake)
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/path/to/gl_wrap/")
    include(gl_wrap)

    add_executable( <YOUR_EXECUTABLE>
        # ...
        ${GLWRAP_HEADERS} ${GLWRAP_SOURCES}
    )

    # Add 'gl_wrap' includes search path
    target_include_directories( <YOUR_EXECUTABLE> ${GLWRAP_INCLUDE_DIRECTORIES} )

    # --------------------------------------------------------------------------
]]

set(GLWRAP_INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_LIST_DIR}/include/
)

set(GLWRAP_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/include/gl_wrap/gl_error_checking.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/gl_wrap/gl_extensions.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/gl_wrap/gl_context.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/gl_wrap/gl_glsl_version.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/gl_wrap/gl_glsl_version_str.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/gl_wrap/gl_scissor.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/gl_wrap/gl_version.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/gl_wrap/gl_viewport.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/gl_wrap/shader_program_utils.hpp

    ${CMAKE_CURRENT_LIST_DIR}/include/gl_wrap/utils/gl_ColorRGBA.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/gl_wrap/utils/gl_Rect.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/gl_wrap/utils/macros.hpp


    ${CMAKE_CURRENT_LIST_DIR}/include/gl_wrap/objects/Object.hpp

    ${CMAKE_CURRENT_LIST_DIR}/include/gl_wrap/objects/Shader.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/gl_wrap/objects/ShaderProgram.hpp

    ${CMAKE_CURRENT_LIST_DIR}/include/gl_wrap/objects/Texture.hpp

    ${CMAKE_CURRENT_LIST_DIR}/include/gl_wrap/objects/Buffer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/gl_wrap/objects/VertexArrayObject.hpp

    ${CMAKE_CURRENT_LIST_DIR}/include/gl_wrap/objects/RenderBuffer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/gl_wrap/objects/FrameBuffer.hpp
)

set(GLWRAP_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/sources/gl_error_checking.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/gl_extensions.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/gl_context.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/gl_glsl_version.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/gl_glsl_version_str.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/gl_scissor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/gl_version.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/gl_viewport.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/shader_program_utils.cpp

    ${CMAKE_CURRENT_LIST_DIR}/sources/utils/gl_ColorRGBA.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/utils/gl_Rect.cpp


    ${CMAKE_CURRENT_LIST_DIR}/sources/objects/Object.cpp

    ${CMAKE_CURRENT_LIST_DIR}/sources/objects/Shader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/objects/ShaderProgram.cpp

    ${CMAKE_CURRENT_LIST_DIR}/sources/objects/Texture.cpp

    ${CMAKE_CURRENT_LIST_DIR}/sources/objects/Buffer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/objects/VertexArrayObject.cpp

    ${CMAKE_CURRENT_LIST_DIR}/sources/objects/RenderBuffer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/objects/FrameBuffer.cpp
)
