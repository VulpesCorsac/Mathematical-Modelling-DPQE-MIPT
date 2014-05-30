object Form1: TForm1
  Left = 16
  Top = 194
  Width = 1305
  Height = 675
  Caption = 'Programma 1'
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
    Top = 8
    Width = 489
    Height = 489
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.Text.Strings = (
      '')
    Title.Visible = False
    Legend.Visible = False
    View3D = False
    View3DWalls = False
    TabOrder = 0
    object Series1: TLineSeries
      Marks.ArrowLength = 8
      Marks.Visible = False
      SeriesColor = clRed
      LinePen.Visible = False
      Pointer.HorizSize = 1
      Pointer.InflateMargins = True
      Pointer.Style = psCircle
      Pointer.VertSize = 1
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
  object TStaticText
    Left = 720
    Top = 48
    Width = 4
    Height = 4
    TabOrder = 1
  end
  object StaticText1: TStaticText
    Left = 1000
    Top = 48
    Width = 321
    Height = 28
    Caption = ' f + 2a * f + (w + A * v cos(vt) ) sin f = 0 '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
  end
  object StaticText2: TStaticText
    Left = 1000
    Top = 24
    Width = 14
    Height = 28
    Caption = '..'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
  end
  object StaticText3: TStaticText
    Left = 1064
    Top = 24
    Width = 9
    Height = 28
    Caption = '.'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
  end
  object StaticText4: TStaticText
    Left = 1112
    Top = 40
    Width = 11
    Height = 20
    Caption = '2'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 5
  end
  object StaticText5: TStaticText
    Left = 1168
    Top = 32
    Width = 11
    Height = 20
    Caption = '2'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 6
  end
  object Edit2: TEdit
    Left = 1032
    Top = 112
    Width = 65
    Height = 32
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 7
    Text = ' w'
  end
  object Edit3: TEdit
    Left = 1032
    Top = 152
    Width = 65
    Height = 32
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 8
    Text = ' A'
  end
  object Edit4: TEdit
    Left = 1032
    Top = 192
    Width = 65
    Height = 32
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 9
    Text = ' v'
  end
  object Edit5: TEdit
    Left = 1112
    Top = 112
    Width = 65
    Height = 32
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 10
    Text = ' fo'
  end
  object Edit6: TEdit
    Left = 1112
    Top = 152
    Width = 65
    Height = 32
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 11
    Text = ' fo'#39
  end
  object Button1: TButton
    Left = 1032
    Top = 248
    Width = 121
    Height = 41
    Caption = 'Print'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 12
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 1032
    Top = 296
    Width = 121
    Height = 41
    Caption = 'stop'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 13
  end
  object Button3: TButton
    Left = 1032
    Top = 344
    Width = 121
    Height = 41
    Caption = 'Exit'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 14
    OnClick = Button3Click
  end
  object TrackBar1: TTrackBar
    Left = 1280
    Top = 112
    Width = 45
    Height = 425
    Max = 300
    Min = 1
    Orientation = trVertical
    Frequency = 5
    Position = 10
    SelEnd = 0
    SelStart = 0
    TabOrder = 15
    TickMarks = tmBottomRight
    TickStyle = tsAuto
  end
  object Chart2: TChart
    Left = 504
    Top = 8
    Width = 481
    Height = 489
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.Text.Strings = (
      'TChart')
    Title.Visible = False
    Legend.Visible = False
    View3D = False
    TabOrder = 16
    object Series2: TLineSeries
      Marks.ArrowLength = 0
      Marks.Visible = False
      SeriesColor = clRed
      Pointer.HorizSize = 2
      Pointer.InflateMargins = True
      Pointer.Pen.Visible = False
      Pointer.Style = psCircle
      Pointer.VertSize = 2
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
end
