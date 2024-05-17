#ifndef MATERIAL_H
#define MATERIAL_H

#include "vector.h"
#include "ray.h"

class Material {
	public:
		Material() {}

		// true == reflected
		// false == absorbed
		virtual bool scatter(const Ray& inc, const Vec3& normal, Ray& out) const {
			//cout << "default\n";
			out.color = color * albedo;
			out.dir = reflect_ray(inc.dir, normal);
			return true;
		}

		virtual Vec3 reflect_ray(const Vec3& inc, const Vec3& normal) const {
			return Vec3();
		}

		void set_albedo(const float a) {
			albedo = a;
		}

		void set_alpha(const float a) {
			alpha = a;
		}

		void set_color(const Vec3& c) {
			color = c;
		}

		float albedo;
		Vec3 color;
		float alpha; // transparency
};

class Normals : public Material {
	public:
		Normals() {
			cout << "n";
			albedo = 1.0;
		}

		virtual bool scatter(const Ray& inc, const Vec3& normal, Ray& out) const override {
			cout << "Normals\n";
			out.color = normal;
			return false;
		}

		virtual Vec3 reflect_ray(const Vec3& inc, const Vec3& normal) const override {
			return Vec3();
		}
};

class Diffuse : public Material {
	public:
		Diffuse() {
			albedo = 0.5;
			alpha = 0.0;
		}

		virtual Vec3 reflect_ray(const Vec3& inc, const Vec3& normal) const override {
			return Vec3::random_on_hemisphere(normal);
		}
};

class Mirror : public Material {
	public:
		Mirror() {
			albedo = 1.0;
		}
		virtual Vec3 reflect_ray(const Vec3& inc, const Vec3& normal) const override {
			return Vec3::reflected(inc, normal);
		}
};

#endif