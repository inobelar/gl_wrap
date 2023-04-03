#include <gl_wrap/utils/gl_ColorRGBA.hpp>

#include <cmath>   // for std::isnan()

// -----------------------------------------------------------------------------
// Compile-time tests (hidden here, to execute them once, not on each include)

static_assert(
    sizeof(gl::ColorRGBA) == (sizeof(float) * 4),
    "gl::ColorRGBA size is not the same as data in it"
);

static_assert( gl::ColorRGBA::fromUInts(255,0,255,0) == gl::ColorRGBA(1.0f, 0.0f, 1.0f, 0.0f), "Test failed");

// -----------------------------------------------------------------------------

/*
    The body of this function is implemented here (in source *.cpp file, not in
    header *.hpp file), since:

      - We dont want to expose <cmath> as public include, which causes
        unnecessary types & functions 'pollution'

      - This function, due to non-constexpr `std::isnan()` usage cannot be
        constexpr, so may be freely hidden in *.cpp
*/
void gl::ColorRGBA::normalize()
{
    for(float& component : _values)
    {
        if     (std::isnan(component)) component = 0.0f;
        else if(component < 0.0f)      component = 0.0f;
        else if(component > 1.0f)      component = 1.0f;
    }
}
