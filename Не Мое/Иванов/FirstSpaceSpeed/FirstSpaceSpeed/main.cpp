#include "afxwin.h"						
#include "afxext.h"	
#define _USE_MATH_DEFINES
#include <cmath>

const long double GM = 398600.4418e+9;

int rd(long double u){
	return (int) (u + 0.5);
};

long double r(long double x, long double y){
	return sqrtl(x*x + y*y);
};

long double g(long double x, long double y){
	long double R = r(x,y);
	return GM / R / R;
};

class CMainWnd : public CFrameWnd
{

public:
	CMainWnd();
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();

private:
	DECLARE_MESSAGE_MAP();
};

BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CMainWnd::OnPaint()
{
	long double x = 0, y = 6.3568e+6, vx = 8.0e+3, vy = 0.0, ax = 0.0, ay = -g(x, y);
	const long double a = 6.3781e+6, b = 6.3568e+6;
	CPaintDC dc(this);
	RECT rect;
	GetClientRect(&rect);
	long double xs = rect.right; //Ширина окна
	long double ys = rect.bottom; //Высота окна
	long double h = 0.01;
	long double cosinus, sinus;
	long double max = 1.6e+7;
	CPen Line(PS_SOLID, 1, RGB(0, 0, 0));
	dc.Ellipse(rd(xs / 2.0 - ys / 2.0*a / max), rd(ys / 2.0 - ys / 2.0*b / max), rd(xs / 2.0 + ys / 2.0*a / max), rd(ys / 2.0 + ys / 2.0*b / max));
	//Сетка
	dc.SelectObject(Line);
	dc.MoveTo(0, rd(ys / 2));
	dc.LineTo(rd(xs), rd(ys / 2));
	dc.MoveTo(rd(xs / 2), 0);
	dc.LineTo(rd(xs / 2), rd(ys));
	long double phi = (1+sqrtl(5.0)) / 2.0;
	long double m = 0.0, n = 12.0e+3;
	unsigned long long i = 1;
	long double y1, y2;
	long double vmin = 0.0, vstart;
	while (fabsl(n-m)>10.0){
		if (vmin > m)
			m = vmin;
		if (i % 2 != 0){
			vx = m + (n - m) / 3.0;
			vstart = vx;
		}
		else{
			vx = n - (n - m) / 3.0;
			vstart = vx;
		}
		x = 0, y=6.3569e+6, vy = 0.0, ax = 0.0, ay = -g(x, y);
		dc.MoveTo(rd(xs / 2), rd(ys / 2.0 *(1.0 - y / max)));
		while (x >= 0){
			cosinus = -x / r(x, y);
			sinus = -y / r(x, y);
			x += (h*vx + ax*h*h / 2);
			y += (h*vy + ay*h*h / 2);
			ax = g(x, y)*cosinus;
			ay = g(x, y)*sinus;
			vx += h*ax;
			vy += h*ay;
			dc.LineTo(rd(xs / 2 + ys / 2.0*x / max), rd(ys / 2.0*(1.0 - y / max)));
			if (x*x / a / a + y*y / b / b <= 1){
				vmin = vstart;
				break;
			}
		}
		if (i % 2 != 0)
			y1 = y;
		else{
			y2 = y;
			if (y1 < y2)
				m = vstart;
			else if (vstart>vmin)
				n = vstart;
		}
		while (x <= 0){
			cosinus = -x / r(x, y);
			sinus = -y / r(x, y);
			x += (h*vx + ax*h*h / 2);
			y += (h*vy + ay*h*h / 2);
			ax = g(x, y)*cosinus;
			ay = g(x, y)*sinus;
			vx += h*ax;
			vy += h*ay;
			dc.LineTo(rd(xs / 2 + ys / 2.0*x / max), rd(ys / 2.0*(1.0 - y / max)));
			if (x*x / a / a + y*y / b / b <= 1){
				vmin = vstart;
				break;
			}
		}
		i++;
	}
	long double speed = vstart;
	CString s;
	s.Format(L"Первая космическая скорость для данного тела равна %0.2Lf км/с",speed/1000);
	dc.TextOutW(5,5,s);
}
		/*long double v = 9.0e+3;
	long double yz=0.0;
	int i = 1;
	while (fabsl(yz - b) / b > 0.001){
		dc.MoveTo(rd(xs / 2), rd(ys / 2-b));
	while((fabsl(a-x)>0.01)&&(x>0)&&(y>0)){
		x = 0, y = 6.371e+6, vx=v, vy = 0.0, ax = 0.0, ay = -g(x, y);

	}
	//for (long double t = 0; t < 10000; t += h){
	cosinus = -x / r(x, y);
	sinus = -y / r(x, y);
	x += (h*vx + ax*h*h / 2);
	y += (h*vy + ay*h*h / 2);
	ax = g(x, y)*cosinus;
	ay = g(x, y)*sinus;
	vx += h*ax;
	vy += h*ay;
	if ((fabsl(x) < 1) && (y < 0))
	yz = y;
	if (i < 2)
	vz = v;
	else{
	if ((xc != xz) && (v != vz)){
	long double vt = v;
	v -= (xc - l)*(v - vz) / (xc - xz);
	xz = xc;
	vz = vt;
	}
	}
	dc.LineTo(rd(xs / 2 + ys / 2.0*x / max), rd(ys / 2.0*(1.0 - y / max)));
	}
	}*/

int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)  return -1;
	return 0;
}

CMainWnd::CMainWnd()
{
	int x = 1024, y = 600;
	RECT rect;
	rect.left = 0, rect.right = x; rect.top = 0; rect.bottom = y;
	Create(NULL, L"Первая космическая. Иванов Сергей. 254 группа.", WS_OVERLAPPEDWINDOW, rect, NULL, NULL);
}

class CMyApp : public CWinApp
{

public:
	CMyApp();
	virtual BOOL InitInstance();
};

CMyApp::CMyApp()
{}

BOOL CMyApp::InitInstance()
{
	m_pMainWnd = new CMainWnd();
	ASSERT(m_pMainWnd);
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
};

CMyApp theApp;