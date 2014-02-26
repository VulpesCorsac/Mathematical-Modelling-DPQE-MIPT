#ifndef VECTOR3D_H_INCLUDED
#define VECTOR3D_H_INCLUDED

#include "Geometry3D.hpp"

template < class T >
class Vector3D {
public:
    T x;
    T y;
    T z;

    Vector3D(const T &_x = 0, const T &_y = 0, const T &_z = 0) {
        x = _x;
        y = _y;
        z = _z;
    }

    Vector3D(const Point3D < T > &A) {
        x = A.x;
        y = A.y;
        z = A.z;
    }

    Vector3D(const Point3D < T > &A, const Point3D < T > &B) {
        x = B.x - A.x;
        y = B.y - A.y;
        z = B.z - A.z;
    }

    ~Vector3D() {

    }

    double Norm() const {
        return sqrt(_SQR(x) + _SQR(y) + _SQR(z));
    }

    Vector3D &operator = (const Vector3D &a) {
        if (this == &a)
            return *this;
        x = a.x;
        y = a.y;
        z = a.z;
        return *this;
    }

    friend bool operator == (const Vector3D &a, const Vector3D &b) {
        return (_ABS(a.x - b.x) < EPS && _ABS(a.y - b.y) < EPS && _ABS(a.z - b.z) < EPS);
    }

    friend bool operator != (const Vector3D &a, const Vector3D &b) {
        return (!(a == b));
    }


    friend const Vector3D& operator + (const Vector3D &a) {
        return a;
    }

    friend const Vector3D operator - (const Vector3D &a) {
        return Vector3D(-a.x, -a.y, -a.z);
    }

    friend Vector3D operator + (const Vector3D &a, const Vector3D &b) {
        return Vector3D(a.x + b.x, a.y + b.y, a.z + b.z);
    }

    friend Vector3D operator += (Vector3D &a, const Vector3D &b) {
        a.x += b.x;
        a.y += b.y;
        a.z += b.z;
        return a;
    }

    friend Point3D < T > operator + (const Point3D < T > &P, const Vector3D &V) {
        return Point3D < T > (P.x + V.x, P.y + V.y, P.z + V.z);
    }

    friend Point3D < T > operator += (Point3D < T > &P, const Vector3D &V) {
        P.x += V.x;
        P.y += V.y;
        P.z += V.z;
        return P;
    }

    friend Vector3D operator - (const Vector3D &a, const Vector3D &b) {
        return Vector3D (a.x - b.x, a.y - b.y, a.z - b.z);
    }

    friend Vector3D operator -= (Vector3D &a, const Vector3D &b) {
        a.x -= b.x;
        a.y -= b.y;
        a.z -= b.z;
        return a;
    }

    friend Point3D < T > operator - (const Point3D < T > &P, const Vector3D &V) {
        return Vector3D (P.x - V.x, P.y - V.y, P.z - V.z);
    }

    friend Point3D < T > operator -= (Point3D < T > &P, const Vector3D &V) {
        Point3D < T > ans = P;
        P.x -= V.x;
        P.y -= V.y;
        P.z -= V.z;
        return P;
    }

    friend Vector3D operator * (const T &m, const Vector3D &a) {
        return Vector3D(a.x * m, a.y * m, a.z * m);
    }

    friend Vector3D& operator *= (Vector3D &a, const T &m) {
        a.x *= m;
        a.y *= m;
        a.z *= m;
        return a;
    }

    friend Vector3D operator / (const Vector3D &a, const T &m) {
        return Vector3D(a.x / m, a.y / m, a.z / m);
    }

    friend Vector3D& operator /= (Vector3D &a, const T &m) {
        a.x /= m;
        a.y /= m;
        a.z /= m;
        return a;
    }

    friend std::ostream& operator << (std::ostream& outputstream, const Vector3D &P) {
        outputstream << "(" << P.x << "," << P.y << "," << P.z << ")";
        return outputstream;
    }

    friend std::istream& operator >> (std::istream& inputstream, Vector3D &P) {
        inputstream >> P.x >> P.y >> P.z;
        return inputstream;
    }

};

#endif // VECTOR3D_H_INCLUDED
