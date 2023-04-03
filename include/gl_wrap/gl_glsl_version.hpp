#pragma once

namespace gl {

/**
    ## References:

    - https://en.wikipedia.org/wiki/OpenGL_Shading_Language#Versions
    - https://stackoverflow.com/a/19022416/
    - https://stackoverflow.com/tags/glsl/info
    - https://stackoverflow.com/a/62026028/

    ## Notes about implementation

    - Compile-time function form used to allow function execution both in
      run-time and compile-time.

        @code{.cpp}

        // Get OpenGL version in run-time
        GLint gl_version_major = 0, gl_version_minor = 0;
        glGetIntegerv(GL_MAJOR_VERSION, &gl_version_major);
        glGetIntegerv(GL_MINOR_VERSION, &gl_version_minor);

        // Get GLSL version
        const auto glsl_version = gl::get_glsl_version(gl_version_major, gl_version_minor, false);
        if( glsl_version.is_defined() ) {
            // ...
        }
        @endcode

      Alternate solution, much readable, but not allows run-time is:

        @code{.cpp}
        template <int gl_version_major, int gl_version_minor, bool gl_es>
        struct glsl_version { static constexpr GLSL_Version info = GLSL_Version::undefined(); };

        // OpenGL GLSL version
        template <>
        struct glsl_version<2, 0, false> { static constexpr GLSL_Version info = GLSL_Version(110, "110"); };
        template <>
        struct glsl_version<2, 1, false> { static constexpr GLSL_Version info = GLSL_Version(120, "120"); };
        // ...

        // OpenGL ES GLSL version
        template <>
        struct glsl_version<2, 0, true> { static constexpr GLSL_Version info = GLSL_Version(100, "100 es"); };
        template <>
        struct glsl_version<3, 0, true> { static constexpr GLSL_Version info = GLSL_Version(300, "300 es"); };
        template <>
        struct glsl_version<3, 1, true> { static constexpr GLSL_Version info = GLSL_Version(310, "310 es"); };
        // ...

        // Compile-time testing
        static_assert( glsl_version<0, 0, false>::info.version ==   0, "Test failed");
        static_assert( glsl_version<2, 0, false>::info.version == 110, "Test failed");
        static_assert( glsl_version<2, 1, false>::info.version == 120, "Test failed");
        static_assert( glsl_version<0, 0,  true>::info.version ==   0, "Test failed");
        static_assert( glsl_version<2, 0,  true>::info.version == 100, "Test failed");
        @endcode

    - Ternary-operator form (which is kinda unreadable) is used, due to C++11
      support.

      In C++11, in constexpr-function, we cannot use `if/else` or `switch` for
      conditional branching control, except ternary operators. That ability is
      come only since C++14, and in that case functions may be implemented in
      the next form:

        @code{.cpp}
        constexpr uint16_t pack_version(int major, int minor)
        {
            return ( ((uint16_t)(uint8_t)(major) << 8) |
                     ((uint16_t)(uint8_t)(minor)) );
        }

        constexpr int get_glsl_version(int gl_version_major, int gl_version_minor, bool gl_es)
        {
            if(gl_es == false)
            {
                switch( pack_version(gl_version_major, gl_version_minor) )
                {
                    case pack_version(2, 0): return GLSL_Version(110, "110");
                    case pack_version(2, 1): return GLSL_Version(120, "120");
                    case pack_version(3, 0): return GLSL_Version(130, "130");
                    // ...
                    default: return GLSL_Version::undefined();
                }
            }
            else // (gl_es == true)
            {
                switch( pack_version(gl_version_major, gl_version_minor) )
                {
                    case pack_version(2, 0): return GLSL_Version::(100, "100 es");
                    case pack_version(3, 0): return GLSL_Version::(300, "300 es");
                    case pack_version(3, 1): return GLSL_Version::(310, "310 es");
                    // ...
                    default: return GLSL_Version::undefined();
                }
            }
        }
        @endcode

    - Unfortunately we cannot split `constexpr` functions on header & source
      files. Also them implicetely marked as `inline`.

    ----------------------------------------------------------------------------

    Alternate solution, instead of using this functions - to use
    `GL_SHADING_LANGUAGE_VERSION`, which requires run-time parsing after OpenGL
    context initialization, accordingly to:
        https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetString.xhtml

        > The `GL_VERSION` and `GL_SHADING_LANGUAGE_VERSION` strings begin with a
        > version number. The version number uses one of these forms:
        > `major_number.minor_number` `major_number.minor_number.release_number`
        >
        > Vendor-specific information may follow the version number. Its format
        > depends on the implementation, but a space always separates the
        > version number and the vendor-specific information.
*/

struct GLSL_Version
{
    const int   version = 0;
    const char* str     = nullptr;

    constexpr GLSL_Version(int version_, const char* str_)
        : version(version_), str(str_)
    {}

    // Explicitely named c-tor (instead default c-tor) for readability
    static constexpr GLSL_Version undefined() {
        return GLSL_Version(0, nullptr);
    }

    constexpr bool is_defined() const {
        return (version != 0);
    }
};

constexpr GLSL_Version get_glsl_gl_version(int gl_version_major, int gl_version_minor)
{
    return
            /* if */ (gl_version_major == 2) ?
            (
                /* if */ (gl_version_minor == 0) ?
                (
                    GLSL_Version(110, "110") /* OpenGL 2.0 */
                )
                /* else */ : /* (gl_version_minor != 0) */
                (
                    /* if */ (gl_version_minor == 1) ?
                    (
                        GLSL_Version(120, "120") /* OpenGL 2.1 */
                    )
                    /* else */ : /* (gl_version_minor != 1) */
                    (
                        GLSL_Version::undefined() /* OpenGL 2.x - undefined */
                    )
                )
            )
            /* else */ : /* (gl_version_major != 2) */
            (
                /* if */ (gl_version_major == 3) ?
                (
                    /* if */ (gl_version_minor == 0) ?
                    (
                        GLSL_Version(130, "130") /* OpenGL 3.0 */
                    )
                    /* else */ : /* (gl_version_minor != 0) */
                    (
                        /* if */ (gl_version_minor == 1) ?
                        (
                            GLSL_Version(140, "140") /* OpenGL 3.1 */
                        )
                        /* else */ : /* (gl_version_minor != 1) */
                        (
                            /* if */ (gl_version_minor == 2) ?
                            (
                                GLSL_Version(150, "150") /* OpenGL 3.2 */
                            )
                            /* else */ : /* (gl_version_minor != 2) */
                            (
                                /* if */ (gl_version_minor == 3) ?
                                (
                                    GLSL_Version(330, "330") /* OpenGL 3.3 */
                                )
                                /* else */ : /* (gl_version_minor != 3) */
                                (
                                    GLSL_Version::undefined() /* OpenGL 3.x - undefined */
                                )
                            )
                        )
                    )
                )
                /* else */ : /* (gl_version_major != 3) */
                (
                    /* if */ (gl_version_major == 4) ?
                    (
                        /* if */ (gl_version_minor == 0) ?
                        (
                            GLSL_Version(400, "400") /* OpenGL 4.0 */
                        )
                        /* else */ : /* (gl_version_minor != 0) */
                        (
                            /* if */ (gl_version_minor == 1) ?
                            (
                                GLSL_Version(410, "410") /* OpenGL 4.1 */
                            )
                            /* else */ : /* (gl_version_minor != 1) */
                            (
                                /* if */ (gl_version_minor == 2) ?
                                (
                                    GLSL_Version(420, "420") /* OpenGL 4.2 */
                                )
                                /* else */ : /* (gl_version_minor != 2) */
                                (
                                    /* if */ (gl_version_minor == 3) ?
                                    (
                                        GLSL_Version(430, "430") /* OpenGL 4.3 */
                                    )
                                    /* else */ : /* (gl_version_minor != 3) */
                                    (
                                        /* if */ (gl_version_minor == 4) ?
                                        (
                                            GLSL_Version(440, "440") /* OpenGL 4.4 */
                                        )
                                        /* else */ : /* (gl_version_minor != 4) */
                                        (
                                            /* if */ (gl_version_minor == 5) ?
                                            (
                                                GLSL_Version(450, "450") /* OpenGL 4.5 */
                                            )
                                            /* else */ : /* (gl_version_minor != 5) */
                                            (
                                                /* if */ (gl_version_minor == 6) ?
                                                (
                                                    GLSL_Version(460, "460") /* OpenGL 4.6 */
                                                )
                                                /* else */ : /* (gl_version_minor != 6) */
                                                (
                                                    GLSL_Version::undefined() /* OpenGL 4.x - undefined */
                                                )
                                            )
                                        )
                                    )
                                )
                            )
                        )
                    )
                    /* else */ : /* (gl_version_major != 4) */
                    (
                        GLSL_Version::undefined() /* OpenGL x.x - undefined */
                    )
                )
            );
}

constexpr GLSL_Version get_glsl_es_version(int gl_version_major, int gl_version_minor)
{
    return
            /* if */ (gl_version_major == 2) ?
            (
                /* if */ (gl_version_minor == 0) ?
                (
                    GLSL_Version(100, "100 es") /* OpenGL ES 2.0 */
                )
                /* else */ : /* (gl_version_minor != 0) */
                (
                    GLSL_Version::undefined() /* OpenGL ES 2.x - undefined */
                )
            )
            /* else */ : /* (gl_version_major != 2) */
            (
                /* if */ (gl_version_major == 3) ?
                (
                    /* if */ (gl_version_minor == 0) ?
                    (
                        GLSL_Version(300, "300 es") /* OpenGL ES 3.0 */
                    )
                    /* else */ : /* (gl_version_minor != 0) */
                    (
                        /* if */ (gl_version_minor == 1) ?
                        (
                            GLSL_Version(310, "310 es") /* OpenGL ES 3.1 */
                        )
                        /* else */ : /* (gl_version_minor != 1) */
                        (
                            /* if */ (gl_version_minor == 2) ?
                            (
                                GLSL_Version(320, "320 es") /* OpenGL ES 3.2 */
                            )
                            /* else */ : /* (gl_version_minor != 2) */
                            (
                                GLSL_Version::undefined() /* OpenGL ES 3.x - undefined */
                            )
                        )
                    )
                )
                /* else */ : /* (gl_version_major != 3) */
                (
                    GLSL_Version::undefined() /* OpenGL ES x.x - undefined */
                )
            );
}

constexpr GLSL_Version get_glsl_version(int gl_version_major, int gl_version_minor, bool gl_es)
{
    return
            /* if */ (gl_es == false) ?
            (
                get_glsl_gl_version(gl_version_major, gl_version_minor)
            )
            /* else */ : /* (gl_es == true) */
            (
                get_glsl_es_version(gl_version_major, gl_version_minor)
            );
}

} // namespace gl
