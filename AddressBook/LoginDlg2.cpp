// LoginDlg2.cpp: 实现文件
//

#include "pch.h"
#include "AddressBook.h"
#include "LoginDlg2.h"
#include "afxdialogex.h"

#include<string>

#include"ResetDlg.h"

extern CFont tipsFont;
extern HICON dialogIcon;
extern bool loginCancal;

extern int numberOfFace;
extern std::string password;
extern int rememberPassword;

// LoginDlg2 对话框

IMPLEMENT_DYNAMIC(LoginDlg2, CDialogEx)

LoginDlg2::LoginDlg2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(LOFIN_DIALOG2, pParent)
{

}

LoginDlg2::~LoginDlg2()
{
}

void LoginDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, LOGIN_PICTURE2, loginPicture2);
	DDX_Control(pDX, TIPS_STATIC6, tipsStatic6);
	DDX_Control(pDX, LOGIN_EDIT, loginEdit);
	DDX_Control(pDX, LOGIN_BUTTON2, loginButton2);
	DDX_Control(pDX, LOGIN_CHECK2, loginCheck2);
}


BEGIN_MESSAGE_MAP(LoginDlg2, CDialogEx)
	ON_BN_CLICKED(LOGIN_BUTTON2, &LoginDlg2::OnBnClickedButtonLogin2)
	ON_BN_CLICKED(IDCANCEL, &LoginDlg2::OnBnClickedCancel)
	ON_WM_PAINT()
	ON_BN_CLICKED(FORGET_BUTTON, &LoginDlg2::OnBnClickedButtonForget)
END_MESSAGE_MAP()


// LoginDlg2 消息处理程序


void LoginDlg2::OnBnClickedButtonLogin2()
{
	// TODO: 在此添加控件通知处理程序代码

	bool isPasswordRight;
	CString Cpassword;
	GetDlgItem(LOGIN_EDIT)->GetWindowText(Cpassword);
	USES_CONVERSION;
	std::string passwordInput(W2A(Cpassword));
	if (password == passwordInput) {
		isPasswordRight = true;
	}
	else {
		isPasswordRight = false;
	}
	if (isPasswordRight) {
		loginCancal = false;
		if (BST_CHECKED == IsDlgButtonChecked(LOGIN_CHECK2))
		{
			//IDC_CHECK1是CheckBox控件。
			//Check Box被选中执行相关动作
			rememberPassword = 1;
		}
		else rememberPassword = 0;
		CDialogEx::OnOK();
	}
	else MessageBox(L"密码错误！", L"输入错误", MB_ICONEXCLAMATION);

}


void LoginDlg2::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码

	loginCancal = true;

	CDialogEx::OnCancel();
}


BOOL LoginDlg2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//IDR_ICON为图标资源名

	SetIcon(dialogIcon, TRUE); // Set big icon

	SetIcon(dialogIcon, FALSE); // Set small icon

	if (rememberPassword == 1) {
		loginCheck2.SetCheck(1);
		CString Cpassword;
		Cpassword = password.c_str();
		GetDlgItem(LOGIN_EDIT)->SetWindowText(Cpassword);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void LoginDlg2::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()

	CBitmap bitmap;    // CBitmap对象，用于加载位图  
	HBITMAP hbmp;      // 保存CBitmap加载的位图句柄 
	bitmap.LoadBitmap(numberOfFace); //位图加载
	hbmp = (HBITMAP)bitmap.GetSafeHandle();// 获取bitmap位图句柄 
	loginPicture2.SetBitmap(hbmp);//设置图片控件要显示的位图：IDB_BITMAP2

	tipsStatic6.SetFont(&tipsFont);
	loginEdit.SetFont(&tipsFont);
	loginButton2.SetFont(&tipsFont);

}


void LoginDlg2::OnBnClickedButtonForget()
{
	// TODO: 在此添加控件通知处理程序代码

	ResetDlg rd;
	rd.DoModal();
	OnPaint();
	OnInitDialog();
	UpdateWindow();

}
