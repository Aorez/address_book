#pragma once


// DetatilsDlg 对话框

class DetatilsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DetatilsDlg)

public:
	DetatilsDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DetatilsDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = DETAILS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl detailsList;
	CStatic detailsPicture;
	afx_msg void OnPaint();
	afx_msg void On32779DetailsMenu();
	afx_msg void OnNMRClickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void On32790Copy();
	afx_msg void On32791CopyAll();
};
