#pragma once

#include <gl_wrap/objects/ShaderProgram.hpp>

namespace gl {

ShaderProgram* make_program(
        const char* name,
        const char** vertexShaderSource, int vertexShaderSourceCount,
        const char** fragmentShaderSource, int fragmentShaderSourceCount);

bool make_program(
        const char* name,
        gl::ShaderProgram& program,
        const char** vertexShaderSource, int vertexShaderSourceCount,
        const char** fragmentShaderSource, int fragmentShaderSourceCount);

// -----------------------------------------------------------------------------

ShaderProgram* make_program(
        const char* name,
        const char* vertexShaderSource,
        const char* fragmentShaderSource);

bool make_program(
        const char* name,
        gl::ShaderProgram& program,
        const char* vertexShaderSource,
        const char* fragmentShaderSource);

// -----------------------------------------------------------------------------

ShaderProgram* make_program_compat(
        const char* name,
        const char* vertexShaderSource,
        const char* fragmentShaderSource);

bool make_program_compat(
        const char* name,
        gl::ShaderProgram& program,
        const char* vertexShaderSource,
        const char* fragmentShaderSource);


} // namespace gl
