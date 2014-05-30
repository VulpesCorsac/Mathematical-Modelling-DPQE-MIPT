//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Math.h"

double tt,vv,xx,v1,x1,w0=1,A,g=10;
int n=10000,i;
double func3(double,double,double);

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        double st=0,fin=100;
        tt=(fin-st)/n;
}
//---------------------------------------------------------------------------

double func3(double t,double v,double x) 
{
	return -(w0*w0+A*g*g*cos(g*t))*sin(x);
}

void __fastcall TForm1::Button1Click(TObject *Sender)
{
        double t,v,x=3.13;
        A = StrToFloat(Edit1->Text.c_str());
        Series1->Clear();
        Series2->Clear();
        for(i=0; i<n; i++)
        {
                Series1->AddXY(t,x,"",clRed);
                Series2->AddXY(x,v,"",clRed);
                v1=v+tt*func3(t,v,x);
                x1=x+tt*v1;
                x=x1;
		v=v1;
		t=t+tt;
                Application->ProcessMessages();
                if(Button2->Focused()) break;
                //Memo1->Lines->Add(x);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
        double t,v,x=3.14;
        A = StrToFloat(Edit1->Text.c_str());
        Series1->Clear();
        Series2->Clear();
        for(i=0; i<n; i++)
        {
                Series1->AddXY(t,x,"",clRed);
                Series2->AddXY(x,v,"",clRed);
                vv=v+tt*func3(t,v,x);
                xx=x+tt*v;
                v1=v+tt/2*(func3(t,v,x)+func3(t+tt,vv,xx));
                x1=x+tt/2*(v+vv);
                //Application->ProcessMessages();
                x=x1;
		v=v1;
		t=t+tt;
                if(Button2->Focused()) break;
        }
}
//---------------------------------------------------------------------------




