//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Math.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#define h 0.025

TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
        double u1=0, u2=0, v1=0, v2=0, t=0, m, K, Kc, g, f, k1, k2, k3, k4;
        int i=0;
        m = StrToFloat(Edit1->Text.c_str());
        K = StrToFloat(Edit2->Text.c_str());
        Kc = StrToFloat(Edit3->Text.c_str());
        f = StrToFloat(Edit4->Text.c_str());
        g = StrToFloat(Edit5->Text.c_str());

        while(!(Button2->Focused()))
        {
                k1 = -(K+Kc)*u1 + Kc*u2 - f*v1 + cos(g*t);
                k2 = -(K+Kc)*u1 + Kc*u2 - f*(v1+k1/2) + cos(g*(t+h/2));
                k3 = -(K+Kc)*u1 + Kc*u2 - f*(v1+k2/2) + cos(g*(t+h/2));
                k4 = -(K+Kc)*u1 + Kc*u2 - f*(v1+k3) + cos(g*(t+h));
                v1+=(k1+2*k2+2*k3+k4)*h/m/6;

                k1 = -(K+Kc)*u2 + Kc*u1 - f*v2;
                k2 = -(K+Kc)*u2 + Kc*u1 - f*(v2+k1/2);
                k3 = -(K+Kc)*u2 + Kc*u1 - f*(v2+k2/2);
                k4 = -(K+Kc)*u2 + Kc*u1 - f*(v2+k3);
                v2+=(k1+2*k2+2*k3+k4)*h/m/6;

                u2+=h*v2;
                u1+=h*v1;
                t+=h;

                Series1->AddXY(v1, u1, "", clBackground);
                Series2->AddXY(v2, u2, "", clBackground);
                Series3->AddXY(t, u1, "", clBackground);
                Series4->AddXY(t, u2, "", clBackground);

                Application->ProcessMessages();
                i++;
        }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
        Series1->Clear();
        Series2->Clear();
        Series3->Clear();
        Series4->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
        double u1=0, u2=0, v1, v2, t=0, m, g=0.8, K, Kc, f, k1, k2, k3, k4, max1=0, max2=0;
        m = StrToFloat(Edit1->Text.c_str());
        K = StrToFloat(Edit2->Text.c_str());
        Kc = StrToFloat(Edit3->Text.c_str());
        f = StrToFloat(Edit4->Text.c_str());

        Series3->Clear();
        Series4->Clear();

        while(g<1.4)
        {
                while(t<2000)
                {
                        k1 = -(K+Kc)*u1 + Kc*u2 - f*v1 + cos(g*t);
                        k2 = -(K+Kc)*u1 + Kc*u2 - f*(v1+k1/2) + cos(g*(t+h/2));
                        k3 = -(K+Kc)*u1 + Kc*u2 - f*(v1+k2/2) + cos(g*(t+h/2));
                        k4 = -(K+Kc)*u1 + Kc*u2 - f*(v1+k3) + cos(g*(t+h));
                        v1+=(k1+2*k2+2*k3+k4)*h/m/6;

                        k1 = -(K+Kc)*u2 + Kc*u1 - f*v2;
                        k2 = -(K+Kc)*u2 + Kc*u1 - f*(v2+k1/2);
                        k3 = -(K+Kc)*u2 + Kc*u1 - f*(v2+k2/2);
                        k4 = -(K+Kc)*u2 + Kc*u1 - f*(v2+k3);
                        v2+=(k1+2*k2+2*k3+k4)*h/m/6;

                        u2+=h*v2;
                        u1+=h*v1;
                        t+=h;

                        if (t>1950 && max2<u2) max2 = u2;
                        if (t>1950 && max1<u1) max1 = u1;
                }
        if (g!=0.8)
        {
                Series3->AddXY(g, max1, "", clBackground);
                Series4->AddXY(g, max2, "", clBackground);
        }
        t=0;
        v1=0;
        v2=0;
        u1=0;
        u2=0;
        g+=0.005;
        max1=0;
        max2=0;
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button5Click(TObject *Sender)
{
        double u1=0, u2=0, v1=0, v2=0, t=0, tmin, tmax, m, K, Kc, g, f, k1, k2, k3, k4;
        int i=0;
        m = StrToFloat(Edit1->Text.c_str());
        K = StrToFloat(Edit2->Text.c_str());
        Kc = StrToFloat(Edit3->Text.c_str());
        f = StrToFloat(Edit4->Text.c_str());
        g = StrToFloat(Edit5->Text.c_str());
        tmin = StrToFloat(Edit6->Text.c_str());
        tmax = StrToFloat(Edit7->Text.c_str());

        Series1->Clear();
        Series2->Clear();
        Series3->Clear();
        Series4->Clear();

        while(t<tmax)
        {
                k1 = -(K+Kc)*u1 + Kc*u2 - f*v1 + cos(g*t);
                k2 = -(K+Kc)*u1 + Kc*u2 - f*(v1+k1/2) + cos(g*(t+h/2));
                k3 = -(K+Kc)*u1 + Kc*u2 - f*(v1+k2/2) + cos(g*(t+h/2));
                k4 = -(K+Kc)*u1 + Kc*u2 - f*(v1+k3) + cos(g*(t+h));
                v1+=(k1+2*k2+2*k3+k4)*h/m/6;

                k1 = -(K+Kc)*u2 + Kc*u1 - f*v2;
                k2 = -(K+Kc)*u2 + Kc*u1 - f*(v2+k1/2);
                k3 = -(K+Kc)*u2 + Kc*u1 - f*(v2+k2/2);
                k4 = -(K+Kc)*u2 + Kc*u1 - f*(v2+k3);
                v2+=(k1+2*k2+2*k3+k4)*h/m/6;

                u2+=h*v2;
                u1+=h*v1;
                t+=h;

                if (t<tmax && t>tmin)
                {
                        Series1->AddXY(v1, u1, "", clBackground);
                        Series2->AddXY(v2, u2, "", clBackground);
                        Series3->AddXY(t, u1, "", clBackground);
                        Series4->AddXY(t, u2, "", clBackground);
                }
                i++;
        }
}
//---------------------------------------------------------------------------

