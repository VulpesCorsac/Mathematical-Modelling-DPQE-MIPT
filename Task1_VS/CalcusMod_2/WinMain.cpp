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

#define all(c) c.begin(), c.end()
typedef long long lint;
typedef long double ldouble;

struct Color {
	int r, g, b;
};

using namespace std;

vector < Color > default_color;

static TCHAR s[500];
static TCHAR *szWindowClass = _T("Geo");
static TCHAR *szTitle = _T("Математическое моделирование");

HINSTANCE hInst;
HWND hWnd;
HDC hdc;
HBRUSH brush;
HPEN hPen;
WNDCLASSEX wcex;
MSG msg;

const int Maxx = 700;
const int Maxy = 700;
const DWORD SleepTime = 200;
const ldouble pi = 3.1415926535897932384626433832795088693993;
const int eps = 40;
const bool analytics = true;

ldouble lambda, w0, w, x0, v0, t0, tmax, dt, gamma, t_analytics;
ldouble x_plot, y_plot, x_zero, y_zero, x_adding, y_adding;

bool __analytics;
vector < ldouble > __x;
vector < vector < ldouble > > __y;

// Получение ширины окна
int getmaxx(void) {
	return Maxx - 2*eps;
}

// Получение высоты экрана
int getmaxy(void) {
	return Maxy - 2*eps;
}

// Округление
int _round(ldouble x) {
	return floor(x + 0.5);
}

// Возведение в квадрат
ldouble _sqr(ldouble x) {
    return x*x;
}

// Модуль аргумента
ldouble _abs(ldouble x) {
    if (x < 0)
        return -x;
    return x;
}

// Наибольшее значение из двух чисел
ldouble _max(const ldouble a, const ldouble b) {
    if (a > b)
        return a;
    return b;
}

// Наименьшее значение из двух чисел
ldouble _min(const ldouble a, const ldouble b) {
    if (a < b)
        return a;
    return b;
}

// Наибольшее знаение из вектора
ldouble _max(const vector < ldouble > v) {
    double maxx = v[0];
    for (size_t i = 0; i < v.size(); maxx = _max(maxx, v[i++]));
    return maxx;
}

// Наименьшее значение из вектора
ldouble _min(const vector < ldouble > v) {
    double minn = v[0];
    for (size_t i = 0; i < v.size(); minn = _min(minn, v[i++]));
    return minn;
}

// Заполнение вектора арифметической прогрессией
vector < ldouble > set_dt_v(int n, ldouble d, ldouble s = 0) {
    vector < ldouble > res(n, s);
    for (int i = 0; i < n; res[i] += i*d, i++);
    return res;
}

// Уравнение
double f(const double t, const double v, const double x) {
    return -(2*lambda*v + _sqr(w0)*x);
}

// Аналитическое решение
double f_analytics(const double t) {
    return exp(-lambda*t)*(x0*cos(w*t) + (lambda*x0 +v0)*sin(w*t)/w);
}

// Инициализация констант
void init(void) {
    lambda = 0.1;
    gamma = 0;
    x0 = 0.01;
    w0 = 1;
    v0 = 1;
    dt = 0.05;
	t0 = 0;

    w = sqrt(_sqr(w0) - _sqr(lambda));
    tmax = 2.0 * (2.0 * pi / w);
    t_analytics = tmax / 2.0;

	default_color.resize(4);
	// Amber - Янтарный
	default_color[0].r = 255;
	default_color[0].g = 191;
	default_color[0].b = 0;
	// American Rose - Американская роза
	default_color[1].r = 255;
	default_color[1].g = 3;
	default_color[1].b = 62;
	// Azure - Лазурный, Азур
	default_color[2].r = 0;
	default_color[2].g = 127;
	default_color[2].b = 255;
	// Apple Green - Яблочно-зелёный
	default_color[3].r = 141;
	default_color[3].g = 182;
	default_color[3].b = 0;

	return;
}

// Метод Эйлера
void solve0(vector < ldouble > &xn, vector < ldouble > &vn) {
    int n = 0;
    xn.clear();
    vn.clear();
    xn.push_back(x0);
    vn.push_back(v0);
    
	ldouble t = t0;
    while (t < tmax) {
        vn.push_back(vn[n] + dt * f(t, vn[n], xn[n]));
        xn.push_back(xn[n] + dt * vn[n]);
        t += dt;
        n++;
    }

	return;
}

// Метод Эйлера улучшенный 
void solve1(vector < ldouble > &xn, vector < ldouble > &vn) {
    int n = 0;
    xn.clear();
    vn.clear();
    xn.push_back(x0);
    vn.push_back(v0);

    ldouble t = t0;
    while (t < tmax) {
        vn.push_back(vn[n] + dt * f(t, vn[n], xn[n]));
        xn.push_back(xn[n] + dt * vn[n+1]);
        t += dt;
        n++;
    }

	return;
}

// Метод предикат-корректоров
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

	return;
}

// Метод Рунге-Кутте
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
		k1 = dt*f(t + dt, vn[n], xn[n]);
		k2 = dt*f(t + dt / 2.0, vn[n] + k1 / 2.0, xn[n] + k1 / 2.0);
		k3 = dt*f(t + dt / 2.0, vn[n] + k2 / 2.0, xn[n] + k2 / 2.0);
		k4 = dt*f(t + dt, vn[n] + k3, xn[n] + k3);
        xn.push_back(xn[n] + 1/6.0*(k1 + 2.0*k2 + 2.0*k3 + k4));
        vn.push_back(vn[n] + 1/6.0*(k1 + 2.0*k2 + 2.0*k3 + k4));
        n++;
    }

	return;
}

// Разница между двумя векторами
vector < ldouble > delta(const vector < ldouble > a, const vector < ldouble > b) {
    vector < ldouble > res(a.size());
    for (size_t i = 0; i < a.size(); res[i] = a[i] - b[i], i++);
    return res;
}

// Сравнение полученного решения с аналитическим
vector < ldouble > delta(const vector < ldouble > a) {
    vector < ldouble > res(a.size());
    for (size_t i = 0; i < a.size(); res[i] = a[i] - f_analytics(t0+i*dt), i++);
    return res;
}

// Ширина полосы построения
ldouble get_axis_range(const vector < ldouble > v) {
    return (_max(v) - _min(v));
}

// Установка цвета
void set_color(int r, int g, int b) {
	hPen = CreatePen(PS_SOLID, 1, RGB(r, g, b));
	SelectObject(hdc, hPen);
	return;
}

// Сохранение старых параметров
void export_params(ldouble A, ldouble B, ldouble get_x_zero, ldouble get_y_zero, ldouble adding_x, ldouble adding_y) {
	x_plot = A;
    y_plot = B;
    x_zero = get_x_zero;
    y_zero = get_y_zero;
    x_adding = adding_x;
    y_adding = adding_y;
	
	return;
}

// Использование старых параметров
void import_params(ldouble &A, ldouble &B, ldouble &get_x_zero, ldouble &get_y_zero, ldouble &adding_x, ldouble &adding_y) {
	A = x_plot;
    B = y_plot;
    get_x_zero = x_zero;
    get_y_zero = y_zero;
    adding_x = x_adding;
    adding_y = y_adding;

	return;
}

// Выводе графика
void draw(const vector < ldouble > x, const vector < vector < ldouble > > y, bool _analytics = false) {
	int max_x_graph = getmaxx();
    int max_y_graph = getmaxy();
    ldouble max_x_real = get_axis_range(x);
    ldouble max_y_real = get_axis_range(y[0]);
    ldouble A = max_x_graph / max_x_real;
    ldouble B = max_y_graph / max_y_real;
    ldouble get_x_zero;
    ldouble get_y_zero;
    ldouble adding_x;
    ldouble adding_y;
	
	set_color(255 - 242, 255 - 243, 255 - 244);
	if (_min(y[0]) * _max(y[0]) <= 0) {
		get_x_zero = -B*_min(y[0]);
		adding_y = get_x_zero;
	} else {
		get_x_zero = -1;
		adding_y = -B*abs(_min(y[0]));
	}
	if (get_x_zero >= 0) {
		MoveToEx(hdc, eps + 0, eps + max_y_graph - get_x_zero, NULL);
		LineTo(hdc, eps + max_x_graph, eps + max_y_graph - get_x_zero);
	}
	if (_min(x) * _max(x) <= 0) {
		get_y_zero = -A*_min(x);
		adding_x = get_y_zero;
	} else {
		get_y_zero = -1;
		adding_x = -A*abs(_min(x));
	}
	if (get_y_zero >= 0) {
		MoveToEx(hdc, eps + get_y_zero, eps + 0, NULL);
		LineTo(hdc, eps + get_y_zero, eps + max_y_graph);
	}

    int len = swprintf(s, 100, L"Minx = %lf, Maxx = %lf", (double) _min(x), (double) _max(x));
	TextOut(hdc, eps + 2, eps + 20, s, len);
		len = swprintf(s, 100, L"Miny = %lf, Maxy = %lf", (double) _min(y[0]), (double) _max(y[0]));
    TextOut(hdc, eps + 2, eps + 50, s, len);

	for (size_t graph_num = 0; graph_num < y.size(); graph_num++) {
		set_color(default_color[graph_num].r, default_color[graph_num].g, default_color[graph_num].b);
		MoveToEx(hdc, eps + A*x[0] + adding_x, eps + max_y_graph - (B*y[graph_num][0] + adding_y), NULL);
		for (size_t i = 0; i < x.size(); i++)
			LineTo(hdc, eps + A*x[i] + adding_x, eps + max_y_graph - (B*y[graph_num][i] + adding_y));
	}
	
	Sleep(SleepTime);

	if (_analytics) {
		set_color(default_color[default_color.size()-1].r, default_color[default_color.size()-1].g, default_color[default_color.size()-1].b);
		MoveToEx(hdc, eps + A*x[0] + adding_x, eps + max_y_graph - (B*f_analytics(t0) + adding_y), NULL);
        for (size_t i = 0; i < x.size(); i++)
			LineTo(hdc, eps + A*x[i] + adding_x, eps + max_y_graph - (B*f_analytics(t0 + i*dt) + adding_y));
	}

	return;
}

// Обработка сообщений, поступающих от GetMessage
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_PAINT:
		SelectObject(hdc, hPen);
		PAINTSTRUCT pp;
		BeginPaint(hWnd, &pp);
		draw(__x, __y, __analytics);	//!
		EndPaint(hWnd, &pp);
//		draw1();
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

// Инициализация графики
int init_magic(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// создаем класс и задаем ему параметры
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	//регистрируем класс
    if (!RegisterClassEx(&wcex)) {
        MessageBox(NULL, _T("WTF?"), _T("WTF?"), NULL);
        return 1;
    }

	return 0;
}

// Пересоздание окна
int magic(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	//создаем окно данного класса
    hInst = hInstance; 
    hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, Maxx, Maxy, NULL, NULL, hInstance, NULL);
	hdc = GetWindowDC(hWnd);

	//проверка того, создалось ли окно.
	if (!hWnd) {
        MessageBox(NULL, _T("Call to CreateWindow failed!"), _T("Folak"), NULL);
        return -1;
    }

	//показываем окно, начинаем получать сообщения
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

	return 0;
}

// Отрисовка
void Magic_draw(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, const vector < ldouble > x, const vector < vector < ldouble > > y, bool _analytics = false) {
	__x = x;
	__y = y;
	__analytics = _analytics;

	magic(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
        DispatchMessage(&msg);
	}
}

// Точка входа - инициализация приложения
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
//*
	freopen("cout.txt", "a+", stdout);
	freopen("cerr.txt", "a+", stderr);
	cerr << "Started" << endl;
	ldouble d0, d0_analytics, d1, d1_analytics, d2, d2_analytics, d4, d4_analytics;
	init();
    int t_n = round(t_analytics / dt);
	if (t_n % 2)
		t_n--;
    cerr << "Inited" << endl;

    vector < ldouble > xn;
    vector < ldouble > _xn;
    vector < ldouble > vn;
    vector < ldouble > _vn;
    vector < ldouble > dn0;
    vector < ldouble > dn1;
    vector < ldouble > dn2;
    vector < ldouble > dn4;
    vector < ldouble > tn;
	vector < vector < ldouble > > y;
//*/
	init_magic(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	cerr << "Graph Inited" << endl;
//*
	// Метод Эйлера
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
	y.push_back(xn);
    Magic_draw(hInstance, hPrevInstance, lpCmdLine, nCmdShow, tn, y, analytics);
	y.clear();

	// Улучшенный метод Эйлера
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
	y.push_back(xn);
	Magic_draw(hInstance, hPrevInstance, lpCmdLine, nCmdShow, tn, y, analytics);
    y.clear();

    // Предикат-корректоры
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
	y.push_back(xn);
	Magic_draw(hInstance, hPrevInstance, lpCmdLine, nCmdShow, tn, y, analytics);
    y.clear();

	// Метод Рунге-Кутта
/*
    solve4(xn, vn);
    dt *= 2.0;
    solve4(_xn, _vn);
    dt /= 2.0;
    d1 = abs(xn[t_n] - _xn[t_n / 2]);
    if (analytics) {
        dn4 = delta(xn);
        d4_analytics = dn4[t_n];
    }

    cerr << "Solved 4" << endl;
	y.push_back(xn);
	Magic_draw(hInstance, hPrevInstance, lpCmdLine, nCmdShow, tn, y, analytics);
    y.clear();
*/ 

	// delta
    if (analytics) {
		y.push_back(dn0);
		y.push_back(dn1);
		y.push_back(dn2);
//		y.push_back(dn4);
		Magic_draw(hInstance, hPrevInstance, lpCmdLine, nCmdShow, tn, y);
		y.clear();
		cerr << fixed << setprecision(10);
        cerr << "d0 = " << d0 << ", d0_analytics = " << d0_analytics << endl;
        cerr << "d1 = " << d1 << ", d1_analytics = " << d1_analytics << endl;
        cerr << "d2 = " << d2 << ", d2_analytics = " << d2_analytics << endl;
//        cerr << "d4 = " << d2 << ", d4_analytics = " << d2_analytics << endl;
    }
	
	y.push_back(vn);
	Magic_draw(hInstance, hPrevInstance, lpCmdLine, nCmdShow, xn, y);
	y.clear();
//*/
	fclose(stdout);
	fclose(stderr);

    return (int) msg.wParam;
}
