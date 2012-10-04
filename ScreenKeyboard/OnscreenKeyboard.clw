; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=COnscreenKeyboardDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "OnscreenKeyboard.h"

ClassCount=3
Class1=COnscreenKeyboardApp
Class2=COnscreenKeyboardDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_ONSCREENKEYBOARD_DIALOG
Resource4=IDR_TRAY_MENU

[CLS:COnscreenKeyboardApp]
Type=0
HeaderFile=OnscreenKeyboard.h
ImplementationFile=OnscreenKeyboard.cpp
Filter=N

[CLS:COnscreenKeyboardDlg]
Type=0
HeaderFile=OnscreenKeyboardDlg.h
ImplementationFile=OnscreenKeyboardDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=COnscreenKeyboardDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=OnscreenKeyboardDlg.h
ImplementationFile=OnscreenKeyboardDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_ONSCREENKEYBOARD_DIALOG]
Type=1
Class=COnscreenKeyboardDlg
ControlCount=0

[MNU:IDR_TRAY_MENU]
Type=1
Class=COnscreenKeyboardDlg
Command1=IDM_HIDE_KEYBOARD
Command2=IDM_SHOW_KEYBOARD
Command3=IDM_EXIT
CommandCount=3

