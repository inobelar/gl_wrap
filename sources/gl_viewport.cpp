#include <gl_wrap/gl_viewport.hpp>

#include <gl_wrap/gl_context.hpp>
#include <gl_wrap/gl_error_checking.hpp>

// -----------------------------------------------------------------------------

void gl::Viewport::setRect(int x, int y, int width, int height)
{
    GLWRAP_GL_CHECK( glViewport(x, y, width, height) );
}

void gl::Viewport::getRect(int& x, int& y, int& width, int& height)
{
    int values[4];
    GLWRAP_GL_CHECK( glGetIntegerv(GL_VIEWPORT, values) );
    x      = values[0];
    y      = values[1];
    width  = values[2];
    height = values[3];
}

// -----------------------------------------------------------------------------

void gl::Viewport::setRect(const gl::Rect& rect)
{
    setRect(rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight());
}

gl::Rect gl::Viewport::getRect()
{
    int values[4];
    GLWRAP_GL_CHECK( glGetIntegerv(GL_VIEWPORT, values) );
    return gl::Rect(values[0], values[1], values[2], values[3]);
}

// -----------------------------------------------------------------------------

void gl::Viewport::getMaxDimentions(int& width, int& height)
{
    int values[2];
    GLWRAP_GL_CHECK( glGetIntegerv(GL_MAX_VIEWPORT_DIMS, values) );
    width  = values[0];
    height = values[1];
}
