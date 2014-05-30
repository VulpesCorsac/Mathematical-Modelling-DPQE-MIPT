#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <stdlib.h>

#define L 10 // размер решетки
double p = 0.4; // вероятность
int n = 1000; // число туров
int GG = 100; //менять если нужна статистика

int edin=0, polovina=0, nul=0;
double ky = 300;
	FILE *f1, *f2, *f3, *f4;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void OnPaint(HWND);
void OnDestroy(HWND);

void vivod (int*);

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
		WS_OVERLAPPEDWINDOW, 10, 10, 1010, 700,
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

		HPEN BlackPen1, BlackPen2, RedPen, GreenPen, BluePen;

			BlackPen1=CreatePen(PS_SOLID,3,RGB(0,0,0));
			BlackPen2=CreatePen(PS_SOLID,2,RGB(0,0,0));
			RedPen=CreatePen(PS_SOLID,3,RGB(150,0,0));
			GreenPen=CreatePen(PS_SOLID,1,RGB(0,150,0));
			BluePen=CreatePen(PS_SOLID,2,RGB(0,0,150));
//-----------------------------------------------------
//  User code

	//оси
	MoveToEx(hdc, 50, 505, NULL);
	LineTo(hdc, 50, 100);
	
	MoveToEx(hdc, 45, 500, NULL);
	LineTo(hdc, 900, 500);


	f1 = fopen("rezults.txt", "wt");
	f2 = fopen("tablica.txt", "wt");
	f4 = fopen("rezults2.txt", "wt");

	int i, g, j, ww, za = 0, protiv = 0, t, ii;
	double w, kx;
	kx = 800/double(n);
	int A[L+3][L+3] = {0};
	int Anext[L+3][L+3] = {0};

	srand (time(0));

	for (g=1; g<= GG; g++)
	{
	//первый тур///


	for (i = 1; i <= L; i++)
		for (j = 1; j <= L; j++)
		{
			w = rand()/double(32767);
			
			if(w < p)
				A[i][j] = 1;
			else
				 A[i][j] = 0;
			
			if (A[i][j] == 1)
				za++;
	
		}
		vivod(&A[1][1]);

		MoveToEx(hdc, 50, 500 - ky*za/double(L*L), NULL);

	//стенки

		for (i = 1; i <= L; i++)
		{
			A[0][i] = A[L][i];
			A[L+1][i] = A[1][i];
			A[i][0] = A[i][L];
			A[i][L+1] = A[i][1];
		}
	// новые туры	
	for (t = 2; t <= n; t++) 
	{
		za = 0;

	for (i = 1; i <= L; i++)
		for (j = 1; j <= L; j++)
		{
			ww = rand()%4;
			if (ww == 0)
			{
				Anext[i][j] = A[i-1][j];
			}
			else if (ww == 1)
			{
				Anext[i][j] = A[i][j-1];
			}
			else if (ww == 2)
			{
				Anext[i][j] = A[i+1][j];
			}
			else if (ww == 3)
			{
				Anext[i][j] = A[i][j+1];
			}
	
			}
		//стенки новые
		for (i = 1; i <= L; i++)
		{
			Anext[0][i] = Anext[L][i];
			Anext[L+1][i] = Anext[1][i];
			Anext[i][0] = Anext[i][L];
			Anext[i][L+1] = Anext[i][1];
		}
		for (i = 0; i <= L+1; i++)
		for (j = 0; j <= L+1; j++)
		{
			// записываем новые данные в старый массив
				A[i][j]=Anext[i][j];
		}
		//вывод массива
		for (i = 1; i <= L; i++)
			for (j = 1; j <= L; j++)
			{		
				if(A[i][j] == 1)
				za++;
			}
		
		if(g == GG)	
		{
			vivod(&A[1][1]);
			fprintf (f1, "za: %f\n", za/double(L*L));
			LineTo(hdc, 50 + kx*t, 500 - ky*za/double(L*L) );
		}
	}
	
	if (abs(za/double(L*L) - 1) < 0.000001)
		edin++;
	if (abs(za/double(L*L) - 0.5) < 0.000001)
		polovina++;
	if (abs(za/double(L*L)) < 0.000001)
		nul++;

	
	}	
	fprintf (f4, "1: %d\n1/2: %d\n0: %d\n", edin, polovina, nul);
	
	SelectPen(hdc,GreenPen);
//		MoveToEx(hdc, 50, 500 - ky, NULL);
//		LineTo(hdc, 800, 500 - ky);


//
//  End of User code
//-----------------------------------------------------

	EndPaint(hwnd,&ps);
}

void OnDestroy(HWND) {
	PostQuitMessage(0);
}

void vivod (int *t)
{
	for (int i = 1; i <= L; i++)
		for (int j = 1; j <= L; j++)
		{
			fprintf (f2,"%d ", *t++);
			if (j == L) t+=3;
			if (j == L) fprintf (f2,"\n");	
		}
	fprintf (f2,"\n");
}