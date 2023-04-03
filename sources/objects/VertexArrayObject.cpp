#include <gl_wrap/objects/VertexArrayObject.hpp>

#include <gl_wrap/gl_context.hpp>

#include <gl_wrap/gl_version.hpp>
#include <gl_wrap/gl_error_checking.hpp>
#include <gl_wrap/gl_extensions.hpp>

#include <cstdio> // for fprintf(), stderr

using func_ptr_glGenVertexArrays    = void      (*)(GLsizei n,       GLuint *arrays);
using func_ptr_glDeleteVertexArrays = void      (*)(GLsizei n, const GLuint *arrays);
using func_ptr_glBindVertexArray    = void      (*)(GLuint array);
using func_ptr_glIsVertexArray      = GLboolean (*)(GLuint array);

// -----------------------------------------------------------------------------

static void dummy_glGenVertexArrays(GLsizei n, GLuint *arrays)
{
    fprintf(stderr, "[GLWRAP] :: glGenVertexArrays(%d, %p) not supported!\n", n, arrays);
}

static void dummy_glDeleteVertexArrays(GLsizei n, const GLuint *arrays)
{
    fprintf(stderr, "[GLWRAP] :: glDeleteVertexArrays(%d, %p) not supported!\n", n, arrays);
}

static void dummy_glBindVertexArray(GLuint array)
{
    fprintf(stderr, "[GLWRAP] :: glBindVertexArray(%u) not supported!\n", array);
}

static GLboolean dummy_glIsVertexArray(GLuint array)
{
    fprintf(stderr, "[GLWRAP] :: glIsVertexArray(%u) not supported!\n", array);
    return GL_FALSE;
}

static func_ptr_glGenVertexArrays    my__glGenVertexArrays    = dummy_glGenVertexArrays;
static func_ptr_glDeleteVertexArrays my__glDeleteVertexArrays = dummy_glDeleteVertexArrays;
static func_ptr_glBindVertexArray    my__glBindVertexArray    = dummy_glBindVertexArray;
static func_ptr_glIsVertexArray      my__glIsVertexArray      = dummy_glIsVertexArray;

// -----------------------------------------------------------------------------

// https://www.khronos.org/registry/OpenGL/extensions/OES/OES_vertex_array_object.txt

static constexpr GLenum MY_GL_VERTEX_ARRAY_BINDING =
{
    #if defined(GL_VERTEX_ARRAY_BINDING)
        GL_VERTEX_ARRAY_BINDING
    #elif defined(VERTEX_ARRAY_BINDING_OES)
        VERTEX_ARRAY_BINDING_OES
    #else
        0x85B5
    #endif
};

// -----------------------------------------------------------------------------

static bool FUNCTIONS_INITED = false;

static void init_functions()
{
    // Only once
    if(FUNCTIONS_INITED == false)
    {
        // In case of GLES2, we trying to use Extention for it
#if (defined(GLWRAP_GL_GLES) && (GLWRAP_GL_VER_MAJOR < 3))
        // if( gl::isExtensionSupported("GL_OES_vertex_array_object") )
        {
            my__glGenVertexArrays    = reinterpret_cast<func_ptr_glGenVertexArrays   >( gl::getProcAddress("glGenVertexArraysOES") );
            my__glDeleteVertexArrays = reinterpret_cast<func_ptr_glDeleteVertexArrays>( gl::getProcAddress("glDeleteVertexArraysOES") );
            my__glBindVertexArray    = reinterpret_cast<func_ptr_glBindVertexArray   >( gl::getProcAddress("glBindVertexArrayOES") );
            my__glIsVertexArray      = reinterpret_cast<func_ptr_glIsVertexArray     >( gl::getProcAddress("glIsVertexArrayOES") );

            // If some of pointers-to-procedures is null, it means:
            //   1) gl::getProcAddress() is non-implemented --> returns nullptr
            //   2) possible error in backend, that provides pointers
            if( (my__glGenVertexArrays    == nullptr) ||
                (my__glDeleteVertexArrays == nullptr) ||
                (my__glBindVertexArray    == nullptr) ||
                (my__glIsVertexArray      == nullptr) )
            {
                // Restore 'dummy' version
                my__glGenVertexArrays    = dummy_glGenVertexArrays;
                my__glDeleteVertexArrays = dummy_glDeleteVertexArrays;
                my__glBindVertexArray    = dummy_glBindVertexArray;
                my__glIsVertexArray      = dummy_glIsVertexArray;

                fprintf(stderr, "[GLWRAP] VertexArrayObject function pointers invalid!\n");
                fflush(stderr);
            }
        }
#else // Desktop GL or GLES3
        {
            my__glGenVertexArrays    = glGenVertexArrays;
            my__glDeleteVertexArrays = glDeleteVertexArrays;
            my__glBindVertexArray    = glBindVertexArray;
            my__glIsVertexArray      = glIsVertexArray;
        }
#endif

        FUNCTIONS_INITED = true;
    }
}

// -----------------------------------------------------------------------------

gl::VertexArrayObject::VertexArrayObject()
    : Object()
{
    init_functions();

    GLWRAP_GL_CHECK( my__glGenVertexArrays(1, &_id) );
}

gl::VertexArrayObject::~VertexArrayObject()
{
    GLWRAP_GL_CHECK( my__glDeleteVertexArrays(1, &_id) );
}

// -----------------------------------------------------------------------------

void gl::VertexArrayObject::bind()
{
    GLWRAP_GL_CHECK( my__glBindVertexArray(_id) );
}

void gl::VertexArrayObject::unbind()
{
    init_functions();

    GLWRAP_GL_CHECK( my__glBindVertexArray(0) );
}

// -----------------------------------------------------------------------------

bool gl::VertexArrayObject::isOk() const
{
    GLboolean result;
    GLWRAP_GL_CHECK( result = my__glIsVertexArray(_id) );
    return (result != GL_FALSE);
}

// -----------------------------------------------------------------------------

gl::VertexArrayObject::id_t gl::VertexArrayObject::getBindedId()
{
    // This is static function, and may be called without creating an object,
    // so we need to try initialize related functions for it.
    init_functions();

    int current_vao;
    GLWRAP_GL_CHECK( glGetIntegerv(MY_GL_VERTEX_ARRAY_BINDING, &current_vao) );
    return static_cast<id_t>(current_vao);
}

void gl::VertexArrayObject::setBindedId(gl::Object::id_t id)
{
    // This is static function, and may be called without creating an object,
    // so we need to try initialize related functions for it.
    init_functions();

    GLWRAP_GL_CHECK( my__glBindVertexArray(id) );
}

bool gl::VertexArrayObject::isBinded() const
{
    return isOk() && (_id == getBindedId());
}
