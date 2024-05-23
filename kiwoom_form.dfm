object FormKiwoom: TFormKiwoom
  Left = 0
  Top = 0
  Caption = 'FormKiwoom'
  ClientHeight = 529
  ClientWidth = 1019
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
    OnReceiveMsg = KHOpenAPI1ReceiveMsg
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
    Width = 249
    Height = 313
    Caption = #51452#47928' ('#54632#49688#54840#52636')'
    TabOrder = 1
    object Label1: TLabel
      Left = 16
      Top = 35
      Width = 26
      Height = 15
      Caption = 'code'
    end
    object Label2: TLabel
      Left = 16
      Top = 75
      Width = 26
      Height = 15
      Caption = 'price'
    end
    object Label3: TLabel
      Left = 16
      Top = 115
      Width = 40
      Height = 15
      Caption = 'volume'
    end
    object EditStockCode: TEdit
      Left = 64
      Top = 32
      Width = 73
      Height = 23
      NumbersOnly = True
      TabOrder = 0
      Text = '005930'
    end
    object EditPrice: TEdit
      Left = 64
      Top = 72
      Width = 73
      Height = 23
      NumbersOnly = True
      TabOrder = 1
      Text = '70000'
    end
    object CheckBoxMarketPrice: TCheckBox
      Left = 160
      Top = 75
      Width = 73
      Height = 17
      Caption = #49884#51109#44032
      TabOrder = 2
    end
    object EditVolume: TEdit
      Left = 64
      Top = 112
      Width = 73
      Height = 23
      NumbersOnly = True
      TabOrder = 3
      Text = '1'
    end
    object Button1: TButton
      Left = 25
      Top = 168
      Width = 75
      Height = 25
      Caption = #47588#49688
      TabOrder = 4
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 144
      Top = 168
      Width = 75
      Height = 25
      Caption = #47588#46020
      TabOrder = 5
      OnClick = Button2Click
    end
    object Button3: TButton
      Left = 25
      Top = 216
      Width = 75
      Height = 25
      Caption = #47588#49688' '#51221#51221
      TabOrder = 6
      OnClick = Button3Click
    end
    object Button4: TButton
      Left = 144
      Top = 216
      Width = 75
      Height = 25
      Caption = #47588#46020' '#51221#51221
      TabOrder = 7
      OnClick = Button4Click
    end
    object Button5: TButton
      Left = 25
      Top = 264
      Width = 75
      Height = 25
      Caption = #47588#49688' '#52712#49548
      TabOrder = 8
      OnClick = Button5Click
    end
    object Button6: TButton
      Left = 144
      Top = 264
      Width = 75
      Height = 25
      Caption = #47588#46020' '#52712#49548
      TabOrder = 9
      OnClick = Button6Click
    end
  end
  object Memo1: TMemo
    Left = 0
    Top = 440
    Width = 1019
    Height = 89
    Align = alBottom
    ScrollBars = ssBoth
    TabOrder = 2
    ExplicitTop = 439
    ExplicitWidth = 954
  end
  object GroupBox1: TGroupBox
    Left = 304
    Top = 104
    Width = 249
    Height = 313
    Caption = #51452#47928' (thread)'
    TabOrder = 3
    object Label4: TLabel
      Left = 16
      Top = 35
      Width = 26
      Height = 15
      Caption = 'code'
    end
    object Label5: TLabel
      Left = 16
      Top = 75
      Width = 26
      Height = 15
      Caption = 'price'
    end
    object Label6: TLabel
      Left = 16
      Top = 115
      Width = 40
      Height = 15
      Caption = 'volume'
    end
    object EditStockCode2: TEdit
      Left = 64
      Top = 32
      Width = 73
      Height = 23
      NumbersOnly = True
      TabOrder = 0
      Text = '005930'
    end
    object EditPrice2: TEdit
      Left = 64
      Top = 72
      Width = 73
      Height = 23
      NumbersOnly = True
      TabOrder = 1
      Text = '70000'
    end
    object CheckBoxMarketPrice2: TCheckBox
      Left = 160
      Top = 75
      Width = 73
      Height = 17
      Caption = #49884#51109#44032
      TabOrder = 2
    end
    object EditVolume2: TEdit
      Left = 64
      Top = 112
      Width = 73
      Height = 23
      NumbersOnly = True
      TabOrder = 3
      Text = '1'
    end
    object Button7: TButton
      Left = 25
      Top = 168
      Width = 75
      Height = 25
      Caption = #47588#49688
      TabOrder = 4
      OnClick = Button7Click
    end
    object Button8: TButton
      Left = 144
      Top = 168
      Width = 75
      Height = 25
      Caption = #47588#46020
      TabOrder = 5
      OnClick = Button8Click
    end
    object Button9: TButton
      Left = 25
      Top = 216
      Width = 75
      Height = 25
      Caption = #47588#49688' '#51221#51221
      TabOrder = 6
      OnClick = Button9Click
    end
    object Button10: TButton
      Left = 144
      Top = 216
      Width = 75
      Height = 25
      Caption = #47588#46020' '#51221#51221
      TabOrder = 7
      OnClick = Button10Click
    end
    object Button11: TButton
      Left = 25
      Top = 264
      Width = 75
      Height = 25
      Caption = #47588#49688' '#52712#49548
      TabOrder = 8
      OnClick = Button11Click
    end
    object Button12: TButton
      Left = 144
      Top = 264
      Width = 75
      Height = 25
      Caption = #47588#46020' '#52712#49548
      TabOrder = 9
      OnClick = Button12Click
    end
  end
  object Button13: TButton
    Left = 464
    Top = 56
    Width = 75
    Height = 25
    Caption = 'add'
    TabOrder = 4
    OnClick = Button13Click
  end
  object EditObject: TEdit
    Left = 337
    Top = 57
    Width = 121
    Height = 23
    TabOrder = 5
    Text = '005930'
  end
  object GroupBox3: TGroupBox
    Left = 584
    Top = 104
    Width = 233
    Height = 161
    Caption = 'TR'#47785#47197
    TabOrder = 6
    object Button16: TButton
      Left = 22
      Top = 31
      Width = 195
      Height = 25
      Caption = #50696#49345#52404#44208#46321#46973#47456#49345#50948#50836#52397
      TabOrder = 0
      OnClick = Button16Click
    end
    object Button15: TButton
      Left = 22
      Top = 77
      Width = 195
      Height = 25
      Caption = #44144#47000#45824#44552#49345#50948#50836#52397
      TabOrder = 1
      OnClick = Button15Click
    end
  end
  object Button14: TButton
    Left = 624
    Top = 73
    Width = 121
    Height = 25
    Caption = 'object list '#51312#54924
    TabOrder = 7
    OnClick = Button14Click
  end
  object Button17: TButton
    Left = 1016
    Top = 175
    Width = 75
    Height = 25
    Caption = #49892#49884#44036' '#50836#52397
    TabOrder = 8
    OnClick = Button17Click
  end
end
