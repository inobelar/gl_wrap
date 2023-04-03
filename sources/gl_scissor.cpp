#include <gl_wrap/gl_scissor.hpp>

#include <gl_wrap/gl_context.hpp>
#include <gl_wrap/gl_error_checking.hpp>

void gl::Scissor::setEnabled(bool enabled)
{
    if(enabled) {
        GLWRAP_GL_CHECK( glEnable(GL_SCISSOR_TEST) );
    } else {
        GLWRAP_GL_CHECK( glDisable(GL_SCISSOR_TEST) );
    }
}

bool gl::Scissor::isEnabled()
{
    GLboolean is_enabled = GL_FALSE;
    GLWRAP_GL_CHECK( is_enabled = glIsEnabled(GL_SCISSOR_TEST) );
    return (is_enabled != GL_FALSE);
}

// -----------------------------------------------------------------------------

void gl::Scissor::setRect(int x, int y, int width, int height)
{
    GLWRAP_GL_CHECK( glScissor(x, y, width, height) );
}

void gl::Scissor::getRect(int &x, int &y, int &width, int &height)
{
    int values[4];
    GLWRAP_GL_CHECK( glGetIntegerv(GL_SCISSOR_BOX, values) );
    x      = values[0];
    y      = values[1];
    width  = values[2];
    height = values[3];
}

// -----------------------------------------------------------------------------

void gl::Scissor::setRect(const gl::Rect &rect)
{
    setRect(rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight());
}

gl::Rect gl::Scissor::getRect()
{
    int values[4];
    GLWRAP_GL_CHECK( glGetIntegerv(GL_SCISSOR_BOX, values) );
    return gl::Rect(values[0], values[1], values[2], values[3]);
}
