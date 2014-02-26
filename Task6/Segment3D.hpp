#ifndef SEGMENT3D_HPP_INCLUDED
#define SEGMENT3D_HPP_INCLUDED

#include "Geometry3D.hpp"

template < class T >
class Segment3D {
public:
    Point3D < T > A;
    Point3D < T > B;

    Segment3D(const Point3D < T > &_A, const Point3D < T > &_B) {
        A = _A;
        B = _B;
    }

    ~Segment3D () {

    }

    T length() const {
        return sqrt(_SQR(B.x - A.x) + _SQR(B.y - A.y) + _SQR(B.z - A.z));
    }

    Segment3D &operator = (const Segment3D &a) {
        if (this == &a)
            return *this;
        A = a.A;
        B = a.B;
        return *this;
    }

    friend bool operator == (const Segment3D &S1, const Segment3D &S2) {
        return (S1.A == S2.A && S1.B == S2.B);
    }

    friend bool operator != (const Segment3D &S1, const Segment3D &S2) {
        return (!(S1 == S2));
    }

    friend std::ostream& operator << (std::ostream& outputstream, const Segment3D &S) {
        outputstream << "[" << S.A << "," << S.B << "]";
        return outputstream;
    }

    friend std::istream& operator >> (std::istream& inputstream, Segment3D &S) {
        inputstream >> S.A >> S.B;
        return inputstream;
    }
};


#endif // SEGMENT3D_HPP_INCLUDED
