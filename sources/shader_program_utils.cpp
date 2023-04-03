#include <gl_wrap/shader_program_utils.hpp>

#include <gl_wrap/gl_context.hpp>

#include <gl_wrap/gl_glsl_version_str.hpp>

#include <cstdio> // for: fprintf(), stderr

gl::ShaderProgram *gl::make_program(
        const char *name,
        const char **vertexShaderSource, int vertexShaderSourceCount,
        const char **fragmentShaderSource, int fragmentShaderSourceCount)
{
    auto* vertexShader = new gl::Shader(GL_VERTEX_SHADER);
    vertexShader->setSource(vertexShaderSourceCount, vertexShaderSource, nullptr);
    vertexShader->compile();
    if(!vertexShader->isCompiled())
    {
        fprintf(stderr, "[GLWRAP] %s %i: (%s) Vertex shader compilation error:\n%s\n", __FILE__, __LINE__, name, vertexShader->getInfoLog().c_str());
        fflush(stderr);

        delete vertexShader;
        return nullptr;
    }

    auto* fragmentShader = new gl::Shader(GL_FRAGMENT_SHADER);
    fragmentShader->setSource(fragmentShaderSourceCount, fragmentShaderSource, nullptr);
    fragmentShader->compile();
    if(!fragmentShader->isCompiled())
    {
        fprintf(stderr, "[GLWRAP] %s %i: (%s) Fragment shader compilation error:\n%s\n", __FILE__, __LINE__, name, fragmentShader->getInfoLog().c_str());
        fflush(stderr);

        delete fragmentShader;
        return nullptr;
    }

    // -------------------------------------------------------------------------

    auto* program = new gl::ShaderProgram();
    program->attachShader(vertexShader);
    program->attachShader(fragmentShader);
    program->link();
    if(!program->isLinked())
    {
        fprintf(stderr, "[GLWRAP] %s %i: (%s) Program linking error:\n%s\n", __FILE__, __LINE__, name, program->getInfoLog().c_str());
        fflush(stderr);

        program->detachShader(vertexShader);
        program->detachShader(fragmentShader);
        delete vertexShader;
        delete fragmentShader;
        delete program;
        return nullptr;
    }
    program->validate();
    if(!program->isValid())
    {
        fprintf(stderr, "[GLWRAP] %s %i: (%s) Program valdation error:\n%s\n", __FILE__, __LINE__, name, program->getInfoLog().c_str());
        fflush(stderr);

        program->detachShader(vertexShader);
        program->detachShader(fragmentShader);
        delete vertexShader;
        delete fragmentShader;
        delete program;
        return nullptr;
    }

    program->detachShader(vertexShader);
    program->detachShader(fragmentShader);
    delete vertexShader;
    delete fragmentShader;

    return program;
}

bool gl::make_program(
        const char *name,
        gl::ShaderProgram &program,
        const char **vertexShaderSource, int vertexShaderSourceCount,
        const char **fragmentShaderSource, int fragmentShaderSourceCount)
{
    auto* vertexShader = new gl::Shader(GL_VERTEX_SHADER);
    vertexShader->setSource(vertexShaderSourceCount, vertexShaderSource, nullptr);
    vertexShader->compile();
    if(!vertexShader->isCompiled())
    {
        fprintf(stderr, "[GLWRAP] %s %i: (%s) Vertex shader compilation error:\n%s\n", __FILE__, __LINE__, name, vertexShader->getInfoLog().c_str());
        fflush(stderr);

        delete vertexShader;
        return false;
    }

    auto* fragmentShader = new gl::Shader(GL_FRAGMENT_SHADER);
    fragmentShader->setSource(fragmentShaderSourceCount, fragmentShaderSource, nullptr);
    fragmentShader->compile();
    if(!fragmentShader->isCompiled())
    {
        fprintf(stderr, "[GLWRAP] %s %i: (%s) Fragment shader compilation error:\n%s\n", __FILE__, __LINE__, name, fragmentShader->getInfoLog().c_str());
        fflush(stderr);

        delete fragmentShader;
        return false;
    }

    // -------------------------------------------------------------------------

    program.attachShader(vertexShader);
    program.attachShader(fragmentShader);
    program.link();
    if(!program.isLinked())
    {
        fprintf(stderr, "[GLWRAP] %s %i: (%s) Program linking error:\n%s\n", __FILE__, __LINE__, name, program.getInfoLog().c_str());
        fflush(stderr);

        program.detachShader(vertexShader);
        program.detachShader(fragmentShader);
        delete vertexShader;
        delete fragmentShader;
        return false;
    }
    program.validate();
    if(!program.isValid())
    {
        fprintf(stderr, "[GLWRAP] %s %i: (%s) Program valdation error:\n%s\n", __FILE__, __LINE__, name, program.getInfoLog().c_str());
        fflush(stderr);

        program.detachShader(vertexShader);
        program.detachShader(fragmentShader);
        delete vertexShader;
        delete fragmentShader;
        return false;
    }

    program.detachShader(vertexShader);
    program.detachShader(fragmentShader);
    delete vertexShader;
    delete fragmentShader;

    return true;
}

// -----------------------------------------------------------------------------

gl::ShaderProgram *gl::make_program(
        const char* name,
        const char *vertexShaderSource,
        const char *fragmentShaderSource)
{
    return make_program(name,
                        &vertexShaderSource,   1,
                        &fragmentShaderSource, 1);
}

bool gl::make_program(
        const char *name,
        gl::ShaderProgram &program,
        const char *vertexShaderSource,
        const char *fragmentShaderSource)
{
    return make_program(name,
                        program,
                        &vertexShaderSource,   1,
                        &fragmentShaderSource, 1);
}

// -----------------------------------------------------------------------------

/*
    References:
        - https://github.com/mattdesl/lwjgl-basics/wiki/GLSL-Versions
        - https://stackoverflow.com/a/43671147/13057514
*/

static constexpr const char* COMPATIBILITY_DEFINES =
{
    "#if !defined(GL_ES)\n" // Desktop GL

        "#if (__VERSION__ >= 110) && (__VERSION__ <= 120)\n"
            "#define COMPAT_IN  varying\n"
            "#define COMPAT_OUT varying\n"

            "#define COMPAT_ATTRIB attribute\n"
            "#define COMPAT_ATTRIB_LOCATION(IDX) attribute\n"

            "#define COMPAT_TEXTURE_2D texture2D\n"
            "#define COMPAT_FRAG_COLOR gl_FragColor\n"
        "#elif (__VERSION__ >= 130) && (__VERSION__ <= 140)\n"
            "#define COMPAT_IN  in\n"
            "#define COMPAT_OUT out\n"

            "#define COMPAT_ATTRIB in\n"
            "#define COMPAT_ATTRIB_LOCATION(IDX) in\n"

            "#define COMPAT_TEXTURE_2D texture2D\n" // TODO: is it texture2D() or texture() ?
            "#define COMPAT_FRAG_COLOR gl_FragColor\n"
        "#elif (__VERSION__ == 150)\n"
            "#define COMPAT_IN  in\n"
            "#define COMPAT_OUT out\n"

            "#define COMPAT_ATTRIB in\n"
            "#define COMPAT_ATTRIB_LOCATION(IDX) layout (location = IDX) in\n"

            "#define COMPAT_TEXTURE_2D texture\n"
            "#define COMPAT_FRAG_COLOR gl_FragColor\n"
        "#elif (__VERSION__ >= 330) && (__VERSION__ <= 450)\n"
            "#define COMPAT_IN  in\n"
            "#define COMPAT_OUT out\n"

            "#define COMPAT_ATTRIB in\n"
            "#define COMPAT_ATTRIB_LOCATION(IDX) layout (location = IDX) in\n"

            "#define COMPAT_TEXTURE_2D texture\n"
            "#define COMPAT_FRAG_COLOR FragColor\n"
            "COMPAT_OUT vec4 FragColor;\n" // TODO: must be only in Fragment shader
        "#else\n"
            "#error \"Unsupported GL GLSL Version\"\n"
        "#endif\n"

    "#elif defined(GL_ES)\n" // GL ES

        // TODO: mediump float may not be enough for GLES2 in iOS.
        // see the following discussion: https://github.com/memononen/nanovg/issues/46
        "#if (GL_FRAGMENT_PRECISION_HIGH == 1)\n"
            "precision highp   float;\n"
        "#else\n"
            "precision mediump float;\n"
        "#endif\n"

        "#if (__VERSION__ == 100)\n" // GL ES 2.0
            "#define COMPAT_IN  varying\n"
            "#define COMPAT_OUT varying\n"

            "#define COMPAT_ATTRIB attribute\n"
            "#define COMPAT_ATTRIB_LOCATION(IDX) attribute\n"

            "#define COMPAT_TEXTURE_2D texture2D\n"
            "#define COMPAT_FRAG_COLOR gl_FragColor\n"
        "#elif (__VERSION__ >= 300) && (__VERSION__ <= 320)\n" // {300 (GL ES 3.0), 310 (GL ES 3.1), 320 (GL ES 3.2)}
            "#define COMPAT_IN  in\n"
            "#define COMPAT_OUT out\n"

            "#define COMPAT_ATTRIB in\n"
            "#define COMPAT_ATTRIB_LOCATION(IDX) layout (location = IDX) in\n"

            "#define COMPAT_TEXTURE_2D texture\n"
            "#define COMPAT_FRAG_COLOR FragColor\n"
            "COMPAT_OUT vec4 FragColor;\n" // TODO: must be only in Fragment shader
        "#else\n"
            "#error \"Unsupported GLES GLSL Version\"\n"
        "#endif\n"

    // TODO: add custom define GL_WEBGL to not rely upon GL_ES
    //   Reference: https://developer.mozilla.org/en-US/docs/Web/API/WebGL_API/WebGL_best_practices#avoid_ifdef_gl_es
    //"#elif defined(GL_WEBGL)


    "#endif\n"
};

gl::ShaderProgram *gl:: make_program_compat(
        const char *name,
        const char *vertexShaderSource,
        const char *fragmentShaderSource)
{
    const char* Compat_VertexShaderSource[5]
    {
        "#version ", gl::glsl_version_str(), "\n",

        COMPATIBILITY_DEFINES,

        vertexShaderSource
    };

    const char* Compat_FragmentShaderSource[5]
    {
        "#version ", gl::glsl_version_str(), "\n",

        COMPATIBILITY_DEFINES,

        fragmentShaderSource
    };

    return make_program(name,
                        Compat_VertexShaderSource,   5,
                        Compat_FragmentShaderSource, 5);
}


bool gl::make_program_compat(
        const char *name,
        gl::ShaderProgram &program,
        const char *vertexShaderSource,
        const char *fragmentShaderSource)
{
    const char* Compat_VertexShaderSource[5]
    {
        "#version ", gl::glsl_version_str(), "\n",

        COMPATIBILITY_DEFINES,

        vertexShaderSource
    };

    const char* Compat_FragmentShaderSource[5]
    {
        "#version ", gl::glsl_version_str(), "\n",

        COMPATIBILITY_DEFINES,

        fragmentShaderSource
    };

    return make_program(name,
                        program,
                        Compat_VertexShaderSource,   5,
                        Compat_FragmentShaderSource, 5);
}
