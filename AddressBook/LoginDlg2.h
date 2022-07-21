#pragma once


// LoginDlg2 对话框

class LoginDlg2 : public CDialogEx
{
	DECLARE_DYNAMIC(LoginDlg2)

public:
	LoginDlg2(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~LoginDlg2();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = LOFIN_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLogin2();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	CStatic loginPicture2;
	afx_msg void OnPaint();
	CStatic tipsStatic6;
	CEdit loginEdit;
	CButton loginButton2;
	CButton loginCheck2;
	afx_msg void OnBnClickedButtonForget();
};
