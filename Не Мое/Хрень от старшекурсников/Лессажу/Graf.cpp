//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Graf.h"
#include "Math.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
const pi=3.14159265358979;
double a, b,w1,w2;
int f1=0,f2=0;
a = StrToFloat(Edit1->Text.c_str());
b = StrToFloat(Edit2->Text.c_str());
w1 = StrToFloat(Edit3->Text.c_str());
w2 = StrToFloat(Edit4->Text.c_str());
f1 = StrToFloat(Edit5->Text.c_str())*pi/180;
f2 = StrToFloat(Edit6->Text.c_str())*pi/180;
Series1->Clear();
Series2->Clear();
Series3->Clear();
for (int i=-2000; i<=2000; i++)
{
Series1->AddXY(0.001*pi*i,b*sin(w2*(0.001*pi*i)+f2),"",clRed);
Series2->AddXY(0.001*pi*i,a*cos(w1*(0.001*pi*i)+f1),"",clRed);
Series3->AddXY(a*cos(w2*(0.001*pi*i)+f2),b*sin(w1*(0.001*pi*i)+f1),"",clRed);
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
