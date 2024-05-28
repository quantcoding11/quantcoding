object FormMain: TFormMain
  Left = 0
  Top = 0
  Caption = 'QunatCoding'
  ClientHeight = 648
  ClientWidth = 802
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = #44404#47548#52404
  Font.Style = []
  Menu = MainMenu1
  Position = poDesktopCenter
  OnCloseQuery = FormCloseQuery
  OnShow = FormShow
  TextHeight = 16
  object Button1: TButton
    Left = 24
    Top = 24
    Width = 145
    Height = 25
    Caption = #53412#50880#51613#44428' '#47196#44536#51064
    TabOrder = 0
    OnClick = Button1Click
  end
  object GroupBox1: TGroupBox
    Left = 24
    Top = 80
    Width = 473
    Height = 473
    Caption = #51312#44148' '#44160#49353
    TabOrder = 1
    object Button2: TButton
      Left = 25
      Top = 32
      Width = 152
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
    Top = 559
    Width = 802
    Height = 89
    Align = alBottom
    ScrollBars = ssBoth
    TabOrder = 2
    ExplicitTop = 558
    ExplicitWidth = 798
  end
  object GroupBox2: TGroupBox
    Left = 520
    Top = 80
    Width = 249
    Height = 233
    Caption = ' '#44553#46321#51452' detect'
    TabOrder = 3
    object Memo2: TMemo
      Left = 19
      Top = 34
      Width = 206
      Height = 174
      ScrollBars = ssBoth
      TabOrder = 0
    end
  end
  object MainMenu1: TMainMenu
    Left = 200
    Top = 24
    object file1: TMenuItem
      Caption = 'file'
      object N1: TMenuItem
        Caption = #53412#50880' '#54868#47732' '#48372#44592
        OnClick = N1Click
      end
      object test1: TMenuItem
        Caption = 'test'
        OnClick = test1Click
      end
    end
  end
end
