// Logindlg.cpp: 实现文件
//

#include "pch.h"
#include "AddressBook.h"
#include "Logindlg.h"
#include "afxdialogex.h"

#include<string>

#include"Function.h"

extern bool loginCancal;
extern CFont tipsFont;
extern HICON dialogIcon;

extern bool isNewUser;
extern int numOfPicture;
extern int numberOfFace;
extern std::string password;
extern int rememberPassword;
extern int securityQuestion;
extern std::string answerOfsecurityQuestion;

// Logindlg 对话框

IMPLEMENT_DYNAMIC(Logindlg, CDialogEx)

Logindlg::Logindlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(LOGIN_DIALOG, pParent)
{

}

Logindlg::~Logindlg()
{
}

void Logindlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, LOGIN_PICTURE, loginPicture);
	DDX_Control(pDX, TIPS_STATIC4, tipsStatic4);
	DDX_Control(pDX, TIPS_STATIC1, tipsStatic1);
	DDX_Control(pDX, TIPS_STATIC2, tipsStatic2);
	DDX_Control(pDX, TIPS_STATIC3, tipsStatic3);
	DDX_Control(pDX, SET_PASSWORD_EDIT, setPasswordEdit);
	DDX_Control(pDX, SET_PASSWORD_EDIT2, setPasswordEdit2);
	DDX_Control(pDX, LOGIN_COMBO, loginCombo);
	DDX_Control(pDX, TIPS_STATIC5, tipsStatic5);
	DDX_Control(pDX, LOGIN_BUTTON, loginButton);
	DDX_Control(pDX, FACE_SELECT_BUTTON, faceSelectButton);
	DDX_Control(pDX, LOGIN_CHECK, loginCheck);
	DDX_Control(pDX, SET_PASSWORD_EDIT3, setPasswordEdit3);
}


BEGIN_MESSAGE_MAP(Logindlg, CDialogEx)
	ON_BN_CLICKED(LOGIN_BUTTON, &Logindlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDCANCEL, &Logindlg::OnBnClickedCancel)
	ON_BN_CLICKED(FACE_SELECT_BUTTON, &Logindlg::OnBnClickedButton2)
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// Logindlg 消息处理程序


void Logindlg::OnBnClickedButtonLogin()
{
	// TODO: 在此添加控件通知处理程序代码

	bool isSuccessful;
	loginCancal = false;
	CString Cpassword1, Cpassword2;
	GetDlgItem(SET_PASSWORD_EDIT)->GetWindowText(Cpassword1);
	GetDlgItem(SET_PASSWORD_EDIT2)->GetWindowText(Cpassword2);
	if (Cpassword1 == Cpassword2) {
		USES_CONVERSION;
		std::string password1(W2A(Cpassword1)), password2(W2A(Cpassword2));

		if (password1 == "") {
			MessageBox(L"密码不能为空！", L"输入错误", MB_ICONEXCLAMATION);
			isSuccessful = false;
		}
		else if (password1 == password2) {
			CString CanswerOfsecurityQuestion;
			GetDlgItem(SET_PASSWORD_EDIT3)->GetWindowText(CanswerOfsecurityQuestion);
			USES_CONVERSION;
			std::string stringAnswerOfsecurityQuestion(W2A(CanswerOfsecurityQuestion));
			
			if (stringAnswerOfsecurityQuestion == "") {
				MessageBox(L"密保问题答案不能为空！", L"输入错误", MB_ICONEXCLAMATION);
				isSuccessful = false;
			}	
			else {
				answerOfsecurityQuestion = stringAnswerOfsecurityQuestion;
				isNewUser = false;
				numberOfFace = numOfPicture;
				password = password1;
				if (BST_CHECKED == IsDlgButtonChecked(LOGIN_CHECK))
				{
					//IDC_CHECK1是CheckBox控件。
					//Check Box被选中执行相关动作
					rememberPassword = 1;
				}
				else rememberPassword = 0;

				securityQuestion = loginCombo.GetCurSel(); // 获取选定项的序号
				//loginCombo.GetLBText(cindex, text); // 获取选定项的文本内容

				isSuccessful = true;
			}
		}
		else {
			isSuccessful = false;
		}
	}
	else {
		MessageBox(L"两次输入的密码不一样！", L"输入错误", MB_ICONEXCLAMATION);
		isSuccessful = false;
	}
	
	if(isSuccessful) CDialogEx::OnOK();

}


void Logindlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码

	loginCancal = true;

	CDialogEx::OnCancel();
}


BOOL Logindlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//解决分辨率改变，窗口大小改变问题
	GetClientRect(&m_rect);  //  第二步：在初始化函数OnInitDialog()中添加。
	int nScreenWidth, nScreenHeight;//保存分辨率
	nScreenWidth = GetSystemMetrics(SM_CXSCREEN);//获取分辨率
	nScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	//  HWND hwnd1 = AfxGetApp()->GetMainWnd()->GetSafeHwnd();   //获取主窗口句柄
	SetWindowPos(NULL, 100, 100, nScreenWidth * 0.32, nScreenHeight * 0.8, SWP_NOMOVE);

	//IDR_ICON为图标资源名

	SetIcon(dialogIcon, TRUE); // Set big icon

	SetIcon(dialogIcon, FALSE); // Set small icon

	myFont.CreatePointFont(230, _T("华文隶书"));
	tipsStatic4.SetFont(&myFont);
	
	tipsStatic1.SetFont(&tipsFont);
	tipsStatic2.SetFont(&tipsFont);
	tipsStatic3.SetFont(&tipsFont);
	tipsStatic5.SetFont(&tipsFont);
	setPasswordEdit.SetFont(&tipsFont);
	setPasswordEdit2.SetFont(&tipsFont);
	setPasswordEdit3.SetFont(&tipsFont);
	loginCombo.SetFont(&tipsFont);
	loginCombo.SetItemHeight(0, 30);
	loginCheck.SetFont(&tipsFont);
	loginButton.SetFont(&tipsFont);
	faceSelectButton.SetFont(&tipsFont);

	CString Cpassword;
	Cpassword = password.c_str();
	GetDlgItem(SET_PASSWORD_EDIT)->SetWindowText(Cpassword);
	GetDlgItem(SET_PASSWORD_EDIT2)->SetWindowText(Cpassword);
	loginCombo.SetCurSel(securityQuestion);
	CString CanswerOfsecurityQuestion;
	CanswerOfsecurityQuestion = answerOfsecurityQuestion.c_str();
	GetDlgItem(SET_PASSWORD_EDIT3)->SetWindowText(CanswerOfsecurityQuestion);
	if (rememberPassword == 1) {
		loginCheck.SetCheck(1);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Logindlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	/*BITMAP hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP1));
	loginPicture.SetBitmap(hBitmap);*/

	/*CRect rect;
	loginPicture.GetWindowRect(&rect);
	HBITMAP hBmp = (HBITMAP)::LoadImage(NULL, 0, IDB_BITMAP1, rect.Width(), rect.Height(), LR_LOADFROMFILE);
	loginPicture.ModifyStyle(NULL, SS_BITMAP);
	loginPicture.SetBitmap(hBmp);
	DeleteObject(hBmp);*/

	CBitmap bitmap;    // CBitmap对象，用于加载位图  
	HBITMAP hbmp;      // 保存CBitmap加载的位图句柄  

	numOfPicture++;
	if (numOfPicture > 243) numOfPicture -= 87;
	bitmap.LoadBitmap(numOfPicture); //位图加载
	hbmp = (HBITMAP)bitmap.GetSafeHandle();// 获取bitmap位图句柄 
	loginPicture.SetBitmap(hbmp);//设置图片控件要显示的位图：IDB_BITMAP2

}


void Logindlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()

	CBitmap bitmap;    // CBitmap对象，用于加载位图  
	HBITMAP hbmp;      // 保存CBitmap加载的位图句柄  
	Function f;
	bitmap.LoadBitmap(numberOfFace);//位图加载
	hbmp = (HBITMAP)bitmap.GetSafeHandle();// 获取bitmap位图句柄 
	loginPicture.SetBitmap(hbmp);//设置图片控件要显示的位图：IDB_BITMAP2

}


void Logindlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码

	if (nType != SIZE_MINIMIZED)
	{
		//IDC_STATIC_PLAY_SPEED    IDC_STATIC

		/*ChangeSize(LOGIN_PICTURE, cx, cy);
		ChangeSize(LOGIN_BUTTON, cx, cy);
		ChangeSize(LOGIN_CHECK, cx, cy);
		ChangeSize(LOGIN_COMBO, cx, cy);
		ChangeSize(FACE_SELECT_BUTTON, cx, cy);
		ChangeSize(TIPS_STATIC1, cx, cy);
		ChangeSize(TIPS_STATIC2, cx, cy);
		ChangeSize(TIPS_STATIC3, cx, cy);
		ChangeSize(TIPS_STATIC4, cx, cy);
		ChangeSize(TIPS_STATIC5, cx, cy);
		ChangeSize(SET_PASSWORD_EDIT, cx, cy);
		ChangeSize(SET_PASSWORD_EDIT2, cx, cy);
		ChangeSize(SET_PASSWORD_EDIT3, cx, cy);*/
		GetClientRect(&m_rect); // 将变化后的对话框大小设为旧大小，否则无法还原控件原始位置
	}

}


void Logindlg::ChangeSize(UINT nID, int cx, int cy) {

	CWnd* pWnd;
	pWnd = GetDlgItem(nID);   //获取控件句柄
	if (pWnd)  //判断是否为空，因为对话框创建时会调用此函数，而当时控件还未创建
	{
		CRect rect;  //获取控件变化前大小
		pWnd->GetWindowRect(&rect);
		ScreenToClient(&rect); //将控件大小转换为在对话框中的区域坐标
		rect.left = rect.left * cx / m_rect.Width();    // 调整控件大小
		rect.right = rect.right * cx / m_rect.Width();
		rect.top = rect.top * cy / m_rect.Height();    // 调整控件大小
		rect.bottom = rect.bottom * cy / m_rect.Height();
		pWnd->MoveWindow(rect);
	}

}