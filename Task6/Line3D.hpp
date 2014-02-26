#ifndef LINE3D_H_INCLUDED
#define LINE3D_H_INCLUDED

#include "Geometry3D.hpp"

template < class T >
class Line3D {
public:
    Point3D < T > P;
    Vector3D < T > V;

    Line3D(const Point3D < T > &_P, const Vector3D < T > &_V) {
        P = _P;
        V = _V;
    }

    Line3D(const Point3D < T > &_P1, const Point3D < T > &_P2) {
        P = _P1;
        V = Vector3D < T > (_P1, _P2);
    }

    ~Line3D() {

    }

    Line3D &operator = (const Line3D &a) {
        if (this == &a)
            return *this;
        P = a.P;
        V = a.V;
        return *this;
    }
    friend bool operator == (const Line3D &A, const Line3D &B) {
        return (Point_in_line_3D(A.P, B) && Point_in_line_3D(A.P + A.V, B) &&
                Point_in_line_3D(B.P, A) && Point_in_line_3D(B.P + B.V, A));
    }

    friend bool operator != (const Line3D &A, const Line3D &B) {
        return (!(A == B));
    }

    friend std::ostream& operator << (std::ostream& outputstream, const Line3D &P) {
        outputstream << P.P << "+t*" << P.V;
        return outputstream;
    }

    friend std::istream& operator >> (std::istream& inputstream, Line3D &P) {
        inputstream >> P.P >> P.V;
        return inputstream;
    }
};

#endif // LINE_H_INCLUDED
