#pragma once

#include <gl_wrap/objects/Object.hpp>

#include <cstddef> // for size_t

namespace gl {

class Buffer : public Object
{
    int _target;

public:

    Buffer(int target);
    virtual ~Buffer();

    // -------------------------------------------------------------------------

    // Moveable
    GLWRAP_MOVE_DEFAULT(Buffer);

    // Non-copyable
    GLWRAP_PREVENT_COPY_AND_ASSIGN(Buffer);

    // -------------------------------------------------------------------------

    void bind();
    void unbind();

    // -------------------------------------------------------------------------

    void setDataRaw(size_t size, const void *data, int usage);

    template <typename T>
    inline void setDataItems(size_t count, const T* data, int usage) {
        setDataRaw((count * sizeof(T)), data, usage);
    }
    template <typename T, size_t SIZE>
    inline void setDataArray(const T(&array)[SIZE], int usage) {
        setDataItems(SIZE, array, usage);
    }

    // -------------------------------------------------------------------------

    void setSubDataRaw(long offset, size_t size, const void* data);

    template <typename T>
    inline void setSubDataItems(long offset, size_t size, const T* data) {
        setSubDataRaw(offset, (size * sizeof(T)), data);
    }

    template <typename T, size_t SIZE>
    inline void setSubDataArray(long offset, const T(&array)[SIZE]) {
        setSubDataItems(offset, SIZE, array);
    }

    // -------------------------------------------------------------------------

    // TODO: mapping: glMapBuffer(), glUnmapBuffer(), glGetBufferPointerv(), glGet( GL_MIN_MAP_BUFFER_ALIGNMENT ), *glMapBufferRange()*??, *glGetBufferSubData()*??

    // -------------------------------------------------------------------------
    // Parameters access

#if !defined(GLWRAP_GL_GLES) // GL_BUFFER_ACCESS not present in OpenGL ES
    int getAccess();
#endif

    int getAccessFlags();

#if !defined(GLWRAP_GL_GLES) // GL_BUFFER_IMMUTABLE_STORAGE not present in OpenGL ES
    bool isImmutableStorage();
#endif

    bool isMapped();
    size_t getMapLenght();
    int getMapOffset();

    /// Returns the size of the buffer object, measured in bytes
    size_t getSize();

#if !defined(GLWRAP_GL_GLES) // GL_BUFFER_STORAGE_FLAGS not present in OpenGL ES
    int getStorageFlags();
#endif

    int getUsage();

    // -------------------------------------------------------------------------

    bool isOk() const;

    // -------------------------------------------------------------------------

    id_t getBindedId() const;
    static void setBindedId(int target, id_t id);
    bool isBinded() const;
};

const char* get_buffer_target_str(int target);
const char* get_buffer_target_description_str(int target);

} // namespace gl
