#pragma once


// Logindlg 对话框

class Logindlg : public CDialogEx
{
	DECLARE_DYNAMIC(Logindlg)

public:
	Logindlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Logindlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = LOGIN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnBnClickedCancel();
	CStatic loginPicture;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton2();
	CFont myFont;
	CStatic tipsStatic4;
	CStatic tipsStatic1;
	CStatic tipsStatic2;
	CStatic tipsStatic3;
	CEdit setPasswordEdit;
	CEdit setPasswordEdit2;
	CComboBox loginCombo;
	CStatic tipsStatic5;
	CButton loginButton;
	CButton faceSelectButton;
	CButton loginCheck;
	CEdit setPasswordEdit3;
	afx_msg void OnPaint();
	CRect m_rect;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void ChangeSize(UINT nID, int cx, int cy);
};
