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
   int i=0,j=0,f=0,M=8,N0=100,n[5]={0,1,2,3,4},nn=0,lab2=0,lab3=0;
  double ver=0,lab1=0,Nsr=0,N2sr=0,Sk=0,pn[5]={0.2,0.4,0.25,0.1,0.05},ntek=0,nvilet=0,K=10000;

  srand(2);
    M=StrToFloat(Edit3->Text);
     K=StrToFloat(Edit5->Text);
 N0=StrToFloat(Edit4->Text);



  for(f=1;f<=K;f++)
  {
        ntek=N0;
        nvilet=N0;

        for(i=1;i<=M;i++)
        {
                ntek=nvilet;
                nvilet=0;
                for(j=1;j<=ntek;j++)
                {
                        ver=rand()/32767.0;
                        if(ver<=0.2) { nn=0; }
                        else if((ver>0.2)&&(ver<=0.6)) { nn=1; }
                        else if((ver>0.6)&&(ver<=0.85)) { nn=2; }
                        else if((ver>0.85)&&(ver<=0.95)) { nn=3; }
                        else if(ver>0.95) { nn=4; }
                        nvilet=nvilet+nn;
                }
        }

        Nsr=Nsr+nvilet/K;
        N2sr=N2sr+nvilet*nvilet/K;
  }
  Sk=sqrt(N2sr-Nsr*Nsr);

  Label5->Caption="Среднее по испытаниям N электронов на выходе умножителя  "+FloatToStr(Nsr);
  Label6->Caption="Среднее квадрата N  "+FloatToStr(N2sr);
  Label7->Caption="Выборочное среднеквадратичное отклонение Sk  "+FloatToStr(Sk);
  Label8->Caption="Статистическая погрешность среднего числа электронов на выходе  "+FloatToStr(1.96*Sk/sqrt(K));
  Label9->Caption="Коэффициент вторичной эмиссии  "+FloatToStr(pow(Nsr/N0,1.0/M));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormResize(TObject *Sender)
{
  Panel1->Align=alClient;
}
//---------------------------------------------------------------------------

