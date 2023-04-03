#include <gl_wrap/objects/RenderBuffer.hpp>

#include <gl_wrap/gl_context.hpp>
#include <gl_wrap/gl_error_checking.hpp>

#if defined(GLWRAP_CHECK_BINDED)
    #include <cassert> // for assert()

    #define GLWRAP_CHECK_BINDED_RENDERBUFFER \
        assert(this->isBinded() == true)
#else
    #define GLWRAP_CHECK_BINDED_RENDERBUFFER
#endif

// -----------------------------------------------------------------------------

gl::RenderBuffer::RenderBuffer()
    : Object()
{
    GLWRAP_GL_CHECK( glGenRenderbuffers(1, &_id) );
}

gl::RenderBuffer::~RenderBuffer()
{
    GLWRAP_GL_CHECK( glDeleteRenderbuffers(1, &_id) );
}

// -----------------------------------------------------------------------------

void gl::RenderBuffer::bind()
{
    GLWRAP_GL_CHECK( glBindRenderbuffer(GL_RENDERBUFFER, _id) );
}

void gl::RenderBuffer::unbind()
{
    GLWRAP_GL_CHECK( glBindRenderbuffer(GL_RENDERBUFFER, 0) );
}

// -----------------------------------------------------------------------------

void gl::RenderBuffer::setStorage(int internalFormat, int width, int height)
{
    GLWRAP_CHECK_BINDED_RENDERBUFFER;

    // TODO: check for:
        // const int maxSize = getMaxSize();
        // assert(width > 0 && width  <= maxSize);
        // assert(height> 0 && height <= maxSize);

    GLWRAP_GL_CHECK( glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, width, height) );
}

#if (GLWRAP_GL_FROM_OPENGL_VER(3, 0) || GLWRAP_GL_FROM_GLES_VER(3, 0))
void gl::RenderBuffer::setStorageMultisample(int samples, int internalFormat, int width, int height)
{
    GLWRAP_CHECK_BINDED_RENDERBUFFER;

    // TODO: check for:
        // const int maxSize = getMaxSize();
        // assert(width > 0 && width  <= maxSize);
        // assert(height> 0 && height <= maxSize);

    GLWRAP_GL_CHECK( glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, internalFormat, width, height) );
}
#endif

// -----------------------------------------------------------------------------

int gl::RenderBuffer::getWidth() const
{
    GLWRAP_CHECK_BINDED_RENDERBUFFER;

    GLint result;
    GLWRAP_GL_CHECK( glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &result) );
    return result;
}

int gl::RenderBuffer::getHeight() const
{
    GLWRAP_CHECK_BINDED_RENDERBUFFER;

    GLint result;
    GLWRAP_GL_CHECK( glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &result) );
    return result;
}

int gl::RenderBuffer::getInternalFormat() const
{
    GLWRAP_CHECK_BINDED_RENDERBUFFER;

    GLint result;
    GLWRAP_GL_CHECK( glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_INTERNAL_FORMAT, &result) );
    return result;
}

// -----------------------------------------------------------------------------

int gl::RenderBuffer::getRedSize() const
{
    GLWRAP_CHECK_BINDED_RENDERBUFFER;

    GLint result;
    GLWRAP_GL_CHECK( glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_RED_SIZE, &result) );
    return result;
}

int gl::RenderBuffer::getGreenSize() const
{
    GLWRAP_CHECK_BINDED_RENDERBUFFER;

    GLint result;
    GLWRAP_GL_CHECK( glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_GREEN_SIZE, &result) );
    return result;
}

int gl::RenderBuffer::getBlueSize() const
{
    GLWRAP_CHECK_BINDED_RENDERBUFFER;

    GLint result;
    GLWRAP_GL_CHECK( glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_BLUE_SIZE, &result) );
    return result;
}

int gl::RenderBuffer::getAlphaSize() const
{
    GLWRAP_CHECK_BINDED_RENDERBUFFER;

    GLint result;
    GLWRAP_GL_CHECK( glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_ALPHA_SIZE, &result) );
    return result;
}

int gl::RenderBuffer::getDepthSize() const
{
    GLWRAP_CHECK_BINDED_RENDERBUFFER;

    GLint result;
    GLWRAP_GL_CHECK( glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_DEPTH_SIZE, &result) );
    return result;
}

int gl::RenderBuffer::getStencilSize() const
{
    GLWRAP_CHECK_BINDED_RENDERBUFFER;

    GLint result;
    GLWRAP_GL_CHECK( glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_STENCIL_SIZE, &result) );
    return result;
}

#if defined(GLWRAP_GL_OPENGL) || GLWRAP_GL_FROM_GLES_VER(3, 0)
int gl::RenderBuffer::getSamples() const
{
    GLWRAP_CHECK_BINDED_RENDERBUFFER;

    GLint result;
    GLWRAP_GL_CHECK( glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_SAMPLES, &result) );
    return result;
}
#endif

int gl::RenderBuffer::getMaxSize()
{
    GLint result;
    GLWRAP_GL_CHECK( glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &result) );
    return result;
}

// -----------------------------------------------------------------------------

gl::Object::id_t gl::RenderBuffer::getBindedId()
{
    GLint currently_binded;
    GLWRAP_GL_CHECK( glGetIntegerv(GL_RENDERBUFFER_BINDING, &currently_binded) );
    return static_cast<id_t>(currently_binded);
}

void gl::RenderBuffer::setBindedId(gl::Object::id_t id)
{
    GLWRAP_GL_CHECK( glBindRenderbuffer(GL_RENDERBUFFER, id) );
}

bool gl::RenderBuffer::isBinded() const
{
    return isOk() && (_id == getBindedId());
}

// -----------------------------------------------------------------------------

bool gl::RenderBuffer::isOk() const
{
    GLboolean result;
    GLWRAP_GL_CHECK( result = glIsRenderbuffer(_id) );
    return (result != GL_FALSE);
}
