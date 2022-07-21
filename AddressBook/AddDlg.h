#pragma once


// AddDlg 对话框

class AddDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddDlg)

public:
	AddDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AddDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = ADD_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAdd();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	CListCtrl addList;
	CEdit addEdit;
	afx_msg void OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnKillfocusEdit();
	int m_Row;
	int m_Col;
	CButton addButton2;
	CButton addCancel;
	int numOfFace2;
	CButton addButton3;
	CStatic addPicture;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnPaint();
	void OnBnClickedCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
