#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

LRESULT CALLBACK MainWinProc(HWND,UINT,WPARAM,LPARAM);
#define ID_MYBUTTON 1
#define ID_MASVALUE 2
#define ID_ACCCONST 3
#define ID_ANGLFIRE 4
#define ID_EARTHMAS 5
#define ID_EQUASION 6
#define ID_FIRSTNAM 7
#define ID_SECONDNM 8
#define ID_THIRDNAM 9
#define ID_FOURTHNM 10
#define ID_FITHNAME 11
#define ID_SIXTHNAM 12
#define ID_STARTSPD 13
#define ID_GRVCONST 14
#define ID_EARTHRNG 15





#define ID_SCALELN1 23
#define ID_SCALELN2 24


float v_y = 0, t = 0, x = 0, x_step = 0, v_y_step = 0, y = 0, y_step = 0, v_x = 0, v_x_step = 0, scale = 1, char_value = 1, accuracy = 0;

float ang = 0, mass = 0, y_start = 0, v_start = 0, x_start = 0, G_const = 0, Mass = 0, C = 0, R = 0, r = 0;
int flag, i, j; // flag = 1 -один выстрел, 2 - подборка оптимального угла, 0 - установка мишение, 4 - пристрелка к мишени

int WINAPI WinMain(HINSTANCE hInst,HINSTANCE,LPSTR,int ss) {
 /* создаем и регистрируем класс главного окна */
 WNDCLASS wc;
 wc.style=0;
 wc.lpfnWndProc=MainWinProc;
 wc.cbClsExtra=wc.cbWndExtra=0;
 wc.hInstance=hInst;
 wc.hIcon=NULL;
 wc.hCursor=NULL;
 wc.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
 wc.lpszMenuName=NULL;
 wc.lpszClassName="Example 4 MainWnd Class";
 if (!RegisterClass(&wc)) return FALSE;

 /* создаем главное окно и отображаем его */
 HWND hMainWnd = CreateWindow("Example 4 MainWnd Class","Model",WS_OVERLAPPEDWINDOW,
  171,64,1024,640,NULL,NULL,hInst,NULL);
 if (!hMainWnd) return FALSE;
 ShowWindow(hMainWnd,ss);
 UpdateWindow(hMainWnd);




 MSG msg; /* цикл обработки событий */
 while (GetMessage(&msg,NULL,0,0)) {
  TranslateMessage(&msg);
  DispatchMessage(&msg);
 }
 return msg.wParam;
}

/* процедура обработки сообщений для главного окна */
LRESULT CALLBACK MainWinProc(HWND hw,UINT msg,WPARAM wp,LPARAM lp) {

HWND hw_angle, hw_earthacc, hw_startspd, hw_mass, hw_earth_mass, hw_gravity_const, hw_range;

char G[20], A[20], M[20], m[20], V0[20], MAX_ANGLE[20], RANGE[20], DISTANCE[20], KK[20], SCALE[20], ACCURACY[20];

char* p;

HDC hDC;
PAINTSTRUCT ps; //создаём контекст устройства


HPEN Pen1 = CreatePen( PS_SOLID, 1, RGB(0, 0, 255));
HPEN Pen_Clear = CreatePen( PS_SOLID, 2, RGB(0, 0, 0));
HPEN Pen_Axis = CreatePen( PS_SOLID, 2, RGB(255, 255, 255));
HPEN Pen4 = CreatePen( PS_SOLID, 1, RGB(0, 255, 0));
HPEN Pen_Graph = CreatePen( PS_SOLID, 2, RGB(255, 0, 0));
HBRUSH Brush_Clear = CreateSolidBrush( RGB(0, 0, 0) );
HBRUSH Brush_Axis = CreateSolidBrush( RGB(255, 255, 255));


 switch (msg) {
  case WM_CREATE:
   /* при создании окна внедряем в него кнопочку */
   CreateWindow("button","FIRE",WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,
    823,140,200,20,hw,(HMENU)ID_MYBUTTON,NULL,NULL);

   /* стиль WS_CHILD означает, что это дочернее окно и для него
    вместо дескриптора меню будет передан целочисленный идентификатор,
    который будет использоваться дочерним окном для оповещения
    родительского окна через WM_COMMAND */


   hw_angle = CreateWindow("EDIT","0.0",WS_BORDER|WS_VISIBLE|WS_CHILD|ES_LEFT|ES_MULTILINE,
        923,60,100,20,hw,(HMENU)ID_ANGLFIRE,NULL,NULL);
   hw_mass = CreateWindow("EDIT","100.0",WS_BORDER|WS_VISIBLE|WS_CHILD|ES_LEFT|ES_MULTILINE,
        923,40,100,20,hw,(HMENU)ID_MASVALUE,NULL,NULL);
   hw_startspd = CreateWindow("EDIT","7.9",WS_BORDER|WS_VISIBLE|WS_CHILD|ES_LEFT|ES_MULTILINE,
        923,20,100,20,hw,(HMENU)ID_STARTSPD,NULL,NULL);
   hw_earth_mass = CreateWindow("EDIT", "5.97", WS_BORDER|WS_VISIBLE|WS_CHILD|ES_LEFT|ES_MULTILINE,
        923,80,100,20,hw,(HMENU)ID_EARTHMAS,NULL,NULL);
   hw_gravity_const = CreateWindow("EDIT", "6.67", WS_BORDER|WS_VISIBLE|WS_CHILD|ES_LEFT|ES_MULTILINE,
        923,100,100,20,hw,(HMENU)ID_GRVCONST,NULL,NULL);
   hw_range = CreateWindow("EDIT", "6.37", WS_BORDER|WS_VISIBLE|WS_CHILD|ES_LEFT|ES_MULTILINE,
        923,120,100,20,hw,(HMENU)ID_EARTHRNG,NULL,NULL);

   CreateWindow("STATIC", "R(км*10^3)", WS_BORDER|WS_VISIBLE|WS_CHILD, 823, 120, 100, 20, hw, (HMENU)ID_FITHNAME, NULL, NULL);
   CreateWindow("STATIC", "ma = G(m*M)/(r*r)", WS_BORDER|WS_VISIBLE|WS_CHILD, 823, 0, 200, 20, hw, (HMENU)ID_EQUASION, NULL, NULL);
   CreateWindow("STATIC", "f(градусы):", WS_BORDER|WS_VISIBLE|WS_CHILD, 823, 60, 100, 20, hw, (HMENU)ID_THIRDNAM, NULL, NULL);
   CreateWindow("STATIC", "m(кг):", WS_BORDER|WS_VISIBLE|WS_CHILD, 823, 40, 100, 20, hw, (HMENU)ID_FOURTHNM, NULL, NULL);
   CreateWindow("STATIC", "V0(км/с):", WS_BORDER|WS_VISIBLE|WS_CHILD, 823, 20, 100, 20, hw, (HMENU)ID_SIXTHNAM, NULL, NULL);
   CreateWindow("STATIC", "M(кг*10^24):", WS_BORDER|WS_VISIBLE|WS_CHILD, 823, 80, 100, 20, hw, (HMENU)ID_FIRSTNAM, NULL, NULL);
   CreateWindow("STATIC", "G(м^3/кг*с^2):", WS_BORDER|WS_VISIBLE|WS_CHILD, 823, 100, 100, 20, hw, (HMENU)ID_SECONDNM, NULL, NULL);
break;

        case WM_PAINT:
hDC = BeginPaint(hw, &ps);

SelectObject( hDC, Pen_Clear);
SelectObject( hDC, Brush_Clear);

Rectangle( hDC, 0, 0, 1023, 639);

SelectObject( hDC, Pen_Axis);
SelectObject( hDC, Brush_Axis);

Ellipse( hDC, 462, 370, 562, 270);      //512, 320 центр поля

SelectObject(hDC, Pen_Graph);

if(flag == 1){
    r = sqrtf(x*x + y*y);
    v_x = v_x - 0.001*C*x/(r*r*r);
    v_y = v_y - 0.001*C*y/(r*r*r);
    x = x + 0.001*v_x;
    y = y + 0.001*v_y;
    t = 0;

    while((r >= R-0.05) && (t <= 300) ){

        MoveToEx(hDC, (50/R)*x+512, -(50/R)*y+320, NULL);

        r = sqrtf(x*x + y*y);
        v_x = v_x - 0.001*C*x/(r*r*r);
        v_y = v_y - 0.001*C*y/(r*r*r);
        x = x + 0.001*v_x;
        y = y + 0.001*v_y;

        LineTo(hDC, (50/R)*x+512, -(50/R)*y+320);

        t = t + 0.001;

    }
}


return 0;
//break;

  case WM_COMMAND:
      flag = 0;
   /* нажата наша кнопочка? */
   if((HIWORD(wp) == 0) || (LOWORD(wp) == ID_MYBUTTON)){
        flag = 1;
        GetDlgItemText(hw, ID_STARTSPD, LPSTR(V0), 80 );
        GetDlgItemText(hw, ID_MASVALUE, LPSTR(m), 80 );
        GetDlgItemText(hw, ID_ANGLFIRE, LPSTR(A), 80 );
        GetDlgItemText(hw, ID_GRVCONST, LPSTR(G), 80 );
        GetDlgItemText(hw, ID_EARTHMAS, LPSTR(M), 80);
        GetDlgItemText(hw, ID_EARTHRNG, LPSTR(RANGE), 80);

        if(V0[0] == 0){
                MessageBox(hw,"Input start speed","ERROR",MB_OK|MB_ICONERROR);
        } else if(m[0] == 0){
            MessageBox(hw,"Input mass","ERROR",MB_OK|MB_ICONERROR);
        } else if(M[0] == 0){
            MessageBox(hw,"Input earth mass","ERROR",MB_OK|MB_ICONERROR);
        } else if(A[0] == 0){
            MessageBox(hw,"Input start angle","ERROR",MB_OK|MB_ICONERROR);
        } else if(G[0] == 0){
            MessageBox(hw,"Input gravity constant","ERROR",MB_OK|MB_ICONERROR);
        } else if(RANGE[0] == 0){
            MessageBox(hw,"Input radius of earth","ERROR",MB_OK|MB_ICONERROR);

        } else {
            Mass = atof(M);
            mass = atof(m);
            G_const = atof(G);
            v_start = atof(V0);
            ang = atof(A);
            R = atof(RANGE);
            x_start = 0;
            y_start = R;
            ang = ang*3.14159/180;
            x = 0;
            y = R;
            v_y = v_start*sin(ang);
            v_x = v_start*cos(ang);
            C = 10*G_const*Mass;

            InvalidateRect(hw, NULL, FALSE);
        }

   }



return 0;
  case WM_DESTROY:
   /* пользователь закрыл окно, программа может завершаться */
   PostQuitMessage(0);
   return 0;
 }
 return DefWindowProc(hw,msg,wp,lp);
}
