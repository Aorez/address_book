
// AddressBookDlg.h: 头文件
//

#pragma once

#include"RoundButton.h"

// CAddressBookDlg 对话框
class CAddressBookDlg : public CDialogEx
{
// 构造
public:
	CAddressBookDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDRESSBOOK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSearch();
	CListCtrl homeList;
	afx_msg void OnBnClickedButtonModify();
	afx_msg void OnBnClickedButtonDisplay();
	afx_msg void OnBnClickedButtonDetach();
	virtual void OnCancel();
	afx_msg void OnNMRClickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void On32771Copy();
	afx_msg void On32772CopyLine();
	afx_msg void On32773Modify();
	afx_msg void On32774Detach();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonClear();
	void ShowOneOnList(int indexToShow);
	afx_msg void OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CBitmapButton searchButton;
	CFont myFont;
	CFont addButtonFont;
	CStatic myStatic;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CEdit searchEdit;
	CButton modifyButton;
	CRoundButton addButton;
	CStatic homePicture;
	CToolTipCtrl m_stat;
	afx_msg void On32781Clear();
	afx_msg void On32784Reset();
	afx_msg void On32785Reset();
	afx_msg void On32786ColorChange();
	afx_msg void On32787DefaultColor();
	afx_msg void OnPaletteIsChanging(CWnd* pRealizeWnd);
	afx_msg void On32789TopStar();
	afx_msg void On32796ModifyMenu();
	afx_msg void On32797DetachMenu();
	afx_msg void On32798Revoke();
	afx_msg void On32795Revoke();
	afx_msg void On32799About();
	//virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	CRect m_rect;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void ChangeSize(UINT nID, int cx, int cy);
	afx_msg void On32800Add();
	afx_msg void On32801Display();
	afx_msg void On32802();
};
