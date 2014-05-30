#include "afxwin.h"						
#include "afxext.h"						
#include <cmath>

long double A1,A2,w1=1/20.0,w2=1/80.0;

int rd(long double x){
	return (int)(x+0.5);
};

long double fx(long double t){
	return A1 * sinl(w1*t);
};

long double fy(long double t){
	return A2 * cosl(w2*t);
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
	long double h = 1.0;
	long double t;
	RECT rect;
	GetClientRect(&rect);
	int x = rect.right;
	int y = rect.bottom;
	A1 = y / 8;
	A2 = y / 8;
	CPaintDC dc(this);
	CPen MyLine(PS_SOLID, 1, RGB(255, 255, 255));
	CPen MySin(PS_SOLID, 3, RGB(0, 0, 255));
	CPen MyCos(PS_SOLID, 3, RGB(0, 255, 0));
	CPen MyFig(PS_SOLID, 3, RGB(255, 0, 0));
		dc.FillSolidRect(0, 0, x, y, 000);
		dc.SelectObject(MyLine);
		dc.MoveTo(0, y/2);
		dc.LineTo(x, y/2);
		dc.MoveTo(x/2, 0);
		dc.LineTo(x/2, y);

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
		dc.TextOutW(x / 4 - 20, rd(y / 4 -A1), "A1");
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
		dc.TextOutW(x / 4 - 20, rd ((3.0 / 4.0)*y -A2), "A2");
		dc.TextOutW(x / 2 - 20, rd ((3.0 / 4.0)*y) + 5, "t");
		dc.TextOutW(x / 4 + 10, y/2+10, "y");

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
		dc.TextOutW(x - 20, y / 4 + 5, "x");
		dc.TextOutW(rd((3.0 / 4.0)*x) + 10, 10, "y");

		dc.SelectObject(MySin);
		dc.MoveTo(0, rd(y/4 - fx(-x/4.0)));
		for (t = -x / 4; t < x / 4; t += h)
			dc.LineTo(rd(t + x / 4), rd(y / 4 - fx(t)));
		dc.SelectObject(MyCos);
		dc.MoveTo(0, rd((3.0 / 4.0)*y - fy(-x/4.0)));
		for (t = -x/4; t < x/4; t+=h)
			dc.LineTo(rd(t+x/4), rd((3.0/4.0)*y - fy(t)));
		dc.SelectObject(MyFig);
		dc.MoveTo(rd((3.0 / 4.0)*x + fx(-x)), rd(y/4 - fy(-x)));
		for (t = -x; t < x; t+=h)
			dc.LineTo(rd((3.0 / 4.0)*x + fx(t)), rd(y/4 - fy(t)));
}

int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)  return -1;
	return 0;
}

CMainWnd::CMainWnd()
{
	Create(NULL, L"Фигуры Лиссажу. Иванов Сергей, 254 группа. 2013 год.", WS_OVERLAPPEDWINDOW, rectDefault,
		NULL, NULL);						
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