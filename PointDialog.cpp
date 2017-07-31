// PointDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCkxlOpenCV.h"
#include "PointDialog.h"
#include "afxdialogex.h"


// CPointDialog 对话框

IMPLEMENT_DYNAMIC(CPointDialog, CDialog)

CPointDialog::CPointDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPointDialog::IDD, pParent)
{

}

CPointDialog::~CPointDialog()
{
}

void CPointDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPointDialog, CDialog)
END_MESSAGE_MAP()


// CPointDialog 消息处理程序
