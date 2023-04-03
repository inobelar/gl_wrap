#pragma once

namespace gl {

class Rect
{
public:

    using data_t = int[4];

private:

    data_t _values;

public:

    constexpr Rect()
        : _values{0, 0, 0, 0}
    {}

    constexpr Rect(int x, int y, int width, int height)
        : _values{x, y, width, height}
    {}

    static constexpr Rect fromSize(int width, int height)
    {
        return {0, 0, width, height};
    }

    // -------------------------------------------------------------------------

    constexpr bool operator == (const Rect& other) const
    {
        return
                (this->getX()      == other.getX())     &&
                (this->getY()      == other.getY())     &&
                (this->getWidth()  == other.getWidth()) &&
                (this->getHeight() == other.getHeight());
    }

    constexpr bool operator != (const Rect& other) const
    {
        return !(*this == other);
    }

    // -------------------------------------------------------------------------

    inline int& refX()      { return _values[0]; }
    inline int& refY()      { return _values[1]; }
    inline int& refWidth()  { return _values[2]; }
    inline int& refHeight() { return _values[3]; }

    constexpr int getX()      const { return _values[0]; }
    constexpr int getY()      const { return _values[1]; }
    constexpr int getWidth()  const { return _values[2]; }
    constexpr int getHeight() const { return _values[3]; }

    inline void setX     (int value) { _values[0] = value; }
    inline void setY     (int value) { _values[1] = value; }
    inline void setWidth (int value) { _values[2] = value; }
    inline void setHeight(int value) { _values[3] = value; }

    // -------------------------------------------------------------------------

    constexpr bool isEmpty() const
    {
        return (getWidth() <= 0) || (getHeight() <= 0);
    }

    constexpr float aspectRatio() const
    {
        return
                /* if */ (getHeight() != 0) ? /* prevent division-by-zero */
                    static_cast<float>( getWidth() ) / static_cast<float>( getHeight() )
                /* else */ :
                    0.0f;
    }

    constexpr int getCenterX() const { return getX() + (getWidth()  / 2); }
    constexpr int getCenterY() const { return getY() + (getHeight() / 2); }

    // -------------------------------------------------------------------------

    inline int* getData()
    {
        return _values;
    }

    constexpr const int* getConstData() const
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
