#pragma once

// -----------------------------------------------------------------------------

#define GLWRAP_PREVENT_COPY_AND_ASSIGN( TYPE ) \
    TYPE(const TYPE &) = delete;               \
    TYPE& operator = (const TYPE& ) = delete

#define GLWRAP_PREVENT_MOVE( TYPE ) \
    TYPE(TYPE &&) = delete;         \
    TYPE& operator = (TYPE &&) = delete

#define GLWRAP_PREVENT_COPY_ASSIGN_AND_MOVE( TYPE ) \
    GLWRAP_PREVENT_COPY_AND_ASSIGN(TYPE);           \
    GLWRAP_PREVENT_MOVE(TYPE)

// -----------------------------------------------------------------------------

#define GLWRAP_MOVE_DEFAULT( TYPE ) \
    TYPE(TYPE &&) = default;        \
    TYPE& operator = (TYPE &&) = default
