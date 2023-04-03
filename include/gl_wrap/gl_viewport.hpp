#pragma once

#include <gl_wrap/utils/gl_Rect.hpp>

namespace gl {

struct Viewport
{
    /*
        OpenGL Viewport rect coordinates is going from bottom-left:

        (0, H) ^---------------+ (W, H)
               ^               |
               ^               |
               ^               |
        (0, 0) +--->--->--->---> (W, 0)
    */

    // -------------------------------------------------------------------------

    static void setRect(int x, int y, int width, int height);
    static void getRect(int& x, int& y, int& width, int& height);

    static void setRect(const gl::Rect& rect);
    static gl::Rect getRect();

    // -------------------------------------------------------------------------

    static void getMaxDimentions(int& width, int& height);

    // -------------------------------------------------------------------------
    // TODO: viewport array (since OpenGL 4.1)
    //   https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glViewportArray.xhtml
};

} // namespace gl
