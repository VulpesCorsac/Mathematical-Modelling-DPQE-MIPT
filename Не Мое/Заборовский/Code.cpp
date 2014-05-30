#include "afxwin.h"						
#include "afxext.h"	
#define _USE_MATH_DEFINES
#include <cmath>
#define IDC_MYBUTTON 100 //Кнопка
#define IDC_MYEDIT1 101 
#define IDC_MYEDIT2 102 
#define IDC_MYEDIT3 103 
#define IDC_MYEDIT4 104 
const long double G = 6.67384e-11;
const long double Ms = 1.989e+30; // Масса Солнца
const long double M1 = 2.12*Ms;
const long double M2 = 0.978*Ms;
const long double r1 = 1e+6;
const long double r2 = 1e+6;
const long double Ae = 149597871000;
const long double L = 25 * Ae;// 25 a.e.
const long double X1 = -L / (M1 / M2 + 1);
const long double X2 = L + X1;
const long double Y1 = 0, Y2 = 0;
const long double F0 = G*M1*M2 / (L*L);
long double Vmp1 = 2 * M_PI * X1 / 1.592 * sqrtl((1 - 0.592) / (1 + 0.592)) / (86400 * 365.25 * 50.09);
long double Vmp2 = 2 * M_PI * X2 / 1.592 * sqrtl((1 - 0.592) / (1 + 0.592)) / (86400 * 365.25 * 50.09);


int a = 1000; // Кратность прорисовки
int dt = 2000;// Шаг по времени, секунда
int year = 31556926;

long double max = 20 * L;
long double X3 = 80 * Ae;
long double Y3 = 0;
long double V0X3 = 0;
long double V0Y3 = 4470;



int rd(long double u){
	return (int)(u + 0.5);
};

long double PrX(long double x, long double y, long double x1, long double y1){
	return (x1 - x) / (hypotl(x - x1, y - y1));
};

long double PrY(long double x, long double y, long double x1, long double y1){
	return (y1 - y) / (hypotl(x - x1, y - y1));
};

//ускорения
long double ax(long double x, long double y, long double x1, long double y1, long double M1){ //c индексом 1 - координаты начала вектора: самого тела
	return PrX(x, y, x1, y1)*G*M1 / (hypotl(x - x1, y - y1)*hypotl(x - x1, y - y1));
};

long double ay(long double x, long double y, long double x1, long double y1, long double M1){
	return PrY(x, y, x1, y1)*G*M1 / (hypotl(x - x1, y - y1)*hypotl(x - x1, y - y1));
};
//Домножение на PrX проецирует вектор a на 0х с учётом знака


class CMainWnd : public CFrameWnd
{

	void press(){
		CString value;
		GetDlgItemText(IDC_MYEDIT1, value);
		X3 = Ae*_ttof(value);
		GetDlgItemText(IDC_MYEDIT2, value);
		Y3 = Ae*_ttof(value);
		GetDlgItemText(IDC_MYEDIT3, value);
		V0X3 = _ttof(value);
		GetDlgItemText(IDC_MYEDIT4, value);
		V0Y3 = _ttof(value);
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

	CPaintDC dc(this);
	RECT rect;
	GetClientRect(&rect);
	long double xs = rect.right;
	long double ys = rect.bottom;

	dc.FillSolidRect(0, 0, xs, ys, RGB(224, 128, 0)); //Заливка экрана

	CPen InvisibleLine(PS_SOLID, 1, RGB(224, 128, 0));

	CPen StarLine(PS_SOLID, 1, RGB(0, 0, 0));
	dc.SelectObject(StarLine);


	//star1
	CBrush Brush1(RGB(0, 127, 255));

	//star2
	CBrush Brush2(RGB(127, 255, 0));

	//тело
	CBrush Brush3(RGB(255, 255, 255));


	//Сетка
	CPen CrossLine(PS_SOLID, 1, RGB(225, 255, 255));

	CPen SkyLine(PS_SOLID, 2, RGB(0, 0, 0));
	dc.SelectObject(SkyLine);

	//Экран выше. Ниже осн. часть

	CPen Line(PS_SOLID, 3, RGB(0, 0, 0));
	dc.SelectObject(Line);
	dc.MoveTo(rd(xs), rd(ys));

	int i, j;
	int k = 1;
	int n = 1;
	long double xgoal = 0, vygoal = 0;

	//Взаимное движение:
	long double ax1, ay1, vx1c, vx1n, vy1c, vy1n, xc1, xn1, yc1, yn1;
	long double ax2, ay2, vx2c, vx2n, vy2c, vy2n, xc2, xn2, yc2, yn2;
	long double ax3, ay3, vx3c, vx3n, vy3c, vy3n, xc3, xn3, yc3, yn3;


	ax1 = F0 / M1;
	ax2 = F0 / M2;
	ay1 = 0;
	ay2 = 0;
	vx1c = 0;
	vx1n = 0;
	vx2n = 0;
	vx2c = 0;
	vy1c = Vmp1;
	vy2c = Vmp2;
	vy1n = 0;
	vy2n = 0;
	xc1 = X1;
	xc2 = X2;
	xn1 = 0;
	xn2 = 0;
	yc1 = 0.0;
	yc2 = 0.0;
	yn1 = 0;
	yn2 = 0;

	//3
	xc3 = X3;
	xn3 = 0;
	yc3 = Y3;
	yn3 = 0;

	vx3c = V0X3;
	vx3n = 0;
	vy3c = V0Y3;
	vy3n = 0;
	//Поиск орбиты

	for (j = 1; j < 10000; j++){   //Шаг по скорости
		for (i = 1; i < 10000 * year; i++){ //Шаг по координате

			ax1 = ax(xc1, yc1, xc2, yc2, M2);
			ax2 = ax(xc2, yc2, xc1, yc1, M1);
			ay1 = ay(xc1, yc1, xc2, yc2, M2);
			ay2 = ay(xc2, yc2, xc1, yc1, M1);

			ax3 = ax(xc3, yc3, xc2, yc2, M2) + ax(xc3, yc3, xc1, yc1, M1);
			ay3 = ay(xc3, yc3, xc2, yc2, M2) + ay(xc3, yc3, xc1, yc1, M1);

			vx1n = vx1c + ax1*dt;
			vx2n = vx2c + ax2*dt;
			vx3n = vx3c + ax3*dt;
			vy1n = vy1c + ay1*dt;
			vy2n = vy2c + ay2*dt;
			vy3n = vy3c + ay3*dt;

			xn1 = xc1 + vx1c*dt;
			xn2 = xc2 + vx2c*dt;
			xn3 = xc3 + vx3c*dt;
			yn1 = yc1 + vy1c*dt;
			yn2 = yc2 + vy2c*dt;
			yn3 = yc3 + vy3c*dt;

			if (i % a == 0)
			{
				dc.SelectObject(CrossLine);
				dc.MoveTo(0, rd(ys / 2));
				dc.LineTo(rd(xs), rd(ys / 2));
				dc.MoveTo(rd(xs / 2), 0);
				dc.LineTo(rd(xs / 2), rd(ys));

				dc.SelectObject(InvisibleLine);

				dc.SelectObject(Brush1);
				dc.Ellipse(rd(xs / 2.0 + xn1*xs / max - 12), rd(ys / 2.0 + yn1*xs / max - 12), rd(xs / 2.0 + xn1*xs / max + 12), rd(ys / 2.0 + yn1*xs / max + 12));
				dc.SelectObject(Brush2);
				dc.Ellipse(rd(xs / 2.0 + xn2*xs / max - 8), rd(ys / 2.0 + yn2*xs / max - 8), rd(xs / 2.0 + xn2*xs / max + 8), rd(ys / 2.0 + yn2*xs / max + 8));

				dc.SelectObject(StarLine);

				dc.SelectObject(Brush3);
				dc.Ellipse(rd(xs / 2.0 + xn3*xs / max - 4), rd(ys / 2.0 + yn3*xs / max - 4), rd(xs / 2.0 + xn3*xs / max + 4), rd(ys / 2.0 + yn3*xs / max + 4));
			}

			xc1 = xn1;
			xc2 = xn2;
			xc3 = xn3;
			yc1 = yn1;
			yc2 = yn2;
			yc3 = yn3;
			vx1c = vx1n;
			vy1c = vy1n;
			vx2c = vx2n;
			vy2c = vy2n;
			vx3c = vx3n;
			vy3c = vy3n;

			if (fabsl(xn1 - xn3) < r1 && fabsl(yn1 - yn3) < r1)
				break;
			if (fabsl(xn2 - xn3)<r2 && fabsl(yn2 - yn3)<r2)
				break;
			if (fabsl(xn3) > 1.5 * max || fabsl(yn3)> 1.5 * max)
				break;

			if (i>10000 && fabsl(Y3 - yn3) < 0.1*Ae && xn3>0){ //Проверка попадания в начальную точку с х=X3
				if (hypotl(X3 - xn3, Y3 - yn3) < 0.1*Ae && fabsl(vx3n - V0X3) < 0.1*Ae && fabsl(vy3n - V0Y3) < 0.1*Ae){ //Проверка совпадения скоростей и координат с начальными. Попал:
					xgoal = X3;
					vygoal = V0Y3;
					break;
				}
				else{ //Не попал
					ax1 = F0 / M1;
					ax2 = F0 / M2;
					ay1 = 0;
					ay2 = 0;
					vx1c = 0;
					vx1n = 0;
					vx2n = 0;
					vx2c = 0;
					vy1c = Vmp1;
					vy2c = Vmp2;
					vy1n = 0;
					vy2n = 0;
					xc1 = X1;
					xc2 = X2;
					xn1 = 0;
					xn2 = 0;
					yc1 = 0.0;
					yc2 = 0.0;
					yn1 = 0;
					yn2 = 0;

					xc3 = X3 + k*X3;
					xn3 = 0;
					yc3 = Y3;
					yn3 = 0;

					vx3c = V0X3;
					vx3n = 0;
					vy3c = V0Y3;
					vy3n = 0;
					k++;
				}
			}
		}
		if (xgoal == X3){
			CString s1;
			CString s2;
			s1.Format(L"%.2Lf", xgoal);
			s2.Format(L"%.2Lf", vygoal);
			dc.TextOutW(rd(xs) - 800, 500, "xgoal = " + s1 + "; vygoal= " + s2 + ".");
			break;
		}
		ax1 = F0 / M1;
		ax2 = F0 / M2;
		ay1 = 0;
		ay2 = 0;
		vx1c = 0;
		vx1n = 0;
		vx2n = 0;
		vx2c = 0;
		vy1c = Vmp1;
		vy2c = Vmp2;
		vy1n = 0;
		vy2n = 0;
		xc1 = X1;
		xc2 = X2;
		xn1 = 0;
		xn2 = 0;
		yc1 = 0.0;
		yc2 = 0.0;
		yn1 = 0;
		yn2 = 0;

		xc3 = X3;
		xn3 = 0;
		yc3 = Y3;
		yn3 = 0;

		vx3c = V0X3;
		vx3n = V0X3;
		vy3c = V0Y3+ 0.01*n*V0Y3;
		vy3n = V0Y3;
		n++;

	}
	dc.TextOutW(rd(xs) - 380, 40, "x");
	dc.TextOutW(rd(xs) - 180, 40, "y");
	dc.TextOutW(rd(xs) - 380, 80, "Vx");
	dc.TextOutW(rd(xs) - 180, 80, "Vy");
}//Конец main'а

// Ниже тоже нужное
int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)  return -1;
	return 0;
}

CMainWnd::CMainWnd()
{
	int x = 1920, y = 1080;
	RECT rect;
	rect.left = 0, rect.right = x; rect.top = 0; rect.bottom = y;
	Create(NULL, L"Twin Star", WS_OVERLAPPEDWINDOW, rect, NULL, NULL);

	MyEdit1 = new CEdit();
	if (MyEdit1 != NULL) MyEdit1->Create(WS_CHILD | WS_VISIBLE | SS_CENTER,
		CRect(x - 380, 40, x - 230, 70), this, IDC_MYEDIT1);

	MyEdit2 = new CEdit();
	if (MyEdit2 != NULL) MyEdit2->Create(WS_CHILD | WS_VISIBLE | SS_CENTER,
		CRect(x - 180, 40, x - 30, 70), this, IDC_MYEDIT2);

	MyEdit3 = new CEdit();
	if (MyEdit3 != NULL) MyEdit3->Create(WS_CHILD | WS_VISIBLE | SS_CENTER,
		CRect(x - 380, 80, x - 230, 110), this, IDC_MYEDIT3);

	MyEdit4 = new CEdit();
	if (MyEdit4 != NULL) MyEdit4->Create(WS_CHILD | WS_VISIBLE | SS_CENTER,
		CRect(x - 180, 80, x - 30, 110), this, IDC_MYEDIT4);
	MyButton = new CButton();
	if (MyButton != NULL) MyButton->Create(L"Перестроить", WS_CHILD | WS_VISIBLE | SS_CENTER,
		CRect(x - 380, 120, x - 30, 150), this, IDC_MYBUTTON);

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