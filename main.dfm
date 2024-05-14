object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'QunatCoding'
  ClientHeight = 732
  ClientWidth = 861
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #44404#47548#52404
  Font.Style = []
  TextHeight = 12
  object Button1: TButton
    Left = 24
    Top = 96
    Width = 75
    Height = 25
    Caption = #47196#44536#51064
    TabOrder = 0
    OnClick = Button1Click
  end
  object GroupBox1: TGroupBox
    Left = 24
    Top = 144
    Width = 473
    Height = 473
    Caption = #51312#44148' '#44160#49353
    TabOrder = 1
    object Button2: TButton
      Left = 25
      Top = 32
      Width = 120
      Height = 25
      Caption = #51312#44148#49885' '#44032#51256#50724#44592
      TabOrder = 0
      OnClick = Button2Click
    end
    object StringGridList: TStringGrid
      Left = 25
      Top = 63
      Width = 192
      Height = 106
      ColCount = 2
      FixedCols = 0
      RowCount = 15
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowSelect]
      ScrollBars = ssVertical
      TabOrder = 1
      OnClick = StringGridListClick
      OnSelectCell = StringGridListSelectCell
      ColWidths = (
        44
        115)
      RowHeights = (
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24)
    end
    object Button3: TButton
      Left = 25
      Top = 183
      Width = 75
      Height = 25
      Caption = #51312#44148' '#44160#49353
      TabOrder = 2
      OnClick = Button3Click
    end
    object StringGridLiteItem: TStringGrid
      Left = 25
      Top = 214
      Width = 424
      Height = 237
      ColCount = 4
      FixedCols = 0
      RowCount = 11
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowSelect]
      ScrollBars = ssVertical
      TabOrder = 3
      ColWidths = (
        44
        114
        75
        142)
      RowHeights = (
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24)
    end
  end
  object Memo1: TMemo
    Left = 0
    Top = 643
    Width = 861
    Height = 89
    Align = alBottom
    ScrollBars = ssBoth
    TabOrder = 2
    ExplicitTop = 547
    ExplicitWidth = 820
  end
  object KHOpenAPI1: TKHOpenAPI
    Left = 24
    Top = 24
    Width = 100
    Height = 50
    TabOrder = 3
    OnReceiveTrData = KHOpenAPI1ReceiveTrData
    OnReceiveRealData = KHOpenAPI1ReceiveRealData
    OnReceiveChejanData = KHOpenAPI1ReceiveChejanData
    OnEventConnect = KHOpenAPI1EventConnect
    OnReceiveInvestRealData = KHOpenAPI1ReceiveInvestRealData
    OnReceiveTrCondition = KHOpenAPI1ReceiveTrCondition
    OnReceiveConditionVer = KHOpenAPI1ReceiveConditionVer
    ControlData = {02000100560A00002B05000000000000}
  end
end
