//---------------------------------------------------------------------------

#ifndef Problema1H
#define Problema1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Series.hpp>
#include "CGRID.h"
#include <QRCtrls.hpp>
#include <QuickRpt.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TChart *Chart1;
        TPanel *Panel1;
        TButton *Button1;
        TButton *Button2;
        TEdit *Edit1;
        TEdit *Edit2;
        TEdit *Edit3;
        TButton *Button3;
        TPointSeries *Series1;
        TButton *Button4;
        TChart *Chart2;
        TPointSeries *Series2;
        TMemo *Memo1;
        TMemo *Memo2;
        TButton *Button5;
        TEdit *Edit5;
        TButton *Button6;
        TMemo *Memo3;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TCColorGrid *CColorGrid1;
        TButton *Button7;
        TChart *Chart3;
        TPointSeries *Series3;
        TEdit *Edit6;
        TEdit *Edit7;
        TCColorGrid *CColorGrid2;
        TButton *Button8;
        TEdit *Edit8;
        TEdit *Edit9;
        TEdit *Edit4;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TButton *Button9;
        TMemo *Memo4;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall Button8Click(TObject *Sender);
        void __fastcall Button9Click(TObject *Sender);

private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
