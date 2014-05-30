object Form1: TForm1
  Left = 213
  Top = 166
  Width = 1077
  Height = 559
  HorzScrollBar.Position = 197
  VertScrollBar.Position = 179
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
    Left = -85
    Top = -171
    Width = 801
    Height = 729
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.Text.Strings = (
      '')
    BottomAxis.Automatic = False
    BottomAxis.AutomaticMaximum = False
    BottomAxis.AutomaticMinimum = False
    BottomAxis.Maximum = 80000
    BottomAxis.Minimum = -80000
    LeftAxis.Automatic = False
    LeftAxis.AutomaticMaximum = False
    LeftAxis.AutomaticMinimum = False
    LeftAxis.Maximum = 80000
    LeftAxis.Minimum = -80000
    Legend.ColorWidth = 15
    View3D = False
    TabOrder = 0
    object Series1: TPointSeries
      Marks.ArrowLength = 0
      Marks.Visible = False
      SeriesColor = clRed
      Title = #1047#1074#1077#1079#1076#1099
      Pointer.Brush.Color = 33023
      Pointer.HorizSize = 12
      Pointer.InflateMargins = True
      Pointer.Pen.Color = 4227327
      Pointer.Style = psCircle
      Pointer.VertSize = 12
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
    object Series2: TPointSeries
      Marks.ArrowLength = 0
      Marks.Visible = False
      SeriesColor = clGreen
      Title = #1057#1087#1091#1090#1085#1080#1082
      Pointer.Brush.Color = clBlack
      Pointer.InflateMargins = True
      Pointer.Pen.Color = clGreen
      Pointer.Pen.Visible = False
      Pointer.Style = psCircle
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
    object Series3: TPointSeries
      Marks.ArrowLength = 0
      Marks.Visible = False
      SeriesColor = clYellow
      Title = #1058#1088#1072#1077#1082#1090#1086#1088#1080#1103
      Pointer.HorizSize = 2
      Pointer.InflateMargins = True
      Pointer.Pen.Visible = False
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
    Left = 723
    Top = -171
    Width = 321
    Height = 729
    TabOrder = 1
    object Label1: TLabel
      Left = 56
      Top = 56
      Width = 55
      Height = 21
      Caption = 'M1/M2'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 72
      Top = 88
      Width = 13
      Height = 21
      Caption = 'X'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
    end
    object Label3: TLabel
      Left = 72
      Top = 120
      Width = 13
      Height = 21
      Caption = 'Y'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
    end
    object Label4: TLabel
      Left = 72
      Top = 152
      Width = 22
      Height = 21
      Caption = 'V0'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
    end
    object Label5: TLabel
      Left = 64
      Top = 184
      Width = 31
      Height = 21
      Caption = 'Alfa'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
    end
    object Button1: TButton
      Left = 24
      Top = 424
      Width = 137
      Height = 41
      Caption = #1057#1090#1072#1088#1090
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 168
      Top = 424
      Width = 137
      Height = 41
      Caption = #1057#1090#1086#1087
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
    end
    object Edit1: TEdit
      Left = 128
      Top = 56
      Width = 89
      Height = 21
      TabOrder = 2
      Text = 'Edit1'
    end
    object Edit2: TEdit
      Left = 128
      Top = 88
      Width = 89
      Height = 21
      TabOrder = 3
      Text = 'Edit2'
    end
    object Button3: TButton
      Left = 24
      Top = 480
      Width = 137
      Height = 41
      Caption = #1054#1095#1080#1089#1090#1080#1090#1100
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      OnClick = Button3Click
    end
    object Button4: TButton
      Left = 168
      Top = 480
      Width = 137
      Height = 41
      Caption = #1058#1088#1072#1077#1082#1090#1086#1088#1080#1103
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
    end
    object Edit3: TEdit
      Left = 128
      Top = 120
      Width = 89
      Height = 21
      TabOrder = 6
      Text = 'Edit3'
    end
    object Edit4: TEdit
      Left = 128
      Top = 152
      Width = 89
      Height = 21
      TabOrder = 7
      Text = 'Edit4'
    end
    object Edit5: TEdit
      Left = 128
      Top = 184
      Width = 89
      Height = 21
      TabOrder = 8
      Text = 'Edit5'
    end
    object CColorGrid1: TCColorGrid
      Left = 48
      Top = 256
      Width = 224
      Height = 120
      TabOrder = 9
    end
  end
end
