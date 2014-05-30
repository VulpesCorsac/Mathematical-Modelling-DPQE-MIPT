#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

LRESULT CALLBACK MainWinProc(HWND,UINT,WPARAM,LPARAM);
#define ID_MYBUTTON 1
#define ID_MASVALUE 2
#define ID_EARTHACC 3
#define ID_ANGLFIRE 4
#define ID_RESISTAN 5
#define ID_EQUASION 6
#define ID_FIRSTNAM 7
#define ID_SECONDNM 8
#define ID_THIRDNAM 9
#define ID_FOURTHNM 10
#define ID_FITHNAME 11
#define ID_SIXTHNAM 12
#define ID_STARTSPD 13
#define ID_FIREMANY 14
#define ID_MAXLENG1 15
#define ID_MAXLENG2 16
#define ID_SETDISTN 17
#define ID_DISTANCE 18
#define ID_DISTNINF 19
#define ID_RESISTN2 20
#define ID_RESISTSQ 21
#define ID_FIRETARG 22
#define ID_SCALELN1 23
#define ID_SCALELN2 24


float v_y = 0, t = 0, x = 0, x_step = 0, v_y_step = 0, y = 0, y_step = 0, v_x = 0, v_x_step = 0, target = 0, d_v = 0, scale = 1, char_value = 1, accuracy = 0;
//float k1, k2, k3, k4, k1n, k2n, k3n, k4n;
float ang = 0, m = 0, y_start = 0, v_start = 0, x_start = 0, g = 0, k = 0, x_last_max[2], max_angle[2], low_angle = 0, d_ang = 0, use_angle = 0, kk = 0;
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

HWND hw_distance, hw_angle, hw_resistan, hw_attconst, hw_earthacc, hw_startspd, hw_mass, hw_resist2;

char G[20], A[20], M[20], K[20], V0[20], MAX_ANGLE[20], RANGE[20], DISTANCE[20], KK[20], SCALE[20], ACCURACY[20];

char* p;

HDC hDC;
PAINTSTRUCT ps; //создаём контекст устройства


HPEN Pen1 = CreatePen( PS_SOLID, 1, RGB(0, 0, 255));
HPEN Pen_Clear = CreatePen( PS_SOLID, 2, RGB(0, 0, 0));
HPEN Pen_Axis = CreatePen( PS_SOLID, 2, RGB(255, 255, 255));
HPEN Pen4 = CreatePen( PS_SOLID, 1, RGB(0, 255, 0));
HPEN Pen_Graph = CreatePen( PS_SOLID, 1, RGB(255, 0, 0));
HBRUSH Brush_Clear = CreateSolidBrush( RGB(0, 0, 0) );


 switch (msg) {
  case WM_CREATE:
   /* при создании окна внедряем в него кнопочку */
   CreateWindow("button","FIRE",WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,
    823,160,200,20,hw,(HMENU)ID_MYBUTTON,NULL,NULL);
   CreateWindow("button","CALCULATE ANGLE",WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,
    823,140,200,20,hw,(HMENU)ID_FIREMANY,NULL,NULL);
   CreateWindow("button","SET TARGET", WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,
    623,80,200,20,hw,(HMENU)ID_SETDISTN,NULL,NULL);
   CreateWindow("button","FIRE ON TARGET", WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,
    623,100,200,20,hw,(HMENU)ID_FIRETARG,NULL,NULL);

   /* стиль WS_CHILD означает, что это дочернее окно и для него
    вместо дескриптора меню будет передан целочисленный идентификатор,
    который будет использоваться дочерним окном для оповещения
    родительского окна через WM_COMMAND */


   hw_distance = CreateWindow("EDIT","19.37",WS_BORDER|WS_VISIBLE|WS_CHILD|ES_LEFT|ES_MULTILINE,
        723,40,100,20,hw,(HMENU)ID_DISTANCE,NULL,NULL);
   hw_earthacc = CreateWindow("EDIT","9.8",WS_BORDER|WS_VISIBLE|WS_CHILD|ES_LEFT|ES_MULTILINE,
        903,80,120,20,hw,(HMENU)ID_EARTHACC,NULL,NULL);
   hw_angle = CreateWindow("EDIT","45.0",WS_BORDER|WS_VISIBLE|WS_CHILD|ES_LEFT|ES_MULTILINE,
        903,60,120,20,hw,(HMENU)ID_ANGLFIRE,NULL,NULL);
   hw_mass = CreateWindow("EDIT","100.0",WS_BORDER|WS_VISIBLE|WS_CHILD|ES_LEFT|ES_MULTILINE,
        903,40,120,20,hw,(HMENU)ID_MASVALUE,NULL,NULL);
   hw_resistan = CreateWindow("EDIT","20.0",WS_BORDER|WS_VISIBLE|WS_CHILD|ES_LEFT|ES_MULTILINE,
        903,100,120,20,hw,(HMENU)ID_RESISTAN,NULL,NULL);
   hw_startspd = CreateWindow("EDIT","600.0",WS_BORDER|WS_VISIBLE|WS_CHILD|ES_LEFT|ES_MULTILINE,
        903,20,120,20,hw,(HMENU)ID_STARTSPD,NULL,NULL);
   hw_resist2 = CreateWindow("EDIT","40.0",WS_BORDER|WS_VISIBLE|WS_CHILD|ES_LEFT|ES_MULTILINE,
        903,120,120,20,hw,(HMENU)ID_RESISTSQ,NULL,NULL);


   CreateWindow("STATIC", "ma = mg - KV - K2V^2", WS_BORDER|WS_VISIBLE|WS_CHILD, 823, 0, 200, 20, hw, (HMENU)ID_EQUASION, NULL, NULL);
   CreateWindow("STATIC", "K(мкПа*с):", WS_BORDER|WS_VISIBLE|WS_CHILD, 823, 100, 80, 20, hw, (HMENU)ID_FIRSTNAM, NULL, NULL);
   CreateWindow("STATIC", "g(м/с^2):", WS_BORDER|WS_VISIBLE|WS_CHILD, 823, 80, 80, 20, hw, (HMENU)ID_SECONDNM, NULL, NULL);
   CreateWindow("STATIC", "f(градусы):", WS_BORDER|WS_VISIBLE|WS_CHILD, 823, 60, 80, 20, hw, (HMENU)ID_THIRDNAM, NULL, NULL);
   CreateWindow("STATIC", "m(кг):", WS_BORDER|WS_VISIBLE|WS_CHILD, 823, 40, 80, 20, hw, (HMENU)ID_FOURTHNM, NULL, NULL);
   CreateWindow("STATIC", "Maximum Range", WS_BORDER|WS_VISIBLE|WS_CHILD|ES_CENTER, 623, 0, 200, 20, hw, (HMENU)ID_MAXLENG1, NULL, NULL);
   CreateWindow("STATIC", "V0(м/с):", WS_BORDER|WS_VISIBLE|WS_CHILD, 823, 20, 80, 20, hw, (HMENU)ID_SIXTHNAM, NULL, NULL);
   CreateWindow("STATIC", "0.0", WS_BORDER|WS_VISIBLE|WS_CHILD|ES_CENTER, 623, 20, 200, 20, hw, (HMENU)ID_MAXLENG2, NULL, NULL );
   CreateWindow("STATIC", "TARGET(км):", WS_BORDER|WS_VISIBLE|WS_CHILD, 623, 40, 100, 20, hw, (HMENU)ID_DISTNINF, NULL, NULL );
   CreateWindow("STATIC", "K2(мкПа*м):", WS_BORDER|WS_VISIBLE|WS_CHILD, 823, 120, 80, 20, hw, (HMENU)ID_RESISTN2, NULL, NULL );
   CreateWindow("STATIC", "ACCURACY(м):", WS_BORDER|WS_VISIBLE|WS_CHILD, 623, 60, 100, 20, hw, (HMENU)ID_SCALELN1, NULL, NULL );
   CreateWindow("EDIT", "50", WS_BORDER|WS_VISIBLE|WS_CHILD|ES_LEFT|ES_MULTILINE, 723, 60, 100, 20, hw, (HMENU)ID_SCALELN2, NULL, NULL );
//   CreateWindow("STATIC", "V(X)", WS_BORDER|WS_VISIBLE|WS_CHILD, 370, 0, 30, 20, hw, (HMENU)ID_GRAFINF3, NULL, NULL );

break;

        case WM_PAINT:
hDC = BeginPaint(hw, &ps);

SelectObject( hDC, Pen_Clear);
SelectObject( hDC, Brush_Clear);

Rectangle( hDC, 0, 0, 1023, 639);

SelectObject( hDC, Pen_Axis);

MoveToEx( hDC, 25, 0, NULL ); //25, 594 точка (0,0)
LineTo( hDC, 25, 639 );
MoveToEx( hDC, 0, 594, NULL );
LineTo( hDC, 1023, 594 );

if(flag != -1){
    MoveToEx( hDC, (target/scale)*750*1000+25, 594, NULL);
    LineTo( hDC, (target/scale)*750*1000+25, 494);
}


SelectObject(hDC, Pen_Graph);


if(flag == 1){                             //Просто выстрел

while(y >= 0){

    v_x = (v_x) - 0.001*(k*v_x*t+kk*v_x*v_x*char_value*t*t)/m;
	x = (x+0.001*v_x);
	v_y = (v_y) - 0.001*(g/char_value+(k*v_y*t+kk*v_y*v_y*char_value*t*t)/m);
    y = (y+0.001*v_y);
	v_x_step = v_x - 0.001*((k*v_x*t)+(kk*v_x*v_x*char_value*t*t))/m;
	v_y_step = v_y - 0.001*(g/char_value+((k*v_y*t)+(kk*v_y*v_y*char_value*t*t))/m);
	x_step = (x+0.001*v_x);
	y_step = (y+0.001*v_y);

    MoveToEx(hDC, (750/scale)*x*(char_value*t*t)+25, (-750/scale)*y*(char_value*t*t)+594, NULL);
    LineTo(hDC, (750/scale)*x_step*(char_value*t*t)+25, (-750/scale)*y_step*(char_value*t*t)+594);


}
x = x*char_value*t*t;
sprintf(RANGE, "%f", x);
SetDlgItemText(hw, ID_MAXLENG2, LPCSTR(RANGE));
}

if(flag == 2){                           //Подборка оптимального угла
        d_ang = 0;
        low_angle = 0;
        max_angle[0] = 0;
        max_angle[1] = 0;
        x_last_max[0] = 0;
        x_last_max[1] = 0;
    for(i = 0; i < 15; i++){
      for(j = 1; j < 3; j++){
            use_angle = (ang*j/3) + d_ang;
            v_y = v_start*sin(use_angle);
            v_x = v_start*cos(use_angle);
            x = x_start;
            y = y_start;

            while(y >= 0){

                v_x = (v_x) - 0.001*(k*v_x*t+kk*v_x*v_x*char_value*t*t)/m;
                x = (x+0.001*v_x);
                v_y = (v_y) - 0.001*(g/char_value+(k*v_y*t+kk*v_y*v_y*char_value*t*t)/m);
                y = (y+0.001*v_y);
                v_x_step = v_x - 0.001*((k*v_x*t)+(kk*v_x*v_x*char_value*t*t))/m;
                v_y_step = v_y - 0.001*(g/char_value+((k*v_y*t)+(kk*v_y*v_y*char_value*t*t))/m);
                x_step = (x+0.001*v_x);
                y_step = (y+0.001*v_y);

                MoveToEx(hDC, (750/scale)*x*(char_value*t*t)+25, (-750/scale)*y*(char_value*t*t)+594, NULL);
                LineTo(hDC, (750/scale)*x_step*(char_value*t*t)+25, (-750/scale)*y_step*(char_value*t*t)+594);
            }
            if(x > x_last_max[0]){          //максимум абсолютный
                x_last_max[0] = x;
                max_angle[0] = use_angle;
            }
            if((x > x_last_max[1]) || (max_angle[1] == 0)){          //максимум по текущей выборке
                x_last_max[1] = x;
                max_angle[1] = use_angle;
            }
            if((x < x_last_max[1]) || (low_angle == 0)){
                low_angle = use_angle;
            }
        }
        if(max_angle[1] > low_angle){
            d_ang = d_ang + ang/3;
        }
        ang = ang*2/3;
        low_angle = 0;
        max_angle[1] = 0;
        }
      sprintf(RANGE, "%f", x_last_max[0]*char_value*t*t);
      SetDlgItemText(hw, ID_MAXLENG2, LPCSTR(RANGE));
      max_angle[0] = max_angle[0]*180/3.14159;
      sprintf(MAX_ANGLE, "%f", max_angle[0]);
      SetDlgItemText(hw, ID_ANGLFIRE, LPCSTR(MAX_ANGLE));
    }

    if(flag == 4){   //Подборка скорости на дальность
        d_v = 100/(char_value*t);
        v_start = 500/(char_value*t);

        for(d_v = 100/(char_value*t);(((x - target*1000/(char_value*t*t)) < -accuracy/(char_value*t*t)) || ((x - target*1000/(char_value*t*t)) > accuracy/(char_value*t*t))); d_v = d_v/2){
            while(x > target*1000/(char_value*t*t)){
                v_start = v_start - d_v;
                v_y = v_start*sin(ang);
                v_x = v_start*cos(ang);
                x = x_start;
                y = y_start;

                while(y >= 0){

                    v_x = (v_x) - 0.001*(k*v_x*t+kk*v_x*v_x*char_value*t*t)/m;
                    x = (x+0.001*v_x);
                    v_y = (v_y) - 0.001*(g/char_value+(k*v_y*t+kk*v_y*v_y*char_value*t*t)/m);
                    y = (y+0.001*v_y);
                    v_x_step = v_x - 0.001*((k*v_x*t)+(kk*v_x*v_x*char_value*t*t))/m;
                    v_y_step = v_y - 0.001*(g/char_value+((k*v_y*t)+(kk*v_y*v_y*char_value*t*t))/m);
                    x_step = (x+0.001*v_x);
                    y_step = (y+0.001*v_y);

                    MoveToEx(hDC, (750/scale)*x*(char_value*t*t)+25, (-750/scale)*y*(char_value*t*t)+594, NULL);
                    LineTo(hDC, (750/scale)*x_step*(char_value*t*t)+25, (-750/scale)*y_step*(char_value*t*t)+594);


            }
            }

            while(x < target*1000/(char_value*t*t)){
                v_start = v_start + d_v;
                v_y = v_start*sin(ang);
                v_x = v_start*cos(ang);
                x = x_start;
                y = y_start;

                while(y >= 0){

                    v_x = (v_x) - 0.001*(k*v_x*t+kk*v_x*v_x*char_value*t*t)/m;
                    x = (x+0.001*v_x);
                    v_y = (v_y) - 0.001*(g/char_value+(k*v_y*t+kk*v_y*v_y*char_value*t*t)/m);
                    y = (y+0.001*v_y);
                    v_x_step = v_x - 0.001*((k*v_x*t)+(kk*v_x*v_x*char_value*t*t))/m;
                    v_y_step = v_y - 0.001*(g/char_value+((k*v_y*t)+(kk*v_y*v_y*char_value*t*t))/m);
                    x_step = (x+0.001*v_x);
                    y_step = (y+0.001*v_y);

                    MoveToEx(hDC, (750/scale)*x*(char_value*t*t)+25, (-750/scale)*y*(char_value*t*t)+594, NULL);
                    LineTo(hDC, (750/scale)*x_step*(char_value*t*t)+25, (-750/scale)*y_step*(char_value*t*t)+594);


                }
            }
            sprintf(V0, "%f", v_start*char_value*t);
            SetDlgItemText(hw, ID_STARTSPD, LPCSTR(V0));
            sprintf(RANGE, "%f", x*char_value*t*t);
            SetDlgItemText(hw, ID_MAXLENG2, LPCSTR(RANGE));
        }
    }


EndPaint(hw, &ps);
return 0;
//break;

  case WM_COMMAND:
   /* нажата наша кнопочка? */
   if ((HIWORD(wp)==0) && ((LOWORD(wp)==ID_MYBUTTON) || (LOWORD(wp)==ID_FIREMANY) || (LOWORD(wp)==ID_SETDISTN) || (LOWORD(wp)==ID_FIRETARG))){

      if((HIWORD(wp)==0) && (LOWORD(wp)==ID_MYBUTTON)){
        flag = 1;
      }

      GetDlgItemText(hw, ID_STARTSPD, LPSTR(V0), 80 );
      GetDlgItemText(hw, ID_MASVALUE, LPSTR(M), 80 );
      GetDlgItemText(hw, ID_ANGLFIRE, LPSTR(A), 80 );
      GetDlgItemText(hw, ID_RESISTAN, LPSTR(K), 80 );
      GetDlgItemText(hw, ID_EARTHACC, LPSTR(G), 80 );
      GetDlgItemText(hw, ID_DISTANCE, LPSTR(DISTANCE), 80);
      GetDlgItemText(hw, ID_RESISTSQ, LPSTR(KK), 80 );
      GetDlgItemText(hw, ID_SCALELN2, LPSTR(ACCURACY), 80 );

      if((HIWORD(wp)==0) && (LOWORD(wp)==ID_SETDISTN)){
            if(DISTANCE[0] == 0){
                MessageBox(hw,"Input distance to target","ERROR",MB_OK|MB_ICONERROR);
                flag = -1;
            } else {
                flag = 0;
            }
      }
      if(ACCURACY[0] == 0){
         MessageBox(hw,"Input accuracy","ERROR",MB_OK|MB_ICONERROR);
      } else
      if(V0[0] == 0){
         MessageBox(hw,"Input start speed","ERROR",MB_OK|MB_ICONERROR);
      } else
      if(M[0] == 0){
         MessageBox(hw,"Input mass","ERROR",MB_OK|MB_ICONERROR);
      } else
      if(A[0] == 0){
         MessageBox(hw,"Input angle of fire","ERROR",MB_OK|MB_ICONERROR);
      } else
      if(G[0] == 0){
         MessageBox(hw,"Input earth acceleration","ERROR",MB_OK|MB_ICONERROR);
      } else
      if(KK[0] == 0){
         MessageBox(hw,"Input second resistance coefficient", "ERROR",MB_OK|MB_ICONERROR);
      } else
      if(K[0] == 0){
         MessageBox(hw,"Input first resistance coefficient","ERROR",MB_OK|MB_ICONERROR);
      } else {

      accuracy = atof(ACCURACY);
      v_start = atof(V0);
      m = atof(M);
      g = atof(G);
      k = atof(K);
      ang = atof(A);
      target = atof(DISTANCE);
      ang = ang*3.14159/180;
      k = k*6*3.14159*0.001;
      kk = atof(KK);
      kk = kk*3*3.14159*0.00001;
      t = 0;
      v_y = v_start*sin(ang);
      v_x = v_start*cos(ang);
      x = x_start;
      y = y_start;

      while(y >= 0){

                v_x = v_x - 0.001*(k*v_x+kk*v_x*v_x)/m;
                x = (x+0.001*v_x);
                v_y = v_y - 0.001*(g+(k*v_y+kk*v_y*v_y)/m);
                y = (y+0.001*v_y);
                v_x_step = v_x - 0.001*(k*v_x+kk*v_x*v_x)/m;
                v_y_step = v_y - 0.001*(g+(k*v_y+kk*v_y*v_y)/m);
                x_step = (x+0.001*v_x);
                y_step = (y+0.001*v_y);
                t = t + 0.001;
//                scale = v_x/t;
      }
      scale = target*1000;
      char_value = -v_y/t;
      v_start = v_start/(char_value*t);
/*    k = k/char_value;
      kk = kk/char_value;
      g = g/char_value;

      sprintf(SCALE, "%f", scale);
      SetDlgItemText(hw, ID_SCALELN2, LPCSTR(SCALE));
*/
      if((HIWORD(wp)==0) && (LOWORD(wp)==ID_FIREMANY)){
        flag = 2;
        ang = 67.5*3.14159/180;
      }
      if((HIWORD(wp)==0) && (LOWORD(wp)==ID_FIRETARG)){
        flag = 4;
      }

      v_y = v_start*sin(ang);
      v_x = v_start*cos(ang);
      x = x_start;
      y = y_start;

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
