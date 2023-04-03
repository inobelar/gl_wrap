#pragma once

namespace gl {

const char* gl_error_to_str(int errorId);

bool check_gl_error(const char* file, int line, const char* str);

} // namespace gl

#if defined(GLWRAP_CHECK_FUNCS)

    #pragma message "GLWRAP :: OpenGL function checking: enabled"

    #define GLWRAP_GL_CHECK(expression) \
        do { \
            expression; \
            (void) gl::check_gl_error(__FILE__, __LINE__, #expression); \
        } while(false)

#else // !defined(GLWRAP_CHECK_FUNCS)

    #pragma message "GLWRAP :: OpenGL function checking: disabled"

    #define GLWRAP_GL_CHECK(expression) \
        expression

#endif
