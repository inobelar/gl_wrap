#pragma once

#include <gl_wrap/objects/Object.hpp>
#include <gl_wrap/objects/RenderBuffer.hpp>

#include <gl_wrap/gl_version.hpp>

namespace gl {

class FrameBuffer : public Object
{
    int _target;

public:

    FrameBuffer(int _target);
    virtual ~FrameBuffer();

    // -------------------------------------------------------------------------

    // Moveable
    GLWRAP_MOVE_DEFAULT(FrameBuffer);

    // Non-copyable
    GLWRAP_PREVENT_COPY_AND_ASSIGN(FrameBuffer);

    // -------------------------------------------------------------------------

    void bind();
    void unbind();

    // -------------------------------------------------------------------------

    int checkStatus();

    // -------------------------------------------------------------------------

    // GLES >= 2.0
    void attachRenderBuffer(int attachment, id_t renderbuffer_id);
    void attachRenderBuffer(int attachment, RenderBuffer* renderbuffer);

    // TODO: attach texture 1D, 3D ???

#if (GLWRAP_GL_FROM_OPENGL_VER(3, 0) || GLWRAP_GL_FROM_GLES_VER(2, 0))
    void attachTexture2D(int attachment, int texTarget, id_t texture_id, int level);
#endif

#if (GLWRAP_GL_FROM_OPENGL_VER(3, 0) || GLWRAP_GL_FROM_GLES_VER(3, 0))
    void attachTextureLayer(int attachment, id_t texture_id, int level, int layer);
#endif

#if (GLWRAP_GL_FROM_OPENGL_VER(3, 2) || GLWRAP_GL_FROM_GLES_VER(3, 2))
    void attachTexture(int attachment, id_t texture_id, int level);
#endif

    // -------------------------------------------------------------------------

    // TODO: glGetFramebufferAttachmentParameteriv

    static id_t getBindedId();
    static void setBindedId(int target, id_t id);
    bool isBinded() const;

    bool isOk() const;
};

} // namespace gl
