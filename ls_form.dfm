object FormLS: TFormLS
  Left = 0
  Top = 0
  Caption = 'FormLS'
  ClientHeight = 559
  ClientWidth = 775
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object XASession1: TXASession
    Left = 144
    Top = 96
    Width = 0
    Height = 0
    OnLogin = XASession1Login
    ControlData = {000A0000D8130000D8130000}
  end
  object XAQuery1: TXAQuery
    Left = 184
    Top = 104
    Width = 0
    Height = 0
    ControlData = {000A0000D8130000D81300000800020000000000}
  end
  object XAReal1: TXAReal
    Left = 264
    Top = 96
    Width = 0
    Height = 0
    ControlData = {000A0000D8130000D81300000800020000000000}
  end
  object Button1: TButton
    Left = 144
    Top = 24
    Width = 75
    Height = 25
    Caption = 'login'
    TabOrder = 3
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 32
    Top = 24
    Width = 75
    Height = 25
    Caption = 'connect'
    TabOrder = 4
    OnClick = Button2Click
  end
end
