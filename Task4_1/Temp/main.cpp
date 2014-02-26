#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>

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

#define PI 3.1415926535

using namespace std;

/*
HINSTANCE hInst;
HWND hWnd;
HDC hdc;
HBRUSH brush;
HPEN hPen;
WNDCLASSEX wcex;
MSG msg;

//LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

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
		Max_x_plot = 500;
		Max_y_plot = 500;
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

//TDraw Draw;
*/

//vector < vector < TDraw::Type > > _x, _y;
vector < vector < double > > _x, _y;

/*
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
*/

double sqr(double x) {
	return x*x;
}

double Rc = 6700*1000;
double Rz = 6371*1000;
double G = 6.67*1e-11;
double Mz = 5.99*1e24;
double Vc = sqrt(G*Mz / Rc);
double Wc = sqrt(G*Mz / (Rc*Rc*Rc));
double U = 6;
double S = 5000;
double f0 = S / Rc;
double dt = 0.0005;
double tmax = 3000;

double func(double coord, double r) {
	return -G*Mz*coord / (r*r*r);
}

double f_station(double t) {
	return Wc*t + f0;
}

double x_station(double t) {
	return Rc*cos(f_station(t));
}

double y_station(double t) {
	return Rc*sin(f_station(t));
}

vector < double > vx;
vector < double > vy;
vector < double > r;
vector < double > f;

double solve(vector < double > &x, vector < double > &y, double beta, double &tr, double &tf, bool quick = true) {
	x.clear(); y.clear(); vx.clear(); vy.clear(); r.clear(); f.clear();
	double t = 0;
	tr = tf = -1;
	bool r_found = false;
	bool f_found = false;
/*
	_y.resize(2);
	_x.resize(2);
	_x[0].push_back(Rc);
	_y[0].push_back(0);
	_x[1].push_back(x_station(t));
	_y[1].push_back(y_station(t));
*/
	x.push_back(Rc);
	y.push_back(0);
	vx.push_back(-U*sin(beta));
	vy.push_back(Vc + U*cos(beta));
	int i = 0;
	double Rr = sqrt(sqr(x[0]) + sqr(y[0]));
	double fr = atan2(y[0], x[0]);
	double fc = atan2(y_station(0), x_station(0));
	double xx = 0, yy = 0, x_s = 0, y_s = 0, dx = 0, dy = 0, dr = 0, df = 0, old_df = 0;
	double xk1, xk2, xk3, xk4, vxk1, vxk2, vxk3, vxk4, yk1, yk2, yk3, yk4, vyk1, vyk2, vyk3, vyk4;
	r.push_back(Rr);
	f.push_back(fr);
	while (t <= tmax) {
		t += dt;
/*
		x.push_back(x[i] + dt*vx[i] + 0.5*sqr(dt)*func(x[i], Rr));
		y.push_back(y[i] + dt*vy[i] + 0.5*sqr(dt)*func(y[i], Rr));
		vx.push_back(vx[i] + 0.5*dt*(func(x[i], Rr) + func(x[i] + dt*vx[i], Rr)));
		vy.push_back(vy[i] + 0.5*dt*(func(y[i], Rr) + func(y[i] + dt*vy[i], Rr)));
*/

		xk1 = dt*vx[i];
		yk1 = dt*vy[i];
		vxk1 = dt*func(x[i], Rr);
		vyk1 = dt*func(y[i], Rr);

		xk2 = dt*(vx[i] + 0.5*vxk1);
		yk2 = dt*(vy[i] + 0.5*vyk1);
		vxk2 = dt*func(x[i] + 0.5*xk1, Rr);
		vyk2 = dt*func(y[i] + 0.5*yk1, Rr);

		xk3 = dt*(vx[i] + 0.5*vxk2);
		yk3 = dt*(vy[i] + 0.5*vyk2);
		vxk3 = dt*func(x[i] + 0.5*xk2, Rr);
		vyk3 = dt*func(y[i] + 0.5*yk2, Rr);

		xk4 = dt*(vx[i] + vxk3);
		yk4 = dt*(vy[i] + vyk3);
		vxk4 = dt*func(x[i] + xk3, Rr);
		vyk4 = dt*func(y[i] + yk3, Rr);

		x.push_back(x[i] + (xk1 + 2*xk2 + 2*xk3 + xk4) / 6);
		y.push_back(y[i] + (yk1 + 2*yk2 + 2*yk3 + yk4) / 6);
		vx.push_back(vx[i] + (vxk1 + 2*vxk2 + 2*vxk3 + vxk4) / 6);
		vy.push_back(vy[i] + (vyk1 + 2*vyk2 + 2*vyk3 + vyk4) / 6);

		i++;
		Rr = sqrt(sqr(x[i]) + sqr(y[i]));
		fr = atan2(y[i], x[i]);
		fc = atan2(y_station(t), x_station(t));
		r.push_back(Rr);
		f.push_back(fr);
/*
		_x[0].push_back(x[i]);
		_y[0].push_back(y[i]);
		_x[1].push_back(x_station(t));
		_y[1].push_back(y_station(t));
*/

		xx = x[i];
		yy = y[i];
		x_s = x_station(t);
		y_s = y_station(t);
		dx = xx - x_s;
		dy = yy - y_s;
		dr = Rr - Rc;
		old_df = df;
		df = fr - fc;

		if (Rr <= Rz) {
			cerr << "Crashed into the Earth! Booooooom!" << endl;
			return 0;
		}

		if (!r_found && r[i] > Rc && r[i-1] < Rc) {
			r_found = true;
			tr = t;
			if (quick)
				return -1;
		}
		if (!f_found && df * old_df < 0) {
			f_found = true;
			tf = t;
			if (quick)
				return 1;
		}
		if (r_found && f_found)
			return tr - tf;
	}

	cerr << "Timeout!" << endl;
	return 0;
}

int main() {
	cout << fixed << setprecision(9);
	vector < double > x, y;
	double bmin = 0;
	double bmax = 0.5*PI;
	double bmid = 0.5*(bmax+bmin);
	double tr, tf;

	while (bmax - bmin > 1e-6) {
		bmid = 0.5*(bmax+bmin);
		cout << "bmax = " << bmax * 180 / PI << endl;
		cout << "bmin = " << bmin * 180 / PI << endl;
		cout << "bmid = " << bmid * 180 / PI << endl;
		double res = solve(x, y, bmid, tr, tf);
		cout << "res = " << res << endl;
		if (tf > 0 && tr > 0) {
			if (res < 0)
				bmin = bmid;
			if (res > 0)
				bmax = bmid;
			if (res == 0)
				break;
		}
		else {
//			cout << "Oh, man...." << endl;
			if (tf < 0 && tr > 0)
				bmin = bmid;
			if (tr < 0 && tf > 0)
				bmax = bmid;
			if (tr < 0 && tf < 0)
				return -2;
		}
		cout << endl;
//		Draw.Draw();
	}
	cout << "found beta = " << bmid * 180 / PI << endl;
	solve(x, y, bmid, tr, tf, false);
	double T = dt*x.size();
	double Rm = Rc - sqrt(sqr(x[0]) + sqr(y[0]));
	vector < double > Rrr;
	for (size_t i = 0; i < x.size(); i++) 
		Rm = max(Rm, Rc - sqrt(sqr(x[i]) + sqr(y[i])));

	double Vcx = -Vc*sin(f_station(T));
	double Vcy = +Vc*cos(f_station(T));
	double Vv = sqrt(sqr(vx[vx.size() - 1] - Vcx) + sqr(vy[vy.size() - 1] - Vcy));
	double alpha = atan2(vy[vy.size() - 1] - Vcy, vx[vx.size() - 1] - Vcx);
	cout << "T = " << T << endl;
	cout << "Rmin = " << Rm << endl;
	cout << "V = " << Vv << endl;
//	cout << "Alpha = " << alpha * 180 / PI << endl;

	getchar();
}