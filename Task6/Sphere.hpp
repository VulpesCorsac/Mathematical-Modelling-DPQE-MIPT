#ifndef SPHERE_HPP_INCLUDED
#define SPHERE_HPP_INCLUDED

#include "Geometry3D.hpp"

template < class T >
class Sphere {
public:
    Point3D < T > Centre;
    T R;

    Sphere(const Point3D < T > &_C, const T &_R = 0) {
        R = _R;
        Centre = _C;
    }

    Sphere (const T &_X = 0, const T &_Y = 0, const T &_Z = 0, const T &_R = 0) {
        Centre.x = _X;
        Centre.y = _Y;
        Centre.z = _Z;
        R = _R;
    }

    ~Sphere() { }

    Sphere &operator = (const Sphere &a) {
        if (this == &a)
            return *this;
        Centre = a.Centre;
        R = a.R;
        return *this;
    }

    friend bool operator == (const Sphere &S1, const Sphere &S2) {
        return (_ABS(S1.R - S2.R) < EPS && S1.Centre == S2.Centre);
    }

    friend bool operator != (const Sphere &S1, const Sphere &S2) {
        return (!(S1 == S2));
    }

    friend std::ostream& operator << (std::ostream& outputstream, const Sphere &S) {
        outputstream << "[" << S.Centre << "," << S.R << "]";
        return outputstream;
    }

    friend std::istream& operator >> (std::istream& inputstream, Sphere &S) {
        inputstream >> S.Centre >> S.R;
        return inputstream;
    }
};

#endif // SPHERE_HPP_INCLUDED
