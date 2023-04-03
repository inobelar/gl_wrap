#include <gl_wrap/objects/ShaderProgram.hpp>

#include <gl_wrap/gl_context.hpp>
#include <gl_wrap/gl_error_checking.hpp>

#if defined(GLWRAP_CHECK_BINDED)
    #include <cassert> // for assert()

    #define GLWRAP_CHECK_BINDED_SHADER_PROGRAM \
        assert(this->isCurrent() == true)
#else
    #define GLWRAP_CHECK_BINDED_SHADER_PROGRAM
#endif

gl::ShaderProgram::ShaderProgram()
    : Object()
{
    GLWRAP_GL_CHECK( _id = glCreateProgram() );
}

gl::ShaderProgram::~ShaderProgram()
{
    GLWRAP_GL_CHECK( glDeleteProgram(_id) );
}

void gl::ShaderProgram::attachShader(unsigned int shader_id)
{
    GLWRAP_GL_CHECK( glAttachShader(_id, shader_id) );
}

void gl::ShaderProgram::attachShader(const gl::Shader *shader)
{
    GLWRAP_GL_CHECK( glAttachShader(_id, shader->getId()) );
}

void gl::ShaderProgram::detachShader(unsigned int shader_id)
{
    GLWRAP_GL_CHECK( glDetachShader(_id, shader_id) );
}

void gl::ShaderProgram::detachShader(const gl::Shader *shader)
{
    GLWRAP_GL_CHECK( glDetachShader(_id, shader->getId()) );
}

void gl::ShaderProgram::link()
{
    GLWRAP_GL_CHECK( glLinkProgram(_id) );
}

void gl::ShaderProgram::validate()
{
    GLWRAP_GL_CHECK( glValidateProgram(_id) );
}

void gl::ShaderProgram::use()
{
    GLWRAP_GL_CHECK( glUseProgram(_id) );
}

void gl::ShaderProgram::unuse()
{
    GLWRAP_GL_CHECK( glUseProgram(0) );
}

void gl::ShaderProgram::bindAttribLocation(unsigned int index, const char *name)
{
    // TODO: add assert for:
    // GLint max_vertex_attribs = 0;
    // glGetIntegerV(GL_MAX_VERTEX_ATTRIBS, &max_vertex_attribs);
    // assert(index >= 0 && index < (uint)max_vertex_attribs);

    GLWRAP_GL_CHECK( glBindAttribLocation(_id, index, name) );
}

// -----------------------------------------------------------------------------

// Make sure, that wrapper-structs over integer is same size as that integer :)
static_assert(sizeof(gl::ShaderProgram::attribute_location) == sizeof(int), "Test failed");
static_assert(sizeof(gl::ShaderProgram::uniform_location  ) == sizeof(int), "Test failed");

gl::ShaderProgram::attribute_location gl::ShaderProgram::getAttribLocation(const char *name) const
{
    GLint result;
    GLWRAP_GL_CHECK( result = glGetAttribLocation(_id, name) );
    return result;
}

gl::ShaderProgram::uniform_location gl::ShaderProgram::getUniformLocation(const char *name) const
{
    GLint result;
    GLWRAP_GL_CHECK( result = glGetUniformLocation(_id, name) );
    return result;
}

// -----------------------------------------------------------------------------

void gl::ShaderProgram::setUniformFloat(gl::ShaderProgram::uniform_location location, float v0)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    GLWRAP_GL_CHECK( glUniform1f(location, v0) );
}

void gl::ShaderProgram::setUniformFloat(gl::ShaderProgram::uniform_location location, float v0, float v1)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    GLWRAP_GL_CHECK( glUniform2f(location, v0, v1) );
}

void gl::ShaderProgram::setUniformFloat(gl::ShaderProgram::uniform_location location, float v0, float v1, float v2)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    GLWRAP_GL_CHECK( glUniform3f(location, v0, v1, v2) );
}

void gl::ShaderProgram::setUniformFloat(gl::ShaderProgram::uniform_location location, float v0, float v1, float v2, float v3)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    GLWRAP_GL_CHECK( glUniform4f(location, v0, v1, v2, v3) );
}

#define SET_UNIFORM_VALUES_BY_NAME( FUNC_SET_VALUES_AT_LOCATION, ...) \
    const uniform_location location = getUniformLocation(name); \
    if(location.isPresent()) { \
        FUNC_SET_VALUES_AT_LOCATION(location, __VA_ARGS__ ); \
    } else { \
        fprintf(stderr, "[GLWRAP] Cannot find uniform: %s\n", name); \
        fflush(stderr); \
    }


void gl::ShaderProgram::setUniformFloat(const char *name, float v0)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    SET_UNIFORM_VALUES_BY_NAME( setUniformFloat , v0);
}

void gl::ShaderProgram::setUniformFloat(const char *name, float v0, float v1)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    SET_UNIFORM_VALUES_BY_NAME( setUniformFloat, v0, v1);
}

void gl::ShaderProgram::setUniformFloat(const char *name, float v0, float v1, float v2)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    SET_UNIFORM_VALUES_BY_NAME( setUniformFloat, v0, v1, v2);
}

void gl::ShaderProgram::setUniformFloat(const char *name, float v0, float v1, float v2, float v3)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    SET_UNIFORM_VALUES_BY_NAME( setUniformFloat, v0, v1, v2, v3);
}

// -----------------------------------------------------------------------------

void gl::ShaderProgram::setUniformInt(gl::ShaderProgram::uniform_location location, int v0)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    GLWRAP_GL_CHECK( glUniform1i(location, v0) );
}

void gl::ShaderProgram::setUniformInt(gl::ShaderProgram::uniform_location location, int v0, int v1)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    GLWRAP_GL_CHECK( glUniform2i(location, v0, v1) );
}

void gl::ShaderProgram::setUniformInt(gl::ShaderProgram::uniform_location location, int v0, int v1, int v2)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    GLWRAP_GL_CHECK( glUniform3i(location, v0, v1, v2) );
}

void gl::ShaderProgram::setUniformInt(gl::ShaderProgram::uniform_location location, int v0, int v1, int v2, int v3)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    GLWRAP_GL_CHECK( glUniform4i(location, v0, v1, v2, v3) );
}

void gl::ShaderProgram::setUniformInt(const char *name, int v0)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    SET_UNIFORM_VALUES_BY_NAME( setUniformInt, v0);
}

void gl::ShaderProgram::setUniformInt(const char *name, int v0, int v1)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    SET_UNIFORM_VALUES_BY_NAME( setUniformInt, v0, v1);
}

void gl::ShaderProgram::setUniformInt(const char *name, int v0, int v1, int v2)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    SET_UNIFORM_VALUES_BY_NAME( setUniformInt, v0, v1, v2);
}

void gl::ShaderProgram::setUniformInt(const char *name, int v0, int v1, int v2, int v3)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    SET_UNIFORM_VALUES_BY_NAME( setUniformInt, v0, v1, v2, v3);
}

// -----------------------------------------------------------------------------

void gl::ShaderProgram::setUniformBool(gl::ShaderProgram::uniform_location location, bool v0)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    setUniformInt(location, static_cast<int>(v0) );
}

void gl::ShaderProgram::setUniformBool(const char *name, bool v0)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    SET_UNIFORM_VALUES_BY_NAME( setUniformBool, v0);
}

// -----------------------------------------------------------------------------

void gl::ShaderProgram::setUniformFloatArray1Ptr(gl::ShaderProgram::uniform_location location, const float *value, int count)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    GLWRAP_GL_CHECK( glUniform1fv(location, count, value) );
}

void gl::ShaderProgram::setUniformFloatArray2Ptr(gl::ShaderProgram::uniform_location location, const float *value, int count)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    GLWRAP_GL_CHECK( glUniform2fv(location, count, value) );
}

void gl::ShaderProgram::setUniformFloatArray3Ptr(gl::ShaderProgram::uniform_location location, const float *value, int count)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    GLWRAP_GL_CHECK( glUniform3fv(location, count, value) );
}

void gl::ShaderProgram::setUniformFloatArray4Ptr(gl::ShaderProgram::uniform_location location, const float *value, int count)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    GLWRAP_GL_CHECK( glUniform4fv(location, count, value) );
}

void gl::ShaderProgram::setUniformFloatArray1Ptr(const char *name, const float *value, int count)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    SET_UNIFORM_VALUES_BY_NAME( setUniformFloatArray1Ptr, value, count);
}

void gl::ShaderProgram::setUniformFloatArray2Ptr(const char *name, const float *value, int count)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    SET_UNIFORM_VALUES_BY_NAME( setUniformFloatArray2Ptr, value, count);
}

void gl::ShaderProgram::setUniformFloatArray3Ptr(const char *name, const float *value, int count)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    SET_UNIFORM_VALUES_BY_NAME( setUniformFloatArray3Ptr, value, count);
}

void gl::ShaderProgram::setUniformFloatArray4Ptr(const char *name, const float *value, int count)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    SET_UNIFORM_VALUES_BY_NAME( setUniformFloatArray4Ptr, value, count);
}

// -----------------------------------------------------------------------------

void gl::ShaderProgram::setUniformIntArray1Ptr(gl::ShaderProgram::uniform_location location, const int *value, int count)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    GLWRAP_GL_CHECK( glUniform1iv(location, count, value) );
}

void gl::ShaderProgram::setUniformIntArray2Ptr(gl::ShaderProgram::uniform_location location, const int *value, int count)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    GLWRAP_GL_CHECK( glUniform2iv(location, count, value) );
}

void gl::ShaderProgram::setUniformIntArray3Ptr(gl::ShaderProgram::uniform_location location, const int *value, int count)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    GLWRAP_GL_CHECK( glUniform3iv(location, count, value) );
}

void gl::ShaderProgram::setUniformIntArray4Ptr(gl::ShaderProgram::uniform_location location, const int *value, int count)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    GLWRAP_GL_CHECK( glUniform4iv(location, count, value) );
}

void gl::ShaderProgram::setUniformIntArray1Ptr(const char *name, const int *value, int count)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    SET_UNIFORM_VALUES_BY_NAME( setUniformIntArray1Ptr, value, count);
}

void gl::ShaderProgram::setUniformIntArray2Ptr(const char *name, const int *value, int count)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    SET_UNIFORM_VALUES_BY_NAME( setUniformIntArray2Ptr, value, count);
}

void gl::ShaderProgram::setUniformIntArray3Ptr(const char *name, const int *value, int count)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    SET_UNIFORM_VALUES_BY_NAME( setUniformIntArray3Ptr, value, count);
}

void gl::ShaderProgram::setUniformIntArray4Ptr(const char *name, const int *value, int count)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    SET_UNIFORM_VALUES_BY_NAME( setUniformIntArray4Ptr, value, count);
}

// -----------------------------------------------------------------------------

void gl::ShaderProgram::setUniformFloatArray1(uniform_location location, const float (&array)[1])
{
    setUniformFloatArray1Ptr(location, array);
}

void gl::ShaderProgram::setUniformFloatArray2(uniform_location location, const float (&array)[2])
{
    setUniformFloatArray2Ptr(location, array);
}

void gl::ShaderProgram::setUniformFloatArray3(uniform_location location, const float (&array)[3])
{
    setUniformFloatArray3Ptr(location, array);
}

void gl::ShaderProgram::setUniformFloatArray4(uniform_location location, const float (&array)[4])
{
    setUniformFloatArray4Ptr(location, array);
}

void gl::ShaderProgram::setUniformFloatArray1(const char *name, const float (&array)[1])
{
    setUniformFloatArray1Ptr(name, array);
}

void gl::ShaderProgram::setUniformFloatArray2(const char *name, const float (&array)[2])
{
    setUniformFloatArray2Ptr(name, array);
}

void gl::ShaderProgram::setUniformFloatArray3(const char *name, const float (&array)[3])
{
    setUniformFloatArray3Ptr(name, array);
}

void gl::ShaderProgram::setUniformFloatArray4(const char *name, const float (&array)[4])
{
    setUniformFloatArray4Ptr(name, array);
}

void gl::ShaderProgram::setUniformIntArray1(uniform_location location, const int (&array)[1])
{
    setUniformIntArray1Ptr(location, array);
}

void gl::ShaderProgram::setUniformIntArray2(uniform_location location, const int (&array)[2])
{
    setUniformIntArray2Ptr(location, array);
}

void gl::ShaderProgram::setUniformIntArray3(uniform_location location, const int (&array)[3])
{
    setUniformIntArray3Ptr(location, array);
}

void gl::ShaderProgram::setUniformIntArray4(uniform_location location, const int (&array)[4])
{
    setUniformIntArray4Ptr(location, array);
}

void gl::ShaderProgram::setUniformIntArray1(const char *name, const int (&array)[1])
{
    setUniformIntArray1Ptr(name, array);
}

void gl::ShaderProgram::setUniformIntArray2(const char *name, const int (&array)[2])
{
    setUniformIntArray2Ptr(name, array);
}

void gl::ShaderProgram::setUniformIntArray3(const char *name, const int (&array)[3])
{
    setUniformIntArray3Ptr(name, array);
}

void gl::ShaderProgram::setUniformIntArray4(const char *name, const int (&array)[4])
{
    setUniformIntArray4Ptr(name, array);
}

// -----------------------------------------------------------------------------

void gl::ShaderProgram::setUniformMatrix2(gl::ShaderProgram::uniform_location location, const float *values, bool transpose)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    GLWRAP_GL_CHECK( glUniformMatrix2fv(location, 1, (transpose ? GL_TRUE : GL_FALSE), values) );
}

void gl::ShaderProgram::setUniformMatrix3(gl::ShaderProgram::uniform_location location, const float *values, bool transpose)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    GLWRAP_GL_CHECK( glUniformMatrix3fv(location, 1, (transpose ? GL_TRUE : GL_FALSE), values) );
}

void gl::ShaderProgram::setUniformMatrix4(gl::ShaderProgram::uniform_location location, const float *values, bool transpose)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    GLWRAP_GL_CHECK( glUniformMatrix4fv(location, 1, (transpose ? GL_TRUE : GL_FALSE), values) );
}

void gl::ShaderProgram::setUniformMatrix2(const char *name, const float *values, bool transpose)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    SET_UNIFORM_VALUES_BY_NAME( setUniformMatrix2, values, transpose);
}

void gl::ShaderProgram::setUniformMatrix3(const char *name, const float *values, bool transpose)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    SET_UNIFORM_VALUES_BY_NAME( setUniformMatrix3, values, transpose);
}

void gl::ShaderProgram::setUniformMatrix4(const char *name, const float *values, bool transpose)
{
    GLWRAP_CHECK_BINDED_SHADER_PROGRAM;

    SET_UNIFORM_VALUES_BY_NAME( setUniformMatrix4, values, transpose);
}

// -----------------------------------------------------------------------------

bool gl::ShaderProgram::isDeleted() const
{
    GLint status;
    GLWRAP_GL_CHECK( glGetProgramiv(_id, GL_DELETE_STATUS, &status) );
    return (status != GL_FALSE);
}

bool gl::ShaderProgram::isLinked() const
{
    GLint status;
    GLWRAP_GL_CHECK( glGetProgramiv(_id, GL_LINK_STATUS, &status) );
    return (status != GL_FALSE);
}

bool gl::ShaderProgram::isValid() const
{
    GLint status;
    GLWRAP_GL_CHECK( glGetProgramiv(_id, GL_VALIDATE_STATUS, &status) );
    return (status != GL_FALSE);
}

int gl::ShaderProgram::getInfoLogLength() const
{
    GLint length;
    GLWRAP_GL_CHECK( glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &length) );
    return length;
}

int gl::ShaderProgram::getAttachedShadersCount() const
{
    GLint count;
    GLWRAP_GL_CHECK( glGetProgramiv(_id, GL_ATTACHED_SHADERS, &count) );
    return count;
}

int gl::ShaderProgram::getActiveAttributesCount() const
{
    GLint count;
    GLWRAP_GL_CHECK( glGetProgramiv(_id, GL_ACTIVE_ATTRIBUTES, &count) );
    return count;
}

int gl::ShaderProgram::getActiveAttributeMaxLenght() const
{
    GLint length;
    GLWRAP_GL_CHECK( glGetProgramiv(_id, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &length) );
    return length;
}

int gl::ShaderProgram::getActiveUniformsCount() const
{
    GLint count;
    GLWRAP_GL_CHECK( glGetProgramiv(_id, GL_ACTIVE_UNIFORMS, &count) );
    return count;
}

int gl::ShaderProgram::getActiveUniformMaxLenght() const
{
    GLint length;
    GLWRAP_GL_CHECK( glGetProgramiv(_id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &length) );
    return length;
}

std::vector<unsigned int> gl::ShaderProgram::getAttachedShaders() const
{
    const int buf_lenght = getAttachedShadersCount();
    if(buf_lenght > 0)
    {
        std::vector<unsigned int> buf(buf_lenght);

        GLsizei actual_count = 0; // Unused, since we already know count
        GLWRAP_GL_CHECK( glGetAttachedShaders(_id, buf_lenght, &actual_count, buf.data()) );

        return buf;
    }

    return {};
}

std::string gl::ShaderProgram::getInfoLog() const
{
    const int buf_length = getInfoLogLength();
    if(buf_length > 1) // Check for '>1', not '>0', since length includes 'null terminator'
    {
        char* buffer = new char[buf_length];

        GLsizei actual_length = 0; // Unused, since we already know size
        GLWRAP_GL_CHECK( glGetProgramInfoLog(_id, buf_length, &actual_length, buffer) );

        // FIXME: here is copy!
        std::string result(buffer, buf_length);
        delete [] buffer;

        return result;
    }

    return {};
}

gl::ShaderProgram::id_t gl::ShaderProgram::getCurrentId()
{
    GLint current_program;
    GLWRAP_GL_CHECK( glGetIntegerv(GL_CURRENT_PROGRAM, &current_program) );
    return static_cast<id_t>(current_program);
}

void gl::ShaderProgram::setCurrentId(gl::Object::id_t id)
{
    GLWRAP_GL_CHECK( glUseProgram(id) );
}

bool gl::ShaderProgram::isCurrent() const
{
    return isOk() && (_id == getCurrentId());
}

bool gl::ShaderProgram::isOk() const
{
    GLboolean result;
    GLWRAP_GL_CHECK( result = glIsProgram(_id) );
    return (result != GL_FALSE);
}

const char *gl::get_shader_variable_type_str(int type)
{
    switch (type) {
    case GL_FLOAT:             return "GL_FLOAT";      // Attribute || Uniform
    case GL_FLOAT_VEC2:        return "GL_FLOAT_VEC2"; // Attribute || Uniform
    case GL_FLOAT_VEC3:        return "GL_FLOAT_VEC3"; // Attribute || Uniform
    case GL_FLOAT_VEC4:        return "GL_FLOAT_VEC4"; // Attribute || Uniform

    case GL_INT:               return "GL_INT";
    case GL_INT_VEC2:          return "GL_INT_VEC2";
    case GL_INT_VEC3:          return "GL_INT_VEC3";
    case GL_INT_VEC4:          return "GL_INT_VEC4";

    case GL_BOOL:              return "GL_BOOL";
    case GL_BOOL_VEC2:         return "GL_BOOL_VEC2";
    case GL_BOOL_VEC3:         return "GL_BOOL_VEC3";
    case GL_BOOL_VEC4:         return "GL_BOOL_VEC4";

    case GL_FLOAT_MAT2:        return "GL_FLOAT_MAT2";    // Attribute || Uniform
    case GL_FLOAT_MAT3:        return "GL_FLOAT_MAT3";    // Attribute || Uniform
    case GL_FLOAT_MAT4:        return "GL_FLOAT_MAT4";    // Attribute || Uniform

#if defined(GL_FLOAT_MAT2x3)
    case GL_FLOAT_MAT2x3:      return "GL_FLOAT_MAT2x3";  // Attribute || Uniform
#endif
#if defined(GL_FLOAT_MAT2x4)
    case GL_FLOAT_MAT2x4:      return "GL_FLOAT_MAT2x4";  // Attribute || Uniform
#endif
#if defined(GL_FLOAT_MAT3x2)
    case GL_FLOAT_MAT3x2:      return "GL_FLOAT_MAT3x2";  // Attribute || Uniform
#endif
#if defined(GL_FLOAT_MAT3x4)
    case GL_FLOAT_MAT3x4:      return "GL_FLOAT_MAT3x4";  // Attribute || Uniform
#endif
#if defined(GL_FLOAT_MAT4x2)
    case GL_FLOAT_MAT4x2:      return "GL_FLOAT_MAT4x2";  // Attribute || Uniform
#endif
#if defined(GL_FLOAT_MAT4x3)
    case GL_FLOAT_MAT4x3:      return "GL_FLOAT_MAT4x3";  // Attribute || Uniform
#endif

#if defined(GL_SAMPLER_1D)
    case GL_SAMPLER_1D:        return "GL_SAMPLER_1D";
#endif
    case GL_SAMPLER_2D:        return "GL_SAMPLER_2D";
#if defined(GL_SAMPLER_3D)
    case GL_SAMPLER_3D:        return "GL_SAMPLER_3D";
#endif
    case GL_SAMPLER_CUBE:      return "GL_SAMPLER_CUBE";

#if defined(GL_SAMPLER_1D_SHADOW)
    case GL_SAMPLER_1D_SHADOW: return "GL_SAMPLER_1D_SHADOW";
#endif
#if defined(GL_SAMPLER_2D_SHADOW)
    case GL_SAMPLER_2D_SHADOW: return "GL_SAMPLER_2D_SHADOW";
#endif
    default: return "Unknown";
    }
}
