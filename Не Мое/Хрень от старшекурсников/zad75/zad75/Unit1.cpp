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
   int i=0;
  double A,z,t,s=0,w0,k,time,del,kolper,gamma,lyam,n,h,fi,fish,fipr,fishpr;

  Chart1->Series[0]->Clear();
  Chart1->Series[1]->Clear();
  Image1->Canvas->MoveTo(0,(Image1->Height)/2);
  Image1->Canvas->LineTo((Image1->Width),(Image1->Height)/2);
  Image1->Canvas->MoveTo((Image1->Width)/2,0);
  Image1->Canvas->LineTo((Image1->Width)/2,(Image1->Height));

  n=StrToFloat(Edit2->Text);
  fipr=StrToFloat(Edit1->Text);
  fishpr=StrToFloat(Edit3->Text);
  lyam=StrToFloat(Edit4->Text);
  w0=StrToFloat(Edit5->Text);
  A=StrToFloat(Edit6->Text);
  gamma=StrToFloat(Edit7->Text);
  k=StrToFloat(Edit8->Text);
  kolper=StrToFloat(Edit9->Text);
  time=StrToFloat(Edit10->Text);

  h=1/n;
  for(i=1;i<=time;i++)
  {
        fish=fishpr+h*(-2*lyam*fishpr-(pow(w0,2)+A*pow(gamma,2)*cos(gamma*i*h))*sin(fipr));
    fi=fipr+h*fishpr;
    if(fi>=3.14159)
    {
          del=floor(fi/3.14159);
          fi=fi-2*3.14159*del;
    }
    if(fi<=-3.14159)
    {
          del=floor(fi/3.14159);
          fi=fi-2*3.14159*del;
    }
    fipr=fi;
    fishpr=fish;
  }
  for(i=time;i<=kolper*n;i++)
  {

    Image1->Canvas->MoveTo((k*fipr+(Image1->Width)/2),((Image1->Height)/2-k*fishpr));
    fish=fishpr+h*(-2*lyam*fishpr-(pow(w0,2)+A*pow(gamma,2)*cos(gamma*i*h))*sin(fipr));
    fi=fipr+h*fishpr;
    if(fi>=3.14159)
    {
          del=floor(fi/3.14159);
          fi=fi-2*3.14159*del;
    }
    if(fi<=-3.14159)
    {
          del=floor(fi/3.14159);
          fi=fi-2*3.14159*del;
    }
    Image1->Canvas->LineTo((k*fi+(Image1->Width)/2),((Image1->Height)/2-k*fish));
    fipr=fi;
    fishpr=fish;
    Chart1->Series[0]->AddXY(i*h,fipr,"",clRed);
    Chart1->Series[1]->AddXY(i*h,fishpr,"",clGreen);
    
  }
  Label16->Caption="����� ����������� �����������: "+FloatToStr(4.75);
  Label20->Caption=FloatToStr(n*kolper);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormResize(TObject *Sender)
{
  Chart1->Align=alLeft;
  Image1->Align=alClient;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
TRect r; //������� ���������, ���� TRect
r.Left=0; //������ ����� ������� �������
r.right=Image1->Width; //������ ������ �������
r.Bottom=Image1->Height; //������ ������ �������
r.Top=0; //������ ������� ������� �������
Image1->Canvas->Brush->Color=clWhite;  //���������� ���� �������
Image1->Canvas->FillRect(r); //��������� ��������� �������
  Image1->Canvas->MoveTo(0,(Image1->Height)/2);
  Image1->Canvas->LineTo((Image1->Width),(Image1->Height)/2);
  Image1->Canvas->MoveTo((Image1->Width)/2,0);
  Image1->Canvas->LineTo((Image1->Width)/2,(Image1->Height));
}
//---------------------------------------------------------------------------


