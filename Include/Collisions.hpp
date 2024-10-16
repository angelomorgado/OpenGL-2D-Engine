#ifndef COLLISIONS_HPP
#define COLLISIONS_HPP

#include <Object.hpp>

namespace Collisions {
    bool checkAABBCollision(Object& obj1, Object& obj2);
    unsigned int checkAABBCollisionComplex(Object& obj1, Object& obj2);
    bool checkCircleCollision(Object& circle, Object& obj);
    unsigned int checkCircleCollisionComplex(Object& circle, Object& obj);
    unsigned int checkWindowCollision(Object& obj);
    unsigned int detectBoundaryOverlap(Object& obj1, Object& obj2);
}

#endif