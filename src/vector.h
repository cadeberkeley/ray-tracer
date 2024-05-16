#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <type_traits>
#include <math.h>

#define newVec3(f1, f2, f3) Vector<float, 3>({f1, f2, f3})
#define Vec3 Vector<float, 3>

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

        static Vector cross(Vector<T, N> a, Vector<T, N> b) {
            assert(N == 3, "Cross product only for 3D vectors.");
            T cross [3] = { a.elements[1] * b.elements[2] - a.elements[2] * b.elements[1],
                                a.elements[2] * b.elements[0] - a.elements[0] * b.elements[2],
                                a.elements[0] * b.elements[1] - a.elements[1] * b.elements[0]
                            };
            return Vector<T, N>(cross);
        }

    public:
        T elements [N];

        Vector() {
            for (int i=0; i < N; i++) {
                elements[i] = (T) 0;
            }
        }

        Vector(T (&from)[N]) {
            std::copy(std::begin(from), std::end(from), std::begin(elements));
        }

        Vector(Vector<T, N> from) {
            std::copy(from.elements.begin(), from.elements.end(), elements);
        }

        T &operator[](int i) {
            return elements[i];
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

        Vector& operator*=(const T scalar) {
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

};

#endif