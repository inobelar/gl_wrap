#pragma once

#include <gl_wrap/utils/macros.hpp>

namespace gl {

class Object
{
public:

    using id_t = unsigned int; // Aka GLuint

protected:

    id_t _id;

public:

    Object();
    virtual ~Object();

    // -------------------------------------------------------------------------

    // Moveable
    GLWRAP_MOVE_DEFAULT(Object);

    // Non-copyable
    GLWRAP_PREVENT_COPY_AND_ASSIGN(Object);

    // -------------------------------------------------------------------------

    id_t getId() const;
};

} // namespace gl
