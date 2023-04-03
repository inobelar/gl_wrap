#include <gl_wrap/gl_error_checking.hpp>

#include <gl_wrap/gl_context.hpp>

#include <cstdio> // for fprintf(), stderr

#if !defined(GL_STACK_OVERFLOW)
    #define GL_STACK_OVERFLOW  0x0503
#endif

#if !defined(GL_STACK_UNDERFLOW)
    #define GL_STACK_UNDERFLOW 0x0504
#endif

const char* gl::gl_error_to_str(/*GLenum*/int errorId)
{
    switch (errorId) {
    case GL_NO_ERROR                      : return "GL_NO_ERROR";
    case GL_INVALID_ENUM                  : return "GL_INVALID_ENUM";
    case GL_INVALID_VALUE                 : return "GL_INVALID_VALUE";
    case GL_INVALID_OPERATION             : return "GL_INVALID_OPERATION";
    case GL_INVALID_FRAMEBUFFER_OPERATION : return "GL_INVALID_FRAMEBUFFER_OPERATION";
    case GL_OUT_OF_MEMORY                 : return "GL_OUT_OF_MEMORY";
    case GL_STACK_UNDERFLOW               : return "GL_STACK_UNDERFLOW";
    case GL_STACK_OVERFLOW                : return "GL_STACK_OVERFLOW";
    default: return "Unknown";
    }
}

bool gl::check_gl_error(const char *file, int line, const char *str)
{
    const GLenum errorId = glGetError();
    if(errorId != GL_NO_ERROR)
    {
        fprintf(stderr, "[GLWRAP] OpenGL error: %08x, (%s) at %s:%i - for \"%s\"!\n",
               errorId, gl_error_to_str(errorId), file, line, str);

        return true;
    }

    return false;
}
