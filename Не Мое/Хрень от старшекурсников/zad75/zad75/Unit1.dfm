object Form1: TForm1
  Left = 193
  Top = 123
  Width = 1138
  Height = 601
  VertScrollBar.Position = 136
  Align = alClient
  Caption = #1047#1072#1076#1072#1095#1072' 84'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 744
    Top = -136
    Width = 593
    Height = 513
    Transparent = True
  end
  object Chart1: TChart
    Left = 0
    Top = -136
    Width = 745
    Height = 513
    BackWall.Brush.Color = clWhite
    Title.Text.Strings = (
      'TChart')
    View3D = False
    View3DOptions.Elevation = 315
    View3DOptions.Orthogonal = False
    View3DOptions.Perspective = 0
    View3DOptions.Rotation = 360
    Align = alLeft
    TabOrder = 0
    object Series1: TLineSeries
      Marks.ArrowLength = 8
      Marks.Visible = False
      SeriesColor = clRed
      LinePen.Width = 2
      Pointer.HorizSize = 5
      Pointer.InflateMargins = True
      Pointer.Style = psCross
      Pointer.VertSize = 5
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
    object Series3: TLineSeries
      Marks.ArrowLength = 8
      Marks.Visible = False
      SeriesColor = clGreen
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
  object Panel1: TPanel
    Left = 0
    Top = 377
    Width = 1337
    Height = 169
    Align = alBottom
    TabOrder = 1
    object Label6: TLabel
      Left = 8
      Top = 8
      Width = 23
      Height = 13
      Caption = #1064#1072#1075':'
    end
    object Label1: TLabel
      Left = 8
      Top = 32
      Width = 23
      Height = 13
      Caption = 'fi(0)='
    end
    object Label2: TLabel
      Left = 8
      Top = 56
      Width = 38
      Height = 13
      Caption = 'fiSH(0)='
    end
    object Label3: TLabel
      Left = 8
      Top = 80
      Width = 56
      Height = 13
      Caption = #1050'-'#1090' '#1090#1088#1077#1085#1080#1103':'
    end
    object Label4: TLabel
      Left = 136
      Top = 8
      Width = 20
      Height = 13
      Caption = 'w0='
    end
    object Label5: TLabel
      Left = 136
      Top = 32
      Width = 13
      Height = 13
      Caption = 'A='
    end
    object Label7: TLabel
      Left = 136
      Top = 56
      Width = 40
      Height = 13
      Caption = 'gamma='
    end
    object Label8: TLabel
      Left = 256
      Top = 8
      Width = 12
      Height = 13
      Caption = 'k='
    end
    object Label9: TLabel
      Left = 504
      Top = 8
      Width = 97
      Height = 13
      Caption = #1058#1086#1095#1082#1080' '#1073#1080#1092#1091#1088#1082#1072#1094#1080#1081':'
    end
    object Label10: TLabel
      Left = 328
      Top = 8
      Width = 73
      Height = 13
      Caption = #1050#1086#1083'. '#1087#1077#1088#1080#1086#1076#1086#1074
    end
    object Label11: TLabel
      Left = 328
      Top = 32
      Width = 73
      Height = 13
      Caption = #1074#1088#1077#1084#1103' '#1085#1072#1095#1072#1083#1072':'
    end
    object Label13: TLabel
      Left = 624
      Top = 8
      Width = 27
      Height = 13
      Caption = '0,340'
    end
    object Label14: TLabel
      Left = 624
      Top = 24
      Width = 27
      Height = 13
      Caption = '0,344'
    end
    object Label15: TLabel
      Left = 624
      Top = 56
      Width = 27
      Height = 13
      Caption = '0,395'
    end
    object Label16: TLabel
      Left = 504
      Top = 88
      Width = 38
      Height = 13
      Caption = 'Label16'
    end
    object Label17: TLabel
      Left = 664
      Top = 8
      Width = 27
      Height = 13
      Caption = '0,450'
    end
    object Label18: TLabel
      Left = 664
      Top = 24
      Width = 27
      Height = 13
      Caption = '0,495'
    end
    object Label19: TLabel
      Left = 664
      Top = 40
      Width = 27
      Height = 13
      Caption = '0,510'
    end
    object Label12: TLabel
      Left = 624
      Top = 40
      Width = 27
      Height = 13
      Caption = '0.365'
    end
    object Label20: TLabel
      Left = 408
      Top = 56
      Width = 38
      Height = 13
      Caption = 'Label20'
    end
    object Label21: TLabel
      Left = 328
      Top = 56
      Width = 69
      Height = 13
      Caption = #1042#1088#1077#1084#1103' '#1082#1086#1085#1094#1072':'
    end
    object Edit2: TEdit
      Left = 72
      Top = 0
      Width = 57
      Height = 21
      TabOrder = 0
      Text = '500'
    end
    object Button1: TButton
      Left = 8
      Top = 104
      Width = 75
      Height = 25
      Caption = #1055#1099#1097#1100'!'
      TabOrder = 1
      OnClick = Button1Click
    end
    object Edit1: TEdit
      Left = 72
      Top = 24
      Width = 57
      Height = 21
      TabOrder = 2
      Text = '0,4'
    end
    object Edit3: TEdit
      Left = 72
      Top = 48
      Width = 57
      Height = 21
      TabOrder = 3
      Text = '0'
    end
    object Edit4: TEdit
      Left = 72
      Top = 72
      Width = 57
      Height = 21
      TabOrder = 4
      Text = '0,1'
    end
    object Edit5: TEdit
      Left = 184
      Top = 0
      Width = 57
      Height = 21
      TabOrder = 5
      Text = '1'
    end
    object Edit6: TEdit
      Left = 184
      Top = 24
      Width = 57
      Height = 21
      TabOrder = 6
      Text = '0,5'
    end
    object Edit7: TEdit
      Left = 184
      Top = 48
      Width = 57
      Height = 21
      TabOrder = 7
      Text = '2'
    end
    object Edit8: TEdit
      Left = 272
      Top = 0
      Width = 41
      Height = 21
      TabOrder = 8
      Text = '50'
    end
    object Edit9: TEdit
      Left = 408
      Top = 0
      Width = 41
      Height = 21
      TabOrder = 9
      Text = '70'
    end
    object Edit10: TEdit
      Left = 408
      Top = 24
      Width = 41
      Height = 21
      TabOrder = 10
      Text = '1'
    end
    object Button2: TButton
      Left = 8
      Top = 136
      Width = 73
      Height = 25
      Caption = 'Clear Graph'
      TabOrder = 11
      OnClick = Button2Click
    end
  end
end
