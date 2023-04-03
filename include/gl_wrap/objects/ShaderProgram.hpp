#pragma once

#include <gl_wrap/objects/Object.hpp>
#include <gl_wrap/objects/Shader.hpp>

#include <string>
#include <vector>

// -----------------------------------------------------------------------------
// Extentions

#if defined(GLWRAP_USE_GLM)

    #include <glm/detail/type_vec2.hpp>   // for glm::vec<2, float, precision Q>
    #include <glm/detail/type_vec3.hpp>   // for glm::vec<3, float, precision Q>
    #include <glm/detail/type_vec4.hpp>   // for glm::vec<4, float, precision Q>

    #include <glm/detail/type_mat2x2.hpp> // for glm::mat<2, 2, float, precision Q>
    #include <glm/detail/type_mat3x3.hpp> // for glm::mat<3, 3, float, precision Q>
    #include <glm/detail/type_mat4x4.hpp> // for glm::mat<4, 4, float, precision Q>

    #include <glm/gtc/type_ptr.hpp>       // for glm::value_ptr<T,Q>()

#endif // GLWRAP_USE_GLM

#if defined(GLWRAP_USE_EIGEN3)

    #include <eigen3/Eigen/Core> // for Eigen::Vector{2|3|4}{f|i}, Eigen::Matrix{2|3|4}f

#endif // GLWRAP_USE_EIGEN3

#if defined(GLWRAP_USE_SFML)

    #include <SFML/System/Vector2.hpp>
    #include <SFML/System/Vector3.hpp>
    #include <SFML/Graphics/Transform.hpp>

#endif // GLWRAP_USE_SFML

// TODO: bullet3
//#include <bullet/LinearMath/btVector3.h>
//#include <bullet/LinearMath/btMatrix3x3.h>

// -----------------------------------------------------------------------------

namespace gl {

class ShaderProgram : public Object
{
public:

    ShaderProgram();
    virtual ~ShaderProgram();

    // -------------------------------------------------------------------------

    // Moveable
    GLWRAP_MOVE_DEFAULT(ShaderProgram);

    // Non-copyable
    GLWRAP_PREVENT_COPY_AND_ASSIGN(ShaderProgram);

    // -------------------------------------------------------------------------

    void attachShader(unsigned int shader_id);
    void attachShader(const Shader* shader);

    void detachShader(unsigned int shader_id);
    void detachShader(const Shader* shader);

    void link();
    void validate();

    void use();
    static void unuse();

    // -------------------------------------------------------------------------
    struct attribute_location {
        const int location;
        attribute_location(int location_) : location(location_) {}
        inline operator int () { return location; }
        inline bool isPresent() const { return (location != -1); }
    };

    struct uniform_location {
        const int location;
        uniform_location(int location_) : location(location_) {}
        inline operator int () { return location; }
        inline bool isPresent() const { return (location != -1); }
    };
    // - - - - - - - - - - - - - - - - - - - - - - - - - - -

    void bindAttribLocation(unsigned int index, const char* name);

    attribute_location getAttribLocation(const char* name) const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - -

    uniform_location getUniformLocation(const char* name) const;

    // -------------------------------------------------------------------------

    // TODO: for every 'setUniform', add debug check - is used

    void setUniformFloat(uniform_location location, float v0);
    void setUniformFloat(uniform_location location, float v0, float v1);
    void setUniformFloat(uniform_location location, float v0, float v1, float v2);
    void setUniformFloat(uniform_location location, float v0, float v1, float v2, float v3);

    void setUniformFloat(const char* name, float v0);
    void setUniformFloat(const char* name, float v0, float v1);
    void setUniformFloat(const char* name, float v0, float v1, float v2);
    void setUniformFloat(const char* name, float v0, float v1, float v2, float v3);

    // - - - - - - - - - - - - - - - - - - - - - - - - - - -

    void setUniformInt(uniform_location location, int v0);
    void setUniformInt(uniform_location location, int v0, int v1);
    void setUniformInt(uniform_location location, int v0, int v1, int v2);
    void setUniformInt(uniform_location location, int v0, int v1, int v2, int v3);

    void setUniformInt(const char* name, int v0);
    void setUniformInt(const char* name, int v0, int v1);
    void setUniformInt(const char* name, int v0, int v1, int v2);
    void setUniformInt(const char* name, int v0, int v1, int v2, int v3);

    // - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Booleans

    void setUniformBool(uniform_location location, bool v0);
    void setUniformBool(const char* name, bool v0);

    // - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Arrays :: float (unsafe version for pointer-to-array)

    void setUniformFloatArray1Ptr(uniform_location location, const float* values, int count = 1);
    void setUniformFloatArray2Ptr(uniform_location location, const float* values, int count = 1);
    void setUniformFloatArray3Ptr(uniform_location location, const float* values, int count = 1);
    void setUniformFloatArray4Ptr(uniform_location location, const float* values, int count = 1);

    void setUniformFloatArray1Ptr(const char* name, const float* values, int count = 1);
    void setUniformFloatArray2Ptr(const char* name, const float* values, int count = 1);
    void setUniformFloatArray3Ptr(const char* name, const float* values, int count = 1);
    void setUniformFloatArray4Ptr(const char* name, const float* values, int count = 1);

    // - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Arrays :: int (unsafe version for pointer-to-array)

    void setUniformIntArray1Ptr(uniform_location location, const int* values, int count = 1);
    void setUniformIntArray2Ptr(uniform_location location, const int* values, int count = 1);
    void setUniformIntArray3Ptr(uniform_location location, const int* values, int count = 1);
    void setUniformIntArray4Ptr(uniform_location location, const int* values, int count = 1);

    void setUniformIntArray1Ptr(const char* name, const int* values, int count = 1);
    void setUniformIntArray2Ptr(const char* name, const int* values, int count = 1);
    void setUniformIntArray3Ptr(const char* name, const int* values, int count = 1);
    void setUniformIntArray4Ptr(const char* name, const int* values, int count = 1);

    // -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
    // Arrays :: float (safe version for known-size arrays)

    void setUniformFloatArray1(uniform_location location, const float (&array)[1]);
    void setUniformFloatArray2(uniform_location location, const float (&array)[2]);
    void setUniformFloatArray3(uniform_location location, const float (&array)[3]);
    void setUniformFloatArray4(uniform_location location, const float (&array)[4]);

    void setUniformFloatArray1(const char* name, const float (&array)[1]);
    void setUniformFloatArray2(const char* name, const float (&array)[2]);
    void setUniformFloatArray3(const char* name, const float (&array)[3]);
    void setUniformFloatArray4(const char* name, const float (&array)[4]);

    // - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Arrays :: int (safe version for known-size arrays)

    void setUniformIntArray1(uniform_location location, const int (&array)[1]);
    void setUniformIntArray2(uniform_location location, const int (&array)[2]);
    void setUniformIntArray3(uniform_location location, const int (&array)[3]);
    void setUniformIntArray4(uniform_location location, const int (&array)[4]);

    void setUniformIntArray1(const char* name, const int (&array)[1]);
    void setUniformIntArray2(const char* name, const int (&array)[2]);
    void setUniformIntArray3(const char* name, const int (&array)[3]);
    void setUniformIntArray4(const char* name, const int (&array)[4]);

    // - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Matrices

    void setUniformMatrix2(uniform_location location, const float* values, bool transpose = false);
    void setUniformMatrix3(uniform_location location, const float* values, bool transpose = false);
    void setUniformMatrix4(uniform_location location, const float* values, bool transpose = false);

    void setUniformMatrix2(const char* name, const float* values, bool transpose = false);
    void setUniformMatrix3(const char* name, const float* values, bool transpose = false);
    void setUniformMatrix4(const char* name, const float* values, bool transpose = false);

    // -------------------------------------------------------------------------

    bool isDeleted() const;
    bool isLinked() const;
    bool isValid() const;
    int getInfoLogLength() const;
    int getAttachedShadersCount() const;

    int getActiveAttributesCount() const;
    int getActiveAttributeMaxLenght() const;

    int getActiveUniformsCount() const;
    int getActiveUniformMaxLenght() const;

    // -------------------------------------------------------------------------

    std::vector<unsigned int> getAttachedShaders() const;

    std::string getInfoLog() const;

    // -------------------------------------------------------------------------

    static id_t getCurrentId();
    static void setCurrentId(id_t id);
    bool isCurrent() const;

    bool isOk() const;

    // -------------------------------------------------------------------------
    // Extentions

    #if defined(GLWRAP_USE_GLM)

        template <glm::qualifier Q>
        inline void setUniformFloatVec2(uniform_location location, const glm::vec<2, float, Q>& vec2)
        {
            setUniformFloatArray2Ptr(location, glm::value_ptr(vec2), 1);
        }

        template <glm::qualifier Q>
        inline void setUniformFloatVec3(uniform_location location, const glm::vec<3, float, Q>& vec3)
        {
            setUniformFloatArray3Ptr(location, glm::value_ptr(vec3), 1);
        }

        template <glm::qualifier Q>
        inline void setUniformFloatVec4(uniform_location location, const glm::vec<4, float, Q>& vec4)
        {
            setUniformFloatArray4Ptr(location, glm::value_ptr(vec4), 1);
        }


        template <glm::qualifier Q>
        inline void setUniformFloatVec2(const char* name, const glm::vec<2, float, Q>& vec2)
        {
            setUniformFloatArray2Ptr(name, glm::value_ptr(vec2), 1);
        }

        template <glm::qualifier Q>
        inline void setUniformFloatVec3(const char* name, const glm::vec<3, float, Q>& vec3)
        {
            setUniformFloatArray3Ptr(name, glm::value_ptr(vec3), 1);
        }

        template <glm::qualifier Q>
        inline void setUniformFloatVec4(const char* name, const glm::vec<4, float, Q>& vec4)
        {
            setUniformFloatArray4Ptr(name, glm::value_ptr(vec4), 1);
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - -

        template <glm::qualifier Q>
        inline void setUniformIntVec2(uniform_location location, const glm::vec<2, int, Q>& vec2)
        {
            setUniformIntArray2Ptr(location, glm::value_ptr(vec2), 1);
        }

        template <glm::qualifier Q>
        inline void setUniformIntVec3(uniform_location location, const glm::vec<3, int, Q>& vec3)
        {
            setUniformIntArray3Ptr(location, glm::value_ptr(vec3), 1);
        }

        template <glm::qualifier Q>
        inline void setUniformIntVec4(uniform_location location, const glm::vec<4, int, Q>& vec4)
        {
            setUniformIntArray4Ptr(location, glm::value_ptr(vec4), 1);
        }


        template <glm::qualifier Q>
        inline void setUniformIntVec2(const char* name, const glm::vec<2, int, Q>& vec2)
        {
            setUniformIntArray2Ptr(name, glm::value_ptr(vec2), 1);
        }

        template <glm::qualifier Q>
        inline void setUniformIntVec3(const char* name, const glm::vec<3, int, Q>& vec3)
        {
            setUniformIntArray3Ptr(name, glm::value_ptr(vec3), 1);
        }

        template <glm::qualifier Q>
        inline void setUniformIntVec4(const char* name, const glm::vec<4, int, Q>& vec4)
        {
            setUniformIntArray4Ptr(name, glm::value_ptr(vec4), 1);
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - -

        template <glm::qualifier Q>
        inline void setUniformMatrix2(uniform_location location, const glm::mat<2, 2, float, Q>& mat2x2, bool transpose = false)
        {
            setUniformMatrix2(location, glm::value_ptr(mat2x2), transpose);
        }

        template <glm::qualifier Q>
        inline void setUniformMatrix3(uniform_location location, const glm::mat<3, 3, float, Q>& mat3x3, bool transpose = false)
        {
            setUniformMatrix3(location, glm::value_ptr(mat3x3), transpose);
        }

        template <glm::qualifier Q>
        inline void setUniformMatrix4(uniform_location location, const glm::mat<4, 4, float, Q>& mat4x4, bool transpose = false)
        {
            setUniformMatrix4(location, glm::value_ptr(mat4x4), transpose);
        }


        template <glm::qualifier Q>
        inline void setUniformMatrix2(const char* name, const glm::mat<2, 2, float, Q>& mat2x2, bool transpose = false)
        {
            setUniformMatrix2(name, glm::value_ptr(mat2x2), transpose);
        }

        template <glm::qualifier Q>
        inline void setUniformMatrix3(const char* name, const glm::mat<3, 3, float, Q>& mat3x3, bool transpose = false)
        {
            setUniformMatrix3(name, glm::value_ptr(mat3x3), transpose);
        }

        template <glm::qualifier Q>
        inline void setUniformMatrix4(const char* name, const glm::mat<4, 4, float, Q>& mat4x4, bool transpose = false)
        {
            setUniformMatrix4(name, glm::value_ptr(mat4x4), transpose);
        }

    #endif // GLWRAP_USE_GLM


    #if defined(GLWRAP_USE_EIGEN3)

        inline void setUniformFloatVec2(uniform_location location, const Eigen::Vector2f& vec2)
        {
            setUniformFloatArray2Ptr(location, vec2.data(), 1);
        }

        inline void setUniformFloatVec3(uniform_location location, const Eigen::Vector3f& vec3)
        {
            setUniformFloatArray3Ptr(location, vec3.data(), 1);
        }

        inline void setUniformFloatVec4(uniform_location location, const Eigen::Vector4f& vec4)
        {
            setUniformFloatArray4Ptr(location, vec4.data(), 1);
        }


        inline void setUniformFloatVec2(const char* name, const Eigen::Vector2f& vec2)
        {
            setUniformFloatArray2Ptr(name, vec2.data(), 1);
        }

        inline void setUniformFloatVec3(const char* name, const Eigen::Vector3f& vec3)
        {
            setUniformFloatArray3Ptr(name, vec3.data(), 1);
        }

        inline void setUniformFloatVec4(const char* name, const Eigen::Vector4f& vec4)
        {
            setUniformFloatArray4Ptr(name, vec4.data(), 1);
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - -

        inline void setUniformIntVec2(uniform_location location, const Eigen::Vector2i& vec2)
        {
            setUniformIntArray2Ptr(location, vec2.data(), 1);
        }

        inline void setUniformIntVec3(uniform_location location, const Eigen::Vector3i& vec3)
        {
            setUniformIntArray3Ptr(location, vec3.data(), 1);
        }

        inline void setUniformIntVec4(uniform_location location, const Eigen::Vector4i& vec4)
        {
            setUniformIntArray4Ptr(location, vec4.data(), 1);
        }


        inline void setUniformIntVec2(const char* name, const Eigen::Vector2i& vec2)
        {
            setUniformIntArray2Ptr(name, vec2.data(), 1);
        }

        inline void setUniformIntVec3(const char* name, const Eigen::Vector3i& vec3)
        {
            setUniformIntArray3Ptr(name, vec3.data(), 1);
        }

        inline void setUniformIntVec4(const char* name, const Eigen::Vector4i& vec4)
        {
            setUniformIntArray4Ptr(name, vec4.data(), 1);
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - -

        inline void setUniformMatrix2(uniform_location location, const Eigen::Matrix2f& mat2x2, bool transpose = false)
        {
            setUniformMatrix2(location, mat2x2.data(), transpose);
        }

        inline void setUniformMatrix3(uniform_location location, const Eigen::Matrix3f& mat3x3, bool transpose = false)
        {
            setUniformMatrix3(location, mat3x3.data(), transpose);
        }

        inline void setUniformMatrix4(uniform_location location, const Eigen::Matrix4f& mat4x4, bool transpose = false)
        {
            setUniformMatrix4(location, mat4x4.data(), transpose);
        }


        inline void setUniformMatrix2(const char* name, const Eigen::Matrix2f& mat2x2, bool transpose = false)
        {
            setUniformMatrix2(name, mat2x2.data(), transpose);
        }

        inline void setUniformMatrix3(const char* name, const Eigen::Matrix3f& mat3x3, bool transpose = false)
        {
            setUniformMatrix3(name, mat3x3.data(), transpose);
        }

        inline void setUniformMatrix4(const char* name, const Eigen::Matrix4f& mat4x4, bool transpose = false)
        {
            setUniformMatrix4(name, mat4x4.data(), transpose);
        }

    #endif // GLWRAP_USE_EIGEN3

    // TODO: CML (https://github.com/demianmnave/CML)

    // TODO: GMTL (https://github.com/imvu/gmtl)

    #if defined(GLWRAP_USE_SFML)

        /*
            NOTE:
            - in SFML analogs of vec4/mat2/mat3 not exists, only sf::Transform
              as analogue of mat4
            - sf::Vector2<T>, sf::Vector3<T> NOT store data in array, so them
              passed as scalars (unpacked)
        */

        inline void setUniformFloatVec2(uniform_location location, const sf::Vector2<float>& vec2)
        {
            setUniformFloat(location, vec2.x, vec2.y);
        }

        inline void setUniformFloatVec3(uniform_location location, const sf::Vector3<float>& vec3)
        {
            setUniformFloat(location, vec3.x, vec3.y, vec3.z);
        }


        inline void setUniformFloatVec2(const char* name, const sf::Vector2<float>& vec2)
        {
            setUniformFloat(name, vec2.x, vec2.y);
        }

        inline void setUniformFloatVec3(const char* name, const sf::Vector3<float>& vec3)
        {
            setUniformFloat(name, vec3.x, vec3.y, vec3.z);
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - -

        inline void setUniformIntVec2(uniform_location location, const sf::Vector2<int>& vec2)
        {
            setUniformInt(location, vec2.x, vec2.y);
        }

        inline void setUniformIntVec3(uniform_location location, const sf::Vector3<int>& vec3)
        {
            setUniformInt(location, vec3.x, vec3.y, vec3.z);
        }


        inline void setUniformIntVec2(const char* name, const sf::Vector2<int>& vec2)
        {
            setUniformInt(name, vec2.x, vec2.y);
        }

        inline void setUniformIntVec3(const char* name, const sf::Vector3<int>& vec3)
        {
            setUniformInt(name, vec3.x, vec3.y, vec3.z);
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - -

        inline void setUniformMatrix4(uniform_location location, const sf::Transform& transform, bool transpose = false)
        {
            setUniformMatrix4(location, transform.getMatrix(), transpose);
        }


        inline void setUniformMatrix4(const char* name, const sf::Transform& transform, bool transpose = false)
        {
            setUniformMatrix4(name, transform.getMatrix(), transpose);
        }

    #endif // GLWRAP_USE_SFML


    // TODO: bullet3
    //    TODO: bullet3's 'btScalar' may be float or double, it must be handled

};

const char* get_shader_variable_type_str(int type);

// TODO: https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glGetActiveAttrib.xml
// TODO: https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glGetActiveUniform.xml
// TODO: https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glGetUniform.xml

} // namespace gl
