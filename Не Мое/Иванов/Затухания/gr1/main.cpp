#include "afxwin.h"						
#include "afxext.h"						
#include <cmath>

#define IDC_MYBUTTON 100
#define IDC_MYEDIT1 101
#define IDC_MYEDIT2 102
#define IDC_MYEDIT3 103
#define IDC_MYEDIT4 104

//x''+A*x'+w^2*x=F(t)

long double w = 20.0, A = 2.0, x0 = 1.0, v0 = 2.0;
int x, y;

long double ft(long double t){
	return 2*t;
};

long double fv(long double t, long double x, long double v){
	return ft(t)-A*v - w*w*x;
};

//Аналитические решения для координаты и скорости
long double fxr(long double t){
	//return expl(-t)*(5.0 * sqrtl(2.0)*sinl(2.0 * sqrtl(2.0)*t) + 12.0 * cosl(2.0 * sqrtl(2.0)*t))/4.0;
	long double D = A*A - 4 * w*w;
	if (D < 0)
		if ((w == 3.0)&&(A == 2.0)&&(x0 == 3.0)&&(v0 == 2.0))
			return expl(-t)*(5.0 * sqrtl(2.0)*sinl(2.0 * sqrtl(2.0)*t) + 12.0 * cosl(2.0 * sqrtl(2.0)*t)) / 4.0;
		else
			/*if ((w == 10.0)&&(A == 2.0)&&(x0 == 3.0)&&(v0 == 2.0))
				return expl(-t)*(5.0*sqrtl(11.0)*sinl(3.0*sqrtl(11.0)*t) + 99.0*cos(3.0*sqrtl(11.0)*t)) / 33.0;
			else*/	
				return NULL;
		//D = sqrtl(-D);
		//return 2*vc*sinl(t*D/2.0)/D/expl(A*t/2.0)+A*xc*expl(A*t/2.0)*sinl(t*D/2.0)/D+xc*expl(A*t/2.0)*cosl(t*D/2.0);
	else{
		D = sqrtl(D);
		return (2.0*v0*(expl(t/2.0*(D-A))-expl(-t/2.0*(D-A)))+A*x0*(expl(t/2.0*(D+A))-expl(-t/2.0*(D+A)))+x0*D*(expl(t/2.0*(D+A))+expl(-t/2.0*(D+A))))/((long double)2.0*D);
	}
	//complex <long double> S(A*A-4*w*w, 0.0);
	//complex <long double> D = sqrt(S);
	//return (2.0*vc*expl(t *(D - A)/ 2.0) - 2.0*vc*expl(-t*(D + A) / 2.0) - A*xc*expl(-t*(D + A) / 2.0) + A*xc*expl(t*(D + A) / 2.0) + xc*D*expl(-t*(D + A) / 2.0) + xc*D*expl(t*(D + A) / 2.0)) / (2.0*D);
	//return (2.0*vc*exp(t / 2.0*(D - A)) - 2.0*vc*exp(-t / 2.0*(D + A)) - A*xc*exp(-t / 2.0*(D + A)) + A*xc*exp(t / 2.0*(D + A)) + xc*D*exp(-t / 2.0*(D + A)) + xc*D*exp(t / 2.0*(D + A))) / ((long double)2.0*D);
	//(2.0*vc*(exp(t / 2.0*(D - A)) - exp(-t / 2.0*(D - A))) + A*xc*(exp(t / 2.0*(D + A)) - exp(-t / 2.0*(D + A))) + xc*D*(exp(t / 2.0*(D + A)) + exp(-t / 2.0*(D + A)))) / ((long double)2.0*D);
	//return 0;
};

long double fvr(long double t){
	if ((w == 3.0)&&(A == 2.0)&&(x0 == 3.0)&&(v0 == 2.0))
		return expl(-t)*(8.0*cosl(2.0*sqrtl(2.0)*t) - 29.0*sqrtl(2.0)*sin(2.0*sqrtl(2.0)*t)) / 4.0;
	else
			return NULL;
};

//Функция округления (необходима для построения графиков в целых числах)
int rd(long double u){
	return (int) (u + 0.5);
};

class CMainWnd : public CFrameWnd
{
void press(){
	CString value;
	GetDlgItemText(IDC_MYEDIT1, value);
	w = _ttof(value);
	GetDlgItemText(IDC_MYEDIT2, value);
	A = _ttof(value);
	GetDlgItemText(IDC_MYEDIT3, value);
	x0 = _ttof(value);
	GetDlgItemText(IDC_MYEDIT4, value);
	v0 = _ttof(value);
	this->InvalidateRect(0);
}

public:
	CMainWnd();
	//~CMainWnd();
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();

private:
	CButton* MyButton;	// Указатель на объект кнопка
	CEdit* MyEdit1;
	CEdit* MyEdit2;
	CEdit* MyEdit3;
	CEdit* MyEdit4;
	DECLARE_MESSAGE_MAP();			
};

BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd) 
	ON_WM_CREATE()						   
	ON_WM_PAINT()	
	ON_COMMAND(IDC_MYBUTTON, press)
END_MESSAGE_MAP()

void CMainWnd::OnPaint()
{
	long double h = 0.01; //Шаг по сетке времени
	long double t; // Время
	long double xn = 0.0, vn = 0.0, xc=x0, vc=v0, xmax = fabsl(x0), vmax = fabsl(v0);
	CPaintDC dc(this);
	RECT rect;
	GetClientRect(&rect);
	x = rect.right; //Ширина окна
	y = rect.bottom; //Высота окна
	//Описание кистей
	CPen MyLine(PS_SOLID, 1, RGB(255, 255, 255)); //Служебные линии
	CPen MyReal(PS_SOLID, 2, RGB(0, 127, 255)); //Аналитические решения
	CPen MyEu(PS_SOLID, 1, RGB(255, 0, 0)); //Метод Эйлера
	CPen MyRK(PS_SOLID, 1, RGB(191, 255, 0)); //Метод Рунге-Кутты
		dc.FillSolidRect(0, 0, x, y, 000); //Закраска фона чёрным цветом
		//Разделение экрана на четыре части
		dc.SelectObject(MyLine);
		dc.MoveTo(0, y/2);
		dc.LineTo(x, y/2);
		dc.MoveTo(x/2, 0);
		dc.LineTo(x/2, y);

		//Построение координатных осей, в том числе стрелок и подписей
		dc.MoveTo(10, y / 4);
		dc.LineTo(x/2-10, y / 4);
		dc.LineTo(x / 2 - 30, y / 4-6);
		dc.MoveTo(x / 2 - 10, y / 4);
		dc.LineTo(x / 2 - 30, y / 4 +6);
		dc.MoveTo(x/4, 10);
		dc.LineTo(x/4, y/2-10);
		dc.MoveTo(x / 4, 10);
		dc.LineTo(x / 4-6, 30);
		dc.MoveTo(x / 4, 10);
		dc.LineTo(x / 4+6, 30);
		dc.SetTextColor(RGB(255,255,255));
		dc.TextOutW(x / 4 - 10, y/4+5, "0");
		dc.TextOutW(x /2 - 20, y/4+5, "t");
		dc.TextOutW(x/4+10,10,"x");

		dc.MoveTo(10, rd((3.0/4.0)*y));
		dc.LineTo(x / 2 - 10, rd ((3.0 / 4.0)*y));
		dc.LineTo(x / 2 - 30, rd ((3.0 / 4.0)*y) - 6);
		dc.MoveTo(x / 2 - 10, rd ((3.0 / 4.0)*y));
		dc.LineTo(x / 2 - 30, rd ((3.0 / 4.0)*y) + 6);
		dc.MoveTo(x / 4, y/2+10);
		dc.LineTo(x / 4, y - 10);
		dc.MoveTo(x / 4, y / 2 + 10);
		dc.LineTo(x / 4-6, y / 2 + 30);
		dc.MoveTo(x / 4, y / 2 + 10);
		dc.LineTo(x / 4 + 6, y / 2 + 30);
		dc.TextOutW(x / 4 - 10, rd((3.0/4.0)*y) + 5, "0");
		dc.TextOutW(x / 2 - 20, rd ((3.0 / 4.0)*y) + 5, "t");
		dc.TextOutW(x / 4 + 10, y/2+10, "v");

		dc.MoveTo(x/2+10, y / 4);
		dc.LineTo(x - 10, y / 4);
		dc.LineTo(x - 30, y / 4-6);
		dc.MoveTo(x - 10, y / 4);
		dc.LineTo(x - 30, y / 4 + 6);
		dc.MoveTo(rd((3.0/4.0)*x), 10);
		dc.LineTo(rd((3.0 / 4.0)*x), y / 2 - 10);
		dc.MoveTo(rd((3.0 / 4.0)*x), 10);
		dc.LineTo(rd((3.0 / 4.0)*x) - 6, 30);
		dc.MoveTo(rd((3.0 / 4.0)*x), 10);
		dc.LineTo(rd((3.0 / 4.0)*x) + 6, 30);
		dc.TextOutW(rd((3.0 / 4.0)*x) - 10, y / 4 + 5, "0");
		dc.TextOutW(x - 20, y / 4 + 5, "v");
		dc.TextOutW(rd((3.0 / 4.0)*x) + 10, 10, "x");
		
		//Масштабирование осей
		for (t = h; t < x / 200.0; t += h){
			vn = vc + h*fv(t, xc, vc);
			xn = xc + h*vc;
			if (fabsl(xn) > xmax)
				xmax = fabsl(xn);
			if (fabsl(vn) > vmax)
				vmax = fabsl(vn);
			/*xc = fxr(t);
			vc = fvr(t);*/
			xc = xn;
			vc = vn;
		}

		xc = x0; vc = v0;
		// Аналитические решения - синие графики
		/*
		dc.MoveTo(0, rd(y / 4.0 - (y/4.0)/xmax * fxr(0.0)));
		dc.SelectObject(MyReal);
		for (t = 0; t < x / 200.0; t += h)
			dc.LineTo(rd(100 * t), rd(y / 4.0 - (y/4.0)/xmax * fxr(t)));
		dc.MoveTo(0, rd(3.0*y / 4.0 - (y / 4.0) / vmax  * fvr(0.0)));
		for (t = 0; t < x / 200.0; t += h)
			dc.LineTo(rd(100 * t), rd(3.0*y / 4.0 - (y/4.0)/vmax * fvr(t)));
		dc.MoveTo(rd(3.0 / 4.0*x + (x/4.0)/xmax * fxr(0.0)), rd(y / 4.0 - (y/4.0)/vmax * fvr(0.0)));
		for (t = 0; t < x / 200.0; t += h)
			dc.LineTo(rd(3.0 / 4.0*x + (x/4.0)/xmax * fxr(t)), rd(y / 4.0 - (y/4.0)/vmax * fvr(t)));
		*/


		// Метод Эйлера - красные графики
		for (t = h; t < x/200.0; t += h){
			vn = vc + h*fv(t, xc, vc);
			xn = xc + h*vc;
			dc.SelectObject(MyEu);
			dc.MoveTo(rd(100*(t-h)), rd(y/4.0-(y/4.0)/xmax*xc));
			dc.LineTo(rd(100 * t), rd(y / 4.0 - (y / 4.0) / xmax*xn));
			dc.MoveTo(rd(100 * (t - h)), rd(3.0*y / 4.0 - (y / 4.0) / vmax*vc));
			dc.LineTo(rd(100 * t), rd(3.0*y / 4.0 - (y / 4.0) / vmax*vn));
			dc.MoveTo(rd(3.0/4.0*x+(x/4.0)/xmax*xc), rd(y/4.0-(y/4.0)/vmax*vc));
			dc.LineTo(rd(3.0/4.0*x+(x/4.0)/xmax*xn), rd(y/4.0-(y/4.0)/vmax*vn));
			xc = xn;
			vc = vn;
		}
		
		//Метод Рунге-Кутты - жёлтый график
		xc = x0, vc = v0;
		long double k1, k2, k3, k4;
		for (t = h; t < x / 200.0; t += h){
			k1 = h*fv(t, xc, vc);
			k2 = h*fv(t + h / 2.0, xc, vc + k1 / 2.0);
			k3 = h*fv(t + h / 2.0, xc , vc + k2 / 2.0);
			k4 = h*fv(t + h, xc, vc + k3);
			vn = vc + (k1 + 2.0*k2 + 2.0*k3 + k4) / 6.0;
			xn = xc + h*vc;
			dc.SelectObject(MyRK);
			dc.MoveTo(rd(100 * (t - h)), rd(y / 4.0 - (y/4.0)/xmax * xc));
			dc.LineTo(rd(100 * t), rd(y / 4.0 - (y/4.0)/xmax * xn));
			dc.MoveTo(rd(100 * (t - h)), rd(3.0*y / 4.0 - (y/4.0)/vmax * vc));
			dc.LineTo(rd(100 * t), rd(3.0*y / 4.0 - (y/4.0)/vmax * vn));
			dc.MoveTo(rd(3.0 / 4.0*x + (x/4.0)/xmax * xc), rd(y / 4.0 - (y/4.0)/vmax * vc));
			dc.LineTo(rd(3.0 / 4.0*x + (x/4.0)/xmax * xn), rd(y / 4.0 - (y/4.0)/vmax * vn));
			xc = xn;
			vc = vn;
		};
}

int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)  return -1;
	return 0;
}

CMainWnd::CMainWnd()
{
	Create(NULL, L"Методы Эйлера и Рунге-Кутты для решения дифференциальных уравнений. Иванов Сергей. 254 группа. 2013 год.", WS_OVERLAPPEDWINDOW, rectDefault,
		NULL, NULL);
	RECT rect;
	GetClientRect(&rect);
	x = 1024; //Ширина окна
	y = 600; //Высота окна
	MyEdit1 = new CEdit();
	if (MyEdit1 != NULL) MyEdit1->Create(WS_CHILD | WS_VISIBLE | SS_CENTER,
		CRect(rd(5.0 / 8.0*x)-10, rd(4.0 / 7.0*y)-40, rd(3.0 / 4.0*x)-10, rd(9.0 / 14.0*y)-40), this, IDC_MYEDIT1);
	MyEdit2 = new CEdit();
	if (MyEdit2 != NULL) MyEdit2->Create(WS_CHILD | WS_VISIBLE | SS_CENTER,
		CRect(rd(3.0 / 4.0*x)+10, rd(4.0 / 7.0*y)-40, rd(7.0 / 8.0*x)+10, rd(9.0 / 14.0*y)-40), this, IDC_MYEDIT2);
	MyEdit3 = new CEdit();
	if (MyEdit3 != NULL) MyEdit3->Create(WS_CHILD | WS_VISIBLE | SS_CENTER,
		CRect(rd(5.0 / 8.0*x) - 10, rd(9.0 / 14.0*y)-20, rd(3.0 / 4.0*x) - 10, rd(5.0 / 7.0*y)-20), this, IDC_MYEDIT3);
	MyEdit4 = new CEdit();
	if (MyEdit4 != NULL) MyEdit4->Create(WS_CHILD | WS_VISIBLE | SS_CENTER,
		CRect(rd(3.0 / 4.0*x) + 10, rd(9.0 / 14.0*y)-20, rd(7.0 / 8.0*x) + 10, rd(5.0 / 7.0*y)-20), this, IDC_MYEDIT4);
	MyButton = new CButton();
	if (MyButton != NULL) MyButton->Create(L"Перестроить", WS_CHILD | WS_VISIBLE | SS_CENTER,
		CRect(rd(5.0/8.0*x), rd(5.0/7.0*y), rd(7.0/8.0*x), rd(6.0/7.0*y)), this, IDC_MYBUTTON);
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