#ifndef POINT3D_H_INCLUDED
#define POINT3D_H_INCLUDED

#include "Geometry3D.hpp"

template < class T >
class Point3D {
public:
    T x;
    T y;
    T z;

    Point3D(const T &_x = 0, const T &_y = 0, const T &_z = 0) {
        x = _x;
        y = _y;
        z = _z;
    }

    ~Point3D() {

    }

    Point3D &operator = (const Point3D &a) {
        if (this == &a)
            return *this;
        x = a.x;
        y = a.y;
        z = a.z;
        return *this;
    }

    friend bool operator == (const Point3D &a, const Point3D &b) {
        return (_ABS(a.x - b.x) < EPS && _ABS(a.y - b.y) < EPS && _ABS(a.z - b.z) < EPS);
    }

    friend bool operator != (const Point3D &a, const Point3D &b) {
        return (!(a == b));
    }

    friend const Point3D& operator + (const Point3D &a) {
        return a;
    }

    friend const Point3D operator - (const Point3D &a) {
        return Point3D(-a.x, -a.y, -a.z);
    }

    friend Point3D operator + (const Point3D &a, const Point3D &b) {
        return Point3D(a.x + b.x, a.y + b.y, a.z + b.z);
    }

    friend Point3D operator += (Point3D &a, const Point3D &b) {
        a.x += b.x;
        a.y += b.y;
        a.z += b.z;
        return a;
    }

    friend Point3D operator - (const Point3D &a, const Point3D &b) {
        return Point3D(a.x - b.x, a.y - b.y, a.z - b.z);
    }

    friend Point3D operator -= (Point3D &a, const Point3D &b) {
        a.x -= b.x;
        a.y -= b.y;
        a.z -= b.z;
        return a;
    }

    friend Point3D operator * (const T &m, const Point3D &a) {
        return Point3D(a.x * m, a.y * m, a.z * m);
    }

    friend Point3D& operator *= (Point3D &a, const T &m) {
        a.x *= m;
        a.y *= m;
        a.z *= m;
        return a;
    }

    friend Point3D operator / (const Point3D &a, const T &m) {
        return Point3D (a.x / m, a.y / m, a.z / m);
    }

    friend Point3D& operator /= (Point3D &a, const T &m) {
        a.x /= m;
        a.y /= m;
        a.z /= m;
        return a;
    }

    friend std::ostream& operator << (std::ostream& outputstream, const Point3D &P) {
        outputstream << "(" << P.x << "," << P.y << "," << P.z << ")";
        return outputstream;
    }

    friend std::istream& operator >> (std::istream& inputstream, Point3D &P) {
        inputstream >> P.x >> P.y >> P.z;
        return inputstream;
    }

};

#endif // POINT_H_INCLUDED
