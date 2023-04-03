#include <gl_wrap/gl_version.hpp>

// -----------------------------------------------------------------------------
// Compile-time tests (hidden here, to execute them once, not on each include)

// Make sure, that `GLWRAP_GL_VER_CHECK` implemented correctly - Major and Minor
// versions is really `packed`, not simply `added`.
static_assert(GLWRAP_GL_VER_CHECK(2, 3) != GLWRAP_GL_VER_CHECK(3, 2), "Test failed");

// -----------------------------------------------------------------------------
