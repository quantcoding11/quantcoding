object FormNH: TFormNH
  Left = 0
  Top = 0
  Caption = 'FormNH'
  ClientHeight = 442
  ClientWidth = 628
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object Memo1: TMemo
    Left = 40
    Top = 224
    Width = 337
    Height = 177
    TabOrder = 0
  end
  object Button1: TButton
    Left = 40
    Top = 24
    Width = 75
    Height = 25
    Caption = 'connect'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 152
    Top = 24
    Width = 75
    Height = 25
    Caption = 'login'
    TabOrder = 2
    OnClick = Button2Click
  end
end
