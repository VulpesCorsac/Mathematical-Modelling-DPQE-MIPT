#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <map>

//#include <iterator>

using namespace std;

double pp(int);

double N = 100000, delta = 0.2, pi = 3.14159, e = 2.718281828459045, ky = 0.05;
int t0 = 200, a = 1, kx = 3, tu = 1;

FILE *f1, *f2, *f3;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void OnPaint(HWND);
void OnDestroy(HWND);

int WINAPI WinMain(HINSTANCE hInst,HINSTANCE,LPSTR,int) {
	char szClassName[]="MainWindow";
	char szTitle[]="list";  //window header, defined by User
	MSG Msg;
	WNDCLASS wc;

	ZeroMemory(&wc,sizeof(wc));
	wc.lpfnWndProc=WndProc;
	wc.hInstance=hInst;
	wc.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	wc.hCursor=LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground=GetStockBrush(WHITE_BRUSH);
	wc.lpszClassName=szClassName;
	RegisterClass(&wc);

	HWND hwnd=CreateWindow(szClassName, szTitle, 
		WS_OVERLAPPEDWINDOW, 0, 0, 1510, 700,
		HWND_DESKTOP, NULL, hInst, NULL);
	ShowWindow(hwnd,SW_SHOWNORMAL);

	while(GetMessage(&Msg,NULL,0,0))
		DispatchMessage(&Msg);

	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, 
		WPARAM wParam, LPARAM lParam) {
	switch(msg) {
		HANDLE_MSG(hwnd,WM_PAINT,OnPaint);
		HANDLE_MSG(hwnd,WM_DESTROY,OnDestroy);
	default:
		return(DefWindowProc(hwnd,msg,wParam,lParam));
	}
}


void OnPaint(HWND hwnd) {
	PAINTSTRUCT ps;
	HDC hdc=BeginPaint(hwnd,&ps);
//-----------------------------------------------------
//  User code for paint and calculation
//

	f3 = fopen("x.txt", "wt");

			HPEN BlackPen1, BlackPen2, RedPen, GreenPen, BluePen;

			BlackPen1=CreatePen(PS_SOLID,3,RGB(0,0,0));
			BlackPen2=CreatePen(PS_SOLID,2,RGB(0,0,0));
			RedPen=CreatePen(PS_SOLID,3,RGB(150,0,0));
			GreenPen=CreatePen(PS_SOLID,1,RGB(0,150,0));
			BluePen=CreatePen(PS_SOLID,2,RGB(0,0,150));
			
			double D = (a*a*(1-4*delta*delta))/(2*tu);
			double v = (delta*2*a)/tu;
			int i, t = 0, x = 0, s = 0, c = 0;
			double w, ww, p, sred = 0;

			map <int,int> M;

			p = 0.5 + delta;

		// гуляем
			for (i = 1; i <= N; i++)
			{
				x = 0;
				t = 0;
				while(t != t0)
				{
					w = rand()/double(32767);

					if(w < p)
						x = x + a;
					if(w > p)
						x = x - a;
					t = t + tu;					
				}
				sred+=(x-v*t)*(x-v*t);
				M[x]++;
			}
			fprintf(f3, "выборочное среднее: %f\n точное: %f\n", sred/double(N),2*D*t);

//построение гистограммы
		int temp=0;
		for (map <int,int>::iterator it = M.begin(); it != M.end(); it++)
		{
			if (it->first % 2)
				temp = it->second;
			else 
			{
				for (x = 500 + (it->first - 1)*2*a*kx; x <= 500 + (it->first + 1)*2*a*kx; x++)
				{
					MoveToEx(hdc, x, 500, NULL);
					LineTo(hdc, x, 500 - ky*(it->second + temp));
				}
			}
		}
		


//распечатываем массив
/*
	for (i = 0; i <= 225; i++)
	{
		fprintf (f1,"%d  %d\n", i, A[i]);
		fprintf (f2,"%d  %d\n", i, B[i]);
	}
*/
//рисуем оси
	MoveToEx(hdc, 100, 500, NULL);
	LineTo(hdc, 900, 500);

	MoveToEx(hdc, 500, 200, NULL);
	LineTo(hdc, 500, 600);

//рисуем точное решение

	SelectPen(hdc,RedPen);
	
	MoveToEx(hdc, 100*a, 500, NULL );
	for(x = -400*a; x <= 400*a; x+=a)
	{
		LineTo(hdc, kx*x + 500, 500 - 4*ky*N*pp(x));
	}
		
//  End of User code for paint and calculation
//-----------------------------------------------------

	EndPaint(hwnd,&ps);
}

void OnDestroy(HWND) {
	PostQuitMessage(0);
}

double pp(int x)
{
	double D = (4*a*a*(1-4*delta*delta))/(2*tu);
	double v = (delta*4*a)/tu;
	return(1/pow(4*pi*D*t0, 0.5)*pow(e,-(x-v*t0)*(x-v*t0)/(4*D*t0)) );
}