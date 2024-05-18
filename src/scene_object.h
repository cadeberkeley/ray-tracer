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
		virtual float intersect(const Ray& r) const = 0;
		virtual Vec3 normal_at(const Ray& r) const = 0;
		virtual Vec3 color_at(const Ray& r) const = 0;
		virtual bool scatter(const Ray& inc, Ray& out) const = 0;

};


class ScenePrimitive: public SceneObject {
	
	public:
		Material* mat;
        Vec3 position;

        ScenePrimitive() : ScenePrimitive(Vec3(), new Normals()) {}

		ScenePrimitive(const Vec3& p) : ScenePrimitive(p, new Normals()) {}

		ScenePrimitive(const Vec3& p, Material* m) {
			position = p;
			mat = m;
		}

		void set_material(Material* m) { mat = m; };
		Material* get_material() const { return mat; };
		
};

class Sphere: public ScenePrimitive {
	public:
		float radius;

		Sphere() : ScenePrimitive() {
			radius = 1.0;
		}

		Sphere(const Vec3& center, const float r) : ScenePrimitive(center) {
			radius = r;
		}

		Sphere(const Vec3& center, const float r, Material* m) : ScenePrimitive(center, m) {
			radius = r;
		}

		virtual float intersect(const Ray& r) const override {
			Vec3 beta = r.origin + position;

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
			Vec3 normal = (intersect - position).normalized();

			return t2;
		}

		virtual Vec3 normal_at(const Ray& r) const override {
			return (r.at(intersect(r)) - position).normalized();
		}

		// Normal coloring for now
		virtual Vec3 color_at(const Ray& r) const override {
			return (normal_at(r) + Vec3(1.0, 1.0, 1.0)) / 2.0;
		}

		virtual bool scatter(const Ray& inc, Ray& out) const override {
			mat->scatter(inc, normal_at(inc), out);
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