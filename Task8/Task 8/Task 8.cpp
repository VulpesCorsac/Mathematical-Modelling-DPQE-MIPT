#include "stdafx.h"
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <algorithm>
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
#include <complex>
#include "FastDiscreteFourierTransform.hpp"
#include "Vector_complex_VS_real.hpp"
#include "Tichonov.hpp"

#define PI 3.14159265358979
#define sqr(x) ((x)*(x))

using namespace std;

HINSTANCE hInst;
HWND hWnd;
HDC hdc;
HBRUSH brush;
HPEN hPen;
WNDCLASSEX wcex;
MSG msg;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//  ласс отрисовки
class TDraw {
public:
	typedef double Type; // Aka template  

private:
	long double CalcusEps; // Comparison
	int GraphEps; // Ѕоковые пол€
	int Max_x_plot, Max_y_plot; // Max graph ranges
	int Max_point_number; // ћаксимальное количчество точек

	// Color structure
public:
	struct TColour {
		int r;
		int g;
		int b;

		TColour(int _r = 0, int _g = 0, int _b = 0) {
			r = _r;
			g = _g;
			b = _b;
		}
	};

	// Variables
private:
	vector < TColour > Colours; // Vector of colours
	Type Max_x_real, Min_x_real, Max_y_real, Min_y_real; // Real graph ranges

	// Abs
private:
	Type _abs(Type &x) {
		if (x < CalcusEps)
			return -x;
		return x;
	}

	// Round
private:
	int _round(Type x) {
		return (int)floor(x + 0.5);
	}

	// X graph range
private:
	int getmaxx(void) {
		return Max_x_plot - 2 * GraphEps;
	}

	// Y graph range
private:
	int getmaxy(void) {
		return Max_y_plot - 2 * GraphEps;
	}

	// Initing colours
public:
	void InitColors(const vector < TColour > _Colours) {
		Colours.clear();
		Colours.resize(_Colours.size());
		assert(_Colours.size());
		for (size_t Colour_Number = 0; Colour_Number < _Colours.size(); Colour_Number++) {
			Colours[Colour_Number] = _Colours[Colour_Number];
		}
		return;
	}

	// Initing default colors
private:
	void InitDefaultColors(void) {
		Colours.resize(3);
		Colours[0].r = 255 - 242;
		Colours[0].g = 255 - 243;
		Colours[0].b = 255 - 244;
		Colours[1].r = 141;
		Colours[1].g = 182;
		Colours[1].b = 0;
		Colours[2].r = 255 - 141;
		Colours[2].g = 255 - 182;
		Colours[2].b = 255 - 0;
		return;
	}

	// Setting colous
private:
	void SetColor(size_t number) {
		assert(number < Colours.size());
		hPen = CreatePen(PS_SOLID, 1, RGB(Colours[number].r, Colours[number].g, Colours[number].b));
		SelectObject(hdc, hPen);
		return;
	}

	// Initing all graph
private:
	int Init_Graph(HINSTANCE hInstance) {
		// создаем класс и задаем ему параметры
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = _T("Geo");
		wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

		//регистрируем класс
		if (!RegisterClassEx(&wcex)) {
			MessageBox(NULL, _T("WTF?"), _T("WTF!"), NULL);
			return -1;
		}

		return 0;
	}

	// Smth must be done before redrawing
private:
	int ReInit_Graph(HINSTANCE hInstance) {
		//создаем окно данного класса
		hInst = hInstance;
		hWnd = CreateWindow(_T("Geo"), _T("Matmod"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, Max_x_plot, Max_y_plot, NULL, NULL, hInstance, NULL);
		hdc = GetWindowDC(hWnd);

		//проверка того, создалось ли окно.
		if (!hWnd) {
			MessageBox(NULL, _T("Call to CreateWindow failed!"), _T("Folak"), NULL);
			return -1;
		}

		//показываем окно, начинаем получать сообщени€
		ShowWindow(hWnd, 1);
		UpdateWindow(hWnd);
		return 0;
	}

	// Smth must be done before closing
private:
	void Close_Graph(HINSTANCE hInstance) {
		return;
	}

	// Min of two
private:
	Type _Min(Type a, Type b) {
		if (a < b)
			return a;
		return b;
	}

	// Max of two
private:
	Type _Max(Type a, Type b) {
		if (a > b)
			return a;
		return b;
	}

	// Min of vector
private:
	Type _Min(const vector < Type > a) {
		assert(a.size());
		Type minn = a[0];
		for (size_t number = 1; number < a.size(); number++)
			minn = _Min(minn, a[number]);
		return minn;
	}

	// Max of vector
private:
	Type _Max(const vector < Type > a) {
		assert(a.size());
		Type maxx = a[0];
		for (size_t number = 1; number < a.size(); number++)
			maxx = _Max(maxx, a[number]);
		return maxx;
	}

	// Min of vector < vector >
private:
	Type _Min(const vector < vector < Type > > a) {
		assert(a.size());
		Type minn = _Min(a[0]);
		for (size_t number = 1; number < a.size(); number++)
			minn = _Min(minn, _Min(a[number]));
		return minn;
	}

	// Max of vector < vector >
private:
	Type _Max(const vector < vector < Type > > a) {
		assert(a.size());
		Type maxx = _Max(a[0]);
		for (size_t number = 1; number < a.size(); number++)
			maxx = _Max(maxx, _Max(a[number]));
		return maxx;
	}

	// Setting ranges
public:
	void SetRanges(const Type _Max_x_real, const Type _Min_x_real,
		const Type _Max_y_real, const Type _Min_y_real) {
		assert(_Max_x_real - _Min_x_real > CalcusEps);
		assert(_Max_y_real - _Min_y_real > CalcusEps);
		Max_x_real = _Max_x_real;
		Min_x_real = _Min_x_real;
		Max_y_real = _Max_y_real;
		Min_y_real = _Min_y_real;
		return;
	}

	// Modifying x
private:
	Type ModifyX(Type x) {
		return x;
	}

	// Modifying y
private:
	Type ModifyY(Type y) {
		return y;
	}

	// MoveTo
private:
	void MoveTo(int x, int y) {
		MoveToEx(hdc, x, y, NULL);
		return;
	}

	// LineTo
private:
	void Line(int x, int y) {
		LineTo(hdc, x, y);
		return;
	}

	// Text printing
private:
	void Texting(const Type _Max_x_real, const Type _Min_x_real,
		const Type _Max_y_real, const Type _Min_y_real) {
		TCHAR s[500];
		int len = swprintf(s, 100, L"Minx = %lf, Maxx = %lf", (double)ModifyX(_Min_x_real), (double)ModifyX(_Max_x_real));
		TextOut(hdc, GraphEps + 2, GraphEps + 20, s, len);
		len = swprintf(s, 100, L"Miny = %lf, Maxy = %lf", (double)ModifyY(_Min_y_real), (double)ModifyY(_Max_y_real));
		TextOut(hdc, GraphEps + 2, GraphEps + 50, s, len);
	}

	// Drawing
public:
	void DDraw(const vector < vector < Type > > x,
		const vector < vector < Type > > y, bool using_ranges = false) {
		//		ReInit_Graph(hInst);
		assert(x.size() == y.size());
		assert(Colours.size() - 1 >= x.size());
		for (size_t number = 0; number < x.size(); number++) {
			assert(x[number].size() == y[number].size());
		}
		int Max_x_graph = getmaxx();
		int Max_y_graph = getmaxy();
		if (!using_ranges) {
			Max_x_real = _Max(x);
			Min_x_real = _Min(x);
			Max_y_real = _Max(y);
			Min_y_real = _Min(y);
		}
		Type A = Max_x_graph / (Max_x_real - Min_x_real);
		Type B = Max_y_graph / (Max_y_real - Min_y_real);
		Type X_zero = 0;
		Type Y_zero = 0;
		Type Adding_x = 0;
		Type Adding_y = 0;

		SetColor(0);
		if (Max_y_real * Min_y_real <= 0) {
			X_zero = -B*Min_y_real;
			Adding_y = X_zero;
		}
		else {
			X_zero = -1;
			Adding_y = -B*_abs(Min_y_real);
		}
		if (X_zero >= 0) {
			MoveTo(_round(GraphEps + 0), _round(GraphEps + Max_y_graph - X_zero));
			Line(_round(GraphEps + Max_x_graph), _round(GraphEps + Max_y_graph - X_zero));
		}
		if (Max_x_real * Min_x_real <= 0) {
			Y_zero = -A*Min_x_real;
			Adding_x = Y_zero;
		}
		else {
			Y_zero = -1;
			Adding_x = -A*_abs(Min_x_real);
		}
		if (Y_zero >= 0)  {
			MoveTo(_round(GraphEps + Y_zero), _round(GraphEps + 0));
			Line(_round(GraphEps + Y_zero), _round(GraphEps + Max_y_graph));
		}

		Texting(Max_x_real, Min_x_real, Max_y_real, Min_y_real);

		int di = 0;
		for (size_t number = 0; number < x.size(); number++) {
			di = x[number].size() / Max_point_number;
			if (di < 1)
				di = 1;
			SetColor(number + 1);
			MoveTo(_round(GraphEps + A*x[number][0] + Adding_x), _round(GraphEps + Max_y_graph - (B*y[number][0] + Adding_y)));
			for (size_t i = 0; i < x[number].size(); i += di)
				Line(_round(GraphEps + A*x[number][i] + Adding_x), _round(GraphEps + Max_y_graph - (B*y[number][i] + Adding_y)));
		}
		return;
	}

public:
	void Draw(void) {
		while (GetMessage(&msg, NULL, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return;
	}

	// Initing all conatants
	void Init(void) {
		CalcusEps = 1e-7;
		GraphEps = 50;
		Max_x_plot = 1500;
		Max_y_plot = 1500;
		Max_point_number = 800;
		return;
	}

	// Setting max_point_number
public:
	void SetMaxPointNumber(int _Max_point_number) {
		Max_point_number = _Max_point_number;
		return;
	}

	// Getting max_point_number
public:
	int GetMaxPointNumber(void) {
		return Max_point_number;
	}

	// Setting Max Plots
public:
	void SettingMaxPlot(int _Max_x_plot, int _Max_y_plot) {
		Max_x_plot = _Max_x_plot;
		Max_y_plot = _Max_y_plot;
		return;
	}

	// Getting Max Plots
public:
	void GettingMaxPlot(int &_Max_x_plot, int &_Max_y_plot) {
		_Max_x_plot = Max_x_plot;
		_Max_y_plot = Max_y_plot;
		return;
	}

	// Constructor
public:
	TDraw() {
		Init();
		Init_Graph(hInst);
		ReInit_Graph(hInst);
		InitDefaultColors();
	}

	// Destructor
public:
	~TDraw() {
		Close_Graph(hInst);
	}
};

TDraw Draw;
vector < vector < TDraw::Type > > _x, _y;

// ќбработка сообщений, поступающих от GetMessage
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT pp;
	switch (message) {
	case WM_MOVE:
		SelectObject(hdc, hPen);
		BeginPaint(hWnd, &pp);
		if (_x.size() > 0)
			Draw.DDraw(_x, _y);
		EndPaint(hWnd, &pp);
		break;
	case WM_PAINT:
		SelectObject(hdc, hPen);
		BeginPaint(hWnd, &pp);
		if (_x.size() > 0)
			Draw.DDraw(_x, _y);
		EndPaint(hWnd, &pp);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}

class Experiment {
private:
	double sigma;
	double T;
	double delta;
	int N;
	vector < double > grating;
	vector < double > results;

	double y(const double &t) {
		return exp(-sqr((t - 0.5*this->T) / this->sigma));
	}

	double v(const double &t) {
		return y(t)*(2 * (t - 0.5*this->T) / this->sigma)*(1.0 / this->sigma);
	}

	double rand01() {
		return 1.0*rand() / RAND_MAX;
	}

	double norm_rand() {
		return sqrt(-2 * log(rand01()))*cos(2 * PI*rand01());
	}

	double noise() {
		return this->delta*norm_rand();
	}

	double y_real(const double &t) {
		return y(t) + noise();
	}

public:
	FDFT < double > F;
	Tichonov < double > Tich;

	void Set_variables(const double &_sigma = 0.5 / PI, const int &_N = 512, const double &_T = 1, const double &_delta = 0.05) {
		this->T = _T;
		this->sigma = _sigma;
		this->delta = _delta;
		this->N = _N;
	}

	void Set_results() {
		this->grating.resize(N);
		this->results.resize(N);
		for (int i = 0; i < this->N; i++) {
			this->grating[i] = 1.0*i*this->T / (this->N - 1);
			this->results[i] = y_real(this->grating[i]);
			if (i % 2)
				results[i] *= -1;
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
		return vector < double >(this->results);
	}

	void trunc(int M) {
		vector < complex < double > > FV = F.Get_Fourier();
		for (int m = -this->N / 2, i = 0; m < this->N / 2; m++, i++) {
			if (m < -M)
				FV[i] = complex < double >(0, 0);
			if (m > M)
				FV[i] = complex < double >(0, 0);
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
		_x.resize(2);
		_y.resize(2);

		cout << "Fourier" << endl;

		Set_results();
		Fill_F_signal();
		F.Run_FDFT();
		trunc(M);

		double e1 = 0, _e1 = 0, e2 = 0, _e2 = 0;

		// ‘-и€
		F.Run_IFDFT();
		vector < complex < double > > Calculated_Y = F.Get_Signal();
		for (int i = 0; i < this->N - 1; i++)
		if (i % 2)
			Calculated_Y[i] *= -1;
		for (int i = 0; i < this->N - 1; i++) {
			e1 = max(e1, abs(y(grating[i]) - Calculated_Y[i]));
			_e1 += sqr(abs(y(grating[i]) - Calculated_Y[i])) / this->N;
			if (i > -1 && i < this->N*2) {
				_x[0].push_back(grating[i]);
				_x[1].push_back(grating[i]);
				_y[0].push_back(y(grating[i]));
				_y[1].push_back(abs(Calculated_Y[i]));
			}
		}
		_e1 = sqrt(_e1);
		cout << "E1 = " << e1 << ", _E1 = " << _e1 << endl;

		// —корость
		vector < complex < double > > Calculated_V = F.Get_Fourier();
		for (int i = 0, m = -this->N / 2; i < (int)Calculated_V.size(); i++, m++)
			Calculated_V[i] *= complex < double >(0, 2.0*PI*m / this->T);
		F.Set_Fourier(Calculated_V);
		F.Run_IFDFT();
		Calculated_V = F.Get_Signal();
		for (int i = 0; i < this->N - 1; i++)
		if (i % 2)
			Calculated_V[i] *= complex < double >(-1, 0);
		for (int i = 0; i < this->N - 1; i++) {
			e2 = max(e2, abs(v(grating[i]) - Calculated_V[i]));
			_e2 += sqr(abs(v(grating[i]) - Calculated_V[i])) / this->N;
//			if (i > -1 && i < this->N * 2) {
//				_x[2].push_back(grating[i]);
//				_x[3].push_back(grating[i]);
//				_y[2].push_back(v(grating[i]));
//				_y[3].push_back(Calculated_V[i].real());
//			}
		}
		_e2 = sqrt(_e2);
		cout << "E2 = " << e2 << ", _E2 = " << _e2 << endl;

		Draw.Draw();
	}

	int Mu() {
		Set_results();
		Fill_F_signal();
		F.Run_FDFT();
		vector < complex < double > > FV = F.Get_Fourier();
		int q = -1;
		for (int m = -this->N / 2, i = 0; m < this->N / 2; m++, i++) {
			if (m == 0)
				q = i;
			if (q > 0)
			if (abs(FV[i] / FV[q]) < 0.36787944117) {
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

	void Work(int T) {
		if (T == 1) 
			Solve(0.5 / PI);
	}

};

class ExperimentT{
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
		return -2 * y(t)*((t - 0.5*T) / a)*(1.0 / a);
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
			_q1 += SQR(Q[i] - y(this->X[i]));
			if (i != 0 && i != this->N) {
				q2 = MAX(q2, ABS(0.5*(Q[i + 1] - Q[i - 1]) / tay - v(this->X[i])));
				_q2 += SQR(0.5*(Q[i + 1] - Q[i - 1]) / tay - v(this->X[i]));
			}
		}

		q1 /= this->A;
		_q1 = sqrt(_q1);
		_q1 /= this->A*sqrt(this->N + 1);
		q2 /= this->B;
		_q2 = sqrt(_q2);
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
	ExperimentT(double _T = 1.0, double _a = 1.0 / 6.0, double _d = 0.01, int _N = 1000) {
		this->T = _T;
		this->a = _a;
		this->d = _d;
		this->N = _N;
		X.clear();
		Y.clear();
		V.clear();
	}

	~ExperimentT() {

	}

	void Run() {
		Fill();
		FillE(this->E1, this->_E1, this->E2, this->_E2, this->Y);
		cout << "Noise = " << this->d << endl;
		cout << "E1 = " << E1 << ", _E1 = " << _E1 << ", E2 = " << E2 << ", _E2 = " << _E2 << endl;
		vector < double > Ans;
		this->Tich.Set_Data(this->N, T / N, Y);

		double tay = 1.0*this->T / this->N;
		_x.resize(3);
		_y.resize(3);
		for (size_t i = 0; i <= this->N; i++) {
			for (size_t j = 0; j <= 2; j++) {
//			if (!(j >= 3 && (i == 0 || i == this->N)))
					_x[j].push_back(X[i]);
			}
//			_y[0].push_back(Y[i]);
			_y[2].push_back(y(X[i]));
			_y[0].push_back(y_real(X[i]));
//			_y[3].push_back(V[i]);
		}

		cout << endl << "Tichonov nesvjazki:" << endl;
		cout << "d = " << this->d << endl;
		Ans = this->Tich.Get_Data(true, this->d);
		FillE(this->e1, this->_e1, this->e2, this->_e2, Ans);
		cout << "e1 = " << e1 << ", _e1 = " << _e1 << ", e2 = " << e2 << ", _e2 = " << _e2 << endl;
		cout << "E1/e1 = " << E1 / e1 << ", _E1/_e1 = " << _E1 / _e1 << ", E2/e2 = " << E2 / e2 << ", _E2/_e2 = " << _E2 / _e2 << endl;

		for (size_t i = 0; i <= this->N; i++) {
			_y[1].push_back(Ans[i]);
//			if (!(i == 0 || i == this->N))
//				_y[4].push_back(0.5*(Ans[i + 1] - Ans[i - 1]) / tay);
		}

		cout << endl << "Tichonov kvazioptimum:" << endl;
		double aaa = 0.000016;
		Ans = this->Tich.Get_Data(false, aaa);
		FillE(this->e1, this->_e1, this->e2, this->_e2, Ans);
		cout << "e1 = " << e1 << ", _e1 = " << _e1 << ", e2 = " << e2 << ", _e2 = " << _e2 << endl;
		cout << "E1/e1 = " << E1 / e1 << ", _E1/_e1 = " << _E1 / _e1 << endl << "E2/e2 = " << E2 / e2 << ", _E2/_e2 = " << _E2 / _e2 << endl;
		cout << endl;

		for (size_t i = 0; i <= this->N; i++) {
//			_y[1].push_back(Ans[i]);
//			if (!(i == 0 || i == this->N))
//				_y[5].push_back(0.5*(Ans[i + 1] - Ans[i - 1]) / tay);
		}

		Draw.Draw();
	}

};

int main(int argc, char *argv[]) {

	srand(time(NULL));
//	Experiment Ex;
	ExperimentT ExT;
//	Ex.Work(1);
	ExT.Run();


	return 0;
}
