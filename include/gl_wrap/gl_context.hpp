#pragma once

#if defined(GLWRAP_USE_SDL2)

    #if !defined(__EMSCRIPTEN__) // <-- Native

        //#include <SDL2/SDL_opengl.h>

    #else // defined(__EMSCRIPTEN__) <-- Emscripten

        //#include <SDL2/SDL_opengles2.h>

    #endif

#elif defined(GLWRAP_USE_GLFW3)

    #include <GLFW/glfw3.h>

#else


#endif

//#ifdef GLWRAP_FUNCTIONS_FILE
//    #include GLWRAP_FUNCTIONS_FILE
//#else
//    #error ""
//#endif

#if defined(GLWRAP_GL_OPENGL)

    // FIXME: glew for experiments
    #include <GL/glew.h>

#elif defined(GLWRAP_GL_GLES)

    #include <GLES3/gl3.h>

#else

    #error "Cannot determine OpenGL functions"

#endif

namespace gl {

void* getProcAddress(const char* proc_name);

bool initLoader();

} // namespace gl
