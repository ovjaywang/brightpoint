// MFCkxlOpenCVView.cpp : implementation of the CMFCkxlOpenCVView class
//

#include "stdafx.h"
#include "MFCkxlOpenCV.h"
#include "MFCkxlOpenCVDoc.h"
#include "CvvImage.h"
#include "MFCkxlOpenCVView.h"
#include "Dlg.h"
//#include "Globle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
using namespace cv;
/////////////////////////////////////////////////////////////////////////////
// CMFCkxlOpenCVView

IMPLEMENT_DYNCREATE(CMFCkxlOpenCVView, CView)

BEGIN_MESSAGE_MAP(CMFCkxlOpenCVView, CView)
	//{{AFX_MSG_MAP(CMFCkxlOpenCVView)
	ON_COMMAND(ID_IMAGE_LARGER, OnImageLarger)
	ON_COMMAND(ID_IMAGE_SMALLER, OnImageSmaller)
	ON_COMMAND(ID_IMAGE_FLIPH, OnImageFliph)
	ON_COMMAND(ID_IMAGE_FLIPV, OnImageFlipv)
	ON_COMMAND(ID_MENU_ROTATE_C, OnMenuRotateC)
	ON_COMMAND(ID_MENU_ROTATE_R, OnMenuRotateR)
	ON_COMMAND(ID_IMAGE_LSER, OnImageLser)
	ON_COMMAND(ID_FILE_UNDO, OnFileUndo)
	ON_COMMAND(ID_FILE_RELOAD, OnFileReload)

	ON_COMMAND(ID_FindBrightPoint, OnFindBrightPoint)//�Զ��庯��
	ON_COMMAND(ID_CUT_COUNT, OnCutCount)
	ON_COMMAND(ID_INFO_GRAY, OnInfoGray)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)

	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	
	
	ON_COMMAND(ID_32805, &CMFCkxlOpenCVView::On32805)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCkxlOpenCVView construction/destruction

CMFCkxlOpenCVView::CMFCkxlOpenCVView()
{
	// TODO: add construction code here

}

CMFCkxlOpenCVView::~CMFCkxlOpenCVView()
{
}

BOOL CMFCkxlOpenCVView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMFCkxlOpenCVView drawing
	
	
							//--------------------Draw-----------------------//
void CMFCkxlOpenCVView::OnDraw(CDC* pDC)
{
	CMFCkxlOpenCVDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
 	if(pDoc->m_pImage != NULL)
 	{
 		CvvImage img;	
// 		if (pDoc->m_pImage->nChannels==1)
// 		{
// 			IplImage* img1=cvCreateImage(cvGetSize(pDoc->m_pImage),IPL_DEPTH_8U,3);
// 			cvCvtColor(pDoc->m_pImage,img1,CV_GRAY2RGB);	
// 			img.CopyOf(img1);
// 		} 
// 		else
// 		{
			img.CopyOf(pDoc->m_pImage);		
//		}
				//ȡ��ͼ��
		
		int x = 0, y = 0;
		CRect rect;
		GetClientRect(&rect);
		
		if(img.Width() < rect.Width())				//��ͼ��ڷ�����ͼ����
		{
			x = rect.Width() - img.Width();
			x = x / 2;
		}
		
		if(img.Height() < rect.Height())
		{
			y = rect.Height() - img.Height();
			y = y / 2;
		}
		//��ʾ
		img.Show(pDC->m_hDC, x, y, pDoc->m_pImage->width, pDoc->m_pImage->height, m_iImgX, m_iImgY);
	}
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMFCkxlOpenCVView printing															
BOOL CMFCkxlOpenCVView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCkxlOpenCVView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCkxlOpenCVView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMFCkxlOpenCVView diagnostics

#ifdef _DEBUG
void CMFCkxlOpenCVView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCkxlOpenCVView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

				//----------------�õ�DOC����ļ�------------------//
CMFCkxlOpenCVDoc* CMFCkxlOpenCVView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCkxlOpenCVDoc)));
	return (CMFCkxlOpenCVDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMFCkxlOpenCVView message handlers


                         //-------------------------�Ŵ�---------------------//
void CMFCkxlOpenCVView::OnImageLarger() 
{
	// TODO: Add your command handler code here
	pImage = GetDocument()->m_pImage;
	if(pImage != NULL)
	{
		GetDocument()->zoom(1.5);//, m_pImageSrc, &m_pImage)
		Invalidate();
	}
	else MessageBox("û��ͼƬ����������ͼƬ!") ;
}


						 //-------------------------��С---------------------//
void CMFCkxlOpenCVView::OnImageSmaller() 
{
	// TODO: Add your command handler code here
	pImage=GetDocument()->m_pImage;
	if (pImage!=NULL)
	{
		GetDocument()->zoom(0.5);
		Invalidate();
	}
	else MessageBox("û��ͼƬ����������ͼƬ!") ;
}

						 //-------------------------������ת---------------------//				
void CMFCkxlOpenCVView::OnImageFliph() 
{
	pImage = GetDocument()->m_pImage;
	if(pImage != NULL)
	{
		GetDocument()->Flip(1);
	//	m_bIsChange = TRUE;
		Invalidate();
	}
	else MessageBox("û��ͼƬ����������ͼƬ!") ;
}

						 //-------------------------������ת---------------------//
void CMFCkxlOpenCVView::OnImageFlipv() 
{
	// TODO: Add your command handler code here
	pImage=GetDocument()->m_pImage;
	if (pImage!=NULL)
	{
		GetDocument()->Flip(0);
		Invalidate();
	}
	else MessageBox("û��ͼƬ����������ͼƬ!") ;
}

						 //-------------------------����ת��---------------------//
void CMFCkxlOpenCVView::OnMenuRotateC() 
{
	// TODO: Add your command handler code here
	pImage=GetDocument()->m_pImage;
	if (pImage!=NULL)
	{
		GetDocument()->Rotate(90);
		Invalidate();
	}
	else MessageBox("û��ͼƬ����������ͼƬ!");	
}

						 //-------------------------����ת��---------------------//
void CMFCkxlOpenCVView::OnMenuRotateR() 
{
	// TODO: Add your command handler code here
	pImage=GetDocument()->m_pImage;
	if (pImage!=NULL)
	{
		GetDocument()->Rotate(-90);
		Invalidate();
	}
	else MessageBox("û��ͼƬ����������ͼƬ!");	
}

						 //-------------------------�Զ������---------------------//
void CMFCkxlOpenCVView::OnImageLser() 
{
	CDlg cdlg;
	// TODO: Add your command handler code here
	pImage=GetDocument()->m_pImage;
	if (pImage!=NULL)
	{	if(cdlg.DoModal()!=IDOK)
		return;
	
		GetDocument()->zoom(cdlg.abc);	
		Invalidate();
	}
	else MessageBox("û��ͼƬ����������ͼƬ!");
}

						 //-------------------------����---------------------//
void CMFCkxlOpenCVView::OnFileUndo() 
{
	// TODO: Add your command handler code here
	if(! GetDocument()->Restore())
	{
		MessageBox("�޷�������");
	}
	Invalidate();
}

						 //-------------------------����---------------------//
void CMFCkxlOpenCVView::OnFileReload() 
{
	// TODO: Add your command handler code here
	GetDocument()->Reload();
	Invalidate();
}




					//----------------��ֵ�ָ�--------------------//
void CMFCkxlOpenCVView::OnCutCount() 
{
	// TODO: Add your command handler code here
	pImage = GetDocument()->m_pImage;
	if(pImage != NULL)
	{
		GetDocument()->CountCut();
		Invalidate();
	}
	else MessageBox("û��ͼƬ����������ͼƬ!") ;
}


					//----------------�ҶȻ�--------------------//
void CMFCkxlOpenCVView::OnInfoGray() 
{
	// TODO: Add your command handler code here
	pImage=GetDocument()->m_pImage;
	if (pImage!=NULL)
	{
		GetDocument()->Gray();
		Invalidate();
	}
	else MessageBox("û��ͼƬ����������ͼƬ!") ;
}


void CMFCkxlOpenCVView::OnFileSaveAs() 
{
	// TODO: Add your command handler code here
	CFileDialog save(FALSE, NULL, GetDocument()->image_s);
	if( save.DoModal() == IDOK)
	{
		CString path;
		path = save.GetPathName();
		GetDocument()->SaveImage(path);	
	}
}


void CMFCkxlOpenCVView::OnFindBrightPoint()
{
	pImage = GetDocument()->m_pImage;
	if (pImage != NULL)
	{
		GetDocument()->fit_ellipse();
		Invalidate();
	}
	else MessageBox("û��ͼƬ����������ͼƬ!");
}


void CMFCkxlOpenCVView::On32805()
{
	pImage = GetDocument()->m_pImage;
	if (pImage != NULL)
	{
		GetDocument()->zoom(0.35);
		Invalidate();
	}
	else MessageBox("û��ͼƬ����������ͼƬ!");
}
