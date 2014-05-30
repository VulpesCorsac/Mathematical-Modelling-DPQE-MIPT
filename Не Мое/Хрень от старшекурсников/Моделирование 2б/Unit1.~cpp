//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Math.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CGRID"
#pragma resource "*.dfm"

#define G1 400200
#define G2 400200
#define h 0.1
#define x1 -30000
#define x2 30000

TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        Series1->AddXY(x1, 0, "", clBackground);
        Series1->AddXY(x2, 0, "", clBackground);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
        long double m, ax, ay, V0, Vx, Vy, x, y, r1, r2, alfa, k1, k2, k3, k4;
        long int i, f = 0;
        m = StrToFloat(Edit1->Text.c_str());
        x = StrToFloat(Edit2->Text.c_str());
        y = StrToFloat(Edit3->Text.c_str());
        V0 = StrToFloat(Edit4->Text.c_str());
        alfa = StrToFloat(Edit5->Text.c_str())*M_PI/180;
        Vx = V0*cos(alfa);
        Vy = V0*sin(alfa);
        while(!(Button2->Focused()))
        {
                if(i % 400 == 1)
                {
                        Series2->AddXY(x, y, "", clBackground);
                        if (Button4->Focused()) Series3->AddXY(x, y, "", CColorGrid1->ForegroundColor);
                        Application->ProcessMessages();
                }
                r1 = (x1-x)*(x1-x) + y*y;
                r2 = (x2-x)*(x2-x) + y*y;
                ax = -G1*m/r1*(x-x1)/sqrt(r1) - G2/r2*(x-x2)/sqrt(r2);
                ay = -G1*m/r1*y/sqrt(r1) - G2/r2*y/sqrt(r2);
                k1=h*Vx;
                k2=h*(Vx+ax*h/2);
                k3=k2;
                k4=h*(Vx+ax*h);
                x+=(k1+2*k2+2*k3+k4)/6;
                k1=h*Vy;
                k2=h*(Vy+ay*h/2);
                k3=k2;
                k4=h*(Vy+ay*h);
                y+=(k1+2*k2+2*k3+k4)/6;
                Vx+=ax*h;
                Vy+=ay*h;
                Series2->Clear();
                i++;
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
        Series2->Clear();
        Series3->Clear();        
}
//---------------------------------------------------------------------------

