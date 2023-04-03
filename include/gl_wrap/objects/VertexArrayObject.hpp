#pragma once

#include <gl_wrap/objects/Object.hpp>

namespace gl {

class VertexArrayObject : public Object
{
public:

    VertexArrayObject();
    virtual ~VertexArrayObject();

    // -------------------------------------------------------------------------

    // Moveable
    GLWRAP_MOVE_DEFAULT(VertexArrayObject);

    // Non-copyable
    GLWRAP_PREVENT_COPY_AND_ASSIGN(VertexArrayObject);

    // -------------------------------------------------------------------------

    void bind();
    static void unbind();

    // -------------------------------------------------------------------------

    bool isOk() const;

    // -------------------------------------------------------------------------

    static id_t getBindedId();
    static void setBindedId(id_t id);
    bool isBinded() const;
};

} // namespace gl
