#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include "vector.h"
#include "material.h"
#include "ray.h"

#include <math.h>

#include <iostream>

class SceneObject {
	public:
		Material* mat;
        Vec3 position;

		SceneObject() {}

		virtual float intersect(const Ray& r) const = 0;
		virtual Vec3 normal_at(const Ray& r) const = 0;
		virtual bool scatter(const Ray& inc, const Vec3& intersection_point, Ray& out) const = 0;
		void set_material(Material* m) { mat = m; };
		Material* get_material() const { return mat; };

};


class ScenePrimitive: public SceneObject {
	
	public:
        ScenePrimitive() : ScenePrimitive(Vec3(), new Normals()) {}

		ScenePrimitive(const Vec3& p) : ScenePrimitive(p, new Normals()) {}

		ScenePrimitive(const Vec3& p, Material* m) {
			position = p;
			mat = m;
		}

		
		
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
			Vec3 beta = r.origin - position;
			float d = beta.dot(r.dir);
			if (d < 0) {
				return -1;
			}
			Vec3 delta = beta.project_onto(r.dir);
			Vec3 gamma = beta - delta;
			
			if (gamma.norm_squared() > radius * radius) {
				return -1;
			}

			float l1 = sqrt(radius * radius - gamma.norm_squared());
			float c = sqrt(beta.norm_squared() - gamma.norm_squared());
			float t1 = c - l1;

			return t1;
		}

		virtual Vec3 normal_at(const Ray& r) const override {
			return (r.at(intersect(r)) - position).normalized();
		}

		virtual bool scatter(const Ray& inc, const Vec3& intersection_point, Ray& out) const override {
			out.origin = intersection_point;
			return mat->scatter(inc, normal_at(inc), out);
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