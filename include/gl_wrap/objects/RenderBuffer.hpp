#pragma once

#include <gl_wrap/objects/Object.hpp>

#include <gl_wrap/gl_version.hpp>

namespace gl {

class RenderBuffer : public Object
{
public:

    RenderBuffer();
    virtual ~RenderBuffer();

    // -------------------------------------------------------------------------

    // Moveable
    GLWRAP_MOVE_DEFAULT(RenderBuffer);

    // Non-copyable
    GLWRAP_PREVENT_COPY_AND_ASSIGN(RenderBuffer);

    // -------------------------------------------------------------------------

    void bind();
    static void unbind();

    // -------------------------------------------------------------------------

    // TODO: desktop gl 3.0+,  gles:2.0+
    void setStorage(int internalFormat, int width, int height);

#if (GLWRAP_GL_FROM_OPENGL_VER(3, 0) || GLWRAP_GL_FROM_GLES_VER(3, 0))
    void setStorageMultisample(int samples, int internalFormat, int width, int height);
#endif

    // -------------------------------------------------------------------------

    int getWidth() const;
    int getHeight() const;
    int getInternalFormat() const;

    int getRedSize() const;
    int getGreenSize() const;
    int getBlueSize() const;
    int getAlphaSize() const;
    int getDepthSize() const;
    int getStencilSize() const;

#if defined(GLWRAP_GL_OPENGL) || GLWRAP_GL_FROM_GLES_VER(3, 0) // GL_RENDERBUFFER_SAMPLES not available int GLES 2.0
    int getSamples() const;
#endif

    // -------------------------------------------------------------------------

    static int getMaxSize();

    // -------------------------------------------------------------------------

    static id_t getBindedId();
    static void setBindedId(id_t id);
    bool isBinded() const;

    bool isOk() const;
};

} // namespace gl
