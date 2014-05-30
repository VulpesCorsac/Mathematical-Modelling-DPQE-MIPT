//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Math.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define Gs 132736162900
#define Gz 800000000
#define Gm 400000000
#define PM 46001210
#define Pv 107476259
#define Pz 147098074
#define Pl 15000000
#define Pm 206620000
#define Pf 10000000
#define Pd 15000000
#define VM 59.5
#define Vv 36
#define Vz 30.27
#define Vl 23
#define Vm 26.5
#define Vf 32.5
#define Vd 32
#define h 20

TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        Series1->AddXY(0,0,"", clBackground);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button1Click(TObject *Sender)
{
        double  rM, axM, ayM, yM, xM, VxM, VyM,
                rv, axv, ayv, yv, xv, Vxv, Vyv,
                rz, axz, ayz, yz, xz, Vxz, Vyz,
                rm, axm, aym, ym, xm, Vxm, Vym,
                rls, rlz, axl, ayl, xl, yl, Vxl, Vyl,
                rlm, axf, ayf, xf, yf, Vxf, Vyf,
                axd, ayd, xd, yd, Vxd, Vyd,
                k1, k2, k3, k4;
        int i=0;

        xM = -PM;
        yM = 0;
        VxM = 0;
        VyM = VM;

        xv = -Pv;
        yv = 0;
        Vxv = 0;
        Vyv = Vv;

        xz = -Pz;
        yz = 0;
        Vxz = 0;
        Vyz = Vz;

        xl = -Pz-Pl;
        yl = 0;
        Vxl = 0;
        Vyl = Vl;

        xm = -Pm;
        ym = 0;
        Vxm = 0;
        Vym = Vm;

        xf = -Pm+Pf;
        yf = 0;
        Vxf = 0;
        Vyf = Vf;

        xd = -Pm+Pd;
        yd = 0;
        Vxd = 0;
        Vyd = Vd;

        while (!(Button2->Focused()))
        {
                if (i % 5000 == 1)
                {
                        Series2->AddXY(xM, yM, "", clBackground);
                        Series3->AddXY(xv, yv, "", clBackground);
                        Series4->AddXY(xz, yz, "", clBackground);
                        Series5->AddXY(xl, yl, "", clBackground);
                        Series6->AddXY(xm, ym, "", clBackground);
                        Series7->AddXY(xf, yf, "", clBackground);
                        Series8->AddXY(xd, yd, "", clBackground);
                        Application->ProcessMessages();
                }
                //Меркурий
                rM = xM*xM+yM*yM;
                axM = -Gs/rM*xM/sqrt(rM);
                ayM = -Gs/rM*yM/sqrt(rM);
                k1=h*VxM;
                k2=h*(VxM+axM*h/2);
                k3=k2;
                k4=h*(VxM+axM*h);
                xM+=(k1+2*k2+2*k3+k4)/6;
                k1=h*VyM;
                k2=h*(VyM+ayM*h/2);
                k3=k2;
                k4=h*(VyM+ayM*h);
                yM+=(k1+2*k2+2*k3+k4)/6;
                VxM+=axM*h;
                VyM+=ayM*h;
                //Венера
                rv = xv*xv+yv*yv;
                axv = -Gs/rv*xv/sqrt(rv);
                ayv = -Gs/rv*yv/sqrt(rv);
                k1=h*Vxv;
                k2=h*(Vxv+axv*h/2);
                k3=k2;
                k4=h*(Vxv+axv*h);
                xv+=(k1+2*k2+2*k3+k4)/6;
                k1=h*Vyv;
                k2=h*(Vyv+ayv*h/2);
                k3=k2;
                k4=h*(Vyv+ayv*h);
                yv+=(k1+2*k2+2*k3+k4)/6;
                Vxv+=axv*h;
                Vyv+=ayv*h;
                //Земля
                rz = xz*xz+yz*yz;
                axz = -Gs/rz*xz/sqrt(rz);
                ayz = -Gs/rz*yz/sqrt(rz);
                k1=h*Vxz;
                k2=h*(Vxz+axz*h/2);
                k3=k2;
                k4=h*(Vxz+axz*h);
                xz+=(k1+2*k2+2*k3+k4)/6;
                k1=h*Vyz;
                k2=h*(Vyz+ayz*h/2);
                k3=k2;
                k4=h*(Vyz+ayz*h);
                yz+=(k1+2*k2+2*k3+k4)/6;
                Vxz+=axz*h;
                Vyz+=ayz*h;
                //Луна
                rls = xl*xl+yl*yl;
                rlz = (xz-xl)*(xz-xl)+(yz-yl)*(yz-yl);
                axl = -Gs/rls*xl/sqrt(rls) -Gz/rlz*(xl-xz)/sqrt(rlz);
                ayl = -Gs/rls*yl/sqrt(rls) -Gz/rlz*(yl-yz)/sqrt(rlz);
                k1=Vxl;
                k2=(Vxl+axl*h/2);
                k3=k2;
                k4=(Vxl+axl*h);
                xl+=h*(k1+2*k2+2*k3+k4)/6;
                k1=Vyl;
                k2=(Vyl+ayl*h/2);
                k3=k2;
                k4=(Vyl+ayl*h);
                yl+=h*(k1+2*k2+2*k3+k4)/6;
                Vxl+=axl*h;
                Vyl+=ayl*h;
                //Марс
                rm = xm*xm+ym*ym;
                axm = -Gs/rm*xm/sqrt(rm);
                aym = -Gs/rm*ym/sqrt(rm);
                k1=h*Vxm;
                k2=h*(Vxm+axm*h/2);
                k3=k2;
                k4=h*(Vxm+axm*h);
                xm+=(k1+2*k2+2*k3+k4)/6;
                k1=h*Vym;
                k2=h*(Vym+aym*h/2);
                k3=k2;
                k4=h*(Vym+aym*h);
                ym+=(k1+2*k2+2*k3+k4)/6;
                Vxm+=axm*h;
                Vym+=aym*h;
                //Фобос
                rls = xf*xf+yf*yf;
                rlm = (xm-xf)*(xm-xf)+(ym-yf)*(ym-yf);
                axf = -Gs/rls*xf/sqrt(rls) -Gm/rlm*(xf-xm)/sqrt(rlm);
                ayf = -Gs/rls*yf/sqrt(rls) -Gm/rlm*(yf-ym)/sqrt(rlm);
                k1=Vxf;
                k2=(Vxf+axf*h/2);
                k3=k2;
                k4=(Vxf+axf*h);
                xf+=h*(k1+2*k2+2*k3+k4)/6;
                k1=Vyf;
                k2=(Vyf+ayf*h/2);
                k3=k2;
                k4=(Vyf+ayf*h);
                yf+=h*(k1+2*k2+2*k3+k4)/6;
                Vxf+=axf*h;
                Vyf+=ayf*h;
                //Деймос
                rls = xd*xd+yd*yd;
                rlm = (xm-xd)*(xm-xd)+(ym-yd)*(ym-yd);
                axd = -Gs/rls*xd/sqrt(rls) -Gm/rlm*(xd-xm)/sqrt(rlm);
                ayd = -Gs/rls*yd/sqrt(rls) -Gm/rlm*(yd-ym)/sqrt(rlm);
                k1=Vxd;
                k2=(Vxd+axd*h/2);
                k3=k2;
                k4=(Vxd+axd*h);
                xd+=h*(k1+2*k2+2*k3+k4)/6;
                k1=Vyd;
                k2=(Vyd+ayd*h/2);
                k3=k2;
                k4=(Vyd+ayd*h);
                yd+=h*(k1+2*k2+2*k3+k4)/6;
                Vxd+=axd*h;
                Vyd+=ayd*h;
                ///
                Series2->Clear();
                Series3->Clear();
                Series4->Clear();
                Series5->Clear();
                Series6->Clear();
                Series7->Clear();
                Series8->Clear();
                i++;

        }
}
//---------------------------------------------------------------------------
