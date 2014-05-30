#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "FastDiscreteFourierTransform.hpp"
#include "Vector_complex_VS_real.hpp"

#define PI 3.14159265358979
#define sqr(x) ((x)*(x))

using namespace std;

class Experiment {
private:
    double sigma;
    double T;
    double delta;
    int N;
    vector < double > grating;
    vector < double > results;

    double y(const double &t) {
        return exp(-sqr((t - 0.5*this->T)/this->sigma ));
    }

    double v(const double &t) {
        return y(t)*(2*(t - 0.5*this->T) / this->sigma)*(1.0/this->sigma);
    }

    double rand01() {
        return 1.0*rand() / RAND_MAX;
    }

    double norm_rand() {
        return sqrt(-2*log(rand01()))*cos(2*PI*rand01());
    }

    double noise() {
        return this->delta*norm_rand();
    }

    double y_real(const double &t) {
        return y(t) + noise();
    }

public:
    FDFT < double > F;

    void Set_variables(const double &_sigma = 0.5/PI, const int &_N = 512, const double &_T = 1, const double &_delta = 0.005) {
        this->T = _T;
        this->sigma = _sigma;
        this->delta = _delta;
        this->N = _N;
    }

    void Set_results() {
        this->grating.resize(N);
        this->results.resize(N);
        for (int i = 0; i < this->N; i++) {
            this->grating[i] = 1.0*i*this->T/(this->N-1);
            this->results[i] = y_real(this->grating[i]);
            if (i % 2)
                results[i] *= -1;
//            cout << "x[" << i << "] = " << grating[i] << ", y[" << i << "] = " << results[i] << endl;
//            this->results[i] = sin(this->grating[i]);
        }
        return;
    }

    void Fill_F_signal() {
        assert(grating.size() > 0);
        assert(grating.size() == results.size());
        this->F.Set_Signal(Vector_real_to_complex(this->results));
        return;
    }

    vector < double > Get_results() {
        return vector < double > (this->results);
    }

    void trunc(int M) {
        vector < complex < double > > FV = F.Get_Fourier();
        for (int m = -this->N/2, i = 0; m < this->N/2; m++, i++) {
            if (m < -M)
                FV[i] = complex < double > (0, 0);
            if (m > M)
                FV[i] = complex < double > (0, 0);
        }
        F.Set_Fourier(FV);
        return;
    }

    Experiment() {
        Set_variables();
    }

    ~Experiment() {

    }

    void Run(int M) {
        Set_results();
        Fill_F_signal();
        F.Run_FDFT();
        trunc(M);

        double e1 = 0, _e1 = 0, e2 = 0, _e2 = 0;

        // Ф-ия
        F.Run_IFDFT();
        vector < complex < double > > Calculated_Y = F.Get_Signal();
        for (int i = 0; i < this->N - 1; i++)
            if (i % 2)
                Calculated_Y[i] *= -1;
        for (int i = 0; i < this->N - 1; i++) {
             e1  = max(e1, abs(y(grating[i]) - Calculated_Y[i]));
            _e1 +=     sqr(abs(y(grating[i]) - Calculated_Y[i])) / this->N;
        }
        _e1 = sqrt(_e1);
        cout << "E1 = " << e1 << ", _E1 = " << _e1 << endl;

        // Скорость
        vector < complex < double > > Calculated_V = F.Get_Fourier();
        for (int i = 0, m = -this->N/2; i < (int) Calculated_V.size(); i++, m++)
            Calculated_V[i] *= complex < double > (0, 2.0*PI*m/this->T);
        F.Set_Fourier(Calculated_V);
        F.Run_IFDFT();
        Calculated_V = F.Get_Signal();
        for (int i = 0; i < this->N - 1; i++)
            if (i % 2)
                Calculated_V[i] *= complex < double > (-1, 0);
        for (int i = 0; i < this->N - 1; i++) {
             e2  = max(e2, abs(v(grating[i]) - Calculated_V[i]));
            _e2 +=     sqr(abs(v(grating[i]) - Calculated_V[i])) / this->N;
//            if (i % 5 == 0)
//                cout << v(grating[i]) << " VS " << Calculated_V[i] << ", d = " << abs(-v(grating[i]) - Calculated_V[i]) << endl;
        }
        _e2 = sqrt(_e2);
        cout << "E2 = " << e2 << ", _E2 = " << _e2 << endl;
    }

    int Mu() {
        Set_results();
        Fill_F_signal();
        F.Run_FDFT();
        vector < complex < double > > FV = F.Get_Fourier();
        int q = -1;
        for (int m = -this->N/2, i = 0; m < this->N/2; m++, i++) {
            if (m == 0)
                q = i;
            if (q > 0)
                if (abs(FV[i]/FV[q]) < 0.36787944117) {
                    return m;
                }
        }

    }

    void Solve(double Q) {
        Set_variables(Q, 512, 1, 0);
        cout << "Spectre width: " << Mu() << endl;
        Set_variables(Q);
        cout << "Filtre:" << endl;
        int m = 1;
        while (m != 0) {
            cin >> m;
            if (m == 0)
                return;
            Run(m);
        }
    }

};

int main() {
    srand(time(NULL));
    Experiment Ex;
    Ex.Solve(0.5/PI);
    Ex.Solve(0.25/PI);
//    Ex.F.Fourier_test();
//    vector < double > x, y;

    return 0;
}
