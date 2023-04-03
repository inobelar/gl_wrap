#include <gl_wrap/gl_glsl_version_str.hpp>

#include <gl_wrap/gl_version.hpp>

#include <gl_wrap/gl_glsl_version.hpp>

static constexpr gl::GLSL_Version GLSL_VERSION =

    #if defined(GLWRAP_GL_OPENGL)

        gl::get_glsl_version(GLWRAP_GL_VER_MAJOR, GLWRAP_GL_VER_MINOR, false)

    #elif defined(GLWRAP_GL_GLES)

        gl::get_glsl_version(GLWRAP_GL_VER_MAJOR, GLWRAP_GL_VER_MINOR,  true)

    #else

        #error "Cannot resolve GLSL version!"

    #endif
;

static_assert(GLSL_VERSION.is_defined() == true, "Cannot resolve GLSL version!");

const char* gl::glsl_version_str()
{
    return GLSL_VERSION.str;
}
