; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPlayTicTacToe
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Tic Tac Toe.h"

ClassCount=4
Class1=CTicTacToeApp
Class2=CTicTacToeDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_TICTACTOE_DIALOG
Class4=CPlayTicTacToe
Resource4=IDD_PLAY

[CLS:CTicTacToeApp]
Type=0
HeaderFile=Tic Tac Toe.h
ImplementationFile=Tic Tac Toe.cpp
Filter=N

[CLS:CTicTacToeDlg]
Type=0
HeaderFile=Tic Tac ToeDlg.h
ImplementationFile=Tic Tac ToeDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CTicTacToeDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=Tic Tac ToeDlg.h
ImplementationFile=Tic Tac ToeDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_TICTACTOE_DIALOG]
Type=1
Class=CTicTacToeDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDC_CVP,button,1342242816
Control3=IDC_PVP,button,1342242816
Control4=IDC_HELP2,button,1342242817

[DLG:IDD_PLAY]
Type=1
Class=CPlayTicTacToe
ControlCount=12
Control1=IDOK,button,1342242816
Control2=IDCANCEL,button,1342242816
Control3=IDC_HELP1,button,1342242816
Control4=IDC_STATIC,button,1342177287
Control5=IDC_P1,static,1342308352
Control6=IDC_P2,static,1342308352
Control7=IDC_PD,static,1342308352
Control8=IDC_EDITP1,edit,1484849280
Control9=IDC_EDITP2,edit,1484849280
Control10=IDC_EDITD,edit,1484849280
Control11=IDC_PLAY,button,1342242817
Control12=IDC_TURN,edit,1476460672

[CLS:CPlayTicTacToe]
Type=0
HeaderFile=PlayTicTacToe.h
ImplementationFile=PlayTicTacToe.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CPlayTicTacToe

