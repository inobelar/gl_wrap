#pragma once

#include <gl_wrap/utils/gl_Rect.hpp>

namespace gl {

struct Scissor
{
    /*
        OpenGL Scissor rect coordinates is going from bottom-left:

        (0, H) ^---------------+ (W, H)
               ^               |
               ^               |
               ^               |
        (0, 0) +--->--->--->---> (W, 0)
    */

    // -------------------------------------------------------------------------

    static void setEnabled(bool enabled);
    static bool isEnabled();

    static void setRect(int x, int y, int width, int height);
    static void getRect(int& x, int& y, int& width, int& height);

    static void setRect(const gl::Rect& rect);
    static gl::Rect getRect();

    // -------------------------------------------------------------------------
    // TODO: scissor array (since OpenGL 4.1):
    //   https://www.khronos.org/opengl/wiki/Scissor_Test
};

} // namespace gl
