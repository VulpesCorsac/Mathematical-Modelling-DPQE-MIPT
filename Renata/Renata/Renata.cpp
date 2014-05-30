
#include "stdafx.h"

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include "time.h"

LRESULT CALLBACK MainWinProc(HWND, UINT, WPARAM, LPARAM);


const int N = 200;
const int NS = N * 2 + 1;
const int K = 10000;

const int R = 60;	//must be lower than N

int hd[NS];
double hdf[NS];
double avgX2, avgT;

void calc()
{
	//расчет гистограммы для времени N, число повторов K
	avgX2 = 0;
	for (int i = 0; i < NS; i++)
	{
		hd[i] = 0;
	}

	for (int ci = 0; ci < K; ci++)
	{
		int cx = N;
		for (int i = 0; i < N; i++)
		{
			rand() & 1 ? cx++ : cx--;
		}
		int dx = cx - N;
		hd[cx]++;
		avgX2 += dx * dx;
	}
	avgX2 /= K;
	for (int i = 0; i < NS; i++)
	{
		hdf[i] = float(hd[i]) / K;
	}

	//расчет <T> для заданного R
	avgT = 0;
	for (int ci = 0; ci < K; ci++)
	{
		int cx = N;
		int ct = 0;
		while (true)
		{
			rand() & 1 ? cx++ : cx--;
			if (abs(cx - N) > R) break;
			ct++;
		}
		avgT += ct;
	}
	avgT /= K;

	printf("<x^2> = %.8f, 2Dt = %.1f\n", avgX2, (double)N);
	printf("<T> = %.8f, R^2/2D = %.1f\n", avgT, (double)R*R);
}


HPEN Pen1, PenG;
HBRUSH Brush1, BrushB;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int ss) {
	/* создание и регистрирация класс главного окна */
	WNDCLASS wc;
	wc.style = 0;
	wc.lpfnWndProc = MainWinProc;
	wc.cbClsExtra = wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = NULL;
	wc.hCursor = NULL;
	HBRUSH Brushsss1 = CreateSolidBrush(RGB(0, 0, 0));
	wc.hbrBackground = Brushsss1;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "Example 4 MainWnd Class";
	if (!RegisterClass(&wc)) return FALSE;

	AllocConsole();
	freopen("CONOUT$", "wb", stdout);

	srand(time(NULL));

	Pen1 = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));        //1с
	PenG = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));        //1с
	Brush1 = CreateSolidBrush(RGB(0, 0, 127));
	BrushB = CreateSolidBrush(RGB(255, 255, 255));

	/* создание и отображение окна */
	HWND hMainWnd = CreateWindow("Example 4 MainWnd Class", " ", WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInst, NULL);
	if (!hMainWnd) return FALSE;
	ShowWindow(hMainWnd, ss);
	UpdateWindow(hMainWnd);

	calc();

	InvalidateRect(hMainWnd, NULL, true);
	MSG msg; /* цикл обработки событий */
	while (true)
	{
		if (PeekMessageA(&msg, NULL, 0, 0, true))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Sleep(1);
	}
	fclose(stdout);
	FreeConsole();
	return 0;
}

/* процедура обработки сообщений для главного окна */
LRESULT CALLBACK MainWinProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp) {

	RECT s;
	GetClientRect(hw, &s);
	int wt = s.right - s.left;
	int ht = s.bottom - s.top;

	HDC hDC;
	PAINTSTRUCT ps; //создаём контекст устройства

	switch (msg) {
	case WM_CREATE:
		/* при создании окна внедряем в него кнопочку */

		break;


	case WM_PAINT:

	{
					 hDC = BeginPaint(hw, &ps);

					 FillRect(hDC, &s, BrushB);
					 SelectObject(hDC, Brush1);
					 SelectObject(hDC, Pen1);

					 float mltY = 10.0f;
					 float mltX = 3.0f;

					 //отрисовка гистограммы
					 float D = 0.5f;
					 float T = N;
					 for (int i = 0; i < NS; i += 2)
					 {
						 float v1 = (hdf[i] + hdf[i + 1]) * 0.5f;
						 int rx = ((i * mltX - (mltX - 1) * N) * s.right) / NS;
						 int rx2 = (((i + 2)  * mltX - (mltX - 1) * N) * s.right) / NS;

						 Rectangle(hDC, rx, (int)(s.bottom - mltY * v1 * s.bottom), rx2, s.bottom);
					 }

					 //отрисовка графика
					 SelectObject(hDC, PenG);
					 for (int i = 0; i < NS; i++)
					 {
						 float x = (i - N) * 1.0f;
						 float vg = 1 / sqrtf(4 * 3.14159f * D * T) * expf(-x * x / (4 * D * T));
						 int rx = ((i  * mltX - (mltX - 1) * N) * s.right) / NS;
						 if (i == 0)
						 {
							 MoveToEx(hDC, rx, (int)(s.bottom - mltY * vg * s.bottom), NULL);
						 }
						 else {
							 LineTo(hDC, rx, (int)(s.bottom - mltY * vg * s.bottom));
						 }
					 }

					 EndPaint(hw, &ps);

					 break;
	}


	case WM_COMMAND:
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hw, msg, wp, lp);
}

