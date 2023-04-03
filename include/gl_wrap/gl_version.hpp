#pragma once

// -----------------------------------------------------------------------------

#if (!defined(GLWRAP_GL_OPENGL) && !defined(GLWRAP_GL_GLES))
    #error "GLWRAP :: none of GLWRAP_GL_OPENGL or GLWRAP_GL_GLES is defined!"
#endif

#if (defined(GLWRAP_GL_OPENGL) && defined(GLWRAP_GL_GLES))
    #error "GLWRAP :: both of GLWRAP_GL_OPENGL and GLWRAP_GL_GLES are defined!"
#endif

// -----------------------------------------------------------------------------

#if !defined(GLWRAP_GL_VER_MAJOR)
    #error "GLWRAP :: GLWRAP_GL_VER_MAJOR is not defined!"
#endif

#if !defined(GLWRAP_GL_VER_MINOR)
    #error "GLWRAP :: GLWRAP_GL_VER_MINOR is not defined!"
#endif

// -----------------------------------------------------------------------------

/*
    `GLWRAP_GL_VER` is: (major << 8) + minor.

    Can be used like: `#if (GLWRAP_GL_VER >= GLWRAP_GL_VER_CHECK(2, 1))`

    Inspired by Qt's `QT_VERSION` & `QT_VERSION_CHECK` (in qglobal.h)
*/

#define GLWRAP_GL_VER_CHECK( MAJOR, MINOR ) \
    ((MAJOR << 8) | MINOR )

#define GLWRAP_GL_VER \
    GLWRAP_GL_VER_CHECK(GLWRAP_GL_VER_MAJOR, GLWRAP_GL_VER_MINOR)

// -----------------------------------------------------------------------------

/**
    @brief Commonly-used macros for defining functions availability, based on
           GL context & version.

    Example of usage:

    @code{.cpp}
    // - 'OpenGL' (desktop) - it always available
    // - 'OpenGL ES' - OpenGL ES 3' only, since in 'OpenGL ES 2' not
    //    exists `glGetTexLevelParameteriv()`
    #if (GLWRAP_GL_FROM_OPENGL_VER(2, 0) || GLWRAP_GL_FROM_GLES_VER(3, 1))
    int gl::Texture::getWidth(int level = 0) const
    {
        GLint result;
        glGetTexLevelParameteriv(_target, level, GL_TEXTURE_WIDTH, &result);
        return result;
    }
    #endif
    @endcode
*/

#if defined(GLWRAP_GL_OPENGL)
    #define GLWRAP_GL_FROM_OPENGL_VER( MAJOR, MINOR ) \
        (GLWRAP_GL_VER >= GLWRAP_GL_VER_CHECK(MAJOR, MINOR))
#else
    #define GLWRAP_GL_FROM_OPENGL_VER( MAJOR, MINOR ) \
        (false)
#endif

#if defined(GLWRAP_GL_GLES)
    #define GLWRAP_GL_FROM_GLES_VER( MAJOR, MINOR ) \
        (GLWRAP_GL_VER >= GLWRAP_GL_VER_CHECK(MAJOR, MINOR))
#else
    #define GLWRAP_GL_FROM_GLES_VER( MAJOR, MINOR ) \
        (false)
#endif

// -----------------------------------------------------------------------------
