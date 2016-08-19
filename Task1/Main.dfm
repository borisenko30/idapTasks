object Form1: TForm1
  Left = 192
  Top = 124
  Width = 526
  Height = 453
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object StringGrid1: TStringGrid
    Left = 16
    Top = 56
    Width = 465
    Height = 329
    ColCount = 3
    FixedCols = 0
    RowCount = 1
    FixedRows = 0
    TabOrder = 0
    OnClick = StringGrid1Click
    OnDrawCell = StringGrid1DrawCell
    ColWidths = (
      25
      368
      64)
  end
  object BitBtn1: TBitBtn
    Left = 16
    Top = 16
    Width = 75
    Height = 25
    Caption = 'Check all'
    TabOrder = 1
    OnClick = BitBtn1Click
    Kind = bkAll
    Layout = blGlyphRight
  end
  object BitBtn2: TBitBtn
    Left = 144
    Top = 16
    Width = 75
    Height = 25
    Caption = 'Sort'
    TabOrder = 2
    OnClick = BitBtn2Click
    Kind = bkRetry
    Layout = blGlyphRight
  end
  object BitBtn3: TBitBtn
    Left = 272
    Top = 16
    Width = 75
    Height = 25
    Caption = 'Add row'
    TabOrder = 3
    OnClick = BitBtn3Click
    Kind = bkOK
    Layout = blGlyphRight
  end
  object BitBtn4: TBitBtn
    Left = 408
    Top = 16
    Width = 75
    Height = 25
    Caption = 'Delete'
    TabOrder = 4
    OnClick = BitBtn4Click
    Kind = bkCancel
    Layout = blGlyphRight
  end
end
