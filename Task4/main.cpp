#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>

#define PI 3.1415926535

using namespace std;

double sqr(double x) {
    return x*x;
}

double Rc = 6700*1000;
double Rz = 6371*1000;
double G = 6.67*1e-11;
double Mz = 5.99*1e24;
double Vc = sqrt(G*Mz/Rc);
double Wc = sqrt(G*Mz/(Rc*Rc*Rc));
double U = 6;
double S = 5000;
double f0 = S/Rc;
double dt = 0.1;
double tmax = 3000;

double func(double coord, double r) {
    return -G*Mz*coord/(r*r*r);
}

double f_station(double t) {
    return Wc*t + f0;
}

double x_station(double t) {
//    return Rc*cos(f_station(t));
    return Rc*(cos(S/Rc) + cos(Vc*t/Rc));
}

double y_station(double t) {
//    return Rc*cos(f_station(t));
    return Rc*(sin(S/Rc) + sin(Vc*t/Rc));
}

double solve(vector < double > &x, vector < double > &y, double beta, double &tx, double &ty) {
    vector < double > vx;
    vector < double > vy;
    x.clear(); y.clear();
    double t = 0;
    tx = ty = -1;
    bool x_found = false;
    bool y_found = false;

    x.push_back(Rc);
    y.push_back(0);
    vx.push_back(-U*sin(beta));
    vy.push_back(Vc+U*cos(beta));
    int i = 0;
    double Rr = sqrt(sqr(x[0]) + sqr(y[0]));
    double fr = atan2(y[0], x[0]);
    double fc = atan2(y_station(0), x_station(0));
    while (t <= tmax) {
        if (i % 1000 == 0) {
            cerr << " x[" << i << "] = " << x[i] << endl;
            cerr << " y[" << i << "] = " << y[i] << endl;
            cerr << "xc[" << i << "] = " << x_station(t) << endl;
            cerr << "yc[" << i << "] = " << y_station(t) << endl;
            cerr << "vx[" << i << "] = " << vx[i] << endl;
            cerr << "vy[" << i << "] = " << vy[i] << endl;
            cerr << "fr = " << fr << endl;
            cerr << "fc = " << fc << endl;
        }
        t += dt;
        x.push_back(x[i] + dt*vx[i] + 0.5*sqr(dt)*func(x[i], Rr));
        y.push_back(y[i] + dt*vy[i] + 0.5*sqr(dt)*func(y[i], Rr));
        vx.push_back(vx[i] + 0.5*dt*(func(x[i], Rr) + func(x[i] + dt*vx[i], Rr)));
        vy.push_back(vy[i] + 0.5*dt*(func(y[i], Rr) + func(y[i] + dt*vy[i], Rr)));
        i++;

        Rr = sqrt(sqr(x[i]) + sqr(y[i]));
        fr = atan2(y[i], x[i]);
        fc = atan2(y_station(i), x_station(i));

        if (Rr <= Rz) {
            cerr << "Crashed into the Earth! Booooooom!" << endl;
            // х сравнялся раньше
            return -1;
        }

        if (!x_found && x[i] < x_station(t) && x[i-1] > x_station(t-dt)) {
            x_found = true;
            tx = t;
        }
        if (!y_found && y[i] > y_station(t) && y[i-1] < y_station(t-dt)) {
            y_found = true;
            ty = t;
        }
        if (y_found && x_found)
            return tx - ty;
    }

    cerr << "Timeout!" << endl;
    if (!x_found)
        tx = tmax;
    if (!y_found)
        ty = tmax;
    return tx - ty;
}

int main() {
    cout << fixed << setprecision(9);
    vector < double > x, y;
    double bmin = 0;
    double bmax = 0.5*PI;
    double tx, ty;

    int q = 0;
    while (bmax - bmin > 1e-3) {
        double bmid = 0.3*(bmax+bmin);
        cout << "bmid = " << bmid*180/PI << endl;
        cout << "bmax = " << bmax*180/PI << endl;
        cout << "bmin = " << bmin*180/PI << endl;
        double res = solve(x, y, bmid, tx, ty);
        cout << "res = " << res << endl;
        if (tx > 0 && ty > 0) {
            if (res < 0)
                bmax = bmid;
            if (res > 0)
                bmin = bmid;
            if (res == 0)
                return -1;
        } else {
            cout << "Oh, man...." << endl;
        }
        q++;
        if (q > 0)
            return -2;
    }

}
