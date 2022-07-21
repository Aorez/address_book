#pragma once


// ResetDlg 对话框

class ResetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ResetDlg)

public:
	ResetDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ResetDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = RESET_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CStatic resetStatic;
	CEdit resetEdit;
	CButton resetButton;
	afx_msg void OnBnClickedButton();
	bool resetCancal;
	virtual void OnCancel();
};
