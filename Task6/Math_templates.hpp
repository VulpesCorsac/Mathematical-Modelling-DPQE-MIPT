#ifndef MATH_TEMPLATES_HPP_INCLUDED
#define MATH_TEMPLATES_HPP_INCLUDED

// Helpful Functions

template < class T >
T _ABS(const T &x) {
    if (x < 0)
        return -x;
    return x;
}

template < class T >
T _SQR(const T &x) {
    return x * x;
}

#endif // MATH_TEMPLATES_HPP_INCLUDED
