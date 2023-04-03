#include <gl_wrap/gl_extensions.hpp>

#include <gl_wrap/gl_context.hpp>

#include <gl_wrap/gl_version.hpp>
#include <gl_wrap/gl_error_checking.hpp>

#include <cstring> // for strcmp(), strstr()

/*
    Modern way of getting extensions is:

        1. glGetIntegerv() + GL_NUM_EXTENSIONS
        2. glGetStringi()  + GL_EXTENSIONS

        Must be used in:
            - GL_OPENGL: 3.x
            - GL_GLES  : 3.x

        Reference:
            https://github.com/gonetz/GLideN64/issues/1092

    Old way is using:

        1. glGetString() + GL_EXTENSIONS

        Must be used in:
            - GL_OPENGL: 2.x
            - GL_GLES  : 2.x
*/

#if ( \
        ( defined(GLWRAP_GL_OPENGL) && GLWRAP_GL_FROM_OPENGL_VER(3, 0) ) || \
        ( defined(GLWRAP_GL_GLES)   && GLWRAP_GL_FROM_GLES_VER(3, 0) )      \
    )

    #define GLWRAP_GL_SUPPORTS_NUM_EXTENSIONS

#endif

bool gl::isExtensionSupported(const char* name)
{
    #if defined(GLWRAP_GL_SUPPORTS_NUM_EXTENSIONS)
    {
        int extensions_count = 0;
        GLWRAP_GL_CHECK( glGetIntegerv(GL_NUM_EXTENSIONS, &extensions_count) );

        for(int i = 0; i < extensions_count; ++i)
        {
            GLubyte const* extension_str = nullptr;
            GLWRAP_GL_CHECK( extension_str = glGetStringi(GL_EXTENSIONS, i) );

            // In case of error it returns nullptr
            if(extension_str == nullptr)
            {
                return false;
            }

            // If 'extension' string same as 'extension name' we looking for
            if ( strcmp((const char*)extension_str, name) == 0 )
            {
                return true;
            }
        }

        return false;
    }
    #else // !defined(GLWRAP_GL_SUPPORTS_NUM_EXTENSIONS)
    {
        GLubyte const* extension_str = nullptr;
        GLWRAP_GL_CHECK( extension_str = glGetString(GL_EXTENSIONS) );

        // In case of error it returns nullptr
        if(extension_str == nullptr)
        {
            return false;
        }

        // If 'extensions' string contains 'extension name' sub-string
        if ( strstr((const char*)extension_str, name) != nullptr )
        {
            return true;
        }

        return false;
    }
    #endif
}

// Function below is used only in case, when 'GL_NUM_EXTENSIONS' not supported,
// so we simply not create it, when its dont needed
#if !defined(GLWRAP_GL_SUPPORTS_NUM_EXTENSIONS)

/*
    This function suitable to extract from (NULL-terminated) string sub-strings,
    without spaces

    @code{.cpp}
    static const auto test = [](const char* str)
    {
        printf("Test: [%s]\n", str);
        const auto items = split_by_space(str);
        for(const std::string& s : items)
        {
            printf("[%s]\n", s.c_str());
        }
    };

    test("");                      // -> []
    test(" ");                     // -> []
    test("  ");                    // -> []
    test("   ");                   // -> []
    test("    ");                  // -> []
    test("qwe");                   // -> ["qwe"]
    test(" qwe ");                 // -> ["qwe"]
    test("qwe   ");                // -> ["qwe"]
    test("   qwe   ");             // -> ["qwe"]
    test("   qwe   asd");          // -> ["qwe","asd"]
    test("   qwe   asd zxc");      // -> ["qwe","asd","zxc"]
    test("   qwe   asd zxc   ");   // -> ["qwe","asd","zxc"]
    test("   qwe   asd   zxc");    // -> ["qwe","asd","zxc"]
    test("   qwe   asd   zxc   "); // -> ["qwe","asd","zxc"]
    @endcode
*/
static std::vector<std::string> split_by_space(const char* str)
{
    std::vector<std::string> items;

    const char* begin = str;
    const char* end   = str;

    while(*end != '\0')
    {
        if(*begin != ' ') // Piece of string not 'space'
        {
            // Iterate string until 'space' found
            while( (*end != '\0') && (*end != ' ') )
            {
                ++end;
            }

            // Now 'begin' and 'end' non-space
            items.emplace_back(begin, end); // Construct `std::string(begin, end)` in-place without unnecessary copy
            begin = end;
        }
        else // *begin == ' '
        {
            // Eat all spaces
            while( (*end != '\0') && (*end == ' ') )
            {
                ++end;
            }
            begin = end;
        }
    }

    return items;
}

#endif // !defined(GLWRAP_GL_SUPPORTS_NUM_EXTENSIONS)

std::vector<std::string> gl::getExtensions()
{
    #if defined(GLWRAP_GL_SUPPORTS_NUM_EXTENSIONS)
    {
        std::vector<std::string> extensions;

        int extensions_count = 0;
        GLWRAP_GL_CHECK( glGetIntegerv(GL_NUM_EXTENSIONS, &extensions_count) );

        for(int i = 0; i < extensions_count; ++i)
        {
            GLubyte const* extension_str = nullptr;
            GLWRAP_GL_CHECK( extension_str = glGetStringi(GL_EXTENSIONS, i) );

            // In case of error it returns nullptr
            if(extension_str == nullptr)
            {
                return {};
            }

            extensions.emplace_back((const char*)extension_str); // Construct `std::string((const char*)extension_str)` in-place without unnecessary copy
        }

        return extensions;
    }
    #else // !defined(GLWRAP_GL_SUPPORTS_NUM_EXTENSIONS)
    {
        std::vector<std::string> extensions;

        GLubyte const* extension_str = nullptr;
        GLWRAP_GL_CHECK( extension_str = glGetString(GL_EXTENSIONS) );

        // In case of error it returns nullptr
        if(extension_str == nullptr)
        {
            return {};
        }

        // Extensions separated by 'space' character
        return split_by_space((const char*)extension_str);
    }
    #endif
}
