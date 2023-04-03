#pragma once

#include <cstdint> // for uint8_t, uint32_t

namespace gl {

class ColorRGBA
{
public:

    using data_t = float[4];

private:

    data_t _values;

public:

    constexpr ColorRGBA()
        : _values{1.0f, 1.0f, 1.0f, 1.0f} // Opaque white
    {}

    constexpr ColorRGBA(float r, float g, float b, float a = 1.0f)
        : _values{r, g, b, a}
    {}

    static constexpr ColorRGBA fromUInts(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
    {
        /*
            Note: `(1.0f / 255.0f) * (float)(component)` used instead of simple
            form `(float)(component) / 255.0f` to maximize chance, that compiler
            will pick `FIMUL` instruction.

            References:
                https://community.khronos.org/t/how-to-convert-from-rgb-255-to-opengl-float-color/29288/4
         */
        return {
            (1.0f/255.0f) * static_cast<float>(r), // R
            (1.0f/255.0f) * static_cast<float>(g), // G
            (1.0f/255.0f) * static_cast<float>(b), // B
            (1.0f/255.0f) * static_cast<float>(a), // A
        };
    }

    /*
        Note: unofortunately this function cannot be `constexpr`, since
        `reinterpret_cast<>` is not allowed in constant expression.

        So we can't unpack de-compose uint32_t as 4 uint8_t in compile-time by
        using such strategy.

        Alternate solution: unpack by using bit-shifts, but this requires
        endianess check for safety: https://stackoverflow.com/a/6502825/
     */
    static inline ColorRGBA fromUInt(uint32_t color)
    {
        static_assert(
            sizeof(uint32_t) == (sizeof(uint8_t) * 4),
            "uint32_t cannot be unpacked into uint8_t[4] array"
        );

        const uint8_t* bytes = reinterpret_cast<const uint8_t*>(&color);
        return fromUInts(
            bytes[0], // R
            bytes[1], // G
            bytes[2], // B
            bytes[3]  // A
        );
    }

    static constexpr ColorRGBA transparent()
    {
        return {0.0f, 0.0f, 0.0f, 0.0f};
    }

    static constexpr ColorRGBA RGB_with_A(const ColorRGBA& color, float a)
    {
        return {color.getR(), color.getG(), color.getB(), a};
    }

    // -------------------------------------------------------------------------

    constexpr bool operator == (const ColorRGBA& other) const
    {
        return
                (this->getR() == other.getR()) &&
                (this->getG() == other.getG()) &&
                (this->getB() == other.getB()) &&
                (this->getA() == other.getA());
    }

    constexpr bool operator != (const ColorRGBA& other) const
    {
        return !(*this == other);
    }

    // -------------------------------------------------------------------------

    inline float& refR() { return _values[0]; }
    inline float& refG() { return _values[1]; }
    inline float& refB() { return _values[2]; }
    inline float& refA() { return _values[3]; }

    constexpr float getR() const { return _values[0]; }
    constexpr float getG() const { return _values[1]; }
    constexpr float getB() const { return _values[2]; }
    constexpr float getA() const { return _values[3]; }

    inline void setR(float value) { _values[0] = value; }
    inline void setG(float value) { _values[1] = value; }
    inline void setB(float value) { _values[2] = value; }
    inline void setA(float value) { _values[3] = value; }

    // -------------------------------------------------------------------------

    constexpr bool isTransparent() const
    {
        return (getA() <= 0.0f);
    }

    constexpr bool isSemiTransparent() const
    {
        return ( (getA() > 0.0f) && (getA() < 1.0f) );
    }

    constexpr bool isOpaque() const
    {
        return (getA() >= 1.0f);
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    constexpr bool isSameRGB(const ColorRGBA& other) const
    {
        return
                (this->getR() == other.getR()) &&
                (this->getG() == other.getG()) &&
                (this->getB() == other.getB());
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    constexpr bool isNormalized() const
    {
        /*
            Notice, that here is no `isnan()` checks, since if some component
            is `NaN`, it always returns false on comparison with ordinary value.
            Also `isnan()` is non-constexpr.
         */
        return
                ( (getR() >= 0.0f) && (getR() <= 1.0f) ) &&
                ( (getG() >= 0.0f) && (getG() <= 1.0f) ) &&
                ( (getB() >= 0.0f) && (getB() <= 1.0f) ) &&
                ( (getA() >= 0.0f) && (getA() <= 1.0f) );
    }

    void normalize();

    ColorRGBA normalized() const
    {
        ColorRGBA result = (*this);
        result.normalize();
        return result;
    }

    // -------------------------------------------------------------------------

    // TODO: untested
    inline void asUints(uint8_t& r, uint8_t& g, uint8_t& b, uint8_t& a) const
    {
        const gl::ColorRGBA self_normalized = this->normalized();

        r = static_cast<uint8_t>( self_normalized.getR() * 255.0f );
        g = static_cast<uint8_t>( self_normalized.getG() * 255.0f );
        b = static_cast<uint8_t>( self_normalized.getB() * 255.0f );
        a = static_cast<uint8_t>( self_normalized.getA() * 255.0f );
    }

    // TODO: untested
    inline uint32_t asUint() const
    {
        static_assert(
            sizeof(uint8_t[4]) == sizeof(uint32_t),
            "uint8_t[4] array cannot be unpacked into uint32_t"
        );

        uint8_t components[4]; // RGBA
        asUints(components[0], components[1], components[2], components[3]);

        const uint32_t* result = reinterpret_cast<const uint32_t*>(components);
        return (*result);
    }

    // -------------------------------------------------------------------------

    inline float* getData()
    {
        return _values;
    }

    constexpr const float* getConstData() const
    {
        return _values;
    }

    inline data_t& getDataRef()
    {
        return _values;
    }

    constexpr data_t const& getConstDataRef() const
    {
        return _values;
    }
};

} // namespace gl
