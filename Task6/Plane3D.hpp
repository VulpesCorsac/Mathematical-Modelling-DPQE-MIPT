#ifndef PLANE3D_H_INCLUDED
#define PLANE3D_H_INCLUDED

#include "Geometry3D.hpp"

template < class T >
class Plane3D {
public:
    T A;
    T B;
    T C;
    T D;

    Plane3D(const T &_A, const T &_B, const T &_C, const T &_D) {
        A = _A;
        B = _B;
        C = _C;
        D = _D;
    }

    Plane3D(const Point3D < T > &P1, const Point3D < T > &P2, const Point3D < T > &P3) {
        Vector3D < T > N = Vector_mul(Vector3D < T > (P1, P2), Vector3D < T > (P1, P3));
        A = N.x;
        B = N.y;
        C = N.z;
        D = -A*P1.x - B*P1.y - C*P1.z;
    }

    Plane3D(const Point3D < T > &P, const Vector3D < T > &V1, const Vector3D < T > &V2) {
        Vector3D < T > N = Vector_mul(Vector3D < T > (P, P + V1), Vector3D < T > (P, P + V2));
        A = N.x;
        B = N.y;
        C = N.z;
        D = -A*P.x - B*P.y - C*P.z;
    }

    Plane3D &operator = (const Plane3D &a) {
        if (this == &a)
            return *this;
        A = a.A;
        B = a.B;
        C = a.C;
        D = a.D;
        return *this;
    }

    friend bool operator == (const Plane3D &P1, const Plane3D &P2) {
        return (_ABS(P1.A*P2.B - P2.A*P1.B) < EPS &&
                _ABS(P1.B*P2.C - P2.B*P1.C) < EPS &&
                _ABS(P1.C*P2.D - P2.C*P1.D) < EPS &&
                _ABS(P1.D*P2.A - P2.D*P1.A) < EPS);
    }

    friend bool operator != (const Plane3D &P1, const Plane3D &P2) {
        return (!(P1 == P2));
    }

    friend std::ostream& operator << (std::ostream& outputstream, const Plane3D &P) {
        outputstream << P.A << "*x";
        if (P.B >= 0)
            outputstream << "+";
        outputstream << P.B << "*y";
        if (P.C >= 0)
            outputstream << "+";
        outputstream << P.B << "*z";
        if (P.D >= 0)
            outputstream << "+";
        outputstream << P.D << "=0";

        return outputstream;
    }

    friend std::istream& operator >> (std::istream& inputstream, Plane3D &P) {
        inputstream >> P.A >> P.B >> P.C >> P.D;
        return inputstream;
    }

};

#endif // PLANE3D_H_INCLUDED
