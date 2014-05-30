object Form1: TForm1
  Left = 229
  Top = 228
  Width = 928
  Height = 480
  VertScrollBar.Position = 279
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Chart1: TChart
    Left = 8
    Top = -271
    Width = 345
    Height = 353
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.Text.Strings = (
      'Y(t)')
    BottomAxis.TickLength = 0
    BottomAxis.Title.Caption = 't'
    LeftAxis.Title.Angle = 0
    LeftAxis.Title.Caption = 'Y'
    Legend.Visible = False
    View3D = False
    TabOrder = 0
    object Series1: TLineSeries
      Marks.ArrowLength = 8
      Marks.Visible = False
      SeriesColor = clRed
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = False
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
  end
  object Chart2: TChart
    Left = 8
    Top = 89
    Width = 345
    Height = 353
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.Text.Strings = (
      'X(t)')
    BottomAxis.TickLength = 0
    BottomAxis.Title.Caption = 't'
    LeftAxis.Title.Angle = 0
    LeftAxis.Title.Caption = 'Y'
    Legend.Visible = False
    View3D = False
    TabOrder = 1
    object Series2: TLineSeries
      Marks.ArrowLength = 8
      Marks.Visible = False
      SeriesColor = clRed
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = False
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
  end
  object Chart3: TChart
    Left = 360
    Top = -271
    Width = 345
    Height = 353
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.Text.Strings = (
      'Y(X)')
    BottomAxis.TickLength = 0
    BottomAxis.Title.Caption = 't'
    LeftAxis.Title.Angle = 0
    LeftAxis.Title.Caption = 'Y'
    Legend.Visible = False
    View3D = False
    TabOrder = 2
    object Series3: TPointSeries
      Marks.ArrowLength = 8
      Marks.Visible = False
      SeriesColor = clRed
      Pointer.Brush.Color = clRed
      Pointer.HorizSize = 2
      Pointer.InflateMargins = True
      Pointer.Pen.Color = clRed
      Pointer.Style = psCircle
      Pointer.VertSize = 2
      Pointer.Visible = True
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
  end
  object Panel1: TPanel
    Left = 360
    Top = 88
    Width = 345
    Height = 353
    TabOrder = 3
    object Label1: TLabel
      Left = 16
      Top = 80
      Width = 12
      Height = 31
      Caption = 'a'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -27
      Font.Name = 'Arial Narrow'
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 168
      Top = 80
      Width = 12
      Height = 31
      Caption = 'b'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -27
      Font.Name = 'Arial Narrow'
      Font.Style = []
      ParentFont = False
    end
    object Label3: TLabel
      Left = 16
      Top = 128
      Width = 28
      Height = 31
      Caption = 'w1'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -27
      Font.Name = 'Arial Narrow'
      Font.Style = []
      ParentFont = False
    end
    object Label4: TLabel
      Left = 168
      Top = 128
      Width = 28
      Height = 31
      Caption = 'w2'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -27
      Font.Name = 'Arial Narrow'
      Font.Style = []
      ParentFont = False
    end
    object Label5: TLabel
      Left = 16
      Top = 176
      Width = 18
      Height = 31
      Caption = 'f1'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -27
      Font.Name = 'Arial Narrow'
      Font.Style = []
      ParentFont = False
    end
    object Label6: TLabel
      Left = 168
      Top = 176
      Width = 18
      Height = 31
      Caption = 'f2'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -27
      Font.Name = 'Arial Narrow'
      Font.Style = []
      ParentFont = False
    end
    object Label7: TLabel
      Left = 64
      Top = 8
      Width = 183
      Height = 31
      Caption = 'X=a*cos(w1*t + f1)'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -27
      Font.Name = 'Arial Narrow'
      Font.Style = []
      ParentFont = False
    end
    object Label8: TLabel
      Left = 64
      Top = 40
      Width = 177
      Height = 31
      Caption = 'Y=b*sin(w2*t + f2)'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -27
      Font.Name = 'Arial Narrow'
      Font.Style = []
      ParentFont = False
    end
    object Edit1: TEdit
      Left = 48
      Top = 88
      Width = 41
      Height = 21
      TabOrder = 0
      Text = 'Edit1'
    end
    object Edit2: TEdit
      Left = 200
      Top = 88
      Width = 41
      Height = 21
      TabOrder = 1
      Text = 'Edit2'
    end
    object Button1: TButton
      Left = 16
      Top = 272
      Width = 121
      Height = 41
      Caption = #1055#1086#1089#1090#1088#1086#1080#1090#1100
      TabOrder = 2
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 176
      Top = 272
      Width = 129
      Height = 41
      Caption = #1042#1099#1081#1090#1080
      TabOrder = 3
      OnClick = Button2Click
    end
    object Edit3: TEdit
      Left = 48
      Top = 136
      Width = 41
      Height = 21
      TabOrder = 4
      Text = 'Edit3'
    end
    object Edit4: TEdit
      Left = 200
      Top = 136
      Width = 41
      Height = 21
      TabOrder = 5
      Text = 'Edit4'
    end
    object Edit5: TEdit
      Left = 48
      Top = 184
      Width = 41
      Height = 21
      TabOrder = 6
      Text = 'Edit5'
    end
    object Edit6: TEdit
      Left = 200
      Top = 184
      Width = 41
      Height = 21
      TabOrder = 7
      Text = 'Edit6'
    end
  end
end
