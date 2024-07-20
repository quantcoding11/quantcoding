object FormNH: TFormNH
  Left = 0
  Top = 0
  Caption = 'FormNH'
  ClientHeight = 565
  ClientWidth = 649
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object LabelItem: TLabel
    Left = 544
    Top = 252
    Width = 6
    Height = 15
    Caption = '0'
  end
  object Memo1: TMemo
    Left = 42
    Top = 408
    Width = 535
    Height = 129
    ScrollBars = ssVertical
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
  object GroupBox1: TGroupBox
    Left = 42
    Top = 80
    Width = 287
    Height = 249
    Caption = 'GroupBox1'
    TabOrder = 3
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
    object Label4: TLabel
      Left = 176
      Top = 51
      Width = 57
      Height = 15
      Caption = 'order code'
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
    object EditVolume: TEdit
      Left = 64
      Top = 112
      Width = 73
      Height = 23
      NumbersOnly = True
      TabOrder = 2
      Text = '1'
    end
    object Button3: TButton
      Left = 48
      Top = 152
      Width = 75
      Height = 25
      Caption = #47588#49688
      TabOrder = 3
      OnClick = Button3Click
    end
    object Button4: TButton
      Left = 176
      Top = 152
      Width = 75
      Height = 25
      Caption = #47588#46020
      TabOrder = 4
      OnClick = Button4Click
    end
    object Button5: TButton
      Left = 48
      Top = 200
      Width = 75
      Height = 25
      Caption = #51221#51221
      TabOrder = 5
      OnClick = Button5Click
    end
    object Button6: TButton
      Left = 176
      Top = 200
      Width = 75
      Height = 25
      Caption = #52712#49548
      TabOrder = 6
      OnClick = Button6Click
    end
    object EditCode: TEdit
      Left = 176
      Top = 72
      Width = 75
      Height = 23
      TabOrder = 7
    end
  end
  object GroupBox2: TGroupBox
    Left = 352
    Top = 80
    Width = 257
    Height = 130
    Caption = #51648#49688
    TabOrder = 4
    object Button7: TButton
      Left = 24
      Top = 35
      Width = 75
      Height = 25
      Caption = 'kospi'
      TabOrder = 0
      OnClick = Button7Click
    end
    object Button8: TButton
      Left = 123
      Top = 35
      Width = 75
      Height = 25
      Caption = 'kosdaq'
      TabOrder = 1
      OnClick = Button8Click
    end
    object Button9: TButton
      Left = 24
      Top = 88
      Width = 75
      Height = 25
      Caption = #49440#47932#53076#46300
      TabOrder = 2
      OnClick = Button9Click
    end
    object Button10: TButton
      Left = 120
      Top = 88
      Width = 75
      Height = 25
      Caption = #49440#47932#51648#49688
      TabOrder = 3
      OnClick = Button10Click
    end
  end
  object Button11: TButton
    Left = 376
    Top = 248
    Width = 145
    Height = 25
    Caption = #51333#47785#47560#49828#53440#44592#48376#51088#47308
    TabOrder = 5
    OnClick = Button11Click
  end
  object Button12: TButton
    Left = 376
    Top = 288
    Width = 145
    Height = 25
    Caption = #49892#49884#44036' '#45936#51060#53552' '#50836#52397
    TabOrder = 6
    OnClick = Button12Click
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 560
    Top = 288
  end
end
