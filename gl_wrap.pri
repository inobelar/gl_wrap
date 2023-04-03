INCLUDEPATH += $$PWD/include/

HEADERS += \
    $$PWD/include/gl_wrap/gl_error_checking.hpp \
    $$PWD/include/gl_wrap/gl_extensions.hpp \
    $$PWD/include/gl_wrap/gl_context.hpp \
    $$PWD/include/gl_wrap/gl_glsl_version.hpp \
    $$PWD/include/gl_wrap/gl_glsl_version_str.hpp \
    $$PWD/include/gl_wrap/gl_scissor.hpp \
    $$PWD/include/gl_wrap/gl_version.hpp \
    $$PWD/include/gl_wrap/gl_viewport.hpp \
    $$PWD/include/gl_wrap/shader_program_utils.hpp \
    \
    $$PWD/include/gl_wrap/utils/gl_ColorRGBA.hpp \
    $$PWD/include/gl_wrap/utils/gl_Rect.hpp \
    $$PWD/include/gl_wrap/utils/macros.hpp \
    \
    \
    $$PWD/include/gl_wrap/objects/Object.hpp \
    \
    $$PWD/include/gl_wrap/objects/Shader.hpp \
    $$PWD/include/gl_wrap/objects/ShaderProgram.hpp \
    \
    $$PWD/include/gl_wrap/objects/Texture.hpp \
    \
    $$PWD/include/gl_wrap/objects/Buffer.hpp \
    $$PWD/include/gl_wrap/objects/VertexArrayObject.hpp \
    \
    $$PWD/include/gl_wrap/objects/RenderBuffer.hpp \
    $$PWD/include/gl_wrap/objects/FrameBuffer.hpp

SOURCES += \
    $$PWD/sources/gl_error_checking.cpp \
    $$PWD/sources/gl_extensions.cpp \
    $$PWD/sources/gl_context.cpp \
    $$PWD/sources/gl_glsl_version.cpp \
    $$PWD/sources/gl_glsl_version_str.cpp \
    $$PWD/sources/gl_scissor.cpp \
    $$PWD/sources/gl_version.cpp \
    $$PWD/sources/gl_viewport.cpp \
    $$PWD/sources/shader_program_utils.cpp \
    \
    $$PWD/sources/utils/gl_ColorRGBA.cpp \
    $$PWD/sources/utils/gl_Rect.cpp \
    \
    \
    $$PWD/sources/objects/Object.cpp \
    \
    $$PWD/sources/objects/Shader.cpp \
    $$PWD/sources/objects/ShaderProgram.cpp \
    \
    $$PWD/sources/objects/Texture.cpp \
    \
    $$PWD/sources/objects/Buffer.cpp \
    $$PWD/sources/objects/VertexArrayObject.cpp \
    \
    $$PWD/sources/objects/RenderBuffer.cpp \
    $$PWD/sources/objects/FrameBuffer.cpp
