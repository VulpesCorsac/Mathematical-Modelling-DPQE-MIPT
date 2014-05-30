#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex>
#include <iostream>
#include <time.h>
using namespace std;
double twopi=6.28318530717958;
double ky = 100;
int nx = 1024;
int T=1;
double L = 16;
int const NDIM=2049;
complex <double>  y[NDIM] = {0};
complex <double> ym[NDIM] = {0};
void ffta(int nx,  complex <double>* y, int key);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL OnCreate(HWND,LPCREATESTRUCT);
void OnPaint(HWND);
void OnDestroy(HWND);
double func(double x);     //prototype of the User function
int isx = 1200;
int isy = 700;
HPEN hBlackPen, hRedPen, hGreenPen, hBluePen;
int WINAPI WinMain(HINSTANCE hInst,HINSTANCE,LPSTR,int)
{
	char szClassName[]="MainWindow";
	char szTitle[]="Zadacha №44";  //window header, defined by User
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
		WS_OVERLAPPEDWINDOW, 10, 10, isx, isy,
		HWND_DESKTOP, NULL, hInst, NULL);
	ShowWindow(hwnd,SW_SHOWNORMAL);

	while(GetMessage(&Msg,NULL,0,0))
		DispatchMessage(&Msg);

	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, 
		WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		HANDLE_MSG(hwnd,WM_CREATE,OnCreate);
		HANDLE_MSG(hwnd,WM_PAINT,OnPaint);
		HANDLE_MSG(hwnd,WM_DESTROY,OnDestroy);
	default:
		return(DefWindowProc(hwnd,msg,wParam,lParam));
	}
}

BOOL OnCreate(HWND,LPCREATESTRUCT)
{
	hBlackPen=CreatePen(PS_DASH,1,RGB(0,0,0));
	hRedPen=CreatePen(PS_SOLID,1,RGB(150,0,0));
	hGreenPen=CreatePen(PS_SOLID,2,RGB(0,150,0));
	hBluePen=CreatePen(PS_SOLID,1,RGB(0,0,150));
	return TRUE;
}

void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc=BeginPaint(hwnd,&ps);
//-----------------------------------------------------
//  User code
	SelectPen(hdc, hRedPen);
	char stnum[20];
	int m,nxm1;
	double tau, a=5, alpha=0.2, f0=1;
	complex <double>  ci(0.0,1.0);
	complex <double>  di(0.0,-1.0);
	FILE *f1, *f2, *f3;
	f1 = fopen ("начальные данные.txt", "wt");
	f2 = fopen ("коэффициенты Фурье.txt", "wt");
	f3 = fopen ("сравнение.txt", "wt");
	tau = L/nx;
	nxm1=nx-1;
	// Задание сетки
	//MoveToEx(hdc, 50, 200, NULL);
	for (m=0; m<=nxm1; m++)
	{
		m=m-nx/2;
		y[m+nx/2] = exp(-pow(m*tau/a, 10))* cos( twopi*(1-alpha*pow(m*tau/a, 2))*m*tau );
		ym[m+nx/2]=y[m+nx/2];
		fprintf (f1, "%d  (%8.4f,%f)\n", m+nx/2, real(y[m+nx/2]), imag(y[m+nx/2]));
		//LineTo(hdc, 600+m, 200 - real(y[m+nx/2])*ky);
		m=m+nx/2;
	 }
	// Прямое преобразование Фурье
	ffta(nx,y,0);
	for (m=0; m<=nxm1; m++)
	{
		  y[m]=y[m]/(double)nx;
	 }
	y[0]=0;
	for (m = 1; m < nx/2; m++)
	{
		y[m]=di*y[m];
	}
	for (m = nx/2; m <= nx-1/2; m++)
	{
		y[m]=ci*y[m];
	}
	// Обратное преобразованеи Фурье
	ffta(nx,y,1);
	//MoveToEx(hdc, 50, 500, NULL);
	for (m=0; m<=nxm1; m++)
	{
		m=m-nx/2;
		//LineTo(hdc, 600+m, 500 - real(y[m+nx/2])*ky);
		m=m+nx/2;
	 }
	fprintf(f3, "№   ампл.т. ампл.э. фаза.т. фаза.э.\n");
	MoveToEx(hdc, 50, 200, NULL);
	for (m=0; m<=nxm1; m++)
	{
		m=m-nx/2;
		double A=exp(-pow(m*tau/a, 10));
		double B=cos( twopi*(1-alpha*pow(m*tau/a, 2))*m*tau );
			 double a;
			 a=sqrt(abs (y[m+nx/2]) * abs (y[m+nx/2])
				 +abs (ym[m+nx/2]) * abs (ym[m+nx/2]) );
			 fi=ar
			 fprintf(f3, "%3d   %5.3f %5.3f %8.3f %5.3f\n", m+nx/2, A, a, B, abs(ym[m+nx/2])/a);
			 LineTo(hdc, 600+m, 200 - a*ky);
			 LineTo(hdc, 600+m, 200 - A*ky);
			 m=m+nx/2;
	}
	MoveToEx(hdc, 50, 500, NULL);
		for (m=0; m<=nxm1; m++)
		{
		m=m-nx/2;
		double B=twopi*(1-alpha*pow(m*tau/a, 2))*m*tau;
				double A=exp(-pow(m*tau/a, 10));

					 double a;
			 a=sqrt(abs (y[m+nx/2]) * abs (y[m+nx/2]) + abs (ym[m+nx/2]) * abs (ym[m+nx/2]) );
		
		
	    LineTo(hdc, 600+m, 500-atan2(real(ym[m+nx/2])/A, real(y[m+nx/2])/A)*6);
		while ((B<0)&&(B<-twopi/2))
		{
			B=B+twopi;
		}
		while (B>twopi/2)
		{
			B=B-twopi;
		}
	    LineTo(hdc, 600+m, 500-B*6);
	    m=m+nx/2;
		}


	// Построение осей
	SelectPen(hdc, hBlackPen);
	MoveToEx(hdc, 600, 650, NULL);
	LineTo(hdc, 600, 50);
	MoveToEx(hdc, 50, 200, NULL);
	LineTo(hdc, 1120, 200);
	MoveToEx(hdc, 50, 500, NULL);
	LineTo(hdc, 1120, 500);
	//
	//  End of User code
	//-----------------------------------------------------
	EndPaint(hwnd,&ps);
}

void OnDestroy(HWND)
{
	PostQuitMessage(0);
}

void ffta(int nx,  complex <double>* y, int key)
{
	 int kl,le,le2,le21,ml,ml1,n2,l2n,l2nm1,ii,ji,ic,ip,nxm1,nxm2;
	 double angle,sft,twopi;
	 complex <double> zt1,zt2,cwj;
	 complex <double> ci(0.0,1.0);

	 twopi=6.28318530717958;
	 nxm1=nx-1;

		ii=0;
		ji=1;
	 while (ji < nx) {
		ii+=1;
		ji*=2;
	 }
		l2n=ii;
		l2nm1=l2n-1;

		n2=nx/2;

	 if (key == 0)
		sft=-1.;
	 else
		sft=1.;
	 for (kl = 0; kl <= l2nm1; kl++) {
		  le = 1 << (l2n-kl);
		  le2=le/2;
		  le21=le2-1;
		  ml=nx/le;
		  ml1=ml-1;
		for (ji = 0; ji <= le21; ji++) {
			 angle=twopi*(double)ml*(double)ji/(double)nx;
			 cwj = cos(angle) + ci*sft*sin(angle);
		  for (ic = 0; ic <= ml1; ic++) {
			 ii=ji+ic*le;
			 ip=ii+le2;
			 zt1=y[ii];
			 zt2=y[ip];
			 y[ii]=zt1+zt2;
			 y[ip]=(zt1-zt2)*cwj;
		  }
		}
	 }

		nxm2=nx-2;
		ji=0;
	 for (ii = 1; ii <= nxm2; ii++) {
		  ip = n2;
		while (ip < ji+1) {
		  ji=ji-ip;
		  ip=ip/2;
		}
		  ji=ji+ip;
		if (ii < ji) {
		  cwj=y[ji];
		  y[ji]=y[ii];
		  y[ii]=cwj;
		}
	 }
}