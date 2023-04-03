#pragma once

#include <string>

#include <gl_wrap/objects/Object.hpp>

namespace gl {

class Shader : public Object
{
public:

    Shader(int type);
    virtual ~Shader();

    // -------------------------------------------------------------------------

    // Moveable
    GLWRAP_MOVE_DEFAULT(Shader);

    // Non-copyable
    GLWRAP_PREVENT_COPY_AND_ASSIGN(Shader);

    // -------------------------------------------------------------------------

    void setSource(int count, const char** string, const int* lengths);
    void setSource(const char* string, int length);
    void setSource(const char* string);

    template <size_t SIZE>
    void setSourcesArray(const char* (&sources)[SIZE]) {
        setSource(SIZE, sources, nullptr);
    }

    void compile();

    // -------------------------------------------------------------------------

    int getType() const;
    bool isDeleted() const;
    bool isCompiled() const;
    int getInfoLogLength() const;
    int getSourceLength() const;

    // -------------------------------------------------------------------------

    std::string getInfoLog() const;
    std::string getSource() const;

    // -------------------------------------------------------------------------

    bool isOk() const;
};

} // namespace gl
