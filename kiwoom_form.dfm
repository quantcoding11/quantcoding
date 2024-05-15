object FormKiwoom: TFormKiwoom
  Left = 0
  Top = 0
  Caption = 'FormKiwoom'
  ClientHeight = 549
  ClientWidth = 975
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object KHOpenAPI1: TKHOpenAPI
    Left = 24
    Top = 24
    Width = 100
    Height = 50
    TabOrder = 0
    OnReceiveTrData = KHOpenAPI1ReceiveTrData
    OnReceiveRealData = KHOpenAPI1ReceiveRealData
    OnReceiveChejanData = KHOpenAPI1ReceiveChejanData
    OnEventConnect = KHOpenAPI1EventConnect
    OnReceiveInvestRealData = KHOpenAPI1ReceiveInvestRealData
    OnReceiveTrCondition = KHOpenAPI1ReceiveTrCondition
    OnReceiveConditionVer = KHOpenAPI1ReceiveConditionVer
    ControlData = {02000100560A00002B05000000000000}
  end
  object GroupBox2: TGroupBox
    Left = 24
    Top = 104
    Width = 441
    Height = 225
    Caption = #47588#47588' ('#54632#49688#54840#52636')'
    TabOrder = 1
  end
end
