//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#pragma hdrstop

#include "Problema1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CGRID"
#pragma resource "*.dfm"

#define h 0.01
#define ah 100
#define R 6371


TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        double i;
        for (i=-R; i<R; i++)
        {
                Series3->AddXY(i, sqrt(R*R-i*i),"",clBlack);
                Series3->AddXY(i, -sqrt(R*R-i*i),"",clBlack);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{       float alfa, k, v, Vxn, Vxs, Vyn, Vys, xn ,xs, yn, ys;
        AnsiString  alfastr, xsstr;
        v = StrToFloat(Edit1->Text.c_str());
        k = StrToFloat(Edit2->Text.c_str());
        alfa = StrToFloat(Edit3->Text.c_str())*M_PI/180;
        xs = 0;
        ys = 0;
        Vxs=v*cos(alfa);
        Vys=v*sin(alfa);
        while (yn >= 0)
        {
                xn=xs+Vxs*h;
                yn=ys+Vys*h;
                Vxn=Vxs*(1-k*h);
                Vyn=Vys-(9.8+k*Vys)*h;
                Series1->AddXY(xn,yn,"",CColorGrid1->ForegroundColor);
                xs=xn;
                ys=yn;
                Vys=Vyn;
                Vxs=Vxn;
        }
        alfastr = FormatFloat("0.00", StrToFloat(Edit3->Text.c_str()));
        xsstr = FormatFloat("0.00", xs);
        Memo1->Lines->Add("Angle: " + alfastr + "   Dist: " + xsstr);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
        Series1->Clear();
        Memo1->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
        float  i, alm=0, max=0, k, v, Vxn, Vxs, Vyn, Vys, xn ,xs, yn, ys;
        AnsiString maxstr,almstr;
        v = StrToFloat(Edit1->Text.c_str());
        k = StrToFloat(Edit2->Text.c_str());
        for (i = 1; i < 91*ah; i++)
        {
                xs = 0;
                ys = 0;
                Vxs = v*cos(i/ah*M_PI/180);
                Vys = v*sin(i/ah*M_PI/180);
                while(yn>=0)
                {
                        xn = xs+Vxs*h;
                        yn = ys+Vys*h;
                        Vxn = Vxs*(1-k*h);
                        Vyn = Vys-h*(9.8+Vys*k);
                        //Series2->AddXY(xn,yn,"",clBlack);
                        xs=xn;
                        ys=yn;
                        Vxs=Vxn;
                        Vys=Vyn;
                }
                if (max <= xn)
                {
                        max=xn;
                        alm=i/ah;
                }
                xn = 0;
                yn = 0;
                Vxn = 0;
                Vyn = 0;
                Series2->AddXY(i/ah, xs, "", clRed);
        }
        maxstr = FormatFloat("0.00", max);
        almstr = FormatFloat("0.00",alm);
        Memo2->Lines->Add("Angle: " + almstr + "\r\nDistanse: " + maxstr);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button5Click(TObject *Sender)
{
        Series2->Clear();
        Memo2->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
        float k, alfa, x, v, d, vn, vs, Vxn, Vxs, Vyn, Vys, xn=0 ,xs=0, yn=0, ys=0;
        int i;
        AnsiString vstr;
        k = StrToFloat(Edit2->Text.c_str());
        alfa = StrToFloat(Edit4->Text.c_str())*M_PI/180;
        d = StrToFloat(Edit5->Text.c_str());
        x = 0.1;
        while (xn < d)
        {
                v = v+x;
                xs = 0;
                ys = 0;
                xn=0;
                Vxs=v*cos(alfa);
                Vys=v*sin(alfa);
                while (yn >= 0)
                {
                        xn=xs+Vxs*h;
                        yn=ys+Vys*h;
                        Vxn=Vxs*(1-k*h);
                        Vyn=Vys-(9.8+k*Vys)*h;
                        xs=xn;
                        ys=yn;
                        Vys=Vyn;
                        Vxs=Vxn;
                }
                yn=0;
        }
        for (i = 0; i < 10; i++)
        {
                if (xn==d) break;
                else if (xn < d) v = (v+(v+x))/2;
                else v = (v+(v-x))/2;
                xs = 0;
                ys = 0;
                Vxs=v*cos(alfa);
                Vys=v*sin(alfa);
                while (yn >= 0)
                {
                        xn=xs+Vxs*h;
                        yn=ys+Vys*h;
                        Vxn=Vxs*(1-k*h);
                        Vyn=Vys-(9.8+k*Vys)*h;
                        xs=xn;
                        ys=yn;
                        Vys=Vyn;
                        Vxs=Vxn;
                }
                x = x/2;
        }
        vstr = FormatFloat("0.00",v);
        Memo3->Lines->Add(vstr);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
        double i, r, r0, n, a, h1, Cos, v0, alfa, y, x=0, Vx, Vy;
        v0 = StrToFloat(Edit6->Text.c_str());
        alfa = StrToFloat(Edit7->Text.c_str())*M_PI/180;
        h1 = StrToFloat(Edit8->Text.c_str());
        n = StrToFloat(Edit9->Text.c_str());
        y = R+r0;
        Vx = v0*cos(alfa);
        Vy = v0*sin(alfa);
        for(i=0; i<n; i=i+1)
        {
                Series3->AddXY(x, y, "", CColorGrid2->ForegroundColor);
                if (x*x+y*y < R*R) break;
                if (i>n*0.1 && y>(R+r0-50)) if  (y<(R+r0+50)) break;
                r = x*x+y*y;
                Cos = x/sqrt(r);
                a=-400200/r;
                x = x+Vx*h1;
                y = y+Vy*h1;
                Vx = Vx+a*h1*Cos;
                Vy = Vy+a*h1*y*Cos/x;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
        Series3->Clear();
        double i;
        for (i=-R; i<R; i++)
        {
                Series3->AddXY(i, sqrt(R*R-i*i),"",clBlack);
                Series3->AddXY(i, -sqrt(R*R-i*i),"",clBlack);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button9Click(TObject *Sender)
{
        double f=0, f2=0, vk, r, n = 10000, a = 0, h1=1, Cos, v = 7.8, alfa=0, y, x=0, Vx, Vy;
        int i,j;
        AnsiString vkstr;
        y = R+50;

        for (j=1; j<20; j++)
        {
                v = v+j/100;
                Vx = v*cos(alfa);
                Vy = v*sin(alfa);
                f2=0;
                for(i=0; i<n; i++)
                {
                        if (x*x+y*y < R*R) f2=1;
                        if (i>n*0.1 && y>=R-25)
                        {
                                f++;
                               //break;
                        }
                        r = x*x+y*y;
                        Cos = x/sqrt(r);
                        a=-400200/r;
                        x = x+Vx*h1;
                        y = y+Vy*h1;
                        Vx = Vx+a*h1*Cos;
                        Vy = Vy+a*h1*y*Cos/x;

                        if (f!=0 && f2==0)
                        {
                                vk =v;
                                break;
                        }
                }
        }
        vkstr = FormatFloat("0.00",vk);
        Memo4->Lines->Add(vkstr);
}
//---------------------------------------------------------------------------

