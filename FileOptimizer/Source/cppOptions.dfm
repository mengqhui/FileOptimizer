object frmOptions: TfrmOptions
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Options'
  ClientHeight = 406
  ClientWidth = 567
  Color = clWindow
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  DesignSize = (
    567
    406)
  PixelsPerInch = 96
  TextHeight = 13
  object shpDialogBackground: TShape
    Left = 0
    Top = 0
    Width = 562
    Height = 58
    Anchors = [akLeft, akTop, akRight]
    Brush.Style = bsClear
    Pen.Color = clWhite
    ExplicitWidth = 556
  end
  object lblTitle: TLabel
    Left = 8
    Top = 5
    Width = 217
    Height = 16
    Align = alCustom
    AutoSize = False
    Caption = 'Options'
    Color = clWindow
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    WordWrap = True
  end
  object imgDialogPicture: TImage
    Left = 519
    Top = 0
    Width = 48
    Height = 406
    Align = alRight
    Anchors = [akTop, akRight]
    AutoSize = True
    Picture.Data = {
      07544269746D6170E8020000424DE8020000000000003E000000280000003000
      00003A0000000100040002000000AA020000120B0000120B0000020000000000
      0000C6C3C600FFFFFF00301100003011000030110000301100001A1100040001
      121100001A1105001111000019110008001000010F1100001911000800111001
      0F11000018110008001110011011000018110008001110011011000017110008
      0011100111110000171100080011100111110000161100080011100112110000
      0D1100100001111110011100131100000D110400041100080011100113110000
      0D110500000C111001110011121100000D110010001000100111001113110000
      0D1100100011000001110011131100000D110010001110001110011113110000
      0D11020009110200161100000D11020008110A000F1100000D11020009110A00
      0E1100000D1102000F11000400010E1100000D1102000E11000400010F110000
      0D1102000D1100040001101100000D1102000C1100040001111100000D110200
      0B1100040001121100000D1102000A1100040001131100000D11020009110004
      0001141100000D110200081100040001151100000D1102000711000400011611
      0000051102000611020006110004000117110000051100140001111100111110
      0011171100000611001000011110011110001A11000007110010000111001110
      0011191100000811000C0001100110001C1100000911000C0001001000111B11
      00000A110008001000001E1100000D1104001F11000002100900000811000110
      0900141100000210090007110A0014110000301100000A110008001111001E11
      00000911000C0001001000111B1100000811000C0001100110001C1100000711
      00100001110011100011191100000611001000011110011110001A1100000511
      0014000111110011111000111711000005110200061102000611020019110000
      0D110200211100000D110200211100000D110200211100000D11020021110000
      3011000030110000301100003011000030110001}
    Proportional = True
    Transparent = True
    ExplicitHeight = 58
  end
  object lblDescription: TLabel
    Left = 8
    Top = 25
    Width = 505
    Height = 31
    Align = alCustom
    Anchors = [akLeft, akTop, akRight]
    AutoSize = False
    Caption = 'Configure the appearance and behaviour of FileOptimizer'
    Color = clWindow
    ParentColor = False
    ParentShowHint = False
    ShowHint = True
    WordWrap = True
    ExplicitWidth = 672
  end
  object shpDialogLineG1: TShape
    Left = 0
    Top = 56
    Width = 562
    Height = 2
    Anchors = [akLeft, akTop, akRight]
    Brush.Color = clGray
    Pen.Color = clGray
    ExplicitWidth = 556
  end
  object tabOptions: TPageControl
    Left = 0
    Top = 65
    Width = 567
    Height = 303
    ActivePage = pagGeneral
    Align = alCustom
    ParentShowHint = False
    ShowHint = True
    TabOrder = 0
    object pagGeneral: TTabSheet
      Caption = '&General'
      ParentShowHint = False
      ShowHint = True
      object lblOptimizationLevel: TLabel
        Left = 7
        Top = 22
        Width = 155
        Height = 13
        AutoSize = False
        Caption = '&Optimization level'
        FocusControl = cboOptimizationLevel
        ParentShowHint = False
        ShowHint = False
      end
      object lblProcessPriority: TLabel
        Left = 7
        Top = 48
        Width = 155
        Height = 13
        AutoSize = False
        Caption = '&Process priority'
        FocusControl = cboProcessPriority
        ParentShowHint = False
        ShowHint = False
      end
      object lblCheckForUpdates: TLabel
        Left = 7
        Top = 74
        Width = 155
        Height = 13
        AutoSize = False
        Caption = '&Check for updates'
        FocusControl = cboCheckForUpdates
        ParentShowHint = False
        ShowHint = False
      end
      object lblLogLevel: TLabel
        Left = 7
        Top = 99
        Width = 155
        Height = 13
        AutoSize = False
        Caption = '&Log level'
        FocusControl = cboLogLevel
        ParentShowHint = False
        ShowHint = False
      end
      object lblExcludeMask: TLabel
        Left = 7
        Top = 171
        Width = 155
        Height = 13
        AutoSize = False
        Caption = '&Exclude mask'
        FocusControl = txtExcludeMask
        ParentShowHint = False
        ShowHint = False
      end
      object chkKeepAttributes: TCheckBox
        Left = 7
        Top = 123
        Width = 281
        Height = 17
        Hint = 
          'Keep original readonly, system, hidden and archive attributes as' +
          ' well as creation and modification timestamps.'
        Caption = '&Keep file attributes'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
      object cboOptimizationLevel: TComboBox
        Left = 168
        Top = 19
        Width = 145
        Height = 21
        Hint = 'Optimization level from best speed to best compression.'
        Style = csDropDownList
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        Items.Strings = (
          '0: Fastest'
          '1: Faster'
          '2: Fast'
          '3:'
          '4:'
          '5: Normal'
          '6:'
          '7: Good'
          '8: Better'
          '9: Best')
      end
      object cboProcessPriority: TComboBox
        Left = 168
        Top = 45
        Width = 145
        Height = 21
        Hint = 'Process priority from most conservative to best performance.'
        Style = csDropDownList
        ParentShowHint = False
        ShowHint = True
        TabOrder = 2
        Items.Strings = (
          'Idle'
          'Below normal'
          'Normal'
          'Above normal'
          'High'
          'Realtime')
      end
      object cboCheckForUpdates: TComboBox
        Left = 168
        Top = 71
        Width = 145
        Height = 21
        Hint = 'Automatically check for program updates.'
        Style = csDropDownList
        ParentShowHint = False
        ShowHint = True
        TabOrder = 3
        Items.Strings = (
          'Ask'
          'Automatically'
          'Never')
      end
      object cboLogLevel: TComboBox
        Left = 168
        Top = 97
        Width = 145
        Height = 21
        Hint = 'Debugging level to output on program log.'
        Style = csDropDownList
        ParentShowHint = False
        ShowHint = True
        TabOrder = 4
        Items.Strings = (
          '0: None'
          '1: Critical'
          '2: Error'
          '3: Warning'
          '4: Information')
      end
      object chkDoNotUseRecycleBin: TCheckBox
        Left = 7
        Top = 147
        Width = 281
        Height = 17
        Hint = 
          'When checked original files will not be backed up in the system ' +
          'trashcan.'
        Caption = '&Do not use recycle bin'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 6
      end
      object txtExcludeMask: TEdit
        Left = 168
        Top = 171
        Width = 145
        Height = 21
        Hint = 
          'Files containing this mask (substring) on name or path will be e' +
          'xcluded from optimization. You can use semicolon (;) to specify ' +
          'more than one substring being excluded.'
        AutoSize = False
        HideSelection = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 5
      end
    end
    object pagAppearance: TTabSheet
      Caption = '&Appearance'
      ImageIndex = 13
      object lblTheme: TLabel
        Left = 7
        Top = 22
        Width = 155
        Height = 13
        AutoSize = False
        Caption = '&Theme'
        FocusControl = cboTheme
        ParentShowHint = False
        ShowHint = False
      end
      object cboTheme: TComboBox
        Left = 168
        Top = 22
        Width = 145
        Height = 21
        Hint = 'Visual theme.'
        Style = csDropDownList
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        Items.Strings = (
          'Windows')
      end
      object chkUseRibbon: TCheckBox
        Left = 7
        Top = 46
        Width = 281
        Height = 17
        Hint = 
          'Use Microsoft Office alike Ribbon interface instead of classic W' +
          'indows pulldown menus.'
        Caption = '&Use ribbon interface'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
      end
    end
    object pagCSS: TTabSheet
      Caption = '&CSS'
      ImageIndex = 6
      object lblCSSTemplate: TLabel
        Left = 7
        Top = 46
        Width = 155
        Height = 13
        AutoSize = False
        Caption = '&Template'
        FocusControl = cboCSSTemplate
        ParentShowHint = False
        ShowHint = False
      end
      object chkCSSEnableTidy: TCheckBox
        Left = 7
        Top = 22
        Width = 281
        Height = 17
        Hint = 
          'Enable tidy. Results in smaller files, but can happen they are n' +
          'ot editable anymore.'
        Caption = '&Enable Tidy'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        OnClick = chkCSSEnableTidyClick
      end
      object cboCSSTemplate: TComboBox
        Left = 168
        Top = 46
        Width = 145
        Height = 21
        Hint = 
          'Compression template, from safer and worse compression, to highe' +
          'st compression'
        Style = csDropDownList
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        Items.Strings = (
          'Low'
          'High'
          'Highest')
      end
    end
    object pagEXE: TTabSheet
      Caption = '&EXE'
      ImageIndex = 6
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object chkEXEDisablePETrim: TCheckBox
        Left = 7
        Top = 22
        Width = 281
        Height = 17
        Hint = 
          'Disable PETrim. When enabled, PETrim will not be used, resulting' +
          ' in less EXE corruption at the cost of larger file size.'
        Caption = '&Disable PETrim'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
    end
    object pagGZ: TTabSheet
      Caption = '&GZ'
      ImageIndex = 6
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object chkGZCopyMetadata: TCheckBox
        Left = 7
        Top = 22
        Width = 281
        Height = 17
        Hint = 'Copy file metadata. Else strip all unneded information.'
        Caption = '&Copy metadata'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
    end
    object pagHTML: TTabSheet
      Caption = '&HTML'
      ImageIndex = 6
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object chkHTMLEnableTidy: TCheckBox
        Left = 7
        Top = 22
        Width = 281
        Height = 17
        Hint = 
          'Enable Tidy. Results in smaller files, but can happen they are n' +
          'ot editable anymore. Note that this applies to both SVG and HTML' +
          ' file types'
        Caption = '&Enable Tidy'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
    end
    object pagJPEG: TTabSheet
      Caption = '&JPEG'
      ImageIndex = 5
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object chkJPEGCopyMetadata: TCheckBox
        Left = 7
        Top = 22
        Width = 281
        Height = 17
        Hint = 'Copy file metadata. Else strip all unneded information.'
        Caption = '&Copy metadata'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
      object chkJPEGUseArithmeticEncoding: TCheckBox
        Left = 7
        Top = 41
        Width = 281
        Height = 17
        Hint = 
          'Arithmetic encoding gives additional saving reductions, but is i' +
          'ncompatible with most programs.'
        Caption = '&Use arithmetic encoding'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
      end
    end
    object pagJS: TTabSheet
      Caption = '&JS'
      ImageIndex = 6
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object chkJSEnableJSMin: TCheckBox
        Left = 7
        Top = 22
        Width = 281
        Height = 17
        Hint = 
          'Enable jsmin. Results in smaller files, but can happen they are ' +
          'not editable anymore.'
        Caption = '&Enable JSMin'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
    end
    object pagLUA: TTabSheet
      Caption = '&LUA'
      ImageIndex = 12
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object chkLUAEnableLeanify: TCheckBox
        Left = 7
        Top = 22
        Width = 281
        Height = 17
        Hint = 
          'Enable Leanify. Results in smaller files, but can happen they ar' +
          'e not editable anymore.'
        Caption = '&Enable Leanify'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
    end
    object pagMP3: TTabSheet
      Caption = '&MP3'
      ImageIndex = 8
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object chkMP3CopyMetadata: TCheckBox
        Left = 7
        Top = 22
        Width = 281
        Height = 17
        Hint = 'Copy file metadata. Else strip all unneded information.'
        Caption = '&Copy metadata'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
    end
    object pagPDF: TTabSheet
      Caption = '&PDF'
      ImageIndex = 7
      object lblPDFProfile: TLabel
        Left = 7
        Top = 22
        Width = 155
        Height = 13
        AutoSize = False
        Caption = '&Profile'
        FocusControl = cboPDFProfile
        ParentShowHint = False
        ShowHint = False
      end
      object lblPDFCustomDPI: TLabel
        Left = 7
        Top = 49
        Width = 155
        Height = 13
        AutoSize = False
        Caption = '&Custom DPI'
        FocusControl = spnPDFCustomDPI
        ParentShowHint = False
        ShowHint = False
      end
      object cboPDFProfile: TComboBox
        Left = 168
        Top = 22
        Width = 145
        Height = 21
        Hint = 'Compression profile, from less size, to best quality.'
        Style = csDropDownList
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        OnChange = cboPDFProfileChange
        Items.Strings = (
          'None: No downsampling'
          'Screen: 72 dpi'
          'Ebook: 150 dpi'
          'Printer: 300 dpi'
          'Prepress: 300 dpi and color preserve'
          'Custom')
      end
      object spnPDFCustomDPI: TSpinEdit
        Left = 168
        Top = 49
        Width = 121
        Height = 22
        Hint = 
          'When custom profile is choosen, it allows you to specify a custo' +
          'm DPI for downsampling images'
        Increment = 50
        MaxValue = 3000
        MinValue = 50
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        Value = 50
      end
    end
    object pagPNG: TTabSheet
      Caption = '&PNG'
      ImageIndex = 10
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object chkPNGCopyMetadata: TCheckBox
        Left = 7
        Top = 22
        Width = 281
        Height = 17
        Hint = 'Copy file metadata. Else strip all unneded information.'
        Caption = '&Copy metadata'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
      object chkPNGAllowLossy: TCheckBox
        Left = 7
        Top = 41
        Width = 281
        Height = 17
        Hint = 
          'Allowing lossy optimizations will get higher files reduction at ' +
          'the cost of some quality loss, even if visually unnoticeable or ' +
          'not'
        Caption = '&Allow lossy optimizations'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
      end
    end
    object pagXML: TTabSheet
      Caption = '&XML'
      ImageIndex = 11
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object chkXMLEnableLeanify: TCheckBox
        Left = 7
        Top = 22
        Width = 281
        Height = 17
        Hint = 
          'Enable Leanify. Results in smaller files, but can happen they ar' +
          'e not editable anymore.'
        Caption = '&Enable Leanify'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
    end
    object pagZIP: TTabSheet
      Caption = '&ZIP'
      ImageIndex = 9
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object chkZIPCopyMetadata: TCheckBox
        Left = 7
        Top = 22
        Width = 281
        Height = 17
        Hint = 'Copy file metadata. Else strip all unneded information.'
        Caption = '&Copy metadata'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
      object chkZIPRecurse: TCheckBox
        Left = 7
        Top = 41
        Width = 281
        Height = 17
        Hint = 'Enable optimization inside archives (recursive optimization).'
        Caption = '&Recurse'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
      end
    end
  end
  object butRestoreDefaults: TButton
    Left = 8
    Top = 374
    Width = 95
    Height = 25
    Hint = 'Restore all options to its factory settings values.'
    Caption = '&Restore defaults'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 3
    OnClick = butRestoreDefaultsClick
  end
  object butOK: TButton
    Left = 400
    Top = 374
    Width = 75
    Height = 25
    Hint = 'Accept and apply all changes made to options.'
    Caption = '&OK'
    Default = True
    ParentShowHint = False
    ShowHint = True
    TabOrder = 2
    OnClick = butOKClick
  end
  object butCancel: TButton
    Left = 481
    Top = 374
    Width = 75
    Height = 25
    Hint = 'Discard any changes made to options.'
    Cancel = True
    Caption = '&Cancel'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 1
    OnClick = butCancelClick
  end
end
