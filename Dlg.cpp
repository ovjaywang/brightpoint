// Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCkxlOpenCV.h"
#include "Dlg.h"

#include "MFCkxlOpenCVDoc.h"
#include "MFCkxlOpenCVView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg dialog


CDlg::CDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg)
		// NOTE: the ClassWizard will add member initialization here
	abc=0.0;
	//}}AFX_DATA_INIT
}


void CDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Text(pDX, IDC_EDIT1, abc);
	DDV_MinMaxDouble(pDX, abc, 1.e-009, 1000000.);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg, CDialog)
	//{{AFX_MSG_MAP(CDlg)
	//}}AFX_MSG_MAP
//	ON_EN_CHANGE(IDC_EDIT1, &CDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg message handlers

void CDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	CDialog::OnOK();
}
