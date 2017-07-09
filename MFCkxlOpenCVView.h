// MFCkxlOpenCVView.h : interface of the CMFCkxlOpenCVView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFCKXLOPENCVVIEW_H__7715BA64_AC06_41D1_A3F7_20EA46C0C573__INCLUDED_)
#define AFX_MFCKXLOPENCVVIEW_H__7715BA64_AC06_41D1_A3F7_20EA46C0C573__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cv.h"
#include "highgui.h"

class CMFCkxlOpenCVView : public CView
{
protected: // create from serialization only
	CMFCkxlOpenCVView();
	DECLARE_DYNCREATE(CMFCkxlOpenCVView)

// Attributes
public:
	CMFCkxlOpenCVDoc* GetDocument();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCkxlOpenCVView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	void OnFileOpen();
	//}}AFX_VIRTUAL

// Implementation
public:
	IplImage* _pImage;
	int m_iImgY;
	int m_iImgX;
	IplImage* pImage;
	virtual ~CMFCkxlOpenCVView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMFCkxlOpenCVView)
	afx_msg void OnImageLarger();
	afx_msg void OnImageSmaller();
	afx_msg void OnImageFliph();
	afx_msg void OnImageFlipv();
	afx_msg void OnMenuRotateC();
	afx_msg void OnMenuRotateR();
	afx_msg void OnImageLser();
	afx_msg void OnFileUndo();
	afx_msg void OnFileReload();
	afx_msg void OnInfoHistogram();
	afx_msg void OnInfoDft();
	afx_msg void OnAddLaplace();
	afx_msg void OnCutSobel();
	afx_msg void OnCutGaussia();

	afx_msg void OnCutCandy();
	afx_msg void OnAddHistogram();
	afx_msg void OnAddGauss();
	afx_msg void OnResumeGaussnoise();
	afx_msg void OnResumeMid();
	afx_msg void OnResumeSoltnoise();
	afx_msg void OnInfoGray();
	afx_msg void OnAddHough();
	afx_msg void OnFileSaveAs();
	afx_msg void OnFace();
	afx_msg void OnCutCount();
	afx_msg void OnFindBrightPoint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void On32805();
};

#ifndef _DEBUG  // debug version in MFCkxlOpenCVView.cpp
inline CMFCkxlOpenCVDoc* CMFCkxlOpenCVView::GetDocument()
   { return (CMFCkxlOpenCVDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCKXLOPENCVVIEW_H__7715BA64_AC06_41D1_A3F7_20EA46C0C573__INCLUDED_)
