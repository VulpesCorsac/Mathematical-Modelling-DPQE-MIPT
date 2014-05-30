#include "afxwin.h"						
#include "afxext.h"	
#define _USE_MATH_DEFINES
#include <cmath>

#define IDC_MYBUTTON 100 //Кнопка
#define IDC_MYEDIT1 101 //Альфа среды
#define IDC_MYEDIT2 102 //Расстояние до цели

long double A = 0.2, R = 6371e+3, g0 = (398574e+9)/R/R, gmax=g0, H, l = 2.0/*2*M_PI*R*/;

int rd(long double u){
	return (int) (u + 0.5);
};

long double m = 1.0, d;
long double xz, vz;

long double g(long double r){
	long double n = R/(R+r);
	return g0*n*n;
};

long double alpha(long double y){
	return A*expl(1.0-y/(118e+3));
}

long double ax(long double vnapr, long double y, long double v){
	return alpha(y) / m*v*vnapr;
};

long double ay(long double vy, long double y, long double v){
	return g(y)+d*ax(vy,y,v);
};

class CMainWnd : public CFrameWnd
{
	void press(){
		CString value;
		GetDlgItemText(IDC_MYEDIT1, value);
		A = _ttof(value);
		GetDlgItemText(IDC_MYEDIT2, value);
		l = _ttof(value);
		this->InvalidateRect(0);
	}

public:
	CMainWnd();
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();

private:
	CButton* MyButton;	// Указатель на объект кнопка
	CEdit* MyEdit1;
	CEdit* MyEdit2;
	DECLARE_MESSAGE_MAP();			
};

BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd) 
	ON_WM_CREATE()						   
	ON_WM_PAINT()
	ON_COMMAND(IDC_MYBUTTON, press)
END_MESSAGE_MAP()

void CMainWnd::OnPaint()
{
	long double x, y;
	long double p = (1.0 + sqrtl(5.0)) / 2.0;
	CPaintDC dc(this);
	RECT rect;
	GetClientRect(&rect);
	x = rect.right; //Ширина окна
	y = rect.bottom; //Высота окна
	dc.FillSolidRect(0,0,rd(x),rd(y),RGB(224,255,255));
	long double v = 5.0;
	long double xmax = v*v / g(0.0), ymax = v*v / 2.0 / g(0.0);
	//long double xmax = 1000, ymax = 1000;
	long double a = 0.0, b = M_PI_2;
	long double phi;
	long double x1, x2;
	long double vf;
	CPen Line(PS_SOLID, 3, RGB(0, 0, 0));
	dc.SelectObject(Line);
	for (unsigned long long i = 1; i <= 60; i++){
		if (i % 2 != 0)
			phi = b - (b - a) / p;
		else
			phi = a + (b - a) / p;
		d = 1.0;
		long double xc = 0.0, vxc = v*cosl(phi), xn, vxn;
		long double yc = 0.0, vyc = v*sinl(phi), yn, vyn;
		long double t = 0, h = 0.00005;
		long double k1, k2, k3, k4, q1, q2, q3, q4;
		
		//Метод Рунге-Кутты
		dc.MoveTo(rd(x), rd(y));
		while (yc >= 0){
			if (vyc < 0)
				d = -1.0;
			vf = sqrtl(vxc*vxc+vyc*vyc);
			q1 = h*ay(vyc, yc, vf);
			q2 = h*ay(vyc + q1 / 2.0, yc, vf);
			q3 = h*ay(vyc + q2 / 2.0, yc, vf);
			q4 = h*ay(vyc + q3, yc, vf);
			vyn = vyc - d*(q1 + 2.0*q2 + 2.0*q3 + q4) / 6.0;
			yn = yc + d*h*vyc;

			k1 = h*ax(vxc, yc, vf);
			k2 = h*ax(vxc + k1 / 2.0, yc, vf);
			k3 = h*ax(vxc + k2 / 2.0, yc, vf);
			k4 = h*ax(vxc + k3, yc, vf);
			vxn = vxc - (k1 + 2.0*k2 + 2.0*k3 + k4) / 6.0;
			xn = xc + h*vxc;
			if (i<13)
				dc.LineTo(rd(x*xc / xmax), rd(y*(1.0 - yc / ymax)));
			yc = yn;
			vyc = vyn;
			xc = xn;
			vxc = vxn;
			t += h;
		}
		if (i % 2 != 0)
			x1 = xc;
		else{
			x2 = xc;
			if (x1 <= x2)
				a = b - (b - a) / p;
			else
				b = a + (b - a) / p;
		}
	}
	long double angle = phi;
	CString s;
	s.Format(L"%.2Lf", angle*45.0/M_PI_4);
	
	//Стрельба в мишень
	CPen Line2(PS_SOLID, 2, RGB(0, 0, 255));
	dc.SelectObject(Line2);
	dc.FillSolidRect(0,0,rd(x),rd(y), RGB(224, 255, 255));
	dc.TextOutW(5, 5, "Оптимальный для стрельбы угол - " + s + " градусов");
	xmax = l*1.5;
	ymax = l*tanl(angle)/2.0;
	dc.FillSolidRect(rd(x*l / xmax) - 5, rd(y) - 10, 10, 10, RGB(255, 0, 0));
	dc.FillSolidRect(0, 0, 1, 1, RGB(224, 255, 255));
	v = sqrtl(l*g(0.0)/sinl(2.0*angle));
	xz = 0.0;
	int i = 1;
	while(fabsl(1.0-xz/l)>0.001){
		if (i == 2)
			v *= l/xz;
		d = 1.0;
		long double xc = 0.0, vxc = v*cosl(angle), xn, vxn;
		long double yc = 0.0, vyc = v*sinl(angle), yn, vyn;
		long double t = 0, h = 0.0001;
		long double k1, k2, k3, k4, q1, q2, q3, q4;
		long double vstart = 0.0;

		//Метод Рунге-Кутты
		dc.MoveTo(rd(x), rd(y));
		while (yc >= 0){
			if (vyc < 0){
				d = -1.0;
				H = yc;
				gmax = g(H);
				vstart = v;
			}
			q1 = h*ay(vyc, yc, vf);
			q2 = h*ay(vyc + q1 / 2.0, yc, vf);
			q3 = h*ay(vyc + q2 / 2.0, yc, vf);
			q4 = h*ay(vyc + q3, yc, vf);
			vyn = vyc - d*(q1 + 2.0*q2 + 2.0*q3 + q4) / 6.0;
			yn = yc + d*h*vyc;

			k1 = h*ax(vxc, yc, vf);
			k2 = h*ax(vxc + k1 / 2.0, yc,vf);
			k3 = h*ax(vxc + k2 / 2.0, yc, vf);
			k4 = h*ax(vxc + k3, yc, vf);
			vxn = vxc - (k1 + 2.0*k2 + 2.0*k3 + k4) / 6.0;
			xn = xc + h*vxc;

			dc.LineTo(rd(x*xc / xmax), rd(y*(1.0 - yc / ymax)));
			yc = yn;
			vyc = vyn;
			xc = xn;
			vxc = vxn;
			t += h;
		}
		if (i < 2){
			xz = xc;
			vz = v;
		}
		else{
			if ((xc != xz) && (v != vz)){
				long double vt = v;
				v -= (xc - l)*(v - vz) / (xc - xz);
				xz = xc;
				vz = vt;
			}
		}
		s.Format(L"Расстояние выстрела - %.1Lf м, промах на %.1Lf процентов. Высота подъёма - %.1Lf м, g=%.3Lf м/c^2. Стартовая скорость - %.0Lf м/с", xz, fabsl(1-xz/l)*100, H, gmax, vstart);
		dc.TextOutW(5, 35+25*i, s);
		i++;
	}
		s.Format(L"%.2Lf", v);
		dc.TextOutW(5, 35, "Скорость, необходимая для попадания в тело, равна "+ s +"м/с");
}

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
	Create(NULL, L"Стрельба из пушки. Иванов Сергей. 254 группа.", WS_OVERLAPPEDWINDOW, rect, NULL, NULL);
	//CreateWindowW(NULL, L"Стрельба из пушки. Иванов Сергей. 254 группа.", WS_MAXIMIZE, rectDefault, NULL, NULL);
	MyEdit1 = new CEdit();
	if (MyEdit1 != NULL) MyEdit1->Create(WS_CHILD | WS_VISIBLE | SS_CENTER,
		CRect(x-210,0,x-110,20), this, IDC_MYEDIT1);
	MyEdit2 = new CEdit();
	if (MyEdit2 != NULL) MyEdit2->Create(WS_CHILD | WS_VISIBLE | SS_CENTER,
		CRect(x-100, 0, x, 20), this, IDC_MYEDIT2);
	MyButton = new CButton();
	if (MyButton != NULL) MyButton->Create(L"Перестроить", WS_CHILD | WS_VISIBLE | SS_CENTER,
		CRect(x-170, 30, x-40, 60), this, IDC_MYBUTTON);
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