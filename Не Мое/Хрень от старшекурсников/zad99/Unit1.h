//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
  TChart *Chart1;
  TLineSeries *Series1;
  TPanel *Panel1;
  TEdit *Edit2;
  TLabel *Label6;
  TButton *Button1;
  TLineSeries *Series3;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label1;
        TLabel *Label2;
        TEdit *Edit1;
        TLabel *Label3;
        TLabel *Label4;
        TEdit *Edit3;
        TLabel *Label5;
        TChart *Chart2;
        TLineSeries *Series2;
  void __fastcall Button1Click(TObject *Sender);
  void __fastcall FormResize(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
