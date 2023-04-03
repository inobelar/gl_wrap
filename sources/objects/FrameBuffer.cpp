#include <gl_wrap/objects/FrameBuffer.hpp>

#include <gl_wrap/gl_context.hpp>
#include <gl_wrap/gl_error_checking.hpp>

#if defined(GLWRAP_CHECK_BINDED)
    #include <cassert> // for assert()

    #define GLWRAP_CHECK_BINDED_FRAMEBUFFER \
        assert(this->isBinded() == true)
#else
    #define GLWRAP_CHECK_BINDED_FRAMEBUFFER
#endif

// -----------------------------------------------------------------------------

gl::FrameBuffer::FrameBuffer(int target)
    : Object()
    , _target(target)
{
    GLWRAP_GL_CHECK( glGenFramebuffers(1, &_id) );
}

gl::FrameBuffer::~FrameBuffer()
{
    GLWRAP_GL_CHECK( glDeleteFramebuffers(1, &_id) );
}

// -----------------------------------------------------------------------------

void gl::FrameBuffer::bind()
{
    GLWRAP_GL_CHECK( glBindFramebuffer(_target, _id) );
}

void gl::FrameBuffer::unbind()
{
    GLWRAP_GL_CHECK( glBindFramebuffer(_target, 0) );
}

// -----------------------------------------------------------------------------

int gl::FrameBuffer::checkStatus()
{
    GLWRAP_CHECK_BINDED_FRAMEBUFFER;

    GLenum status;
    GLWRAP_GL_CHECK( status = glCheckFramebufferStatus(_target) );
    return status;
}

// -----------------------------------------------------------------------------

void gl::FrameBuffer::attachRenderBuffer(int attachment, gl::Object::id_t renderbuffer_id)
{
    GLWRAP_CHECK_BINDED_FRAMEBUFFER;

    GLWRAP_GL_CHECK( glFramebufferRenderbuffer(_target, attachment, GL_RENDERBUFFER, renderbuffer_id) );
}

void gl::FrameBuffer::attachRenderBuffer(int attachment, gl::RenderBuffer *renderbuffer)
{
    GLWRAP_CHECK_BINDED_FRAMEBUFFER;

    GLWRAP_GL_CHECK( glFramebufferRenderbuffer(_target, attachment, GL_RENDERBUFFER, renderbuffer->getId()) );
}

#if (GLWRAP_GL_FROM_OPENGL_VER(3, 0) || GLWRAP_GL_FROM_GLES_VER(2, 0))
void gl::FrameBuffer::attachTexture2D(int attachment, int texTarget, id_t texture_id, int level)
{
    GLWRAP_CHECK_BINDED_FRAMEBUFFER;

    GLWRAP_GL_CHECK( glFramebufferTexture2D(_target, attachment, texTarget, texture_id, level) );
}
#endif

#if (GLWRAP_GL_FROM_OPENGL_VER(3, 0) || GLWRAP_GL_FROM_GLES_VER(3, 0))
void gl::FrameBuffer::attachTextureLayer(int attachment, gl::Object::id_t texture_id, int level, int layer)
{
    GLWRAP_CHECK_BINDED_FRAMEBUFFER;

    GLWRAP_GL_CHECK( glFramebufferTextureLayer(_target, attachment, texture_id, level, layer) );
}
#endif

#if (GLWRAP_GL_FROM_OPENGL_VER(3, 2) || GLWRAP_GL_FROM_GLES_VER(3, 2))
void gl::FrameBuffer::attachTexture(int attachment, id_t texture_id, int level)
{
    GLWRAP_CHECK_BINDED_FRAMEBUFFER;

    GLWRAP_GL_CHECK( glFramebufferTexture(_target, attachment, texture_id, level) );
}
#endif

// -----------------------------------------------------------------------------

gl::Object::id_t gl::FrameBuffer::getBindedId()
{
    GLint currenly_binded;
    GLWRAP_GL_CHECK( glGetIntegerv(GL_FRAMEBUFFER_BINDING, &currenly_binded) );
    return static_cast<id_t>(currenly_binded);
}

void gl::FrameBuffer::setBindedId(int target, gl::Object::id_t id)
{
    GLWRAP_GL_CHECK( glBindFramebuffer(target, id) );
}

bool gl::FrameBuffer::isBinded() const
{
    return isOk() && (_id == getBindedId());
}

// -----------------------------------------------------------------------------

bool gl::FrameBuffer::isOk() const
{
    GLboolean result;
    GLWRAP_GL_CHECK( result = glIsFramebuffer(_id) );
    return (result != GL_FALSE);
}
