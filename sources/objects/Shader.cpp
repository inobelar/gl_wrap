#include <gl_wrap/objects/Shader.hpp>

#include <gl_wrap/gl_context.hpp>
#include <gl_wrap/gl_error_checking.hpp>

gl::Shader::Shader(int type)
    : Object()
{
    GLWRAP_GL_CHECK( _id = glCreateShader( static_cast<GLenum>(type) ) );
}

gl::Shader::~Shader()
{
    GLWRAP_GL_CHECK( glDeleteShader(_id) );
}

// -----------------------------------------------------------------------------

void gl::Shader::setSource(int count, const char **string, const int *lengths)
{
    GLWRAP_GL_CHECK( glShaderSource(_id, count, string, lengths) );
}

void gl::Shader::setSource(const char* string, int length)
{
    GLWRAP_GL_CHECK( glShaderSource(_id, 1, &string, &length) );
}

void gl::Shader::setSource(const char* string)
{
    GLWRAP_GL_CHECK( glShaderSource(_id, 1, &string, nullptr) );
}

// -----------------------------------------------------------------------------

void gl::Shader::compile()
{
    GLWRAP_GL_CHECK( glCompileShader(_id) );
}

// -----------------------------------------------------------------------------

int gl::Shader::getType() const
{
    GLint type;
    GLWRAP_GL_CHECK( glGetShaderiv(_id, GL_SHADER_TYPE, &type) );
    return type;
}

bool gl::Shader::isDeleted() const
{
    GLint status;
    GLWRAP_GL_CHECK( glGetShaderiv(_id, GL_DELETE_STATUS, &status) );
    return (status != GL_FALSE);
}

bool gl::Shader::isCompiled() const
{
    GLint status;
    GLWRAP_GL_CHECK( glGetShaderiv(_id, GL_COMPILE_STATUS, &status) );
    return (status != GL_FALSE);
}

// -----------------------------------------------------------------------------

int gl::Shader::getInfoLogLength() const
{
    GLint length;
    GLWRAP_GL_CHECK( glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &length) );
    return length;
}

int gl::Shader::getSourceLength() const
{
    GLint length;
    GLWRAP_GL_CHECK( glGetShaderiv(_id, GL_SHADER_SOURCE_LENGTH, &length) );
    return length;
}

// -----------------------------------------------------------------------------

std::string gl::Shader::getInfoLog() const
{
    const int buf_length = getInfoLogLength();
    if(buf_length > 1) // Check for '>1', not '>0', since length includes 'null terminator'
    {
        char* buffer = new char[buf_length];

        GLsizei actual_length = 0; // Unused, since we already know size
        GLWRAP_GL_CHECK( glGetShaderInfoLog(_id, buf_length, &actual_length, buffer) );

        // FIXME: here is copy!
        std::string result(buffer, buf_length);
        delete [] buffer;

        return result;
    }

    return {};
}

std::string gl::Shader::getSource() const
{
    const int buf_length = getSourceLength();
    if(buf_length > 1) // Check for '>1', not '>0', since length includes 'null terminator'
    {
        char* buffer = new char[buf_length];

        GLsizei actual_length = 0; // Unused, since we already know size
        GLWRAP_GL_CHECK( glGetShaderSource(_id, buf_length, &actual_length, buffer) );

        // FIXME: here is copy!
        std::string result(buffer, buf_length);
        delete [] buffer;

        return result;
    }

    return {};
}

// -----------------------------------------------------------------------------

bool gl::Shader::isOk() const
{
    GLboolean result;
    GLWRAP_GL_CHECK( result = glIsShader(_id) );
    return (result != GL_FALSE);
}
