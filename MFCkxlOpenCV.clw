; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMFCkxlOpenCVView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MFCkxlOpenCV.h"
LastPage=0

ClassCount=6
Class1=CMFCkxlOpenCVApp
Class2=CMFCkxlOpenCVDoc
Class3=CMFCkxlOpenCVView
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX
Class6=CDlg
Resource3=IDD_DIALOG1

[CLS:CMFCkxlOpenCVApp]
Type=0
HeaderFile=MFCkxlOpenCV.h
ImplementationFile=MFCkxlOpenCV.cpp
Filter=N

[CLS:CMFCkxlOpenCVDoc]
Type=0
HeaderFile=MFCkxlOpenCVDoc.h
ImplementationFile=MFCkxlOpenCVDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CMFCkxlOpenCVDoc

[CLS:CMFCkxlOpenCVView]
Type=0
HeaderFile=MFCkxlOpenCVView.h
ImplementationFile=MFCkxlOpenCVView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=ID_ADD_LAPLACE


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_ADD_LAPLACE




[CLS:CAboutDlg]
Type=0
HeaderFile=MFCkxlOpenCV.cpp
ImplementationFile=MFCkxlOpenCV.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
Command2=ID_FILE_SAVE
Command3=ID_FILE_SAVE_AS
Command4=ID_FILE_RELOAD
Command5=ID_FILE_UNDO
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_IMAGE_LARGER
Command9=ID_IMAGE_SMALLER
Command10=ID_IMAGE_FLIPH
Command11=ID_IMAGE_FLIPV
Command12=ID_MENU_ROTATE_C
Command13=ID_MENU_ROTATE_R
Command14=ID_IMAGE_LSER
Command15=ID_INFO_GRAY
Command16=ID_INFO_HISTOGRAM
Command17=ID_INFO_DFT
Command18=ID_ADD_HISTOGRAM
Command19=ID_ADD_LAPLACE
Command20=ID_ADD_GAUSS
Command21=ID_ADD_HOUGH
Command22=ID_RESUME_SOLTNOISE
Command23=ID_RESUME_GAUSSNOISE
Command24=ID_RESUME_MID
Command25=ID_CUT_SOBEL
Command26=ID_CUT_GAUSSIA
Command27=ID_CUT_CANDY
Command28=ID_CUT_COUNT
Command29=ID_FACE
Command30=ID_APP_ABOUT
CommandCount=30

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDD_DIALOG1]
Type=1
Class=CDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552

[CLS:CDlg]
Type=0
HeaderFile=Dlg.h
ImplementationFile=Dlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

