; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CStatisticsDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ace400statistics.h"
LastPage=0

ClassCount=5
Class1=CAboutDlg
Class2=CACE400MainDlg
Class3=CACE400StatisticsApp
Class4=CConfigDialog
Class5=CStatisticsDialog

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDD_MAIN_DIALOG
Resource3=IDD_STATISTICS_DIALOG
Resource4=IDD_CONFIG_DIALOG

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=ACE400MainDlg.cpp
ImplementationFile=ACE400MainDlg.cpp

[CLS:CACE400MainDlg]
Type=0
BaseClass=CDialog
HeaderFile=ACE400MainDlg.h
ImplementationFile=ACE400MainDlg.cpp

[CLS:CACE400StatisticsApp]
Type=0
BaseClass=CWinApp
HeaderFile=ACE400Statistics.h
ImplementationFile=ACE400Statistics.cpp

[CLS:CConfigDialog]
Type=0
BaseClass=CDialog
HeaderFile=ConfigDialog.h
ImplementationFile=ConfigDialog.cpp

[CLS:CStatisticsDialog]
Type=0
BaseClass=CDialog
HeaderFile=StatisticsDialog.h
ImplementationFile=StatisticsDialog.cpp
LastObject=IDC_BUTTON_INSERT
Filter=D
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MAIN_DIALOG]
Type=1
Class=CACE400MainDlg
ControlCount=3
Control1=IDC_BUTTON_STATISTICS,button,1342242816
Control2=IDC_BUTTON_CONFIG,button,1342242816
Control3=IDOK,button,1342242816

[DLG:IDD_CONFIG_DIALOG]
Type=1
Class=CConfigDialog
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_STATISTICS_DIALOG]
Type=1
Class=CStatisticsDialog
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDC_GRID,MFCGridCtrl,1342242816
Control3=IDC_TREE,SysTreeView32,1350631479
Control4=IDC_EDIT_SELECT,edit,1350633600

