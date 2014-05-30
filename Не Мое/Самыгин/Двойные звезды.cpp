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
#define ID_SEVENNAM 17
#define ID_XSTART 15
#define ID_YSTART 16





#define ID_SCALELN1 23
#define ID_SCALELN2 24


double v_y = 0, t = 0, x = 0, v_y_step = 0, y = 0, v_x = 0, v_x_step = 0, scale = 1, char_value = 1, accuracy = 0;

double ang = 0, m2 = 0, y_start = 0, v_start = 0, x_start = 0, G_const = 0, m1 = 0, C = 0, r1 = 0, r2 = 0;
double x_step = 0, y_step = 0, r1_step = 0, r2_step = 0;
int flag, i, j = 1; // flag = 1 -один выстрел, 2 - подборка оптимального угла, 0 - установка мишение, 4 - пристрелка к мишени

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

HWND hw_angle, hw_earthacc, hw_startspd, hw_mass, hw_earth_mass, hw_gravity_const, hw_x0, hw_y0;

char G[20], A[20], M1[20], M2[20], V0[20], MAX_ANGLE[20], X0[20], DISTANCE[20], KK[20], SCALE[20], ACCURACY[20], Y0[20];

char* p;

HDC hDC;
PAINTSTRUCT ps; //создаём контекст устройства


HPEN Pen_Star = CreatePen( PS_SOLID, 1, RGB(250, 160, 10));
HPEN Pen_Clear = CreatePen( PS_SOLID, 2, RGB(0, 0, 0));
HPEN Pen_Axis = CreatePen( PS_SOLID, 2, RGB(255, 255, 255));
HPEN Pen_Graph2 = CreatePen( PS_SOLID, 1, RGB(255, 0, 0));
HPEN Pen_Graph = CreatePen( PS_SOLID, 3, RGB(0, 0, 255));
HBRUSH Brush_Clear = CreateSolidBrush( RGB(0, 0, 0) );
HBRUSH Brush_Axis = CreateSolidBrush( RGB(255, 255, 255));
HBRUSH Brush_Star = CreateSolidBrush( RGB(250, 160, 10));
HBRUSH Brush_Graph = CreateSolidBrush( RGB(255, 0, 0));


 switch (msg) {
  case WM_CREATE:
   /* при создании окна внедряем в него кнопочку */
   CreateWindow("button","FIRE",WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,
    823,160,200,20,hw,(HMENU)ID_MYBUTTON,NULL,NULL);

   /* стиль WS_CHILD означает, что это дочернее окно и для него
    вместо дескриптора меню будет передан целочисленный идентификатор,
    который будет использоваться дочерним окном для оповещения
    родительского окна через WM_COMMAND */


   hw_angle = CreateWindow("EDIT","42.2",WS_BORDER|WS_VISIBLE|WS_CHILD|ES_LEFT|ES_MULTILINE,
        923,60,100,20,hw,(HMENU)ID_ANGLFIRE,NULL,NULL);
   hw_mass = CreateWindow("EDIT","2",WS_BORDER|WS_VISIBLE|WS_CHILD|ES_LEFT|ES_MULTILINE,
        923,40,100,20,hw,(HMENU)ID_MASVALUE,NULL,NULL);
   hw_startspd = CreateWindow("EDIT","3.465",WS_BORDER|WS_VISIBLE|WS_CHILD|ES_LEFT|ES_MULTILINE,
        923,20,100,20,hw,(HMENU)ID_STARTSPD,NULL,NULL);
   hw_earth_mass = CreateWindow("EDIT", "2", WS_BORDER|WS_VISIBLE|WS_CHILD|ES_LEFT|ES_MULTILINE,
        923,80,100,20,hw,(HMENU)ID_EARTHMAS,NULL,NULL);
   hw_gravity_const = CreateWindow("EDIT", "6.67", WS_BORDER|WS_VISIBLE|WS_CHILD|ES_LEFT|ES_MULTILINE,
        923,100,100,20,hw,(HMENU)ID_GRVCONST,NULL,NULL);
   hw_x0 = CreateWindow("EDIT", "0", WS_BORDER|WS_VISIBLE|WS_CHILD|ES_LEFT|ES_MULTILINE,
        923,120,100,20,hw,(HMENU)ID_XSTART,NULL,NULL);
   hw_y0 = CreateWindow("EDIT", "0", WS_BORDER|WS_VISIBLE|WS_CHILD|ES_LEFT|ES_MULTILINE,
        923,140,100,20,hw,(HMENU)ID_YSTART,NULL,NULL);


   CreateWindow("STATIC", "X0(-512/512)", WS_BORDER|WS_VISIBLE|WS_CHILD, 823, 120, 100, 20, hw, (HMENU)ID_FITHNAME, NULL, NULL);
   CreateWindow("STATIC", "ma = G(m*M)/(r*r)", WS_BORDER|WS_VISIBLE|WS_CHILD, 823, 0, 200, 20, hw, (HMENU)ID_EQUASION, NULL, NULL);
   CreateWindow("STATIC", "f(градусы):", WS_BORDER|WS_VISIBLE|WS_CHILD, 823, 60, 100, 20, hw, (HMENU)ID_THIRDNAM, NULL, NULL);
   CreateWindow("STATIC", "M1(кг*10^30):", WS_BORDER|WS_VISIBLE|WS_CHILD, 823, 40, 100, 20, hw, (HMENU)ID_FOURTHNM, NULL, NULL);
   CreateWindow("STATIC", "V0(Мм/с):", WS_BORDER|WS_VISIBLE|WS_CHILD, 823, 20, 100, 20, hw, (HMENU)ID_SIXTHNAM, NULL, NULL);
   CreateWindow("STATIC", "M2(кг*10^30):", WS_BORDER|WS_VISIBLE|WS_CHILD, 823, 80, 100, 20, hw, (HMENU)ID_FIRSTNAM, NULL, NULL);
   CreateWindow("STATIC", "G*10^-11:", WS_BORDER|WS_VISIBLE|WS_CHILD, 823, 100, 100, 20, hw, (HMENU)ID_SECONDNM, NULL, NULL);
   CreateWindow("STATIC", "Y0(-320/320):", WS_BORDER|WS_VISIBLE|WS_CHILD, 823, 140, 100, 20, hw, (HMENU)ID_SEVENNAM, NULL, NULL);
break;

        case WM_PAINT:
hDC = BeginPaint(hw, &ps);

SelectObject( hDC, Pen_Clear);
SelectObject( hDC, Brush_Clear);

Rectangle( hDC, 0, 0, 1023, 639);

SelectObject( hDC, Pen_Star);
SelectObject( hDC, Brush_Star);

Ellipse( hDC, 187, 345, 237, 295);
Ellipse( hDC, 788, 345, 838, 295);     //512, 320 центр поля 300 пикселей - 1 Гм

SelectObject(hDC, Pen_Graph);

if(flag == 1){
    x = x_start;
    y = y_start;
    r1 = 1000*sqrtf((x-1)*(x-1) + y*y);
    r2 = 1000*sqrtf((x+1)*(x+1) + y*y);
    v_x = v_x - 0.001*C*x*(m1/(r1*r1*r1) + m2/(r2*r2*r2));
    v_y = v_y - 0.001*C*y*(m1/(r1*r1*r1) + m2/(r2*r2*r2));
    x = x + 0.001*v_x/1000;
    y = y + 0.001*v_y/1000;
    t = 0;
    v_x = j*v_x;


    while((t <= 500) && (r1 >= 1) && (r2 >= 1)){

    //    SelectObject(hDC, Pen_Graph);

        MoveToEx(hDC, 30*x+512, -30*y+320, NULL);
       // LineTo(hDC, 30*x+512, -30*y+320);

        r1 = sqrtf((x-10)*(x-10) + y*y);
        r2 = sqrtf((x+10)*(x+10) + y*y);
        v_x = v_x - 0.001*C*(m1*(x-10)/(r1*r1*r1) + m2*(x+10)/(r2*r2*r2));
        v_y = v_y - 0.001*C*y*(m1/(r1*r1*r1) + m2/(r2*r2*r2));
        x = x + 0.001*v_x;
        y = y + 0.001*v_y;
/*
        r1_step = r1;
        r2_step = r2;
        x_step = x;
        y_step = y;
        v_x_step = v_x;
        v_y_step = v_y;

        for(i = 0; i < 10; i++){
                v_x_step = v_x_step - 0.001*C*(m1*(x-10)/(r1*r1*r1) + m2*(x+10)/(r2*r2*r2));
                v_y_step = v_y_step - 0.001*C*y*(m1/(r1*r1*r1) + m2/(r2*r2*r2));
                x_step = x_step + 0.001*v_x_step;
                y_step = y_step+ 0.001*v_y_step;
        }

        SelectObject(hDC, Pen_Graph2);
        SelectObject(hDC, Brush_Graph);
        Ellipse(hDC, 30*x_step+511, -30*y_step+319, 30*x_step+513, -30*y_step+321);
*/
        SelectObject(hDC, Pen_Graph);
        LineTo(hDC, 30*x+512, -30*y+320);
//        Sleep(0.1);
        t = t + 0.001;

    }
   /* x = 0;
    y = 0;
    v_y = 0;
    v_x = 0;
    r1 = 0;
    r2 = 0;*/
    flag = 0;
}


return 0;
//break;

  case WM_COMMAND:
      flag = 0;
   /* нажата наша кнопочка? */
   if((HIWORD(wp) == 0) || (LOWORD(wp) == ID_MYBUTTON)){
        flag = 1;
        GetDlgItemText(hw, ID_STARTSPD, LPSTR(V0), 80 );
        GetDlgItemText(hw, ID_MASVALUE, LPSTR(M1), 80 );
        GetDlgItemText(hw, ID_ANGLFIRE, LPSTR(A), 80 );
        GetDlgItemText(hw, ID_GRVCONST, LPSTR(G), 80 );
        GetDlgItemText(hw, ID_EARTHMAS, LPSTR(M2), 80);
        GetDlgItemText(hw, ID_XSTART, LPSTR(X0), 80);
        GetDlgItemText(hw, ID_YSTART, LPSTR(Y0), 80);

        if(V0[0] == 0){
                MessageBox(hw,"Input start speed","ERROR",MB_OK|MB_ICONERROR);
        } else if(M1[0] == 0){
            MessageBox(hw,"Input first star mass","ERROR",MB_OK|MB_ICONERROR);
        } else if(M2[0] == 0){
            MessageBox(hw,"Input second star mass","ERROR",MB_OK|MB_ICONERROR);
        } else if(A[0] == 0){
            MessageBox(hw,"Input start angle","ERROR",MB_OK|MB_ICONERROR);
        } else if(G[0] == 0){
            MessageBox(hw,"Input gravity constant","ERROR",MB_OK|MB_ICONERROR);
        } else if(X0[0] == 0){
            MessageBox(hw,"Input start x","ERROR",MB_OK|MB_ICONERROR);
        } else if(Y0[0] == 0){
            MessageBox(hw,"Input start y","ERROR",MB_OK|MB_ICONERROR);

        } else {
            m1 = atof(M1);
            m2 = atof(M2);
            G_const = atof(G);
            v_start = atof(V0);
            ang = atof(A);

            if ((ang == 90) || (ang == -90)){
                j = 0;
            } else {
                j = 1;
            }

            x_start = atof(X0);
            y_start = atof(Y0);
            ang = ang*3.14159/180;
            x_start = x_start/30;
            y_start = y_start/30;
            v_y = v_start*sin(ang);
            v_x = v_start*cos(ang);
            C = G_const*10;

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
