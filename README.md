(**WIP**) OpenGL C++ Wrapper library


## Build configuration

- OpenGL type (**required** one of):
    - `GLWRAP_GL_OPENGL`
    - `GLWRAP_GL_GLES`

- OpenGL version (**required** both):
    - `GLWRAP_GL_VER_MAJOR=x`
    - `GLWRAP_GL_VER_MINOR=y`

- Window handling library (**optional** all):
    - `GLWRAP_USE_GLFW3`
    - `GLWRAP_USE_SDL2`
    - None - no 'getProcAddress()' func

- Loaders (**optional** all):
    - `GLWRAP_USE_LOADER_GLEW`
    - None - no loader

- Debugging (**optional** all):
    - `GLWRAP_CHECK_FUNCS`
    - `GLWRAP_CHECK_BINDED`

- Extentions (**optional** all):
    - `GLWRAP_USE_GLM`
    - `GLWRAP_USE_EIGEN3`
    - `GLWRAP_USE_SFML`

