#pragma once


// CPointDialog �Ի���

class CPointDialog : public CDialog
{
	DECLARE_DYNAMIC(CPointDialog)

public:
	CPointDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPointDialog();

// �Ի�������
	enum { IDD = IDD_PTSBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit2();
};
