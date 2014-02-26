#ifndef FUNCTIONS3D_H_INCLUDED
#define FUNCTIONS3D_H_INCLUDED

#include "Geometry3D.hpp"
#include <math.h>
#include <algorithm>

// X to Y

template < class T >
T Point_to_plane(const Point3D < T > &P, const Plane3D < T > &Pl) {
    return Pl.A*P.x + Pl.B*P.y + Pl.C*P.z + Pl.D;
}

// Points

template < class T >
Point3D < T > Part_segment (const Point3D < T > &P1, const Point3D < T > &P2, const T &n, const T &m) {
    return Point3D < T > ((P1.x*n + P2.x*m) / (m + n), (P1.y*n + P2.y*m) / (m + n), (P1.z*n + P2.z*m) / (m + n));
}

// Vectors

template < class T >
T Scalar_mul(const Vector3D < T > &V1, const Vector3D < T > &V2) {
    return V1.x*V2.x + V1.y*V2.y + V1.z*V2.z;
}

template < class T >
Vector3D < T > Vector_mul(const Vector3D < T > &V1, const Vector3D < T > &V2) {
    return Vector3D < T > (V1.y*V2.z - V2.y*V1.z, V2.x*V1.z - V1.x*V2.z, V1.x*V2.y - V2.x*V1.y);
}

template < class T >
Vector3D < T > Norm(const Vector3D < T > &V) {
    return Vector3D < T > (V.x / V.Norm(), V.y / V.Norm(), V.z / V.Norm());
}

// Lines

template < class T >
bool Are_parallel_lines(const Line3D < T > &L1, const Line3D < T > &L2) {
    return (Vector_mul(L1.V, L2.V) == Vector3D < T > (0, 0, 0));
}

template < class T >
Point3D < T > Point_in_line_by_X(const Line3D < T > &L, const T X) {
    T t = (X - L.P.x) / L.V.x;
    return Point3D < T > (L.P.x + t*L.V.x, L.P.y + t*L.V.y, L.P.z + t*L.V.z);
}

template < class T >
Point3D < T > Point_in_line_by_Y(const Line3D < T > &L, const T Y) {
    T t = (Y - L.P.y) / L.V.y;
    return Point3D < T > (L.P.x + t*L.V.x, L.P.y + t*L.V.y, L.P.z + t*L.V.z);
}

template < class T >
Point3D < T > Point_in_line_by_Z(const Line3D < T > &L, const T Z) {
    T t = (Z - L.P.z) / L.V.z;
    return Point3D < T > (L.P.x + t*L.V.x, L.P.y + t*L.V.y, L.P.z + t*L.V.z);
}

// Distanses

template < class T >
T dist(const Point3D < T > &P1, const Point3D < T > &P2) {
    return sqrt(_SQR(P1.x - P2.x) + _SQR(P1.y - P2.y) + _SQR(P1.z - P2.z));
}

template < class T >
T dist(const Point3D < T > &P, const Line3D < T > &L) {
    Vector3D < T > Tmp = Vector_mul(Vector3D < T > (P, L.P), L.V);
    return (Tmp.Norm() / L.V.Norm());
}

template < class T >
T dist(const Point3D < T > &P, const Segment3D < T > &Seg) {
    Vector3D < T > V1(P, Seg.A), V2(P, Seg.B);
    Vector3D < T > S = Vector_mul(V1, V2);
    return (S.Norm() / Seg.length());
}

template < class T >
T dist(const Point3D < T > &P, const Sphere < T > &S) {
    T ans = dist(P, S.Centre) - S.R;
    if (ans < EPS)
        ans = 0;
    return ans;
}

template < class T >
T dist(const Point3D < T > &P, const Plane3D < T > &Pl) {
    return (_ABS(Point_to_plane(P, Pl))) /(sqrt(_SQR(Pl.A) + _SQR(Pl.B) + _SQR(Pl.C)));
}

template < class T >
T dist (const Line3D < T > &L, const Plane3D < T > &P) {
    if ((Point_in_plane(L.P, P) && Point_in_plane(L.P + L.V, P)) ||
        _ABS(P.A*L.V.x + P.B*L.V.y + P.C*L.V.z) >= EPS)
        return 0;
    return dist(L.P, P);
}

template < class T >
T dist(const Segment3D < T > &Seg, const Sphere < T > &Sph) {
    T ans = dist(Sph.Centre, Seg) - Sph.R;
    if (ans < EPS)
        ans = 0;
    return (ans);
}

template < class T >
T dist(const Segment3D < T > &S, const Plane3D < T > &P) {
    if (Point_to_plane(S.A, P)*Point_to_plane(S.B, P) <= EPS)
        return 0;
    return std::min(dist(S.A, P), dist(S.B, P));
}

// A in B

template < class T >
bool Point_in_box(const Point3D < T > &P1, const Point3D < T > &P2, const Point3D < T > &P) {
    return  (abs(P.x - std::min(P1.x, P2.x)) <= EPS || std::min(P1.x, P2.x) <= P.x) &&
            (abs(std::max(P1.x, P2.x) - P.x) <= EPS || std::max(P1.x, P2.x) >= P.x) &&
            (abs(P.y - std::min(P1.y, P2.y)) <= EPS || std::min(P1.y, P2.y) <= P.y) &&
            (abs(std::max(P1.y, P2.y) - P.y) <= EPS || std::max(P1.y, P2.y) >= P.y) &&
            (abs(P.x - std::min(P1.x, P2.x)) <= EPS || std::min(P1.x, P2.x) <= P.x) &&
            (abs(std::max(P1.x, P2.x) - P.x) <= EPS || std::max(P1.x, P2.x) >= P.x);
}

template < class T >
bool Point_in_line_3D(const Point3D < T > &Point, const Line3D < T > &Line) {
    return (Vector_mul(Line.V, Vector3D < T > (Point, Line.P)) == Vector3D < T > (0, 0, 0));
}

template < class T >
bool Point_in_plane_3D(const Point3D < T > &P, const Plane3D < T > &Pl) {
    return (_ABS(Point_to_plane(P, Pl)) < EPS);
}

template < class T >
bool Point_in_segment_3D(const Point3D < T > &P, const Segment3D < T > &S) {
    return (Point_in_box(S.A, S.B, P) && Point_in_line_3D(P, Line3D < T > (S.A, S.B)));
}

template < class T >
bool Point_in_sphere(const Point3D < T > &P, const Sphere < T > &S) {
    return (dist(P. S) <= EPS);
}

template < class T >
bool Segment_cross_sphere(const Segment3D < T > &Seg, const Sphere < T > &Shp) {
    return (dist(Seg, Shp) <= EPS);
}

template < class T >
bool Sphere_cross_plane(const Sphere < T > &S, const Plane3D < T > &P) {
    return (dist(S.Centre, P) <= S.R);
}

template < class T >
bool Line_cross_sphere(const Line3D < T > &L, const Sphere < T > &S) {
    return (dist(S.Centre, L) <= S.R);
}

template < class T >
bool Line_in_plane(const Line3D < T > &L, const Plane3D < T > &P) {
    return (Point_in_plane(L.P, P) && Point_in_plane(L.P + L.V, P));
}

#endif // FUNCTIONS3D_H_INCLUDED
