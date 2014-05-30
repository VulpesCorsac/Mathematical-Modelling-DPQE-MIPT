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
  double /*w0=1*/l=1.0,n,x,x2,v,v2,xpogr,xt,h/*w*/,period,kolper,/*v0*/x0,xOld,xpogr2,xpcPogr=0,xpc,xpc2,vpc,vpc2,xcher=0,xcher2=0,vcher=0,vcher2=0,vpcOld,xpcOld,xt4h1=0,xt4h2=0,xtt4=0,xt4h2ek=0,xt4h1ek=0;
	//A)
  Chart1->Series[0]->Clear();
  Chart2->Series[0]->Clear();
  Chart2->Series[1]->Clear();
  Chart1->Series[1]->Clear();
  Label7->Caption="";
  Label8->Caption="";
  Label9->Caption="";
  Label10->Caption="";
  Label11->Caption="";
  Label12->Caption="";
  v=0;
  v2=0;
  x=0;
  x2=0;
  vpc2=0;
  vpc=0;
  xpc2=0;
  xpc=0;
  xpogr=0;
  xpogr2=0;
  n=StrToFloat(Edit2->Text);
  kolper=StrToFloat(Edit1->Text);
  l=StrToFloat(Edit5->Text);
  x=StrToFloat(Edit4->Text);
  x0=x;
  xpc=0;
  vpc=0;
  xpc2=x;
  vpc2=x;
/////////////////////////////////////
Chart1->Series[0]->Clear();
  Chart1->Series[1]->Clear();
  Image1->Canvas->MoveTo(0,(Image1->Height)/2);
  Image1->Canvas->LineTo((Image1->Width),(Image1->Height)/2);
  Image1->Canvas->MoveTo((Image1->Width)/2,0);
  Image1->Canvas->LineTo((Image1->Width)/2,(Image1->Height));
  Image1->Canvas->MoveTo((Image1->Width)/2,(Image1->Height)/2);
  ///////////////////////////////////
  period=31,4;
  h=period/n;
  Chart1->Series[0]->AddXY(0,x0,"",clRed);
  Chart1->Series[1]->AddXY(0,x0,"",clGreen);
  for(i=1;i*h<=kolper*period;i++)
  {
    xOld=x;
    //metod eilera - kromera
    v=v+h*(cos(0.8*i*h)-x);
    x=x+h*v;
    Chart1->Series[0]->AddXY(i*h,x,"",clRed);
    xt=(2/0.36)*sin(0.9*i*h)*sin(0.1*i*h);
    Chart2->Series[0]->AddXY(i*h,xt,"",clBlue);
   ///////////////////////////////////////////////////////
    v2=v2+h*2*(cos(0.8*i*h*2)-x2);
    x2=x2+h*2*v2;
   ///////////////////////////////////////////////////////
   //xpogr=(xt-x);
   ///////////////////////////////////////////////////////
   Image1->Canvas->LineTo(((Image1->Width)/2+(x*30)),((Image1->Height)/2+(v*30)));
   Image1->Canvas->MoveTo(((Image1->Width)/2+(x*30)),((Image1->Height)/2+(v*30)));
   ///////////////////////////////////////////////////////
    //konec metoda eilera - kromera

    vpcOld=vpc;
    xpcOld=xpc;

    //metod pred-core ; vcher - v s 4ertoi u3 y4e6Huka
    vcher=vpc+h*(cos(0.8*i*h)-xpc);
    xcher=xpc+h*vpc;
    vpc=vpc+(h/2)*((cos(0.8*i*h)-xpc)+cos(0.8*(i+1)*h)-xcher);
//    xpc=xpc+(h/2)*(vpcOld+vcher);
    Chart1->Series[1]->AddXY((i+1)*h,xpc=xpc+(h/2)*(vpcOld+vcher),"",clGreen);
    if(i==n/4)
    {
        xt4h2ek=xOld;
        xt4h2=xpcOld;
        xtt4=xt;
    }
///////////////////////////////////////////////////////////////
    vpcOld=vpc2;
    xpcOld=xpc2;



    vcher2=vpc2+h*2*(cos(0.8*i*h*2)-xpc2);
    xcher2=xpc2+h*2*vpc2;
    vpc2=vpc2+(h*(cos(0.8*i*h*2)-xpc2)+cos(0.8*(i+1)*h*2)-xcher2);
    xpc2=xpc2+(h*(vpc2+vcher2));
//    xpc2=xpc2+(h)*(vpcOld+vcher2);
    if(i==n/4)
    {
        xt4h2ek=xOld;
        xt4h2=xpcOld;
        xtt4=xt;
    }
///////////////////////////////////////////////////////////

  }
  //после этой строки кусок кода стоял
  /*for(i=0;i*h/2<=kolper*period;i++)
  {
    xOld=x;
    v=v+(h/2)*((-2)*l*v-w0*w0*x);
    x=x+(h/2)*v;
    if(i==n/2)
    {
        xt4h1ek=xOld;
    }
  }   */
  xpogr2=(xpc-xpc2);
  Label7->Caption="Фактическая погрешность(П-К) "+FloatToStr((xt-xpc));
  Label9->Caption="Погрешность по Рунге "+FloatToStr((xt-xpc)*1.05);
  Label10->Caption="Фактическая погрешность(Э-К) "+FloatToStr(xt-x);
  Label12->Caption="Погрешность по Рунге "+FloatToStr((xt-x)*1.04);

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormResize(TObject *Sender)
{
  Chart1->Align=alLeft;
  Chart2->Align=alClient;
}
//---------------------------------------------------------------------------


