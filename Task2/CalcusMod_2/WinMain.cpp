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
const double pi = 3.1415926535897932384626433832795088693993;
const double g = 9.82;
const double _eps = 0.002;
const int eps = 40;

double x0 = pi - 0.0002, v0 = 0, t0 = 0.0, tmax = 1000, dt = 0.001, t_analytics = 0;
double AA;

bool __analytics;
vector < double > __x;
vector < double > __y;

// Получение ширины окна 
int getmaxx(void) {
	return Maxx - 2*eps;
}

// Получение высоты экрана
int getmaxy(void) {
	return Maxy - 2*eps;
}

// Перевод градусов в радианы
double degree_to_radian(double x) {
	return (x * pi/180.0);
}

// Перевод радиан в градусы
double radian_to_degree(double x) {
	return (x * 180.0/(1.0*pi));
}

// Форматирование осей
double modify(double x) {
	return radian_to_degree(x);
}

double sqr(double x) {
    return x*x;
}

double _max(const vector < double > v) {
    double maxx = v[0];
    for (int i = 0; i < v.size(); i++)
        maxx = max(maxx, v[i]);
    return maxx;
}

double _min(const vector < double > v) {
    double minn = v[0];
    for (int i = 0; i < v.size(); i++)
        minn = min(minn, v[i]);
    return minn;
}

vector < double > set_dt_v(int n) {
    vector < double > res(n);
    res[0] = t0;
    for (int i = 1; i < n; i++)
        res[i] = res[i-1] + dt;
    return res;
}

//calcus functions
double f(double t, double x) {
    return -(1 + AA*sqrt(2)*10*cos(10*t))*sin(x);
}

void solve2(vector < double > &x, vector < double > &v) {
    int n = 0;
    x.clear();
    v.clear();
    x.push_back(x0);
    v.push_back(v0);
    double xcorrector;
    double vcorrector;
    double t = t0;
    while (t < tmax) {
        t = t + dt;
        vcorrector = v[n] + dt*f(t-dt, x[n]);
        xcorrector = x[n] + dt*v[n];
        v.push_back(v[n] + dt * (f(t-dt, x[n]) + f(t, xcorrector)) / 2.0);
        x.push_back(x[n] + dt * (v[n] + vcorrector) / 2.0);
        n++;
    }
    return;
}

// Проставление цветов
void set_default_color(void) {
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
}

// Инициализация констант
void init(void) {
	set_default_color();
	return;
}

// Установка цвета
void set_color(int r, int g, int b) {
	hPen = CreatePen(PS_SOLID, 1, RGB(r, g, b));
	SelectObject(hdc, hPen);
	return;
}

// Выводе графика
void draw(const vector < double > x, const vector < double > y) {
    int max_x_graph = getmaxx();
    int max_y_graph = getmaxy();
    double max_x_real = _max(x) - _min(x);
    double max_y_real = _max(y) - _min(y);
    double A = max_x_graph / max_x_real;
    double B = max_y_graph / max_y_real;
    double get_x_zero;
    double get_y_zero;
    double adding_x;
    double adding_y;

	set_color(255 - 242, 255 - 243, 255 - 244);
	if (_min(y) * _max(y) <= 0) {
		get_x_zero = -B*_min(y);
		adding_y = get_x_zero;
	} else {
		get_x_zero = -1;
		adding_y = -B*abs(_min(y));
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
	if (get_y_zero >= 0)  {
		MoveToEx(hdc, eps + get_y_zero, eps + 0, NULL);
		LineTo(hdc, eps + get_y_zero, eps + max_y_graph);
	}
	
    int len = swprintf(s, 100, L"Minx = %lf, Maxx = %lf", (double) (_min(x)), (double) (_max(x)));
	TextOut(hdc, eps + 2, eps + 20, s, len);
		len = swprintf(s, 100, L"Miny = %lf, Maxy = %lf", (double) modify(_min(y)), (double) modify(_max(y)));
    TextOut(hdc, eps + 2, eps + 50, s, len);

	int di = x.size() / 1000;
	if (di < 1)
		di = 1;
	set_color(default_color[1].r, default_color[1].g, default_color[1].b);
	MoveToEx(hdc, eps + A*x[0] + adding_x, eps + max_y_graph - (B*y[0] + adding_y), NULL);
	for (size_t i = 0; i < x.size(); i += di)
		LineTo(hdc, eps + A*x[i] + adding_x, eps + max_y_graph - (B*y[i] + adding_y));
	
	return;
}

// Обработка сообщений, поступающих от GetMessage
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_PAINT:
		SelectObject(hdc, hPen);
		PAINTSTRUCT pp;
		BeginPaint(hWnd, &pp);
		draw(__x, __y);	//!
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
void Magic_draw(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, const vector < double > x, const vector < double > y) {
	__x = x;
	__y = y;

	magic(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
        DispatchMessage(&msg);
	}
}

// Точка входа - инициализация приложения
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
//*
	freopen("cerr.txt", "a+", stderr);
	init();

    vector < double > xn;
    vector < double > vn;
    vector < double > tn;
	init_magic(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
//	AA = (1 - _eps);
//	solve2(xn, vn);
//	tn = set_dt_v(xn.size());
//	Magic_draw(hInstance, hPrevInstance, lpCmdLine, nCmdShow, tn, xn);
//	Magic_draw(hInstance, hPrevInstance, lpCmdLine, nCmdShow, xn, vn);
	
	AA = (1 + _eps);
	solve2(xn, vn);
	tn = set_dt_v(xn.size());
	Magic_draw(hInstance, hPrevInstance, lpCmdLine, nCmdShow, tn, xn);
//	Magic_draw(hInstance, hPrevInstance, lpCmdLine, nCmdShow, xn, vn);

	fclose(stderr);

    return (int) msg.wParam;
}