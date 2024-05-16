#ifndef RAY_H
#define RAY_H

#include "vector.h"

class Ray {
    public:
        Vec3 origin, dir;
        Vec3 color;

        Ray(const Vec3& o, const Vec3& d) {
            origin = o;
            dir = (d-o).normalized();
            color = newVec3(0.0, 0.0, 0.0);
        }

        Ray(const Vec3& o, const Vec3& d, const Vec3& c) {
            origin = o;
            dir = (d-o).normalized();
            color = c;
        }

        Vec3 at(float t) const {
            return origin + t * dir;
        }

};

#endif