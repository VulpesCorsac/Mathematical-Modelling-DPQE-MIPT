object Form1: TForm1
  Left = 244
  Top = 147
  Width = 991
  Height = 591
  VertScrollBar.Position = 185
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Scaled = False
  PixelsPerInch = 96
  TextHeight = 13
  object Chart1: TChart
    Left = 8
    Top = -177
    Width = 369
    Height = 353
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.Text.Strings = (
      'Y(X)')
    Legend.LegendStyle = lsLastValues
    Legend.TextStyle = ltsXValue
    Legend.Visible = False
    View3D = False
    Color = 15658734
    TabOrder = 0
    object Series1: TPointSeries
      Marks.ArrowLength = 8
      Marks.BackColor = clRed
      Marks.Frame.Color = clRed
      Marks.Frame.Visible = False
      Marks.Visible = False
      SeriesColor = clRed
      Pointer.HorizSize = 1
      Pointer.InflateMargins = True
      Pointer.Pen.Visible = False
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
  object Panel1: TPanel
    Left = 384
    Top = -177
    Width = 321
    Height = 730
    TabOrder = 1
    object Label1: TLabel
      Left = 40
      Top = 32
      Width = 9
      Height = 23
      Caption = 'v'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'Times New Roman'
      Font.Style = [fsItalic]
      ParentFont = False
    end
    object Label2: TLabel
      Left = 40
      Top = 64
      Width = 10
      Height = 23
      Caption = 'k'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'Times New Roman'
      Font.Style = [fsItalic]
      ParentFont = False
    end
    object Label3: TLabel
      Left = 16
      Top = 96
      Width = 44
      Height = 21
      Caption = 'Angle'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Times New Roman'
      Font.Style = [fsItalic]
      ParentFont = False
    end
    object Label4: TLabel
      Left = 0
      Top = 384
      Width = 67
      Height = 19
      Caption = 'Opt. angle'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Times New Roman'
      Font.Style = [fsItalic]
      ParentFont = False
    end
    object Label5: TLabel
      Left = 0
      Top = 416
      Width = 56
      Height = 19
      Caption = 'Distance'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Times New Roman'
      Font.Style = [fsItalic]
      ParentFont = False
    end
    object Label6: TLabel
      Left = 8
      Top = 504
      Width = 38
      Height = 19
      Caption = 'Speed'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Times New Roman'
      Font.Style = [fsItalic]
      ParentFont = False
    end
    object Label7: TLabel
      Left = 8
      Top = 536
      Width = 37
      Height = 19
      Caption = 'Angle'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Times New Roman'
      Font.Style = [fsItalic]
      ParentFont = False
    end
    object Label8: TLabel
      Left = 176
      Top = 504
      Width = 28
      Height = 19
      Caption = 'Step'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Times New Roman'
      Font.Style = [fsItalic]
      ParentFont = False
    end
    object Label9: TLabel
      Left = 160
      Top = 536
      Width = 52
      Height = 19
      Caption = 'Number'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Times New Roman'
      Font.Style = [fsItalic]
      ParentFont = False
    end
    object Button1: TButton
      Left = 24
      Top = 184
      Width = 113
      Height = 33
      Caption = 'Start'
      TabOrder = 0
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 16
      Top = 688
      Width = 113
      Height = 33
      Caption = 'Close'
      TabOrder = 1
      OnClick = Button2Click
    end
    object Edit1: TEdit
      Left = 72
      Top = 32
      Width = 65
      Height = 21
      TabOrder = 2
      Text = 'Edit1'
    end
    object Edit2: TEdit
      Left = 72
      Top = 64
      Width = 65
      Height = 21
      TabOrder = 3
      Text = 'Edit2'
    end
    object Edit3: TEdit
      Left = 72
      Top = 96
      Width = 65
      Height = 21
      TabOrder = 4
      Text = 'Edit3'
    end
    object Button3: TButton
      Left = 24
      Top = 224
      Width = 113
      Height = 33
      Caption = 'Clear 1'
      TabOrder = 5
      OnClick = Button3Click
    end
    object Button4: TButton
      Left = 24
      Top = 280
      Width = 113
      Height = 33
      Caption = 'Optimal - auto'
      TabOrder = 6
      OnClick = Button4Click
    end
    object Memo1: TMemo
      Left = 152
      Top = 32
      Width = 161
      Height = 145
      Alignment = taCenter
      Lines.Strings = (
        'Angle and distance:')
      TabOrder = 7
    end
    object Memo2: TMemo
      Left = 152
      Top = 280
      Width = 161
      Height = 73
      Lines.Strings = (
        'Optimal angle and distance:')
      TabOrder = 8
    end
    object Button5: TButton
      Left = 24
      Top = 320
      Width = 113
      Height = 33
      Caption = 'Clear 2'
      TabOrder = 9
      OnClick = Button5Click
    end
    object Edit5: TEdit
      Left = 72
      Top = 416
      Width = 65
      Height = 21
      TabOrder = 10
      Text = 'Edit5'
    end
    object Button6: TButton
      Left = 24
      Top = 448
      Width = 113
      Height = 33
      Caption = 'Speed'
      TabOrder = 11
      OnClick = Button6Click
    end
    object Memo3: TMemo
      Left = 152
      Top = 384
      Width = 161
      Height = 57
      HelpType = htKeyword
      Lines.Strings = (
        'Speed:')
      TabOrder = 12
    end
    object CColorGrid1: TCColorGrid
      Left = 152
      Top = 184
      Width = 160
      Height = 72
      TabOrder = 13
    end
    object Button7: TButton
      Left = 16
      Top = 568
      Width = 113
      Height = 33
      Caption = 'Orbite'
      TabOrder = 14
      OnClick = Button7Click
    end
    object Edit6: TEdit
      Left = 56
      Top = 504
      Width = 73
      Height = 21
      TabOrder = 15
      Text = 'Edit6'
    end
    object Edit7: TEdit
      Left = 56
      Top = 536
      Width = 73
      Height = 21
      TabOrder = 16
      Text = 'Edit7'
    end
    object CColorGrid2: TCColorGrid
      Left = 152
      Top = 568
      Width = 160
      Height = 72
      TabOrder = 17
    end
    object Button8: TButton
      Left = 16
      Top = 608
      Width = 113
      Height = 33
      Caption = 'Clear 3'
      TabOrder = 18
      OnClick = Button8Click
    end
    object Edit8: TEdit
      Left = 216
      Top = 504
      Width = 65
      Height = 21
      TabOrder = 19
      Text = 'Edit8'
    end
    object Edit9: TEdit
      Left = 216
      Top = 536
      Width = 65
      Height = 21
      TabOrder = 20
      Text = 'Edit9'
    end
    object Edit4: TEdit
      Left = 72
      Top = 388
      Width = 65
      Height = 21
      TabOrder = 21
      Text = 'Edit4'
    end
    object Button9: TButton
      Left = 16
      Top = 648
      Width = 113
      Height = 33
      Caption = 'Button9'
      TabOrder = 22
      OnClick = Button9Click
    end
    object Memo4: TMemo
      Left = 152
      Top = 648
      Width = 161
      Height = 65
      Lines.Strings = (
        'Memo4')
      TabOrder = 23
    end
  end
  object Chart2: TChart
    Left = 8
    Top = 183
    Width = 369
    Height = 369
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.Text.Strings = (
      'X(alfa)')
    Legend.TextStyle = ltsPlain
    Legend.Visible = False
    View3D = False
    TabOrder = 2
    object Series2: TPointSeries
      Marks.ArrowLength = 8
      Marks.Visible = False
      SeriesColor = clRed
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
  object Chart3: TChart
    Left = 712
    Top = -177
    Width = 649
    Height = 729
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.Text.Strings = (
      '')
    BottomAxis.Automatic = False
    BottomAxis.AutomaticMaximum = False
    BottomAxis.AutomaticMinimum = False
    BottomAxis.Maximum = 20000
    BottomAxis.Minimum = -20000
    LeftAxis.Automatic = False
    LeftAxis.AutomaticMaximum = False
    LeftAxis.AutomaticMinimum = False
    LeftAxis.Maximum = 10000
    LeftAxis.Minimum = -35000
    Legend.Visible = False
    View3D = False
    TabOrder = 3
    object Series3: TPointSeries
      Marks.ArrowLength = 0
      Marks.Visible = False
      SeriesColor = clRed
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
end
