#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include "vector.h"
#include "material.h"
#include "ray.h"

#include <math.h>

#include <iostream>

class SceneObject {
	public:
		SceneObject() {}
		virtual float intersect(const Ray& r) const {};
		virtual Vec3 normal_at(const Ray& r) const {};
		virtual Vec3 color_at(const Ray& r) const {};

};


class ScenePrimitive: public SceneObject {
	

	public:
        Vec3 position;
        ScenePrimitive() {}

};

class Sphere: public ScenePrimitive {
	public:
		Vec3 center;
		float radius;

		Sphere() {
			radius = 1.0;
			center = newVec3(0.0, 0.0, 0.0);
		}

		Sphere(float r, const Vec3& c) {
			radius = r;
			center = c;
		}

		virtual float intersect(const Ray& r) const override {
			Vec3 beta = r.origin + center;

			float beta_len_squared = beta.norm_squared();
			float delta_len = beta.dot(r.dir);

			if (delta_len < 0) {
				return -1;
			}

			float delta_len_squared = delta_len * delta_len;
			float center_to_delta_squared = beta_len_squared - delta_len_squared;
			if (center_to_delta_squared > radius * radius) return -1;
			float delta_to_intersection = sqrt(radius * radius - center_to_delta_squared);

			float t1 = delta_len - delta_to_intersection;
			float t2 = delta_len + delta_to_intersection;

			Vec3 intersect = r.at(t2);
			Vec3 normal = (intersect - center).normalized();

			return t1;
		}

		virtual Vec3 normal_at(const Ray& r) const override {
			return (r.at(intersect(r)) - center).normalized();
		}

		// Normal coloring for now
		virtual Vec3 color_at(const Ray& r) const override {
			return normal_at(r);
		}
};

#endif