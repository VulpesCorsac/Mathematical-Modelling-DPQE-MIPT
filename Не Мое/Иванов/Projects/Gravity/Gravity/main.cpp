#include "afxwin.h"						
#include "afxext.h"	
#define _USE_MATH_DEFINES
#include <cmath>

#define IDC_MYBUTTON 100 //Кнопка
#define IDC_MYEDIT1 101 //Масштаб
#define IDC_MYEDIT2 102 //Лунный коэффициент
#define IDC_MYEDIT3 103 //Время
#define IDC_MYEDIT4 104 //Шаг

struct Object{
	long double x, y, vx, vy, ax, ay;
};

const long double GM = 1.32712440018e+20;
long double MAX=2.5e+11, MOON=10.0, T=0.0, H=1000;

int rd(long double u){
	return (int) (u + 0.5);
};

long double sign(long double x){
	return (x > 0.0) - (x < 0.0);
};

long double r(Object Obj){
	return sqrtl(Obj.x*Obj.x + Obj.y*Obj.y);
};

long double a(Object Obj){
	long double R = r(Obj);
	return GM/R/R;
};

class CMainWnd : public CFrameWnd
{
	void press(){
		CString value;
		GetDlgItemText(IDC_MYEDIT1, value);
		MAX = _ttof(value);
		MAX *= 1.495978707e+11;
		GetDlgItemText(IDC_MYEDIT2, value);
		MOON = _ttof(value);
		GetDlgItemText(IDC_MYEDIT3, value);
		T = _ttof(value);
		T *= 86400;
		GetDlgItemText(IDC_MYEDIT4, value);
		H = _ttof(value);
		H *= 60;
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

	Object Mercury{ 0.0, -4.60012e+10, 100000 * sqrtl(1.6000209905890134 / 4.6001251767), 0.0, 0.0, 0.0 };
	Object Venus{ 0.0, 1.08939e+11, -10000 * sqrtl(13.18232666698794 / 1.089329936), 0.0, 0.0, 0.0 };
	Object Earth{ -1.5209823194717103e+11, 0.0, 0.0, -10000 * sqrtl(13.049465190899799786 / 1.5209823194717103), 0.0, 0.0 };
	Object Moon{ Earth.x - 4.05503e+8, Earth.y, 0.0, Earth.vy - 1000 * sqrtl(4.20483606054820 / 3.632954949), 0.0, 0.0 };
	Object Mars{ 2.066689628835e+11, 0.0, 0.0, 10000 * sqrtl(14.509650135827967 / 2.066689628835), 0.0, 0.0 };
	Object Jupiter{ 0.0, -7.405736e+11, 10000 * sqrtl(13.918548927987795 / 7.40573560320), 0.0, 0.0, 0.0 };
	Object Saturn{ 0.0, 1.513325783e+12, -10000 * sqrtl(1.25317275658852622058 / 1.51332578316992203), 0.0, 0.0, 0.0 };
	Object Uranus{ -2.748938461e+12, 0.0, 0.0, -10000 * sqrtl(1.38605613686489140548 / 2.748938461629847948), 0.0, 0.0 };
	Object Neptune{ 4.553946490e+12, 0.0, 0.0, 10000 * sqrtl(1.31224167015991783158 / 4.553946489640798809), 0.0, 0.0 };

	CPaintDC dc(this);
	RECT rect;
	GetClientRect(&rect);
	long double x = rect.right; //Ширина окна
	long double y = rect.bottom; //Высота окна
	dc.FillSolidRect(0,0,rd(x),rd(y),RGB(0,0,0));
	CPen Line(PS_SOLID, 1, RGB(255, 255, 255));
	CPen lMercury(PS_SOLID, 1, RGB(255, 102, 0));
	CPen lVenus(PS_SOLID, 1, RGB(0, 204, 255));
	CPen lEarth(PS_SOLID, 1, RGB(0, 0, 153));
	CPen lMoon(PS_SOLID, 1, RGB(204, 204, 204));
	CPen lMars(PS_SOLID, 1, RGB(255, 0, 0));
	CPen lJupiter(PS_SOLID, 1, RGB(102, 0, 0));
	CPen lSaturn(PS_SOLID, 1, RGB(204, 204, 255));
	CPen lUranus(PS_SOLID, 1, RGB(255, 204, 255));
	CPen lNeptune(PS_SOLID, 1, RGB(0, 0, 255));
	//Сетка
	dc.SelectObject(Line);
	dc.MoveTo(0, rd(y / 2));
	dc.LineTo(rd(x),rd(y/2));
	dc.MoveTo(rd(x/2), 0);
	dc.LineTo(rd(x/2), rd(y));
	//Подписи кнопок
	dc.SetTextColor(RGB(255,255,255));
	dc.TextOutW(140, 8,"Видимый радиус (1 а.е. = 150 млн. км)");
	dc.TextOutW(140, 38, "Растяжение траектории Луны");
	dc.TextOutW(140, 68, "Время (1 день = 86400 с)");
	dc.TextOutW(140, rd(y-30), "Шаг (1 мин. = 60 с)");
	long double h = H;
	long double cosinus, sinus;
	long double max = MAX; // Нептун - 4.553946490e+12 м, норм - 2.5е+11. На вcякий случай, 1 а.е.= 1.495978707e+11 м 
	//Солнечный диск
	CBrush Sun(RGB(255,204,51));
	dc.SelectObject(Sun);
	dc.Ellipse(rd(x / 2 - 6.96342e+8 / max), rd(y / 2 - 6.96342e+8 / max), rd(x / 2 + 6.96342e+8 / max), rd(y / 2 + 6.96342e+8 / max));
	dc.MoveTo(rd(Mercury.x), rd(Mercury.y));
	for (long double t = 0; t < T; t += h){
		cosinus = -Mercury.x / r(Mercury);
		sinus = -Mercury.y / r(Mercury);
		Mercury.ax = a(Mercury)*cosinus;
		Mercury.ay = a(Mercury)*sinus;
		Mercury.vx += h*Mercury.ax;
		Mercury.vy += h*Mercury.ay;
		Mercury.x += h*Mercury.vx;
		Mercury.y += h*Mercury.vy;
		dc.SelectObject(lMercury);
		dc.LineTo(rd(x / 2 + y / 2.0*Mercury.x / max), rd(y / 2.0*(1.0 - Mercury.y / max)));
		dc.MoveTo(rd(x / 2 + y / 2.0*Venus.x / max), rd(y / 2.0*(1.0 - Venus.y / max)));
		cosinus = -Venus.x / r(Venus);
		sinus = -Venus.y / r(Venus);
		Venus.ax = a(Venus)*cosinus;
		Venus.ay = a(Venus)*sinus;
		Venus.vx += h*Venus.ax;
		Venus.vy += h*Venus.ay;
		Venus.x += h*Venus.vx;
		Venus.y += h*Venus.vy;
		dc.SelectObject(lVenus);
		dc.LineTo(rd(x / 2 + y / 2.0*Venus.x / max), rd(y / 2.0*(1.0 - Venus.y / max)));
		dc.MoveTo(rd(x / 2 + y / 2.0*Earth.x / max), rd(y / 2.0*(1.0 - Earth.y / max)));
		cosinus = -Earth.x / r(Earth);
		sinus = -Earth.y/r(Earth);
		Earth.ax = a(Earth)*cosinus;
		Earth.ay = a(Earth)*sinus;
		Earth.vx += h*Earth.ax;
		Earth.vy += h*Earth.ay;
		Earth.x += h*Earth.vx;
		Earth.y += h*Earth.vy;
		dc.SelectObject(lEarth);
		dc.LineTo(rd(x/2+y/2.0*Earth.x/max),rd(y/2.0*(1.0-Earth.y/max)));
		//Отчаянная попытка логарифмического масштаба
		//if ((Earth.x != 0.0) && (Earth.y != 0.0))
			//dc.LineTo(rd(x / 2 + y / 2.0*sign(Earth.x)*log(fabsl(Earth.x)) / log(max)), rd(y / 2.0*(1.0 - sign(Earth.y)*log(fabsl(Earth.y)) / log(max))));
		dc.MoveTo(rd(x / 2 + y / 2.0*(Moon.x + MOON * (Moon.x - Earth.x)) / max), rd(y / 2.0*(1.0 - (Moon.y + MOON * (Moon.y - Earth.y)) / max)));
		//Экспериментальный блок - Луна
		cosinus = -Moon.x / r(Moon);
		sinus = -Moon.y / r(Moon);
		Moon.ax = a(Moon)*cosinus;
		Moon.ay = a(Moon)*sinus;
		long double R = sqrtl(powl(Moon.x - Earth.x, 2.0) + powl(Moon.y - Earth.y, 2.0));
		cosinus = -(Moon.x-Earth.x) / R;
		sinus = -(Moon.y-Earth.y) / R;
		Moon.ax += (3.986004418e+14 / R / R)*cosinus;
		Moon.ay += (3.986004418e+14 / R / R)*sinus;
		Moon.vx += h*Moon.ax;
		Moon.vy += h*Moon.ay;
		Moon.x += h*Moon.vx;
		Moon.y += h*Moon.vy;
		dc.SelectObject(lMoon);
		dc.LineTo(rd(x / 2 + y / 2.0*(Moon.x + MOON * (Moon.x - Earth.x)) / max), rd(y / 2.0*(1.0 - (Moon.y + MOON * (Moon.y - Earth.y)) / max)));
		dc.MoveTo(rd(x / 2 + y / 2.0*Mars.x / max), rd(y / 2.0*(1.0 - Mars.y / max)));
		//
		cosinus = -Mars.x / r(Mars);
		sinus = -Mars.y / r(Mars);
		Mars.ax = a(Mars)*cosinus;
		Mars.ay = a(Mars)*sinus;
		Mars.vx += h*Mars.ax;
		Mars.vy += h*Mars.ay;
		Mars.x += h*Mars.vx;
		Mars.y += h*Mars.vy;
		dc.SelectObject(lMars);
		dc.LineTo(rd(x / 2 + y / 2.0*Mars.x / max), rd(y / 2.0*(1.0 - Mars.y / max)));
		dc.MoveTo(rd(x / 2 + y / 2.0*Jupiter.x / max), rd(y / 2.0*(1.0 - Jupiter.y / max)));
		cosinus = -Jupiter.x / r(Jupiter);
		sinus = -Jupiter.y / r(Jupiter);
		Jupiter.ax = a(Jupiter)*cosinus;
		Jupiter.ay = a(Jupiter)*sinus;
		Jupiter.vx += h*Jupiter.ax;
		Jupiter.vy += h*Jupiter.ay;
		Jupiter.x += h*Jupiter.vx;
		Jupiter.y += h*Jupiter.vy;
		dc.SelectObject(lJupiter);
		dc.LineTo(rd(x / 2 + y / 2.0*Jupiter.x / max), rd(y / 2.0*(1.0 - Jupiter.y / max)));
		dc.MoveTo(rd(x / 2 + y / 2.0*Saturn.x / max), rd(y / 2.0*(1.0 - Saturn.y / max)));
		cosinus = -Saturn.x / r(Saturn);
		sinus = -Saturn.y / r(Saturn);
		Saturn.ax = a(Saturn)*cosinus;
		Saturn.ay = a(Saturn)*sinus;
		Saturn.vx += h*Saturn.ax;
		Saturn.vy += h*Saturn.ay;
		Saturn.x += h*Saturn.vx;
		Saturn.y += h*Saturn.vy;
		dc.SelectObject(lSaturn);
		dc.LineTo(rd(x / 2 + y / 2.0*Saturn.x / max), rd(y / 2.0*(1.0 - Saturn.y / max)));
		dc.MoveTo(rd(x / 2 + y / 2.0*Uranus.x / max), rd(y / 2.0*(1.0 - Uranus.y / max)));
		cosinus = -Uranus.x / r(Uranus);
		sinus = -Uranus.y / r(Uranus);
		Uranus.ax = a(Uranus)*cosinus;
		Uranus.ay = a(Uranus)*sinus;
		Uranus.vx += h*Uranus.ax;
		Uranus.vy += h*Uranus.ay;
		Uranus.x += h*Uranus.vx;
		Uranus.y += h*Uranus.vy;
		dc.SelectObject(lUranus);
		dc.LineTo(rd(x / 2 + y / 2.0*Uranus.x / max), rd(y / 2.0*(1.0 - Uranus.y / max)));
		dc.MoveTo(rd(x / 2 + y / 2.0*Neptune.x / max), rd(y / 2.0*(1.0 - Neptune.y / max)));
		cosinus = -Neptune.x / r(Neptune);
		sinus = -Neptune.y / r(Neptune);
		Neptune.ax = a(Neptune)*cosinus;
		Neptune.ay = a(Neptune)*sinus;
		Neptune.vx += h*Neptune.ax;
		Neptune.vy += h*Neptune.ay;
		Neptune.x += h*Neptune.vx;
		Neptune.y += h*Neptune.vy;
		dc.SelectObject(lNeptune);
		dc.LineTo(rd(x / 2 + y / 2.0*Neptune.x / max), rd(y / 2.0*(1.0 - Neptune.y / max)));
		dc.MoveTo(rd(x / 2 + y / 2.0*Mercury.x / max), rd(y / 2.0*(1.0 - Mercury.y / max)));
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
	Create(NULL, L"Гравитация. Иванов Сергей. 254 группа.", WS_OVERLAPPEDWINDOW, rect, NULL, NULL);
	MyEdit1 = new CEdit();
	if (MyEdit1 != NULL) MyEdit1->Create(WS_CHILD | WS_VISIBLE | SS_CENTER,
		CRect(5, 5, 130, 30), this, IDC_MYEDIT1);
	MyEdit2 = new CEdit();
	if (MyEdit2 != NULL) MyEdit2->Create(WS_CHILD | WS_VISIBLE | SS_CENTER,
		CRect(5, 35, 130, 60), this, IDC_MYEDIT2);
	MyEdit3 = new CEdit();
	if (MyEdit3 != NULL) MyEdit3->Create(WS_CHILD | WS_VISIBLE | SS_CENTER,
		CRect(5, 65, 130, 90), this, IDC_MYEDIT3);
	MyEdit4 = new CEdit();
	if (MyEdit4 != NULL) MyEdit4->Create(WS_CHILD | WS_VISIBLE | SS_CENTER,
		CRect(5, y-100, 130, y-75), this, IDC_MYEDIT4);
	MyButton = new CButton();
	if (MyButton != NULL) MyButton->Create(L"Перестроить", WS_CHILD | WS_VISIBLE | SS_CENTER,
		CRect(5, 100, 130, 140), this, IDC_MYBUTTON);
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