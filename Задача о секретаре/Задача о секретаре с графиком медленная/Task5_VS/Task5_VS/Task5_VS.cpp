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

using namespace std;

HINSTANCE hInst;
HWND hWnd;
HDC hdc;
HBRUSH brush;
HPEN hPen;
WNDCLASSEX wcex;
MSG msg;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Класс отрисовки
class TDraw {
public:
	typedef double Type; // Aka template  

private:
	long double CalcusEps; // Comparison
	int GraphEps; // Боковые поля
	int Max_x_plot, Max_y_plot; // Max graph ranges
	int Max_point_number; // Максимальное количчество точек

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
		Colours.resize(11);
		Colours[0].r = 255 - 242;
		Colours[0].g = 255 - 243;
		Colours[0].b = 255 - 244;
		Colours[1].r = 141;
		Colours[1].g = 182;
		Colours[1].b = 0;
		Colours[2].r = 255 - 141;
		Colours[2].g = 255 - 182;
		Colours[2].b = 255 - 0;
		Colours[3].r = 255;
		Colours[3].g = 218;
		Colours[3].b = 185;
		Colours[4].r = 47;
		Colours[4].g = 79;
		Colours[4].b = 79;
		Colours[5].r = 119;
		Colours[5].g = 136;
		Colours[5].b = 153;
		Colours[6].r = 0;
		Colours[6].g = 191;
		Colours[6].b = 255;
		Colours[7].r = 85;
		Colours[7].g = 107;
		Colours[7].b = 47;
		Colours[8].r = 124;
		Colours[8].g = 252;
		Colours[8].b = 0;
		Colours[9].r = 178;
		Colours[9].g = 34;
		Colours[9].b = 34;
		Colours[10].r = 255;
		Colours[10].g = 0;
		Colours[10].b = 255;
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

		//показываем окно, начинаем получать сообщения
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

TDraw Draw;
vector < vector < TDraw::Type > > _x, _y;

// Обработка сообщений, поступающих от GetMessage
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

// Класс обсчета экспериментов
class Experiment{
private:
	vector < int > employee; // Рейтинги кандидатов
	int k; // Количество кандидатов, которых мы сразу отсеиваем
	int N; // Число людей в очереди
	int K; // Число экспериментов
	int Max; // Рейтинг лучшего кандидата

public:
	// Инициализация количеств людей в очереди и экспериментов
	Experiment(int _N = 100, int _K = 30000) {
		N = _N;
		K = _K;
		employee.resize(N);
	}
	
	// Инициализация рейтингов кандидатов
	void Init(int _k) {
		Max = -1; // Текущий максимальный рейтинг отрицательный => любой будет лучше
		k = _k; // Количество кандидатов, которых мы сразу отсеиваем
		int r; // Случайный рейтинг
		set < int > used; // множество уже занятых рейтингов
		used.clear(); // Сделать это множество пустым
		for (int i = 0; i < N; i++) { // Для каждого кандидата
			do
				r = rand(); // Сгенерируем случайный рейтинг
			while (used.count(r) > 0); // Пока этот рейтинг не занят
			employee[i] = r; // Присвоить кандидату рейтинг
			Max = max(r, Max); // Пересчитать текущий максимальный рейтинг
			used.insert(r); // Добавить этот рейтинг в множество занятых
		}
	}

	// Запуск одного эксперимента. Возвращает 1 в случае успеха и 0 - в случае неуспеха
	int Run_one() {
		int m = -1; // Текущий максимальный рейтинг отрицательный => первый же временно станет лучшим
		for (int i = 0; i < k; i++) // Для каждого из априорно отсеиваемых кандидатов 
			m = max(m, employee[i]); // Смотрим, кто из них лучший
		for (int i = k; i < N; i++) // Смотрим на остальных кандидатов
			if (employee[i] > m) { // Если он лучше их
				if (employee[i] == Max) // Если он лучший из всех
					return 1; // Эксперимент удался
				else // Иначе
					return 0; // Мы выбрали не лучшего из них
			}
		if (employee[N - 1] == Max) // Если мы дошли до последнего, мы обязаны его взять. А лучший ли он?
			return 1; // Да
		return 0; // Нет
	}

	// Поиск вероятности выбора лучшего при априорном отсеивании к кандидатов
	double P(int _k) {
		double res = 0; // Число успешных исходов
		for (int i = 0; i < K; i++) { // Запуск серии экспериментов
			Init(_k); // Инициализировать рейтинг кандидатов
			res += Run_one(); // В случае успеха res учеличится на 1
		}
		return res / K; // Число успешных к числу неуспешных
	}

	// Запуск всего эксперимента
	void Run() {
		double p; // Вероятность выбора лучшего
		int m = 0; // При каком количестве априорного отсева у нас максимальна вероятность выбрать наилучшего
		_x.resize(1); // Массив для вывода графика
		_y.resize(1); // Массив для вывода графика
		_x[0].resize(N - 1); // Массив для вывода графика
		_y[0].resize(N - 1); // Массив для вывода графика
		for (int k = 0; k < N; k++) { // При отсеве от 0 до N-1
			p = P(k); // Рассчитать вероятность
			cout << "P(" << k << ") = " << p << endl; // Вывести её на экран
			_x[0][k] = k; // Записать в массив для графики
			_y[0][k] = p; // Записать в массив для графики
			if (_y[0][k] > _y[0][m]) // Если данное количество априорного отсева лучше
				m = k; // Изменить максимум
		}
		cout << "best is << " << m << endl; // Вывесли наилучшее число априорного отсева
	}

};

int main(int argc, char *argv[]) {
	Experiment Ex(100, 3000); // Инициализация числа экспериментов
	cerr << "Inited" << endl; // Вывести на экран хоть что-то, чтобы не было ощущения, что он завис
	Ex.Run(); // Запустить весь эксперимент
 	Draw.Draw(); // Вывести график. Для этого нужно будет мышкой перевести окошко в чуть другое место. 
				 // Т.е. отрисовка происходит КАК ТОЛЬКО окно сместится хоть куда-то.
				 // Само оно, разумеется, не сместится. Так что придется дернуть самой
				 // ОБЯЗАТЕЛЬНО проект собирай как релиз. Там есть окошечко наверху, где написано DEBUG. Его надо сменить на RELEASE
				 // Для 3000 экспериментов эта фигня считается порядка 2,5 минут. А тебе нужно в 10 раз больше!
				 // Сильно тормозит именно графический модуль, увы. Он _постоянно_ включен, просто иначе писать гораздо тяжелее и мне немного лень
				 // На всякий случай там есть проект Code::Blocks, там нет описаний или графики, но зато данные он выводит раз в 10 быстрее
				 // Т.е. чтобы просто показать, что да, оно, в принципе, работает - вполне реально. Кстати, работает ли - тоже вопрос.
				 // ИМХО - там что-то странное творится в самом конце, когда мы априори отсеиваем N-1 кандидатов. 
				 // Теоретически там вероятность выбора лучшего должна быть 0.01, а у меня раза в 2 больше Х_Х
	system("pause"); // После завершения не сразу выйти, а подождать нажатия любой клавиши
	return 0;
}