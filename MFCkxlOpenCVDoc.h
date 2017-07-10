// MFCkxlOpenCVDoc.h : interface of the CMFCkxlOpenCVDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFCKXLOPENCVDOC_H__0A9FBD54_A502_49CE_8227_F2D8AF1942D4__INCLUDED_)
#define AFX_MFCKXLOPENCVDOC_H__0A9FBD54_A502_49CE_8227_F2D8AF1942D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include<cxcore.h>
#include<highgui.h>
#include<cv.h>
#include "dbscan.h"
#include "MFCkxlOpenCV.h"

class CMFCkxlOpenCVDoc : public CDocument
{
protected: // create from serialization only
	CMFCkxlOpenCVDoc();
	DECLARE_DYNCREATE(CMFCkxlOpenCVDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCkxlOpenCVDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	CString image_s;
	bool SaveImage(CString path);
	bool LaplaceAdd(int me);
	bool CountCut();
	bool CandyCut();
	bool AddHough();
	bool HistogramAve();
	bool GaussLow();
	bool Midd();
	bool InfoDft();
	bool Gray();
	bool Reload();
	IplImage* m_pImageFirst;
	void Backup();
	int pIm;
	IplImage* pImage[20];
	bool Restore();
	bool Rotate(int);
	bool fit_ellipse();//Õ÷‘≤ƒ‚∫œ
	bool Flip(int flip_mode);
	bool zoom(double ratio);
	double getFangcha(double aa[]);
	Point2D getCenterPoint(vector<Point2D> vt);
	Point2D center1, center2, center3, center4, center5, center6, center7;
	vector<Point2D> getThreeData(int mode, vector<Point2D> vt, int xy);
	int getKeyCtrlNum(vector<Point2D> vt, int mode, int xy);
	void getAllCtrlPointCoor(vector<vector<Point2D>> vt,vector<Point2D> centerPts);
	int LastOccurence(char *szStr, char *szSub);
//	CMFCkxlOpenCVView myview;
	IplImage* m_pImage;
	IplImage* m_pCont;
//	IplImage* m_pImageGray;
	IplImage* m_pImageSrc;
	virtual ~CMFCkxlOpenCVDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMFCkxlOpenCVDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCKXLOPENCVDOC_H__0A9FBD54_A502_49CE_8227_F2D8AF1942D4__INCLUDED_)
