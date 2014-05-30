#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>


int Sred = 100; // количество опытов для каждого N
int NN = 400; // max N
int ky1 = 20;

static const int T = 50; //время блуждания(гистограмма) 
int NG = 10000; //сколько частиц запускаем (гистограмма)
int ky2 = 10000;

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
		WS_OVERLAPPEDWINDOW, 10, 10, 1510, 700,
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

	//рисуем оси
	MoveToEx(hdc, 50, 500, NULL);
	LineTo(hdc, 360, 500);

	MoveToEx(hdc, 50, 500, NULL);
	LineTo(hdc, 50, 250);

	f1 = fopen("vozvr(N).txt", "wt");
	f2 = fopen("A[i].txt", "wt");
	f3 = fopen("x.txt", "wt");

			HPEN BlackPen1, BlackPen2, RedPen, GreenPen, BluePen;

			BlackPen1=CreatePen(PS_SOLID,3,RGB(0,0,0));
			BlackPen2=CreatePen(PS_SOLID,2,RGB(0,0,0));
			RedPen=CreatePen(PS_SOLID,3,RGB(150,0,0));
			GreenPen=CreatePen(PS_SOLID,1,RGB(0,150,0));
			BluePen=CreatePen(PS_SOLID,2,RGB(0,0,150));

			int A[T] = {0};
			double w, s = 50;
			int x = 0, vozvr = 0;
		// гуляем
			MoveToEx(hdc, 50, 500, NULL);
			for (int N = 1; N <= NN; N++)
			{
				vozvr = 0;
				for (int sred = 1; sred <= Sred; sred++)
				{
					x = 0;	
					for (int t = 0; t <= N; t++)
					{		
						w = rand()/double(32767);

						if(w < 0.5)
							x++;
						if(w > 0.5)
							x--;

						if (x == 0)
							vozvr++;
					}				
				}
			//Рисуем зависимость (vozvr от N)
				s += 300/double(NN);
				LineTo(hdc, int(s), 500 - ky1*vozvr/Sred);
				fprintf(f1, "%d  %d\n", N, vozvr/Sred);
			}
			
			// Гистограмма
			int time = 0; //время на положит. полуоси
			for (int i = 1; i <= NG; i++)
			{
				time = 0;
				x = 0;
				for (int t = 1; t < T; t++)
				{
					w = rand()/double(32767);

						if(w < 0.5)
							x++;
						if(w > 0.5)
							x--;		

					if (x > 0)
						time++;
				}
				A[time]++;
			}
			
			int l = 600 / T;
			x = 600;
			
			for (int i = 0; i < T; i++)
			{
				for (int j = 0; j < l; j++)
				{
					MoveToEx(hdc, x, 500, NULL);
					LineTo(hdc, x++, 500 - int(ky2*A[i]/double(NG)));
				}
			}
			
//распечатываем массив

	for (int i = 0; i <= T; i++)
	{
		fprintf (f2,"%d  %f\n", i, A[i]/double(NG));
	}



//рисуем точное решение

	SelectPen(hdc,RedPen);
	
	MoveToEx(hdc, 600, 0, NULL );
	for(x = 600; x <= 1200; x++)
	{
		LineTo(hdc, x, 500 - ky2/T/3.1415/sqrt((double(x)/600 - 1)*(2-double(x)/600)) );
	}

		
//  End of User code for paint and calculation
//-----------------------------------------------------

	EndPaint(hwnd,&ps);
}

void OnDestroy(HWND) {
	PostQuitMessage(0);
}
