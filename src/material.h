#ifndef MATERIAL_H
#define MATERIAL_H

#include "vector.h"

class Material {
	public:
		Material(float r, float g, float b, float a) {
            this->r = r;
            this->g = g;
            this->b = b;
            this->a = a;
        }
		Material(float r, float g, float b) : Material(r, g, b, 0.0) {}
		Material(const Vec3& c) : Material(c[0], c[1], c[2]) {}
		Material() : Material(0.0, 0.0, 0.0, 0.0) {}

	private:
		float r, g, b, a;
};

#endif