#pragma once

#include <gl_wrap/objects/Object.hpp>

#include <gl_wrap/gl_version.hpp>

namespace gl {

class Texture : public Object
{
    int _target;

public:

    Texture(int target);
    virtual ~Texture();

    // -------------------------------------------------------------------------

    // Moveable
    GLWRAP_MOVE_DEFAULT(Texture);

    // Non-copyable
    GLWRAP_PREVENT_COPY_AND_ASSIGN(Texture);

    // -------------------------------------------------------------------------

    void bind();
    void unbind();

    // -------------------------------------------------------------------------

#if !defined(GLWRAP_GL_GLES) // Not present in OpenGL ES
    void setImage1D(int level,
                    int internalFormat,
                    int width,
                    int border,
                    int format, int type, const void* pixels);
#endif

    void setImage2D(int level,
                    int internalFormat,
                    int width, int height,
                    int border,
                    int format, int type, const void* pixels);

#if defined(GLWRAP_GL_OPENGL) || GLWRAP_GL_FROM_GLES_VER(3, 0)
    void setImage3D(int level,
                    int internalFormat,
                    int width, int height, int depth,
                    int border,
                    int format, int type, const void* pixels);
#endif

    // -------------------------------------------------------------------------

#if !defined(GLWRAP_GL_GLES) // Not present in OpenGL ES
    void setSubImage1D(int level,
                       int xoffset,
                       int width,
                       int format, int type, const void* pixels);
#endif

    void setSubImage2D(int level,
                       int xoffset, int yoffset,
                       int width, int height,
                       int format, int type, const void* pixels);

#if defined(GLWRAP_GL_OPENGL) || GLWRAP_GL_FROM_GLES_VER(3, 0)
    void setSubImage3D(int level,
                       int xoffset, int yoffset, int zoffset,
                       int width, int height, int depth,
                       int format, int type, const void* pixels);
#endif

    // -------------------------------------------------------------------------

    void setWrapS(int value);
    void setWrapT(int value);
    void setMagFilter(int value);
    void setMinFilter(int value);

    // Convenient functions
    void setWrapST(int valueS, int valueT);
    void setWrapST(int value);
    void setMinMagFilter(int valueMin, int valueMag);
    void setMinMagFilter(int value);

    // -------------------------------------------------------------------------

    // NOTE: GLES3 only, since in GLES2 not exists `glGetTexLevelParameteriv()`
#if (GLWRAP_GL_FROM_OPENGL_VER(2, 0) || GLWRAP_GL_FROM_GLES_VER(3, 1))
    int getWidth(int level = 0) const;
    int getHeight(int level = 0) const;
#endif


//    GL_TEXTURE_DEPTH,
//    GL_TEXTURE_INTERNAL_FORMAT,
//    GL_TEXTURE_RED_SIZE,
//    GL_TEXTURE_GREEN_SIZE,
//    GL_TEXTURE_BLUE_SIZE,
//    GL_TEXTURE_ALPHA_SIZE,
//    GL_TEXTURE_DEPTH_SIZE,
//    GL_TEXTURE_COMPRESSED,
//    GL_TEXTURE_COMPRESSED_IMAGE_SIZE,
//    GL_TEXTURE_BUFFER_OFFSET are accepted.

    // -------------------------------------------------------------------------

//    id_t getBindedId() const;
//    bool isBinded() const;

    // TODO: GLES10.glGetIntegerv(GL10.GL_MAX_TEXTURE_SIZE, maxTextureSize, 0);


    bool isOk() const;
};

} // namespace gl
