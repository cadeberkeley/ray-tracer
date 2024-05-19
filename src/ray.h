#ifndef RAY_H
#define RAY_H

#include "vector.h"

class Ray {
    public:
        Vec3 origin, dir;
        Vec3 color;

        Ray() {
            origin = Vec3();
            dir = Vec3();
            color = Vec3();
        }

        Ray(const Vec3& o, const Vec3& d) {
            origin = o;
            dir = (d-o).normalized();
            color = Vec3(0.0, 0.0, 0.0);
        }

        Ray(const Vec3& o, const Vec3& d, const Vec3& c) {
            origin = o;
            dir = (d-o).normalized();
            color = c;
        }

        Vec3 at(float t) const {
            return origin + t * dir;
        }

        friend std::ostream & operator<<(std::ostream& os, const Ray& r) {
            os << "Ray origin: " << r.origin << "; direction: " << r.dir;
            return os;
        }

};

#endif