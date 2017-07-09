// MFCkxlOpenCV.h : main header file for the MFCKXLOPENCV application
//

#if !defined(AFX_MFCKXLOPENCV_H__9C21E43F_5FA7_4BE5_9CA4_441A210AFCD7__INCLUDED_)
#define AFX_MFCKXLOPENCV_H__9C21E43F_5FA7_4BE5_9CA4_441A210AFCD7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMFCkxlOpenCVApp:
// See MFCkxlOpenCV.cpp for the implementation of this class
//

class CMFCkxlOpenCVApp : public CWinApp
{
public:
	CMFCkxlOpenCVApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCkxlOpenCVApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMFCkxlOpenCVApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCKXLOPENCV_H__9C21E43F_5FA7_4BE5_9CA4_441A210AFCD7__INCLUDED_)
