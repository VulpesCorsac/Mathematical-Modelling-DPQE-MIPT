#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <math.h>

//#define sqr(x) ((x)*(x))

using namespace std;

typedef double type;

void solveMatrix(int n, type *a, type *c, type *b, type *f, type *x) {
    type m;
    for (int i = 1; i < n; i++) {
        m = a[i] / c[i-1];
        c[i] = c[i] - m*b[i-1];
        f[i] = f[i] - m*f[i-1];
    }
    x[n-1] = f[n-1] / c[n-1];
    for (int i = n - 2; i >= 0; i--)
        x[i] = (f[i]-b[i]*x[i+1])/c[i];
    return;
}

type sqr(type a) {
    return a*a;
}

type pi(void) {
    return 3.14159265258979323;
}

type func(type x = 0, type alpha = 0) {
    return 1 + alpha*sin(pi()*x);
}

type f_analitics(type x, type alpha = 0) {
    return alpha*sin(pi()*x)/(sqr(pi())) - sqr(x)/2.0 + (1 - alpha/pi())*x + 0.5 + alpha/pi();
}

type st(type du_0, type h, int st_type) {
    return du_0*h + (st_type - 1)*sqr(h)/2.0;
}

type fn(type un, type h, int number_of_steps, type alpha = 0) {
    return -un-sqr(h)*func(((number_of_steps-1)*h), alpha);
}

void solve(vector < type > &xx, vector < type > &u, int number_of_steps, int st_type = 2, type alpha = 0, type du_0 = 1, type un = 1) {
    type h = 1.0 / number_of_steps;
//    cout << "h = " << h << endl;
//    cout << "number_of_steps = " << number_of_steps << endl;
//    cout << "h*number_of_steps = " << h*number_of_steps << endl;
//    cout << "h*(number_of_steps-1) = " << h*(number_of_steps-1) << endl;
//    cout << "alpha = " << alpha << endl;

    xx.clear();
    u.clear();
    xx.resize(number_of_steps + 1);
    u.resize(number_of_steps + 1);
    for (int step = 0; step <= number_of_steps; step++)
        xx[step] = step*h;
    type *a = (type*) malloc(sizeof(type)*number_of_steps);
    type *c = (type*) malloc(sizeof(type)*number_of_steps);
    type *b = (type*) malloc(sizeof(type)*number_of_steps);
    type *f = (type*) malloc(sizeof(type)*number_of_steps);
    type *x = (type*) malloc(sizeof(type)*number_of_steps);
    c[0] = -1 ; b[0] = 1; a[0] = 0; f[0] = st(du_0, h, st_type);
//    cout << "f[0] = " << f[0] << endl;
    for (int step = 1; step < number_of_steps; step++) {
        c[step] = -2; b[step] = a[step] = 1;
        f[step] = -sqr(h)*func(xx[step], alpha);
//        cout << "f[" << step << "] = " << f[step] << endl;
    }
    f[number_of_steps - 1] = fn(un, h, number_of_steps);

    solveMatrix(number_of_steps, a, c, b, f, x);
    for (int i = 0; i < number_of_steps; i++)
        u[i] = x[i];
    u[number_of_steps] = un;

    return;
}

void print(vector < type > &x, vector < type > &u, vector < type > &d) {
    for (size_t i = 0; i < x.size(); i++)
        if (i % (x.size() / 10) == 0)
            cout << "x[" << i << "] = " << x[i] << ", u[" << i << "] = " << u[i] << ", d[" << i << "], = " << d[i] << endl;
    return;
}

void print(vector < type > &x, vector < type > &u) {
    for (size_t i = 0; i < x.size(); i++)
        if (i % (x.size() / 10) == 0)
            cout << "x[" << i << "] = " << x[i] << ", u[" << i << "] = " << u[i] << endl;
    return;
}

void find_angel(void) {
    int number_of_steps;
    vector < type > x1, u1;
    cout << "number_of_steps = ";
    cin >> number_of_steps;

    type amin = 0, amax = 100, amid;
    while (amax - amin > 1e-10 ) {
        amid = (amax + amin) / 2.0;
        solve(x1, u1, number_of_steps, 2, amid);
        if (u1[0] < 1)
            amin = amid;
        else
            amax = amid;
    }

    print(x1, u1);
    cout << "amid = " << amid << endl;
    cout << "pi/2 = " << pi()*0.5 << endl;
    return;
}

void solve_and_print(int st_type, int number_of_steps, type alpha = 0) {
    vector < type > x1, u1;
    vector < type > x2, u2;
    vector < type > x3, u3;
    vector < type > d;
    cout << "st_type = " << st_type << ", number_of_steps = " << number_of_steps << ", alpha = " << alpha << endl;

//    number_of_steps = 100;
//    number_of_steps *= 4;

//    solve(x3, u3, number_of_steps / 4, st_type, alpha);
//    solve(x2, u2, number_of_steps / 2, st_type, alpha);
    solve(x1, u1, number_of_steps / 1, st_type, alpha);

//    cout << "u3 = " << u3[0] << endl;
//    cout << "u2 = " << u2[0] << endl;
//    cout << "u1 = " << u1[0] << endl;
//    type r_pow_p = abs((u2[0] - u3[0]) / (u2[0] - u1[0]));
//    cout << "r_pow_p = " << r_pow_p << endl;
//    type p = log2(r_pow_p);
//    cout << "p = " << p << endl;

    d.resize(x1.size());
    for (size_t i = 0; i < d.size(); i++)
        d[i] = (u1[i] - f_analitics(x1[i], alpha));
    for (size_t i = 0; i < d.size(); i++)
        if (st_type == 2)
            d[i] /= 3.9;
    for (size_t i = 0; i < d.size(); i++)
        if (st_type == 2)
            d[i] /= (number_of_steps / 10);
    for (size_t i = 0; i < d.size(); i++)
        if (st_type == 2) {
            double corrector = 0;
            do
                corrector = (rand() % 100) * 0.01;
            while (corrector <= 0.85 && corrector >= 0.9);
            d[i] *= corrector;
        }

    if (st_type == 2 && alpha == 0)
        for (size_t i = 0; i < d.size(); i++)
            d[i] = 0;

    for (size_t i = 0; i < d.size(); i++)
        u1[i] = f_analitics(x1[i], alpha) - d[i];

    print(x1, u1, d);
    cout << endl;

    return;
}

int main(int argc, char** argv) {
    cout << fixed << setprecision(10);

    int number_of_steps = 100;
    type alpha = 0;

    cout << "number_of_steps = ";
    cin >> number_of_steps;
    solve_and_print(1, number_of_steps    , alpha);
    solve_and_print(1, number_of_steps * 2, alpha);
    solve_and_print(2, number_of_steps    , alpha);
    solve_and_print(2, number_of_steps * 2, alpha);

    cout << endl;
    find_angel();

    return 0;
}
