#include "stdafx.h"
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <iomanip>
#include "Tichonov.hpp"

using namespace std;

class Experiment {
private:
	double T;
	double a;
	double d;
	size_t N;

	vector < double > X;
	vector < double > Y;
	vector < double > V;

	double A;
	double B;
	double E1;
	double _E1;
	double E2;
	double _E2;
	double e1;
	double _e1;
	double e2;
	double _e2;

	Tichonov <double > Tich;

	double ABS(double x) {
		if (x < 0)
			return -x;
		return x;
	}

	double SQR(double x) {
		return x * x;
	}

	double MAX(double a, double b) {
		if (a > b)
			return a;
		return b;
	}

	double MIN(double a, double b) {
		if (a < b)
			return a;
		return b;
	}

	double pi() {
		return 3.14159265358979;
	}
	
	double rand01() {
		return 1.0*rand() / RAND_MAX;
	}

	double norm_rand() {
		return sqrt(-2 * log(rand01()))*cos(2 * pi()*rand01());
	}

	double y(double t) {
		return(exp(-SQR((t - 0.5*T) / a)));
	}
	
	double v(double t) {
		return -2*y(t)*((t - 0.5*T) / a)*(1.0 / a);
	}

	double noise() {
		return d*norm_rand();
	}

	double y_real(double t) {
		return y(t) + noise();
	}
	
	double v_real(double t) {
		return v(t);
	}

	void FillE(double &q1, double &_q1, double &q2, double &_q2, const vector < double > &Q) {
		assert(Q.size() == this->N + 1 && "Q.size() != N + 1");
		double tay = this->T / this->N;
		 q1 = ABS(Q[0] - y(this->X[0]));
		 q2 = ABS(0.5*(Q[2] - Q[0]) / tay - v(this->X[1]));
		_q1 = 0;
		_q2 = 0;
		for (size_t i = 0; i <= this->N; i++) {
			 q1 = MAX(q1, ABS(Q[i] - y(this->X[i])));
			_q1 +=        SQR(Q[i] - y(this->X[i]));
			if (i != 0 && i != this->N) {
				 q2 = MAX(q2, ABS(0.5*(Q[i + 1] - Q[i - 1]) / tay - v(this->X[i])));
				_q2 +=        SQR(0.5*(Q[i + 1] - Q[i - 1]) / tay - v(this->X[i]));
			}
		}

		 q1 /= this->A;
		_q1  = sqrt(_q1);
		_q1 /= this->A*sqrt(this->N + 1);
		 q2 /= this->B;
		_q2  = sqrt(_q2);
		_q2 /= this->B*sqrt(this->N - 1);
	}

	void Fill() {
		double tay = T / N;
		X.reserve(N + 1);
		Y.reserve(N + 1);
		V.reserve(N + 1);
		for (size_t i = 0; i <= N; i++) {
			X.push_back(tay*i);
			Y.push_back(y_real(X[i]));
			V.push_back(v_real(X[i]));
			if (i == 0) {
				A = Y[0];
				B = V[0];
			}
			A = MAX(A, y(this->X[i]));
			B = MAX(B, v(this->X[i]));
		}
	}
	
public:
	Experiment(double _T = 1.0, double _a = 1.0 / 6.0, double _d = 0.01, int _N = 1000) {
		this->T = _T;
		this->a = _a;
		this->d = _d;
		this->N = _N;
		X.clear();
		Y.clear();
		V.clear();
	}

	~Experiment() {

	}

	void Run() {
		Fill();
		FillE(this->E1, this->_E1, this->E2, this->_E2, this->Y);
		cout << "Noise = " << this->d << endl;
		cout << "E1 = " << E1 << ", _E1 = " << _E1 << ", E2 = " << E2 << ", _E2 = " << _E2 << endl;
		vector < double > Ans;
		this->Tich.Set_Data(this->N, T / N, Y);

		cout << endl << "Tichonov nesvjazki:" << endl;
		cout << "d = " << this->d << endl;
		Ans = this->Tich.Get_Data(true, this->d);
		FillE(this->e1, this->_e1, this->e2, this->_e2, Ans);
		cout << "e1 = " << e1 << ", _e1 = " << _e1 << ", e2 = " << e2 << ", _e2 = " << _e2 << endl;
		cout << "E1/e1 = " << E1 / e1 << ", _E1/_e1 = " << _E1 / _e1 << ", E2/e2 = " << E2 / e2 << ", _E2/_e2 = " << _E2 / _e2 << endl;

		cout << endl << "Tichonov kvazioptimum:" << endl;
		double aaa = 1;
		while (aaa > 0.0000000001) {
			Ans = this->Tich.Get_Data(false, aaa);
			FillE(this->e1, this->_e1, this->e2, this->_e2, Ans);
//			cout << "e1 = " << e1 << ", _e1 = " << _e1 << ", e2 = " << e2 << ", _e2 = " << _e2 << endl;
			cout << "E1/e1 = " << E1 / e1 << ", _E1/_e1 = " << _E1 / _e1 << endl << "E2/e2 = " << E2 / e2 << ", _E2/_e2 = " << _E2 / _e2 << endl;
			aaa /= 2;
			cout << endl;
		}
	}

};

int _tmain(int argc, _TCHAR* argv[]) {
	cerr << fixed << setprecision(11);
	Experiment Ex;
	Ex.Run();
	system("pause");
	return 0;
}