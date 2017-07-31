#pragma once


// CPointDialog 对话框

class CPointDialog : public CDialog
{
	DECLARE_DYNAMIC(CPointDialog)

public:
	CPointDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPointDialog();

// 对话框数据
	enum { IDD = IDD_PTSBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit2();
};
