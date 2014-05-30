#include "afxwin.h"						
#include "afxext.h"	
#define _USE_MATH_DEFINES
#include <cmath>

#define IDC_MYBUTTON 100 //Кнопка
#define IDC_MYEDIT1 101 //Координата X
#define IDC_MYEDIT2 102 //Координата Y
#define IDC_MYEDIT3 103 //Скорость X
#define IDC_MYEDIT4 104 //Скорость Y

struct Object{
	long double GM, x, y, vx, vy, ax, ay, R;
};

Object Planet{ 0.0, -2.9e+12, -0.0e+12, 0.0, -789.0, 0.0, 0.0, 0.0 };
long double T=1.0;

class CMainWnd : public CFrameWnd
{
	void press(){
		T = 2.0e+10;
		CString value;
		GetDlgItemText(IDC_MYEDIT1, value);
		Planet.x = _ttof(value);
		Planet.x *= 1.495978707e+11;
		GetDlgItemText(IDC_MYEDIT2, value);
		Planet.y = _ttof(value);
		Planet.y *= 1.495978707e+11;
		GetDlgItemText(IDC_MYEDIT3, value);
		Planet.vx = _ttof(value);
		Planet.vx *= 1.0e+3;
		GetDlgItemText(IDC_MYEDIT4, value);
		Planet.vy = _ttof(value);
		Planet.vy *= 1.0e+3;
		this->InvalidateRect(0);
	}

public:
	CMainWnd();
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();

private:
	CButton* MyButton;
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

	Object A{ 2.680795435464e+20, -1.531367579292792e+12, 0.0, 0.0, -1.923828617202e+3 * M_PI / 1.581035760 * sqrtl(5.1/19.9), 0.0, 0.0, 1.40491e+9 };
	Object B{ 1.2979296712296e+20, 3.19134145606896e+12, 0.0, 0.0, 4.009222934760e+3 * M_PI / 1.581035760 * sqrtl(5.1 / 19.9), 0.0, 0.0, 5.8422e+7 };
	CPaintDC dc(this);
	RECT rect;
	GetClientRect(&rect);
	long double x = rect.right; //Ширина окна
	long double y = rect.bottom; //Высота окна
	dc.FillSolidRect(0, 0, lrintl(x), lrintl(y), RGB(0, 0, 0));
	CPen Line(PS_SOLID, 1, RGB(255, 255, 255));
	CBrush Star1(RGB(255,255,255));
	CBrush Star2(RGB(0, 0, 0));
	CBrush BPlanetoid(RGB(0, 127, 127));
	CPen Planetoid(PS_SOLID, 1, RGB(0, 127, 127));
	CPen Background(PS_SOLID, 1, RGB(0, 0, 0));
	dc.SetTextColor(RGB(255, 255, 255));
	dc.TextOutW(5, 5, "Координаты планеты, а.е.");
	dc.TextOutW(5, 65, "Скорость планеты, км/с");
	long double h = 5.0e+4;
	long double max = 3.2e+12;

	dc.MoveTo(lrintl(x / 2 + y / 2.0*A.x / max), lrintl(y / 2.0*(1.0 - A.y / max)));
	for (long double t = 0; t < T; t += h){
		long double dx = B.x - A.x, dy = B.y - A.y;
		long double R = hypotl(dx, dy);
		long double cosinus = dx / R, sinus = dy / R;
		R *= R;
		// Сириус А
		A.ax = B.GM / R * cosinus;
		A.ay = B.GM / R * sinus;
		A.vx += h*A.ax;
		A.vy += h*A.ay;

		// Сириус Б
		B.ax = -A.GM / R * cosinus;
		B.ay = -A.GM / R * sinus;
		B.vx += h*B.ax;
		B.vy += h*B.ay;

		dx = Planet.x - A.x, dy = Planet.y - A.y;
		R = hypotl(dx, dy);
		cosinus = dx / R; sinus = dy / R;
		R *= R;
		Planet.ax = -A.GM / R * cosinus;
		Planet.ay = -A.GM / R * sinus;
		dx = Planet.x - B.x; dy = Planet.y - B.y;
		R = hypotl(dx, dy);
		cosinus = dx / R; sinus = dy / R;
		R *= R;
		Planet.ax += -B.GM / R * cosinus;
		Planet.ay += -B.GM / R * sinus;
		Planet.vx += h*Planet.ax;
		Planet.vy += h*Planet.ay;
		bool k = (llrintl(t) % 1000 == 0);

		if (k){
			dc.SelectObject(Line);
			dc.MoveTo(0, lrintl(y / 2));
			dc.LineTo(lrintl(x), lrintl(y / 2));
			dc.MoveTo(lrintl(x / 2), 0);
			dc.LineTo(lrintl(x / 2), lrintl(y));
		};
		if (k){
			dc.SelectObject(Background);
			dc.SelectObject(Star2);
			dc.Ellipse(lrintl(x / 2 + y / 2.0*A.x / max) - 7, lrintl(y / 2.0*(1.0 - A.y / max)) - 7, lrintl(x / 2 + y / 2.0*A.x / max) + 7, lrintl(y / 2.0*(1.0 - A.y / max)) + 7);
		};
		A.x += h*A.vx;
		A.y += h*A.vy;
		if (k){
			dc.SelectObject(Star1);
			dc.Ellipse(lrintl(x / 2 + y / 2.0*A.x / max) - 7, lrintl(y / 2.0*(1.0 - A.y / max)) - 7, lrintl(x / 2 + y / 2.0*A.x / max) + 7, lrintl(y / 2.0*(1.0 - A.y / max)) + 7);
		};
		//dc.LineTo(lrintl(x / 2 + y / 2.0*A.x / max), lrintl(y / 2.0*(1.0 - A.y / max)));
		//dc.MoveTo(lrintl(x / 2 + y / 2.0*B.x / max), lrintl(y / 2.0*(1.0 - B.y / max)));
		
		if (k){
			dc.SelectObject(Background);
			dc.SelectObject(Star2);
			dc.Ellipse(lrintl(x / 2 + y / 2.0*B.x / max) - 5, lrintl(y / 2.0*(1.0 - B.y / max)) - 5, lrintl(x / 2 + y / 2.0*B.x / max) + 5, lrintl(y / 2.0*(1.0 - B.y / max)) + 5);
		};
		B.x += h*B.vx;
		B.y += h*B.vy;
		if (k){
			dc.SelectObject(Star1);
			dc.Ellipse(lrintl(x / 2 + y / 2.0*B.x / max) - 5, lrintl(y / 2.0*(1.0 - B.y / max)) - 5, lrintl(x / 2 + y / 2.0*B.x / max) + 5, lrintl(y / 2.0*(1.0 - B.y / max)) + 5);
		};

		if (k){
			dc.SelectObject(Background);
			dc.SelectObject(Star2);
			dc.Ellipse(lrintl(x / 2 + y / 2.0*Planet.x / max) - 3, lrintl(y / 2.0*(1.0 - Planet.y / max)) - 3, lrintl(x / 2 + y / 2.0*Planet.x / max) + 3, lrintl(y / 2.0*(1.0 - Planet.y / max)) + 3);
		};
		Planet.x += h*Planet.vx;
		Planet.y += h*Planet.vy;
		if (k){
			dc.SelectObject(BPlanetoid);
			dc.Ellipse(lrintl(x / 2 + y / 2.0*Planet.x / max) - 3, lrintl(y / 2.0*(1.0 - Planet.y / max)) - 3, lrintl(x / 2 + y / 2.0*Planet.x / max) + 3, lrintl(y / 2.0*(1.0 - Planet.y / max)) + 3);
		};
		if ((hypotl(Planet.x - A.x, Planet.y - A.y) < A.R + Planet.R) || (hypotl(Planet.x - B.x, Planet.y - B.y) < B.R + Planet.R) || (fabsl(x/2.0*Planet.x / max)>x) || (fabsl(y/2.0*Planet.y / max)>y))
			break;
		/*
		//dc.LineTo(lrintl(x / 2 + y / 2.0*B.x / max), lrintl(y / 2.0*(1.0 - B.y / max)));
		dc.SelectObject(Planetoid);
		dc.MoveTo(lrintl(x / 2 + y / 2.0*Planet.x / max), lrintl(y / 2.0*(1.0 - Planet.y / max)));
		Planet.x += h*Planet.vx;
		Planet.y += h*Planet.vy;		
		dc.LineTo(lrintl(x / 2 + y / 2.0*Planet.x / max), lrintl(y / 2.0*(1.0 - Planet.y / max)));
		//dc.MoveTo(lrintl(x / 2 + y / 2.0*A.x / max), lrintl(y / 2.0*(1.0 - A.y / max)));
		*/
	}
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
	Create(NULL, L"Двойная звезда - Сириус. Лебедев Антон. 254 группа", WS_OVERLAPPEDWINDOW, rect, NULL, NULL);
	MyEdit1 = new CEdit();
	if (MyEdit1 != NULL) MyEdit1->Create(WS_CHILD | WS_VISIBLE | SS_CENTER,
		CRect(5, 30, 110, 55), this, IDC_MYEDIT1);
	MyEdit2 = new CEdit();
	if (MyEdit2 != NULL) MyEdit2->Create(WS_CHILD | WS_VISIBLE | SS_CENTER,
		CRect(130, 30, 255, 55), this, IDC_MYEDIT2);
	MyEdit3 = new CEdit();
	if (MyEdit3 != NULL) MyEdit3->Create(WS_CHILD | WS_VISIBLE | SS_CENTER,
		CRect(5, 90, 110, 115), this, IDC_MYEDIT3);
	MyEdit4 = new CEdit();
	if (MyEdit4 != NULL) MyEdit4->Create(WS_CHILD | WS_VISIBLE | SS_CENTER,
		CRect(130, 90, 255, 115), this, IDC_MYEDIT4);
	MyButton = new CButton();
	if (MyButton != NULL) MyButton->Create(L"Запуск", WS_CHILD | WS_VISIBLE | SS_CENTER,
		CRect(5, 130, 255, 170), this, IDC_MYBUTTON);
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