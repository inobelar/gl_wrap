#include <gl_wrap/objects/Object.hpp>

gl::Object::Object()
    : _id(0)
{ }

gl::Object::~Object()
{ }

gl::Object::id_t gl::Object::getId() const
{
    return _id;
}
