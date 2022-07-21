// ModifyDlg.cpp: 实现文件
//

#include "pch.h"
#include "AddressBook.h"
#include "ModifyDlg.h"
#include "afxdialogex.h"

#include<string>

#include"AddressBookDlg.h"
#include"Function.h"

extern bool hasModified;
extern int staticIndex;

// ModifyDlg 对话框

IMPLEMENT_DYNAMIC(ModifyDlg, CDialogEx)

ModifyDlg::ModifyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(MODIFY_DIALOG, pParent)
{

}

ModifyDlg::~ModifyDlg()
{
}

void ModifyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModifyDlg, CDialogEx)
	ON_BN_CLICKED(MODIFY_BUTTON2, &ModifyDlg::OnBnClickedButtonModify2)
	ON_BN_CLICKED(IDCANCEL, &ModifyDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// ModifyDlg 消息处理程序


//修改按钮
void ModifyDlg::OnBnClickedButtonModify2()
{
	// TODO: 在此添加控件通知处理程序代码

	const int lengthOfModifyArray = 7;
	CString CmodifyArray[lengthOfModifyArray];
	int modifyEditArray[7] = { 0, MODIFY_EDIT1, MODIFY_EDIT2, MODIFY_EDIT3, MODIFY_EDIT4, MODIFY_EDIT5, MODIFY_EDIT6 };
	USES_CONVERSION;
	std::string modifyArray[7];
	for (int i = 1; i < lengthOfModifyArray; i++) {
		GetDlgItem(modifyEditArray[i])->GetWindowText(CmodifyArray[i]);
		modifyArray[i] = W2A(CmodifyArray[i]);
	}
	Function f;
	staticIndex = f.modify(staticIndex, 5, modifyArray[1], modifyArray[2], modifyArray[3], modifyArray[4], modifyArray[5], modifyArray[6]);
 	hasModified = true;
	MessageBox(L"修改成功!\n", L"修改", MB_OK | MB_ICONEXCLAMATION);
	CDialogEx::OnOK();

}

//重载
void ModifyDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码

	hasModified = false;

	CDialogEx::OnCancel();
}


BOOL ModifyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	const int lengthOfModifyArray = 7;
	CString CmodifyArray[lengthOfModifyArray];
	int modifyEditArray[7] = { 0, MODIFY_EDIT1, MODIFY_EDIT2, MODIFY_EDIT3, MODIFY_EDIT4, MODIFY_EDIT5, MODIFY_EDIT6 };
	std::string modifyArray[7];
	Function f;
	for (int i = 1; i < lengthOfModifyArray; i++) {
		CmodifyArray[i] = f.display(staticIndex, i).c_str();
		GetDlgItem(modifyEditArray[i])->SetWindowText(CmodifyArray[i]);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
