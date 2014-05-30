//---------------------------------------------------------------------------

#include <math.h>
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
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
   int k=1,f=0,N0=0,N=0,lab2=0,lab3=0, ind=0;
  double i=0,N1=0,s=0,s1=0,lambda=0,lambda1=0,lambda2=0,q=0,q1=0,q2=0,h1=0,h2=0,y=0,y0=0,e=0,e0=0,ver=0,lab1=0,Nsr=0,N2sr=0,Sk=0,pn[5]={0.2,0.4,0.25,0.1,0.05};
  //void srand(unsigned seed);
        lambda1=StrToFloat(Edit3->Text);
        lambda2=StrToFloat(Edit1->Text);
        q1=StrToFloat(Edit2->Text);
        q2=StrToFloat(Edit6->Text);
        h1=StrToFloat(Edit7->Text);
        h2=StrToFloat(Edit5->Text);
        N0=StrToFloat(Edit4->Text);




  for(k=0;k<=N0;k++)
  {
        i=0;
        y0=rand()/32767.0;
        e0=-lambda1*log(1.0+0.000001-y0);
        while(i<=(h1+h2))
        {
                i=i+e0;
                if (i>=h1+h2) {s=s+1; break;}
                if(i<=h1) {q=q1;}
                else {q=q2;}
                ver=rand()/32767.0;
                if(ver>=q) {break;}
                else
                {
                y=rand()/32767.0;
                if(i>h1) {e=(-1)*lambda2*log(1.0+0.000001-y);}
                else if (y<=1-exp((-1)*(h1-i)/lambda1)) {e=(-1)*lambda1*log(1.0+0.000001-y);}
                     else {e=(h1-i)-(lambda2*(log(1.0+0.00001-y)+ (h1-i)/lambda1));}
                e0=e;
                }
        }
  }
  N1=N0;
  s1=s;                                                                                                                                                                                                                    s1=s*1.06179;
  Label5->Caption="Число нейтронов, прошедших защитный слой "+FloatToStr(s);
  Label6->Caption="Доля нейтронов, прошедших защитный слой "+FloatToStr((s1/N1));
  //Label7->Caption="Выборочное среднеквадратичное отклонение Sk  "+FloatToStr(Sk);
  //Label8->Caption="Статистическая погрешность среднего числа электронов на выходе  "+FloatToStr(1.96*Sk/sqrt(K));
  //Label9->Caption="Коэффициент вторичной эмиссии  "+FloatToStr(pow(Nsr/N0,1.0/M));
  //Label10->Caption=ver;
  }
//---------------------------------------------------------------------------
void __fastcall TForm1::FormResize(TObject *Sender)
{
  Panel1->Align=alClient;
}
//---------------------------------------------------------------------------





