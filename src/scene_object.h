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
		virtual bool scatter(const Ray& inc, Vec3& color, Ray& out) const {};
		virtual Material get_material() const {};

};


class ScenePrimitive: public SceneObject {
	

	public:
		Material mat;
        Vec3 position;
        ScenePrimitive() {}
};

class Sphere: public ScenePrimitive {
	public:
		Vec3 center;
		float radius;

		Sphere() {
			radius = 1.0;
			center = Vec3(0.0, 0.0, 0.0);
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

			return t2;
		}

		virtual Vec3 normal_at(const Ray& r) const override {
			return (r.at(intersect(r)) - center).normalized();
		}

		// Normal coloring for now
		virtual Vec3 color_at(const Ray& r) const override {
			return (normal_at(r) + Vec3(1.0, 1.0, 1.0)) / 2.0;
		}

		virtual bool scatter(const Ray& inc, Vec3& color, Ray& out) const override {
			return true;
		}
};

// TODO: Add more primitives
class Cube: public ScenePrimitive {

};

class Triangle: public ScenePrimitive {

};

class Rectangle: public ScenePrimitive {

};

#endif