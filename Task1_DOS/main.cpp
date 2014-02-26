#include <dos.h>
#include <graphics.h>
#include <conio.h>
#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <string.h>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <list>
#include <assert.h>

#define all(c) c.begin(), c.end()
typedef long long lint;
typedef double ldouble;

using namespace std;

// variables and constants
ldouble lambda, w0, w, x0, v0, t0, tmax, dt, gamma, Bb, tetha, t_analytics;
ldouble x_plot, y_plot, x_zero, y_zero, x_adding, y_adding;
const ldouble pi = 3.1415926535897932384626433832795088693993;

// helpfull functions
ldouble sqr(ldouble x) {
    return x*x;
}

ldouble abs(ldouble x) {
    if (x < 0)
        return -x;
    return x;
}

ldouble max(const ldouble a, const ldouble b) {
    if (a > b)
        return a;
    return b;
}

ldouble max(const vector < ldouble > v) {
    ldouble maxx = v[0];
    for (size_t i = 0; i < v.size(); maxx = max(maxx, v[i++]));
    return maxx;
}

ldouble min(const vector < ldouble > v) {
    ldouble minn = v[0];
    for (size_t i = 0; i < v.size(); minn = min(minn, v[i++]));
    return minn;
}

vector < ldouble > set_dt_v(int n, ldouble d, ldouble s = 0) {
    vector < ldouble > res(n, s);
    for (int i = 0; i < n; res[i] += i*d, i++);
    return res;
}

//calcus functions
ldouble f(const ldouble t, const ldouble v, const ldouble x) {
    return -(2*lambda*v + sqr(lambda)*x);
}

ldouble f_analytics(const ldouble t) {
    return x0*exp(-lambda*t)*(1+lambda*t);
}

void init() {
    lambda = 1;
    gamma = 0;
    x0 = 1;
    w0 = 0;
    v0 = 0;
    dt = 0.002;
	t0 = 0;

    w = sqrt(sqr(w0) - sqr(lambda));
    tmax = 3 / lambda;
    t_analytics = tmax;
    Bb = 1.0 / sqrt(sqr(sqr(w0) - sqr(gamma)) + sqr(2*lambda*gamma));
    tetha = atan2(2*lambda*gamma, sqr(w0) - sqr(gamma));
}

void solve0(vector < ldouble > &xn, vector < ldouble > &vn) {
    int n = 0;
    xn.clear();
    vn.clear();
    xn.push_back(x0);
    vn.push_back(v0);
    ldouble t = t0;
    while (t < tmax) {
        t += dt;
        vn.push_back(vn[n] + dt * f(t, vn[n], xn[n]));
        xn.push_back(xn[n] + dt * vn[n]);
        n++;
    }
}

void solve1(vector < ldouble > &xn, vector < ldouble > &vn) {
    int n = 0;
    xn.clear();
    vn.clear();
    xn.push_back(x0);
    vn.push_back(v0);
    ldouble t = t0;
    while (t < tmax) {
        t += dt;
        vn.push_back(vn[n] + dt * f(t, vn[n], xn[n]));
        xn.push_back(xn[n] + dt * vn[n+1]);
        n++;
    }
}

void solve2(vector < ldouble > &xn, vector < ldouble > &vn) {
    int n = 0;
    xn.clear();
    vn.clear();
    xn.push_back(x0);
    vn.push_back(v0);
    ldouble xcorrector;
    ldouble vcorrector;
    ldouble t = t0;
    while (t < tmax) {
        t += dt;
        vcorrector = vn[n] + dt*f(t - dt, vn[n], xn[n]);
        xcorrector = xn[n] + dt*vn[n];
        vn.push_back(vn[n] + dt * (f(t - dt, vn[n], xn[n]) + f(t, vcorrector, xcorrector)) / 2.0);
        xn.push_back(xn[n] + dt * (vn[n] + vcorrector) / 2.0);
        n++;
    }
}

void solve4(vector < ldouble > &xn, vector < ldouble > &vn) {
    int n = 0;
    ldouble k1, k2, k3, k4;
    xn.clear();
    vn.clear();
    xn.push_back(x0);
    vn.push_back(v0);
    ldouble t = t0;
    while (t < tmax) {
        t += dt;
        k1 = 0;
        k2 = 0;
        k3 = 0;
        k4 = 0;
        xn.push_back(xn[n-1] + 1/6.0*(k1 + 2.0*k2 + 2.0*k3 + k4));
        n++;
    }
}

vector < ldouble > delta(const vector < ldouble > a, const vector < ldouble > b) {
    vector < ldouble > res(a.size());
    for (size_t i = 0; i < a.size(); res[i] = a[i] - b[i], i++);
    return res;
}

vector < ldouble > delta(const vector < ldouble > a) {
    vector < ldouble > res(a.size());
    for (size_t i = 0; i < a.size(); res[i] = a[i] - f_analytics(t0+i*dt), i++);
    return res;
}

// graph functions
ldouble get_axis_range(const vector < ldouble > v) {
    return (max(v) - min(v));
}

//*
void clear_graph(void) {
    cleardevice();
}

void init_graph(void) {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    clear_graph();
}

void close_graph(void) {
    closegraph();
}

void draw(const vector < ldouble > x, const vector < ldouble > y, bool analytics = false, bool using_plot = false, int get_color_mode = 0) {
    int max_x_graph = getmaxx();
    int max_y_graph = getmaxy();
    ldouble max_x_real = get_axis_range(x);
    ldouble max_y_real = get_axis_range(y);
    ldouble A = max_x_graph / max_x_real;
    ldouble B = max_y_graph / max_y_real;
    ldouble get_x_zero;
    ldouble get_y_zero;
    ldouble addingx;
    ldouble addingy;

    setcolor(WHITE);
    if (min(y) * max(y) < 0) {
        get_x_zero = -B*min(y);
        addingy = get_x_zero;
    } else {
        get_x_zero = -1;
        addingy = -B*abs(min(y));
    }
    if (get_x_zero > 0 && !using_plot) {
        moveto(0, max_y_graph - get_x_zero);
        lineto(max_x_graph, max_y_graph - get_x_zero);
    }
    if (min(x) * max(x) < 0) {
        get_y_zero = -A*min(x);
        addingx = get_y_zero;
    } else {
        get_y_zero = -1;
        addingx = -A*abs(min(x));
    }
    if (get_y_zero > 0 && !using_plot) {
        moveto(get_y_zero, 0);
        lineto(get_y_zero, max_y_graph);
    }

    if (using_plot) {
        A = x_plot;
        B = y_plot;
        get_x_zero = x_zero;
        get_y_zero = y_zero;
        addingx = x_adding;
        addingy = y_adding;
    } else {
        x_plot = A;
        y_plot = B;
        x_zero = get_x_zero;
        y_zero = get_y_zero;
        x_adding = addingx;
        y_adding = addingy;

        setcolor(WHITE);
        char s[500];
        sprintf(s, "Minx = %.10lf, Maxx = %.10lf", (double) min(x), (double) max(x));
        outtextxy(0, 0, s);
        sprintf(s, "Miny = %.10lf, Maxy = %.10lf", (double) min(y), (double) max(y));
        outtextxy(0, 20, s);
    }

    if (get_color_mode == 0)
        setcolor(YELLOW);
    if (get_color_mode == 1)
        setcolor(GREEN);
    if (get_color_mode == 2)
        setcolor(BLUE);
    moveto(A*x[0] + addingx, max_y_graph - (B*y[0] + addingy));
    for (size_t i = 0; i < x.size(); lineto(A*x[i] + addingx, max_y_graph - (B*y[i] + addingy)), i++);

    if (analytics) {
        getch();
        setcolor(GREEN);
        moveto(A*x[0] + addingx, max_y_graph - (B*f_analytics(t0) + addingy));
        for (size_t i = 0; i < x.size(); lineto(A*x[i] + addingx, max_y_graph - (B*f_analytics(t0 + i*dt) + addingy)), i++);
    }

    getch();
}
//*/

// main
int main(int argc, char** argv) {
    cerr << "Started" << endl;
    bool analytics = true;
    bool using_plot = true;
    init();
    ldouble d0, d0_analytics, d1, d1_analytics, d2, d2_analytics;
    int t_n = floor(t_analytics / dt + 0.5);
    cerr << "Inited" << endl;

    vector < ldouble > xn;
    vector < ldouble > _xn;
    vector < ldouble > vn;
    vector < ldouble > _vn;
    vector < ldouble > dn0;
    vector < ldouble > dn1;
    vector < ldouble > dn2;
    vector < ldouble > tn;

    init_graph();
    cerr << "Inited graph" << endl;

    // 0 - level
    solve0(xn, vn);
    dt *= 2.0;
    solve0(_xn, _vn);
    dt /= 2.0;
    d0 = abs(xn[t_n] - _xn[t_n / 2]);
    tn = set_dt_v((int) xn.size(), dt, t0);
    if (analytics) {
        dn0 = delta(xn);
        d0_analytics = dn0[t_n];
    }

    cerr << "Solved 0" << endl;
    draw(tn, xn, analytics);
    clear_graph();

    // 1 - level
    solve1(xn, vn);
    dt *= 2.0;
    solve1(_xn, _vn);
    dt /= 2.0;
    d1 = abs(xn[t_n] - _xn[t_n / 2]);
    if (analytics) {
        dn1 = delta(xn);
        d1_analytics = dn1[t_n];
    }

    cerr << "Solved 1" << endl;
    draw(tn, xn, analytics);
    clear_graph();

    // 2 - level
    solve2(xn, vn);
    dt *= 2.0;
    solve2(_xn, _vn);
    dt /= 2.0;
    d2 = abs(xn[t_n] - _xn[t_n / 2]) / 3.0;
    if (analytics) {
        dn2 = delta(xn);
        d2_analytics = dn2[t_n];
    }

    cerr << "Solved 2" << endl;
    draw(tn, xn, analytics);
    clear_graph();

    // delta
    if (analytics) {
        cout << fixed << setprecision(10);
        cout << "d0 = " << d0 << ", d0_analytics = " << abs(d0_analytics) << endl;
        cout << "d1 = " << d1 << ", d1_analytics = " << abs(d1_analytics) << endl;
        cout << "d2 = " << d2 << ", d2_analytics = " << abs(d2_analytics) << endl;
        draw(tn, dn0, false);
        draw(tn, dn1, false, using_plot, 1);
        draw(tn, dn2, false, using_plot, 2);
        clear_graph();
        draw(tn, dn2, false);
        clear_graph();
    }

    draw(xn, vn);
    close_graph();

    return 0;
}
