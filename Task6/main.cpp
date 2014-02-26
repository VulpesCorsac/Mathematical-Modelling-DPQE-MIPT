#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "Geometry3D.hpp"

long long unknown1 = 0;
long long unknown2 = 0;
long long normal1 = 0;
long long normal2 = 0;

using namespace std;

double pi() {
    return 3.14159265358979;
}

double rand1() {
    return 1.0*rand() / RAND_MAX;
}

double random_lambda(const double &lambda0) {
    return -lambda0*log(1-rand1());
}

double sqr(const double &x) {
    return x * x;
}

double abs(const double &x) {
    if (x < 0)
        return -x;
    return x;
}

Point3D < double > random_point_on_sphere(double R = 1) {
    double fi = 2*pi()*rand1();
    double cos_tetha = 2*rand1() - 1;
    double sin_tetha = sqrt(1 - sqr(cos_tetha));
    double x = R*sin_tetha*cos(fi);
    double y = R*sin_tetha*sin(fi);
    double z = R*cos_tetha;
    Point3D < double > temp(x, y, z);
    return temp;
}

class Model {
private:
    double average_lambda;
    double l1;
    double l2;
    double r1;
    double r2;
    double p;

    bool shoot() {
        Point3D < double > P_old(0, 0, 0), dP, P_new, Cross;
        Plane3D < double >   Safe(Point3D < double > (l1, 0, 0), Point3D < double > (l1, 1, 0), Point3D < double > (l1, 0, 1));
        Sphere  < double > Target(Point3D < double > (l2, 0, 0), r2);

        while (true) {
            dP = random_lambda(average_lambda)*random_point_on_sphere();
            P_new = P_old + dP;
            Line3D < double > L(P_old, P_new);

            Cross = Point_in_line_by_X(L, l1);
            if (sqr(Cross.y) + sqr(Cross.z) <= sqr(r1) && Point_in_box(P_old, P_new, Cross))
                return false;

            Segment3D < double > Seg(P_old, P_new);
            if (Segment_cross_sphere(Seg, Target))
                return true;

            if (rand1() < p)
                return false;
            P_old = P_new;
        }
        return true;
    }

public:
    long long N;
    long long n;

    Model(double _average_lambda = 1.0, double _l1 = 1.0, double _l2 = 2.0, double _r1 = 0.2, double _r2 = 0.2, double _p = 0.2) {
        average_lambda = _average_lambda;
        l1 = _l1;
        l2 = _l2;
        r1 = _r1;
        r2 = _r2;
        p  = _p;
        N = 0;
        n = 0;
    }

    ~Model() {

    }

    void Run() {
        N++;
        if (shoot())
            n++;
        return;
    }

};

void Run(int rounds = 100*1000*1000) {
    freopen("output.txt", "a+", stdout);

    Model Unsafe(1.0, 1.0, 2.0, 0.0, 0.2, 0.2);
    Model   Safe(1.0, 1.0, 2.0, 0.2, 0.2, 0.2);

    srand(time(NULL));

    cout << fixed << setprecision(5);
    cerr << fixed << setprecision(5);
    for (int i = 0; i <= rounds; i++) {
        Unsafe.Run();
        Safe.Run();

        if (i % (100*1000) == 0 && i > 0) {
            cout << "I = " << i << ", ";
            cout << "Safe = " << 1.0 * Safe.n / Safe.N << ", " << "UnSafe = " << 1.0 * Unsafe.n / Unsafe.N << ", ";
            cout << "Safe / Unsafe = " << 1.0 * Safe.n * Unsafe.N / Safe.N / Unsafe.n << endl;

            cerr << "I = " << i << ", ";
            cerr << "Safe = " << 1.0 * Safe.n / Safe.N << ", " << "UnSafe = " << 1.0 * Unsafe.n / Unsafe.N << ", ";
            cerr << "Safe / Unsafe = " << 1.0 * Safe.n * Unsafe.N / Safe.N / Unsafe.n << endl;
        }
    }

    cout << "Result: ";
    cout << "Safe = " << 1.0 * Safe.n / Safe.N << ", " << "UnSafe = " << 1.0 * Unsafe.n / Unsafe.N << ", ";
    cout << "Safe / Unsafe = " << 1.0 * Safe.n * Unsafe.N / Safe.N / Unsafe.n << endl;

    cerr << "Result: ";
    cerr << "Safe = " << 1.0 * Safe.n / Safe.N << ", " << "UnSafe = " << 1.0 * Unsafe.n / Unsafe.N << ", ";
    cerr << "Safe / Unsafe = " << 1.0 * Safe.n * Unsafe.N / Safe.N / Unsafe.n << endl;

    fclose(stdout);
}

int main() {
    Run(10*1000*1000);

    return 0;
}
