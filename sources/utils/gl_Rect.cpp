#include <gl_wrap/utils/gl_Rect.hpp>

// -----------------------------------------------------------------------------
// Compile-time tests (hidden here, to execute them once, not on each include)

static_assert(
    sizeof(gl::Rect) == (sizeof(int) * 4),
    "gl::Rect size is not the same as data in it"
);

// -----------------------------------------------------------------------------
