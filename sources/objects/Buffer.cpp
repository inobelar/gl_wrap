#include <gl_wrap/objects/Buffer.hpp>

#include <gl_wrap/gl_context.hpp>
#include <gl_wrap/gl_error_checking.hpp>

#if defined(GLWRAP_CHECK_BINDED)
    #include <cassert> // for assert()

    #define GLWRAP_CHECK_BINDED_BUFFER \
        assert(this->isBinded() == true)
#else
    #define GLWRAP_CHECK_BINDED_BUFFER
#endif

// -----------------------------------------------------------------------------

gl::Buffer::Buffer(int target)
    : Object()
    , _target(target)
{
    GLWRAP_GL_CHECK( glGenBuffers(1, &_id) );
}

gl::Buffer::~Buffer()
{
    GLWRAP_GL_CHECK( glDeleteBuffers(1, &_id) );
}

// -----------------------------------------------------------------------------

void gl::Buffer::bind()
{
    GLWRAP_GL_CHECK( glBindBuffer(_target, _id) );
}

void gl::Buffer::unbind()
{
    GLWRAP_GL_CHECK( glBindBuffer(_target, 0) );
}

// -----------------------------------------------------------------------------

void gl::Buffer::setDataRaw(size_t size, const void* data, int usage)
{
    GLWRAP_CHECK_BINDED_BUFFER;

    GLWRAP_GL_CHECK( glBufferData(_target, size, data, usage) );
}

void gl::Buffer::setSubDataRaw(long offset, size_t size, const void *data)
{
    GLWRAP_CHECK_BINDED_BUFFER;

    // TODO: check is offset > 0 && offset < curr_size
    // TODO: check is size < curr_size
    // TODO: check is (offset + size) < curr_size

    GLWRAP_GL_CHECK( glBufferSubData(_target, offset, size, data) );
}

// -----------------------------------------------------------------------------

#if !defined(GLWRAP_GL_GLES)
int gl::Buffer::getAccess()
{
    GLWRAP_CHECK_BINDED_BUFFER;

    GLint result = 0;
    GLWRAP_GL_CHECK( glGetBufferParameteriv(_target, GL_BUFFER_ACCESS, &result) );
    return result;
}
#endif

int gl::Buffer::getAccessFlags()
{
    GLWRAP_CHECK_BINDED_BUFFER;

    GLint result = 0;
    GLWRAP_GL_CHECK( glGetBufferParameteriv(_target, GL_BUFFER_ACCESS_FLAGS, &result) );
    return result;
}

#if !defined(GLWRAP_GL_GLES)
bool gl::Buffer::isImmutableStorage()
{
    GLWRAP_CHECK_BINDED_BUFFER;

    GLint result = 0;
    GLWRAP_GL_CHECK( glGetBufferParameteriv(_target, GL_BUFFER_IMMUTABLE_STORAGE, &result) );
    return (result != GL_FALSE);
}
#endif

bool gl::Buffer::isMapped()
{
    GLWRAP_CHECK_BINDED_BUFFER;

    GLint result = 0;
    GLWRAP_GL_CHECK( glGetBufferParameteriv(_target, GL_BUFFER_MAPPED, &result) );
    return (result != GL_FALSE);
}

size_t gl::Buffer::getMapLenght()
{
    GLWRAP_CHECK_BINDED_BUFFER;

    GLint result = 0;
    GLWRAP_GL_CHECK( glGetBufferParameteriv(_target, GL_BUFFER_MAP_LENGTH, &result) );

    return result;
}

int gl::Buffer::getMapOffset()
{
    GLWRAP_CHECK_BINDED_BUFFER;

    GLint result = 0;
    GLWRAP_GL_CHECK( glGetBufferParameteriv(_target, GL_BUFFER_MAP_OFFSET, &result) );
    return result;
}

size_t gl::Buffer::getSize()
{
    GLWRAP_CHECK_BINDED_BUFFER;

    GLint result = 0;
    GLWRAP_GL_CHECK( glGetBufferParameteriv(_target, GL_BUFFER_SIZE, &result) );

    return result;
}

#if !defined(GLWRAP_GL_GLES)
int gl::Buffer::getStorageFlags()
{
    GLWRAP_CHECK_BINDED_BUFFER;

    GLint result = 0;
    GLWRAP_GL_CHECK( glGetBufferParameteriv(_target, GL_BUFFER_STORAGE_FLAGS, &result) );
    return result;
}
#endif

int gl::Buffer::getUsage()
{
    GLWRAP_CHECK_BINDED_BUFFER;

    GLint result = 0;
    GLWRAP_GL_CHECK( glGetBufferParameteriv(_target, GL_BUFFER_USAGE, &result) );
    return result;
}

// -----------------------------------------------------------------------------

bool gl::Buffer::isOk() const
{
    GLboolean result;
    GLWRAP_GL_CHECK(result = glIsBuffer(_id) );
    return (result != GL_FALSE);
}

// -----------------------------------------------------------------------------

gl::Buffer::id_t gl::Buffer::getBindedId() const
{
    GLint currently_binded = 0;

    GLenum target_to_check = 0;
    switch (_target) {
    case GL_ARRAY_BUFFER:              { target_to_check = GL_ARRAY_BUFFER_BINDING;             } break;
#if defined(GL_ATOMIC_COUNTER_BUFFER)
    case GL_ATOMIC_COUNTER_BUFFER:     { target_to_check = GL_ATOMIC_COUNTER_BUFFER_BINDING;    } break;
#endif
#if defined(GL_COPY_READ_BUFFER)
    case GL_COPY_READ_BUFFER:          { target_to_check = GL_COPY_READ_BUFFER_BINDING;         } break;
#endif
#if defined(GL_COPY_WRITE_BUFFER)
    case GL_COPY_WRITE_BUFFER:         { target_to_check = GL_COPY_WRITE_BUFFER_BINDING;        } break;
#endif
#if defined(GL_DISPATCH_INDIRECT_BUFFER)
    case GL_DISPATCH_INDIRECT_BUFFER:  { target_to_check = GL_DISPATCH_INDIRECT_BUFFER_BINDING; } break;
#endif
#if defined (GL_DRAW_INDIRECT_BUFFER)
    case GL_DRAW_INDIRECT_BUFFER:      { target_to_check = GL_DRAW_INDIRECT_BUFFER_BINDING;     } break;
#endif
    case GL_ELEMENT_ARRAY_BUFFER:      { target_to_check = GL_ELEMENT_ARRAY_BUFFER_BINDING;     } break;
#if defined(GL_PIXEL_PACK_BUFFER)
    case GL_PIXEL_PACK_BUFFER:         { target_to_check = GL_PIXEL_PACK_BUFFER_BINDING;        } break;
#endif
#if defined(GL_PIXEL_UNPACK_BUFFER)
    case GL_PIXEL_UNPACK_BUFFER:       { target_to_check = GL_PIXEL_UNPACK_BUFFER_BINDING;      } break;
#endif
#if defined(GL_QUERY_BUFFER)
    case GL_QUERY_BUFFER:              { target_to_check = GL_QUERY_BUFFER_BINDING;             } break;
#endif
#if defined(GL_SHADER_STORAGE_BUFFER)
    case GL_SHADER_STORAGE_BUFFER:     { target_to_check = GL_SHADER_STORAGE_BUFFER_BINDING;    } break;
#endif
#if defined(GL_TEXTURE_BUFFER)
    case GL_TEXTURE_BUFFER:            { target_to_check = GL_TEXTURE_BUFFER_BINDING;           } break;
#endif
#if defined(GL_TRANSFORM_FEEDBACK_BUFFER)
    case GL_TRANSFORM_FEEDBACK_BUFFER: { target_to_check = GL_TRANSFORM_FEEDBACK_BINDING;       } break;
#endif
#if defined(GL_UNIFORM_BUFFER)
    case GL_UNIFORM_BUFFER:            { target_to_check = GL_UNIFORM_BUFFER_BINDING;           } break;
#endif
    }

    if(target_to_check != 0) {
        GLWRAP_GL_CHECK( glGetIntegerv(target_to_check, &currently_binded) );
    }

    return static_cast<id_t>(currently_binded);
}

void gl::Buffer::setBindedId(int target, gl::Object::id_t id)
{
    GLWRAP_GL_CHECK( glBindBuffer(target, id) );
}

bool gl::Buffer::isBinded() const
{
    return isOk() && (_id == getBindedId());
}

// -----------------------------------------------------------------------------

const char *gl::get_buffer_target_str(int target)
{
    switch (target) {
    case GL_ARRAY_BUFFER:              return "GL_ARRAY_BUFFER";
#if defined(GL_ATOMIC_COUNTER_BUFFER)
    case GL_ATOMIC_COUNTER_BUFFER:     return "GL_ATOMIC_COUNTER_BUFFER";
#endif
#if defined(GL_COPY_READ_BUFFER)
    case GL_COPY_READ_BUFFER:          return "GL_COPY_READ_BUFFER";
#endif
#if defined(GL_COPY_WRITE_BUFFER)
    case GL_COPY_WRITE_BUFFER:         return "GL_COPY_WRITE_BUFFER";
#endif
#if defined(GL_DISPATCH_INDIRECT_BUFFER)
    case GL_DISPATCH_INDIRECT_BUFFER:  return "GL_DISPATCH_INDIRECT_BUFFER";
#endif
#if defined(GL_DRAW_INDIRECT_BUFFER)
    case GL_DRAW_INDIRECT_BUFFER:      return "GL_DRAW_INDIRECT_BUFFER";
#endif
    case GL_ELEMENT_ARRAY_BUFFER:      return "GL_ELEMENT_ARRAY_BUFFER";
#if defined(GL_PIXEL_PACK_BUFFER)
    case GL_PIXEL_PACK_BUFFER:         return "GL_PIXEL_PACK_BUFFER";
#endif
#if defined(GL_PIXEL_UNPACK_BUFFER)
    case GL_PIXEL_UNPACK_BUFFER:       return "GL_PIXEL_UNPACK_BUFFER";
#endif
#if defined(GL_QUERY_BUFFER)
    case GL_QUERY_BUFFER:              return "GL_QUERY_BUFFER";
#endif
#if defined(GL_SHADER_STORAGE_BUFFER)
    case GL_SHADER_STORAGE_BUFFER:     return "GL_SHADER_STORAGE_BUFFER";
#endif
#if defined(GL_TEXTURE_BUFFER)
    case GL_TEXTURE_BUFFER:            return "GL_TEXTURE_BUFFER";
#endif
#if defined(GL_TRANSFORM_FEEDBACK_BUFFER)
    case GL_TRANSFORM_FEEDBACK_BUFFER: return "GL_TRANSFORM_FEEDBACK_BUFFER";
#endif
#if defined(GL_UNIFORM_BUFFER)
    case GL_UNIFORM_BUFFER:            return "GL_UNIFORM_BUFFER";
#endif
    default: return "Unknown";
    }
}

const char *gl::get_buffer_target_description_str(int target)
{
    switch (target) {
    case GL_ARRAY_BUFFER:              return "Vertex attributes";
#if defined(GL_ATOMIC_COUNTER_BUFFER)
    case GL_ATOMIC_COUNTER_BUFFER:     return "Atomic counter storage";
#endif
#if defined(GL_COPY_READ_BUFFER)
    case GL_COPY_READ_BUFFER:          return "Buffer copy source";
#endif
#if defined(GL_COPY_WRITE_BUFFER)
    case GL_COPY_WRITE_BUFFER:         return "Buffer copy destination";
#endif
#if defined(GL_DISPATCH_INDIRECT_BUFFER)
    case GL_DISPATCH_INDIRECT_BUFFER:  return "Indirect compute dispatch commands";
#endif
#if defined(GL_DRAW_INDIRECT_BUFFER)
    case GL_DRAW_INDIRECT_BUFFER:      return "Indirect command arguments";
#endif
    case GL_ELEMENT_ARRAY_BUFFER:      return "Vertex array indices";
#if defined(GL_PIXEL_PACK_BUFFER)
    case GL_PIXEL_PACK_BUFFER:         return "Pixel read target";
#endif
#if defined(GL_PIXEL_UNPACK_BUFFER)
    case GL_PIXEL_UNPACK_BUFFER:       return "Texture data source";
#endif
#if defined(GL_QUERY_BUFFER)
    case GL_QUERY_BUFFER:              return "Query result buffer";
#endif
#if defined(GL_SHADER_STORAGE_BUFFER)
    case GL_SHADER_STORAGE_BUFFER:     return "Read-write storage for shaders";
#endif
#if defined(GL_TEXTURE_BUFFER)
    case GL_TEXTURE_BUFFER:            return "Texture data buffer";
#endif
#if defined(GL_TRANSFORM_FEEDBACK_BUFFER)
    case GL_TRANSFORM_FEEDBACK_BUFFER: return "Transform feedback buffer";
#endif
#if defined(GL_UNIFORM_BUFFER)
    case GL_UNIFORM_BUFFER:            return "Uniform block storage";
#endif
    default: return "Unknown";
    }
}
