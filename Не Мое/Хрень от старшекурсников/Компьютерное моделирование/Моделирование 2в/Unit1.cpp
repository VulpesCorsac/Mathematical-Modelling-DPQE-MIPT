//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Math.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define Gs 132736162900
#define Gu 126709678
#define Gc 37938156
#define Gz 400000
#define h 50
#define h1 0.05

double Pz=150000000, Pu=800000000, Pc=1500000000, wz=0.000717, wu=0.000060425,wc=0.000024333;

TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        Series1->AddXY(0,0,"",clBackground);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
        long double alfa_u, yu, xu, alfa_c, yc, xc, alfa_z=M_PI, yz, xz,
                    x, y, r, ax, ay, V, Vx, Vy, k1, k2, k3, k4, u=Pu*2, c=Pc*2;
        int i=0;

        alfa_u = StrToFloat(Edit1->Text.c_str())*M_PI/180;
        alfa_c = StrToFloat(Edit2->Text.c_str())*M_PI/180;
        x = -Pz;
        y = 0;
        V = StrToFloat(Edit3->Text.c_str());
        Vx = 0;
        Vy = V;

        while (!(Button2->Focused()))
        {
                if (i % 10000 == 1)
                {
                        Series2->AddXY(xu, yu, "", clBackground);
                        Series3->AddXY(xc, yc, "", clBackground);
                        Series4->AddXY(xz, yz, "", clBackground);
                        Series5->AddXY(x, y, "", clBackground);
                        Memo1->Lines->Add(FloatToStr(u/1000));
                        Memo2->Lines->Add(FloatToStr(c/1000));
                        Application->ProcessMessages();
                }
                alfa_z-=wz*h1;
                xz=Pz*cos(alfa_z);
                yz=Pz*sin(alfa_z);
                alfa_u-=wu*h1;
                xu=Pu*cos(alfa_u);
                yu=Pu*sin(alfa_u);
                alfa_c-=wc*h1;
                xc=Pc*cos(alfa_c);
                yc=Pc*sin(alfa_c);

                r = x*x+y*y;
                ax = -Gs/r*x/sqrt(r);
                ay = -Gs/r*y/sqrt(r);
                r = (xz-x)*(xz-x)+(yz-y)*(yz-y);
                ax-= Gz/r*(x-xz)/sqrt(r);
                ay-= Gz/r*(y-yz)/sqrt(r);
                r = (xu-x)*(xu-x)+(yu-y)*(yu-y);
                if (r<(u*u)) u=sqrt(r);
                ax-= Gu/r*(x-xu)/sqrt(r);
                ay-= Gu/r*(y-yu)/sqrt(r);
                r = (xc-x)*(xc-x)+(yc-y)*(yc-y);
                if (r<(c*c)) c=sqrt(r);
                ax-= Gc/r*(x-xc)/sqrt(r);
                ay-= Gc/r*(y-yc)/sqrt(r);
                k1=Vx;
                k2=(Vx+ax*h/2);
                k3=k2;
                k4=(Vx+ax*h);
                x+=h*(k1+2*k2+2*k3+k4)/6;
                k1=Vy;
                k2=(Vy+ay*h/2);
                k3=k2;
                k4=(Vy+ay*h);
                y+=h*(k1+2*k2+2*k3+k4)/6;
                Vx+=ax*h;
                Vy+=ay*h;



                Series2->Clear();
                Series3->Clear();
                Series4->Clear();
                Series5->Clear();

                i++;
        }

}
//---------------------------------------------------------------------------

