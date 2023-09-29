#[[
    # Example of usage

    Add into your CMakeLists.txt the next lines:

    # --------------------------------------------------------------------------

    # Include 'gl_wrap.cmake' file - to be able to call 'load_gl_wrap()'
    include(/path/to/gl_wrap/gl_wrap.cmake)

    set(GLWRAP_INCLUDE_DIRECTORIES "")
    set(GLWRAP_HEADERS             "")
    set(GLWRAP_SOURCES             "")
    load_gl_wrap(GLWRAP_INCLUDE_DIRECTORIES GLWRAP_HEADERS GLWRAP_SOURCES)

    add_executable( <YOUR_EXECUTABLE>
        # ...
        ${GLWRAP_HEADERS} ${GLWRAP_SOURCES}
    )

    # Add 'gl_wrap' includes into search pathes
    target_include_directories( <YOUR_EXECUTABLE> ${GLWRAP_INCLUDE_DIRECTORIES} )

    # --------------------------------------------------------------------------
]]

# Store 'CMAKE_CURRENT_LIST_DIR' out-of-function, so it will contain path to
# directory of **this** file, otherwise (if use 'CMAKE_CURRENT_LIST_DIR' inside
# of function) it will contain path, related to file where function called).
set(__GLWRAP_DIR ${CMAKE_CURRENT_LIST_DIR})

function(load_gl_wrap
         include_directories_out headers_out sources_out)

    set(GLWRAP_INCLUDE_DIRECTORIES
        ${__GLWRAP_DIR}/include/
    )

    set(GLWRAP_HEADERS
        ${__GLWRAP_DIR}/include/gl_wrap/gl_error_checking.hpp
        ${__GLWRAP_DIR}/include/gl_wrap/gl_extensions.hpp
        ${__GLWRAP_DIR}/include/gl_wrap/gl_context.hpp
        ${__GLWRAP_DIR}/include/gl_wrap/gl_glsl_version.hpp
        ${__GLWRAP_DIR}/include/gl_wrap/gl_glsl_version_str.hpp
        ${__GLWRAP_DIR}/include/gl_wrap/gl_scissor.hpp
        ${__GLWRAP_DIR}/include/gl_wrap/gl_version.hpp
        ${__GLWRAP_DIR}/include/gl_wrap/gl_viewport.hpp
        ${__GLWRAP_DIR}/include/gl_wrap/shader_program_utils.hpp

        ${__GLWRAP_DIR}/include/gl_wrap/utils/gl_ColorRGBA.hpp
        ${__GLWRAP_DIR}/include/gl_wrap/utils/gl_Rect.hpp
        ${__GLWRAP_DIR}/include/gl_wrap/utils/macros.hpp


        ${__GLWRAP_DIR}/include/gl_wrap/objects/Object.hpp

        ${__GLWRAP_DIR}/include/gl_wrap/objects/Shader.hpp
        ${__GLWRAP_DIR}/include/gl_wrap/objects/ShaderProgram.hpp

        ${__GLWRAP_DIR}/include/gl_wrap/objects/Texture.hpp

        ${__GLWRAP_DIR}/include/gl_wrap/objects/Buffer.hpp
        ${__GLWRAP_DIR}/include/gl_wrap/objects/VertexArrayObject.hpp

        ${__GLWRAP_DIR}/include/gl_wrap/objects/RenderBuffer.hpp
        ${__GLWRAP_DIR}/include/gl_wrap/objects/FrameBuffer.hpp
    )

    set(GLWRAP_SOURCES
        ${__GLWRAP_DIR}/sources/gl_error_checking.cpp
        ${__GLWRAP_DIR}/sources/gl_extensions.cpp
        ${__GLWRAP_DIR}/sources/gl_context.cpp
        ${__GLWRAP_DIR}/sources/gl_glsl_version.cpp
        ${__GLWRAP_DIR}/sources/gl_glsl_version_str.cpp
        ${__GLWRAP_DIR}/sources/gl_scissor.cpp
        ${__GLWRAP_DIR}/sources/gl_version.cpp
        ${__GLWRAP_DIR}/sources/gl_viewport.cpp
        ${__GLWRAP_DIR}/sources/shader_program_utils.cpp

        ${__GLWRAP_DIR}/sources/utils/gl_ColorRGBA.cpp
        ${__GLWRAP_DIR}/sources/utils/gl_Rect.cpp


        ${__GLWRAP_DIR}/sources/objects/Object.cpp

        ${__GLWRAP_DIR}/sources/objects/Shader.cpp
        ${__GLWRAP_DIR}/sources/objects/ShaderProgram.cpp

        ${__GLWRAP_DIR}/sources/objects/Texture.cpp

        ${__GLWRAP_DIR}/sources/objects/Buffer.cpp
        ${__GLWRAP_DIR}/sources/objects/VertexArrayObject.cpp

        ${__GLWRAP_DIR}/sources/objects/RenderBuffer.cpp
        ${__GLWRAP_DIR}/sources/objects/FrameBuffer.cpp
    )

    list(APPEND ${include_directories_out} ${GLWRAP_INCLUDE_DIRECTORIES})
    list(APPEND ${headers_out}             ${GLWRAP_HEADERS})
    list(APPEND ${sources_out}             ${GLWRAP_SOURCES})

    # Return (reference: https://stackoverflow.com/a/53278726/)
    #   Alternate way (requres CMake 3.25):
    #   'return(PROPAGATE ${include_directories_out} ${headers_out} ${sources_out})'
    set(${include_directories_out} "${${include_directories_out}}" PARENT_SCOPE)
    set(${headers_out}             "${${headers_out}}"             PARENT_SCOPE)
    set(${sources_out}             "${${sources_out}}"             PARENT_SCOPE)

endfunction()
