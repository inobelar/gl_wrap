#include <gl_wrap/objects/Texture.hpp>

#include <gl_wrap/gl_context.hpp>
#include <gl_wrap/gl_error_checking.hpp>

#if defined(GLWRAP_CHECK_BINDED)
    #include <cassert> // for assert()

    #define GLWRAP_CHECK_BINDED_TEXTURE \
        assert(this->isBinded() == true)
#else
    #define GLWRAP_CHECK_BINDED_TEXTURE
#endif

// -----------------------------------------------------------------------------

gl::Texture::Texture(int target)
    : Object()
    , _target(target)
{
    GLWRAP_GL_CHECK( glGenTextures(1, &_id) );
}

gl::Texture::~Texture()
{
    GLWRAP_GL_CHECK( glDeleteTextures(1, &_id) );
}

// -----------------------------------------------------------------------------

void gl::Texture::bind()
{
    GLWRAP_GL_CHECK( glBindTexture(_target, _id) );
}

void gl::Texture::unbind()
{
    GLWRAP_GL_CHECK( glBindTexture(_target, 0) );
}

// -----------------------------------------------------------------------------

#if !defined(GLWRAP_GL_GLES)
void gl::Texture::setImage1D(int level, int internalFormat, int width, int border, int format, int type, const void* pixels)
{
    GLWRAP_CHECK_BINDED_TEXTURE;

    GLWRAP_GL_CHECK( glTexImage1D(_target, level, internalFormat, width, border, format, type, pixels) );
}
#endif

void gl::Texture::setImage2D(int level, int internalFormat, int width, int height, int border, int format, int type, const void *pixels)
{
    GLWRAP_CHECK_BINDED_TEXTURE;

    GLWRAP_GL_CHECK( glTexImage2D(_target, level, internalFormat, width, height, border, format, type, pixels) );
}

#if defined(GLWRAP_GL_OPENGL) || GLWRAP_GL_FROM_GLES_VER(3, 0)
void gl::Texture::setImage3D(int level, int internalFormat, int width, int height, int depth, int border, int format, int type, const void *pixels)
{
    GLWRAP_CHECK_BINDED_TEXTURE;

    GLWRAP_GL_CHECK( glTexImage3D(_target, level, internalFormat, width, height, depth, border, format, type, pixels) );
}
#endif

// -----------------------------------------------------------------------------

#if !defined(GLWRAP_GL_GLES)
void gl::Texture::setSubImage1D(int level, int xoffset, int width, int format, int type, const void *pixels)
{
    GLWRAP_CHECK_BINDED_TEXTURE;

    GLWRAP_GL_CHECK( glTexSubImage1D(_target, level, xoffset, width, format, type, pixels) );
}
#endif

void gl::Texture::setSubImage2D(int level, int xoffset, int yoffset, int width, int height, int format, int type, const void *pixels)
{
    GLWRAP_CHECK_BINDED_TEXTURE;

    GLWRAP_GL_CHECK( glTexSubImage2D(_target, level, xoffset, yoffset, width, height, format, type, pixels) );
}

#if defined(GLWRAP_GL_OPENGL) || GLWRAP_GL_FROM_GLES_VER(3, 0)
void gl::Texture::setSubImage3D(int level, int xoffset, int yoffset, int zoffset, int width, int height, int depth, int format, int type, const void *pixels)
{
    GLWRAP_CHECK_BINDED_TEXTURE;

    GLWRAP_GL_CHECK( glTexSubImage3D(_target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels) );
}
#endif

// -----------------------------------------------------------------------------

void gl::Texture::setWrapS(int value)
{
    GLWRAP_CHECK_BINDED_TEXTURE;

    GLWRAP_GL_CHECK( glTexParameteri(_target, GL_TEXTURE_WRAP_S, value) );
}

void gl::Texture::setWrapT(int value)
{
    GLWRAP_CHECK_BINDED_TEXTURE;

    GLWRAP_GL_CHECK( glTexParameteri(_target, GL_TEXTURE_WRAP_T, value) );
}

// -----------------------------------------------------------------------------

void gl::Texture::setMagFilter(int value)
{
    GLWRAP_CHECK_BINDED_TEXTURE;

    GLWRAP_GL_CHECK( glTexParameteri(_target, GL_TEXTURE_MAG_FILTER, value) );
}

void gl::Texture::setMinFilter(int value)
{
    GLWRAP_CHECK_BINDED_TEXTURE;

    GLWRAP_GL_CHECK( glTexParameteri(_target, GL_TEXTURE_MIN_FILTER, value) );
}

// -----------------------------------------------------------------------------

void gl::Texture::setWrapST(int valueS, int valueT)
{
    GLWRAP_CHECK_BINDED_TEXTURE;

    setWrapS(valueS);
    setWrapT(valueT);
}

void gl::Texture::setWrapST(int value)
{
    GLWRAP_CHECK_BINDED_TEXTURE;

    setWrapST(value, value);
}

void gl::Texture::setMinMagFilter(int valueMin, int valueMag)
{
    GLWRAP_CHECK_BINDED_TEXTURE;

    setMinFilter(valueMin);
    setMagFilter(valueMag);
}

void gl::Texture::setMinMagFilter(int value)
{
    setMinMagFilter(value, value);
}

// -----------------------------------------------------------------------------

#if (GLWRAP_GL_FROM_OPENGL_VER(2, 0) || GLWRAP_GL_FROM_GLES_VER(3, 1))
int gl::Texture::getWidth(int level) const
{
    GLWRAP_CHECK_BINDED_TEXTURE;

    GLint result;
    GLWRAP_GL_CHECK( glGetTexLevelParameteriv(_target, level, GL_TEXTURE_WIDTH, &result) );
    return result;
}

int gl::Texture::getHeight(int level) const
{
    GLWRAP_CHECK_BINDED_TEXTURE;

    GLint result;
    GLWRAP_GL_CHECK( glGetTexLevelParameteriv(_target, level, GL_TEXTURE_HEIGHT, &result) );
    return result;
}
#endif

// -----------------------------------------------------------------------------

bool gl::Texture::isOk() const
{
    GLboolean result;
    GLWRAP_GL_CHECK( result = glIsTexture(_id) );
    return (result != GL_FALSE);
}
