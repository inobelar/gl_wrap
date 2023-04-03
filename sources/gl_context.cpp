#include <gl_wrap/gl_context.hpp>

#if defined(GLWRAP_USE_SDL2)

    #include <SDL2/SDL.h>

#elif defined(GLWRAP_USE_GLFW3)

    #define GLFW_INCLUDE_NONE
    #include <GLFW/glfw3.h>

#else

    #include <cstdio> // for fprintf(), stderr

#endif

void* gl::getProcAddress(const char *proc_name)
{
    #if defined(GLWRAP_USE_SDL2)

        return SDL_GL_GetProcAddress(proc_name);

    #elif defined(GLWRAP_USE_GLFW3)

        return glfwGetProcAddress(proc_name);

    #else

        fprintf(stderr, "[GLWRAP] Error: getProcAddress() not implemented! Can't get \'%s\'\n", proc_name);
        fflush(stderr);

        return nullptr;

    #endif
}

// -----------------------------------------------------------------------------

static bool LOADER_INITED = false;

#if defined(GLWRAP_USE_LOADER_GLEW)

    #include <GL/glew.h>
    #pragma message "GLWRAP :: Loader: GLEW"

#else

    #pragma message "GLWRAP :: No loader specified"

#endif

bool gl::initLoader()
{
    #if defined(GLWRAP_USE_LOADER_GLEW)
    if(LOADER_INITED == false)
    {
        // TODO: in case of 'Core' OpenGL context (3.3) we need this:
        //   glewExperimental = GL_TRUE;

        const GLenum glewError = glewInit();
        if (glewError != GLEW_OK)
        {
            // Problem: glewInit failed, something is seriously wrong
            fprintf(stderr, "[GLEW] Init error: %s\n", glewGetErrorString(glewError));
            fflush(stderr);
        }
        else // GLEW inited successfully
        {
            fprintf(stdout, "[GLEW] Version %s\n", glewGetString(GLEW_VERSION));
            fflush(stdout);

            LOADER_INITED = true;
        }
    }
    #else
    {
        // No loader specified
        LOADER_INITED = true;
    }
    #endif

    return LOADER_INITED;
}
