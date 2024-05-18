#ifndef MATERIAL_H
#define MATERIAL_H

#include "vector.h"
#include "ray.h"

class Material {
	public:
		Vec3 color;
		float albedo;
		float alpha; // transparency

		Material() {
		}

		Material(const Vec3& c) {
			color = c;
		}

		// true == reflected
		// false == absorbed
		virtual bool scatter(const Ray& inc, const Vec3& normal, Ray& out) const {
			//out.color = albedo * color - (1-albedo) * inc.color;
			out.dir = reflect_ray(inc.dir, normal);
			return true;
		}

		virtual Vec3 reflect_ray(const Vec3& inc, const Vec3& normal) const = 0;

		void set_albedo(const float a) {
			albedo = a;
		}

		void set_alpha(const float a) {
			alpha = a;
		}

		void set_color(const Vec3& c) {
			color = c;
		}

};

class Normals : public Material {
	public:
		Normals() {
			albedo = 1.0;
		}

		virtual bool scatter(const Ray& inc, const Vec3& normal, Ray& out) const override {
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

		Diffuse(const Vec3& c) : Material(c) {
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

class Metal : public Material {
	public:
		Metal() {
			albedo = 0.8;
		}

		Metal(const Vec3& c) : Material(c) {
			albedo = 0.8;
		}
		virtual Vec3 reflect_ray(const Vec3& inc, const Vec3& normal) const override {
			return Vec3::reflected(inc, normal);
		}
};

class Emissive : public Material {
	public:
		Emissive() {
			albedo = 1.0;
		}

		Emissive(const Vec3& c) : Material(c) {
			albedo = 1.0;
		}

		virtual bool scatter(const Ray& inc, const Vec3& normal, Ray& out) const override {
			out.color = color;
			out.dir = reflect_ray(inc.dir, normal);
			return false;
		}

		virtual Vec3 reflect_ray(const Vec3& inc, const Vec3& normal) const override {
			return Vec3::reflected(inc, normal);
		}
};

#endif