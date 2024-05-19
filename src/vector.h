#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <type_traits>
#include <math.h>
#include <cstdlib>
#include <cassert>

using namespace std;

template <typename T, size_t N> class Vector {
    
    static_assert(std::is_arithmetic<T>::value, "Not an arithmetic type.");

    public:
        static T dot(Vector<T, N> a, Vector<T, N> b) {
            T sum = 0;
            for (int i = 0; i < N; i++) {
                sum += a.elements[i] *= b.elements[i];
            }
            return sum;
        }

        static T random_value() {
            return (T)rand() / (T)RAND_MAX;
        }

        static T random_value(T min, T max) {
            return min + (T)rand()/((T)RAND_MAX/(T)(max-min));
        }

        static Vector random() {
            T e[N];
            for (int i = 0; i < N; i++) {
                e[i] = random_value();
            }
            return Vector(e);
        }

        static Vector random(float min, float max) {
            T e[N];
            for (int i = 0; i < N; i++) {
                e[i] = random_value(min, max);
            }
            return Vector(e);
        }

        static Vector random_unit_vector() {
            return random().normalized();
        }
    
        T elements [N];

        Vector() {
            fill(elements, elements+N, T(0));
        }

        Vector(const T (&from)[N]) {
            std::copy(begin(from), end(from), begin(elements));
        }

        Vector(const Vector<T, N> &from) {
            std::copy(begin(from.elements), end(from.elements), begin(elements));
        }

        Vector(std::initializer_list<T> elems) {
            int i = 0;
            typename std::initializer_list<T>::iterator it;
            for (it = elems.begin() ; it != elems.end() ; ++it) {
                elements[i++] = *it;
            }
        }


        T dot(Vector<T, N> other) const {
            return Vector<T, N>::dot(*this, other);
        }

        Vector cross(Vector<T, N> other) {
            return Vector<T, N>::cross(*this, other);
        }

        Vector normalized() const {
            return *this / norm();
        }

        float norm() const {
            return (T) sqrt(norm_squared());
        }

        float norm_squared() const {
            T sum = 0;
            for (int i = 0; i < N; i++) {
                sum += elements[i] * elements[i];
            }

            return sum;
        }
        
        /* Override common mathematical operators */

        Vector& operator+=(const Vector<T, N>& other) {
            for (int i = 0; i < N; i++) {
                elements[i] += other.elements[i];
            }
            return *this;
        }

        friend Vector operator+(Vector a, const Vector<T, N>& b) {
            a += b;
            return a;
        }

        Vector& operator-=(const Vector<T, N>& other) {
            for (int i = 0; i < N; i++) {
                elements[i] -= other.elements[i];
            }
            return *this;
        }

        friend Vector operator-(Vector a, const Vector<T, N>& b) {
            a -= b;
            return a;
        }

        Vector operator-() {
            for (int i = 0; i < N; i++) {
                elements[i] *= -1;
            }
            return *this;
        }

        Vector operator*=(const T scalar) {
            for (int i = 0; i < N; i++) {
                elements[i] *= scalar;
            }
            return *this;
        }

        friend Vector operator*(Vector v, const T scalar) {
            v *= scalar;
            return v;
        }

        friend Vector operator*(const T scalar, Vector v) {
            v *= scalar;
            return v;
        }

        friend Vector operator*(Vector a, Vector b) {
            for (int i = 0; i < N; i++) {
                a[i] *= b[i];
            }
            return a;
        }

        Vector& operator/=(const T scalar) {
            for (int i = 0; i < N; i++) {
                elements[i] /= scalar;
            }
            return *this;
        }

        friend Vector operator/(Vector v, const T scalar) {
            v /= scalar;
            return v;
        }

        friend std::ostream & operator<<(std::ostream& os, const Vector<T, N>& v) {
            os << "(";
            for (int i = 0; i < N-1; i++) {
                os << v.elements[i] << ", ";
            }
            os << v.elements[N-1] << ")" << std::endl;
            return os;
        }

        T operator[] (int i) const { return elements[i]; }
};

class Vec3 : public Vector<float, 3UL> {
    public:
        Vec3(float f0, float f1, float f2) {
            elements[0] = f0;
            elements[1] = f1;
            elements[2] = f2;
        }

        Vec3(const float (&from)[3]) {
            std::copy(begin(from), end(from), begin(elements));
        }

        Vec3() : Vec3(0.0, 0.0, 0.0) {}

        Vec3(const Vector<float, 3UL>& vec) {
            copy(begin(vec.elements), end(vec.elements), begin(elements));
        }

        Vec3& operator=(const Vector<float, 3UL>& vec) {
            if (this != &vec) {
                copy(begin(vec.elements), end(vec.elements), begin(elements));
            }
            return *this;
        }

        static Vec3 reflected(const Vec3& inc, const Vec3& normal) {
            return inc - 2*dot(inc,normal)*normal;
        }

        static Vec3 random_on_hemisphere(const Vec3& normal) {
            Vec3 unit = random_unit_vector();
            if (dot(unit, normal) > 0.0)
                return unit;
            else
                return -unit;
        }       

        static Vec3 cross(Vec3 a, Vec3 b) {
            float cross [3] = { a.elements[1] * b.elements[2] - a.elements[2] * b[1],
                                a.elements[2] * b.elements[0] - a.elements[0] * b.elements[2],
                                a.elements[0] * b.elements[1] - a.elements[1] * b.elements[0]
                            };
            return Vec3(cross);
        }

};

#endif