//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Math.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        const pi=3.14159;
        int b=1, w=2;
        Series1->Clear();
        for (int i=-100; i<=100; i++)
        {
                Series1->AddXY(0.01*pi*i,b*sin(w*(0.01*pi*i)),"Y(t)",clRed);
        }
}
//---------------------------------------------------------------------------
 