#ifndef MATERIAL_H
#define MATERIAL_H

#include "vector.h"

class Material {
	public:
		
		Material() {}

		virtual bool scatter(const Ray& inc, const Vec3& normal, Ray& out) {
			out.color *= albedo;
			out.dir = reflect_ray(inc.dir, normal);
		}

		virtual Vec3 reflect_ray(const Vec3& inc, const Vec3& normal) const {}

		void set_albedo(float a) {
			albedo = a;
		}

		void set_alpha(float a) {
			alpha = a;
		}

		void set_color(Vec3& c) {
			color = c;
		}

	protected:
		float albedo;
		Vec3 color;
		float alpha; // transparency
};

class Diffuse : protected Material {
	public:
		Diffuse() {
			albedo = 0.5;
			alpha = 0.0;
		}

		virtual Vec3 reflect_ray(const Vec3& inc, const Vec3& normal) const override {
			return Vec3::random_on_hemisphere(normal);
		}
};

class Mirror : protected Material {
	public:
		virtual Vec3 reflect_ray(const Vec3& inc, const Vec3& normal) const override {
			return Vec3::reflected(inc, normal);
		}
};

#endif