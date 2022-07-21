#pragma once


// ModifyDlg 对话框

class ModifyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ModifyDlg)

public:
	ModifyDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ModifyDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = MODIFY_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonModify2();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};
