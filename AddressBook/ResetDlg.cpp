// ResetDlg.cpp: 实现文件
//

#include "pch.h"
#include "AddressBook.h"
#include "ResetDlg.h"
#include "afxdialogex.h"

#include<string>

#include"Logindlg.h"

extern CFont tipsFont;
extern bool loginCancal;
extern bool isReseting;

extern int securityQuestion;
extern std::string answerOfsecurityQuestion;

// ResetDlg 对话框

IMPLEMENT_DYNAMIC(ResetDlg, CDialogEx)

ResetDlg::ResetDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(RESET_DIALOG, pParent)
{

}

ResetDlg::~ResetDlg()
{
}

void ResetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, RESET_STATIC, resetStatic);
	DDX_Control(pDX, RESET_EDIT, resetEdit);
	DDX_Control(pDX, RESET_BUTTON, resetButton);
}


BEGIN_MESSAGE_MAP(ResetDlg, CDialogEx)
	ON_BN_CLICKED(RESET_BUTTON, &ResetDlg::OnBnClickedButton)
END_MESSAGE_MAP()


// ResetDlg 消息处理程序


BOOL ResetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	resetStatic.SetFont(&tipsFont);
	resetEdit.SetFont(&tipsFont);
	resetButton.SetFont(&tipsFont);

	std::string stringSecurityQuestion;
	switch (securityQuestion) {
	case 0:stringSecurityQuestion = "您的密保问题是：父亲的姓氏是？"; break;
	case 1:stringSecurityQuestion = "您的密保问题是：母亲的姓氏是？"; break;
	case 2:stringSecurityQuestion = "您的密保问题是：我的生日是？"; break;
	}
	CString CsecurityQuestion;
	CsecurityQuestion = stringSecurityQuestion.c_str();
	GetDlgItem(RESET_STATIC)->SetWindowText(CsecurityQuestion);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void ResetDlg::OnBnClickedButton()
{
	// TODO: 在此添加控件通知处理程序代码

	CString CanswerOfsecurityQuestion;
	GetDlgItem(RESET_EDIT)->GetWindowText(CanswerOfsecurityQuestion);
	USES_CONVERSION;
	std::string stringAnswerOfsecurityQuestion(W2A(CanswerOfsecurityQuestion));
	if (stringAnswerOfsecurityQuestion == answerOfsecurityQuestion) {
		
		//这个if语句和isReseting变量用于重置账户操作
		if (isReseting) {
			MessageBox(L"正在重置……", L"请等待");
			OnOK();
		}
		else {
			Logindlg ld;
			ld.DoModal();

			if (loginCancal) {}
			else {

				CDialogEx::OnOK();
			}
		}
		
	}
	else MessageBox(L"答案错误！", L"输入错误", MB_ICONEXCLAMATION);

}


void ResetDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	resetCancal = true;
	isReseting = false;

	CDialogEx::OnCancel();
}
