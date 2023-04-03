#include <gl_wrap/gl_glsl_version.hpp>

// -----------------------------------------------------------------------------
// Compile-time tests (hidden here, to execute them once, not on each include)

// OpenGL testing
static_assert( gl::get_glsl_version(0, 0, false).version ==   0, "Test Failed");
static_assert( gl::get_glsl_version(1, 0, false).version ==   0, "Test Failed");
static_assert( gl::get_glsl_version(1, 1, false).version ==   0, "Test Failed");
static_assert( gl::get_glsl_version(2, 0, false).version == 110, "Test Failed");
static_assert( gl::get_glsl_version(2, 1, false).version == 120, "Test Failed");
static_assert( gl::get_glsl_version(2, 2, false).version ==   0, "Test Failed");
static_assert( gl::get_glsl_version(3, 0, false).version == 130, "Test Failed");
static_assert( gl::get_glsl_version(3, 1, false).version == 140, "Test Failed");
static_assert( gl::get_glsl_version(3, 2, false).version == 150, "Test Failed");
static_assert( gl::get_glsl_version(3, 3, false).version == 330, "Test Failed");
static_assert( gl::get_glsl_version(3, 4, false).version ==   0, "Test Failed");
static_assert( gl::get_glsl_version(4, 0, false).version == 400, "Test Failed");
static_assert( gl::get_glsl_version(4, 1, false).version == 410, "Test Failed");
static_assert( gl::get_glsl_version(4, 2, false).version == 420, "Test Failed");
static_assert( gl::get_glsl_version(4, 3, false).version == 430, "Test Failed");
static_assert( gl::get_glsl_version(4, 4, false).version == 440, "Test Failed");
static_assert( gl::get_glsl_version(4, 5, false).version == 450, "Test Failed");
static_assert( gl::get_glsl_version(4, 6, false).version == 460, "Test Failed");
static_assert( gl::get_glsl_version(4, 7, false).version ==   0, "Test Failed");
static_assert( gl::get_glsl_version(5, 0, false).version ==   0, "Test Failed");
static_assert( gl::get_glsl_version(5, 1, false).version ==   0, "Test Failed");

// OpenGL ES testing
static_assert( gl::get_glsl_version(0, 0, true).version ==   0, "Test Failed");
static_assert( gl::get_glsl_version(1, 0, true).version ==   0, "Test Failed");
static_assert( gl::get_glsl_version(1, 1, true).version ==   0, "Test Failed");
static_assert( gl::get_glsl_version(2, 0, true).version == 100, "Test Failed");
static_assert( gl::get_glsl_version(2, 1, true).version ==   0, "Test Failed");
static_assert( gl::get_glsl_version(3, 0, true).version == 300, "Test Failed");
static_assert( gl::get_glsl_version(3, 1, true).version == 310, "Test Failed");
static_assert( gl::get_glsl_version(3, 2, true).version == 320, "Test Failed");
static_assert( gl::get_glsl_version(3, 3, true).version ==   0, "Test Failed");
static_assert( gl::get_glsl_version(4, 0, true).version ==   0, "Test Failed");
static_assert( gl::get_glsl_version(4, 1, true).version ==   0, "Test Failed");

// -----------------------------------------------------------------------------
