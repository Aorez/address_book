
// AddressBookDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "AddressBook.h"
#include "AddressBookDlg.h"
#include "afxdialogex.h"

#include<string>
#include<vector>

extern int numOfFace;
extern std::string name;
extern std::string number;
extern std::string number2;
extern std::string email;
extern std::string address;
extern std::string remarks;

#include"Function.h"
#include"Person.h"
#include"ModifyDlg.h"
#include"AddDlg.h"
#include"AddressBookDlg.h"
#include"DetatilsDlg.h"
#include"Logindlg.h"
#include"LoginDlg2.h"
#include"ResetDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern int R, G, B;
extern COLORREF staticColor;
extern int staticIndex;
extern bool hasModified;
extern bool hasAdded;
extern bool isNewUser;
extern bool loginCancal;
extern bool isModifying;
extern std::vector<Person> addressBook;
extern std::vector<std::string> topArray;
extern CFont tipsFont;
extern HICON dialogIcon;
extern bool isReseting;

extern int numberOfFace;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAddressBookDlg 对话框



CAddressBookDlg::CAddressBookDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADDRESSBOOK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(MAIN_ICON);
}

void CAddressBookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, HOME_LIST, homeList);
	DDX_Control(pDX, SEARCH_BUTTON, searchButton);
	DDX_Control(pDX, MY_STATIC, myStatic);
	DDX_Control(pDX, SEARCH_EDIT, searchEdit);
	DDX_Control(pDX, MODIFY_BUTTON, modifyButton);
	DDX_Control(pDX, ADD_BUTTON, addButton);
	DDX_Control(pDX, HOME_PICTURE, homePicture);
}

BEGIN_MESSAGE_MAP(CAddressBookDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(SEARCH_BUTTON, &CAddressBookDlg::OnBnClickedButtonSearch)
	ON_BN_CLICKED(MODIFY_BUTTON, &CAddressBookDlg::OnBnClickedButtonModify)
	ON_BN_CLICKED(DISPLAY_BUTTON, &CAddressBookDlg::OnBnClickedButtonDisplay)
	ON_BN_CLICKED(DETACH_BUTTON, &CAddressBookDlg::OnBnClickedButtonDetach)
	ON_NOTIFY(NM_RCLICK, HOME_LIST, &CAddressBookDlg::OnNMRClickList)
	ON_COMMAND(ID_32771Copy, &CAddressBookDlg::On32771Copy)
	ON_COMMAND(ID_32772CopyLine, &CAddressBookDlg::On32772CopyLine)
	ON_COMMAND(ID_32773Modify, &CAddressBookDlg::On32773Modify)
	ON_COMMAND(ID_32774Detach, &CAddressBookDlg::On32774Detach)
	ON_BN_CLICKED(ADD_BUTTON, &CAddressBookDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(CLEAR_BUTTON, &CAddressBookDlg::OnBnClickedButtonClear)
	ON_NOTIFY(NM_DBLCLK, HOME_LIST, &CAddressBookDlg::OnNMDblclkList)
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_32781, &CAddressBookDlg::On32781Clear)
	ON_COMMAND(ID_32784, &CAddressBookDlg::On32784Reset)
	ON_COMMAND(ID_32785, &CAddressBookDlg::On32785Reset)
	ON_COMMAND(ID_32786, &CAddressBookDlg::On32786ColorChange)
	ON_COMMAND(ID_32787, &CAddressBookDlg::On32787DefaultColor)
	ON_WM_PALETTEISCHANGING()
	ON_COMMAND(ID_32789, &CAddressBookDlg::On32789TopStar)
	ON_COMMAND(ID_32796, &CAddressBookDlg::On32796ModifyMenu)
	ON_COMMAND(ID_32797, &CAddressBookDlg::On32797DetachMenu)
	ON_COMMAND(ID_32798, &CAddressBookDlg::On32798Revoke)
	ON_COMMAND(ID_32795, &CAddressBookDlg::On32795Revoke)
	ON_COMMAND(ID_32799, &CAddressBookDlg::On32799About)
	ON_WM_SIZE()
	ON_COMMAND(ID_32800, &CAddressBookDlg::On32800Add)
	ON_COMMAND(ID_32801, &CAddressBookDlg::On32801Display)
	ON_COMMAND(ID_32802, &CAddressBookDlg::On32802)
END_MESSAGE_MAP()


// CAddressBookDlg 消息处理程序

BOOL CAddressBookDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//ShowWindow(SW_MAXIMIZE);

	// TODO: 在此添加额外的初始化代码

	//解决分辨率改变，窗口大小改变问题
	GetClientRect(&m_rect);  //  第二步：在初始化函数OnInitDialog()中添加。
	int nScreenWidth, nScreenHeight;//保存分辨率
	nScreenWidth = GetSystemMetrics(SM_CXSCREEN);//获取分辨率
		nScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	//  HWND hwnd1 = AfxGetApp()->GetMainWnd()->GetSafeHwnd();   //获取主窗口句柄
	SetWindowPos(NULL, 100, 100, nScreenWidth * 0.45, nScreenHeight * 0.8, SWP_NOMOVE);
	
	//信息导入
	Function f;
	//f.test();//测试
	f.dataImport();

	//设置对话框左上角图标
	dialogIcon = AfxGetApp()->LoadIcon(MAIN_ICON);



	//设置提示

	m_stat.Create(this);
	m_stat.AddTool(GetDlgItem(ADD_BUTTON), L"点击此处添加联系人"); //IDC_BUTTON为你要添加提示信息的按钮的ID
	m_stat.AddTool(GetDlgItem(DISPLAY_BUTTON), L"点击此处显示全部联系人");
	m_stat.AddTool(GetDlgItem(SEARCH_BUTTON), L"点击搜索");
	m_stat.AddTool(GetDlgItem(HOME_LIST), L"右键打开菜单 || 双击查看详细信息");
	
	m_stat.SetDelayTime(0); //设置延迟，如果为0则不等待，立即显示
	//m_stat.SetTipTextColor( RGB(0,0,255) ); //设置提示文本的颜色
	//m_stat.SetTipBkColor( RGB(255,255,255)); //设置提示框的背景颜色

	//m_stat.SetMaxTipWidth(600);//设置文本框的最大宽度，注意里边的数值单位为像素，所以要通过不断测试来选定最理想的宽度。利用此句可显示多行
	m_stat.Activate(TRUE); //设置是否启用提示


	//设置搜索按钮的图片
	//searchButton.LoadBitmaps(初始, 点击, 恢复, SEARCH_BITMAP1);
	searchButton.LoadBitmaps(SEARCH_BITMAP1, SEARCH_BITMAP2, SEARCH_BITMAP3, MAIN_BITMAP);
	searchButton.SizeToContent();

	//创建所有提示性文本的共同字体属性
	tipsFont.CreatePointFont(100, _T("微软雅黑"));
	//“通讯录”大字的字体属性
	myFont.CreatePointFont(300, _T("华文隶书"));
	myStatic.SetFont(&myFont);
	//设置控件字体属性
	searchEdit.SetFont(&tipsFont);
	homeList.SetFont(&tipsFont);
	//添加按钮中间的“十”字的字体属性
	addButtonFont.CreatePointFont(150, _T("微软雅黑"));
	addButton.SetFont(&addButtonFont);


	//如果是新用户，则创建模态对话框1
	if (isNewUser) {
		Logindlg ld;
		ld.DoModal();
	}
	//否则创建模态对话框2
	else {
		LoginDlg2 ld2;
		ld2.DoModal();
	}
	//参数传递
	if (loginCancal) {
		OnCancel();
	}


	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	homeList.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	homeList.SetExtendedStyle(homeList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 为列表视图控件添加三列   
	const int numberOfListColumns = 13;
	const int multiple = 4;
	homeList.InsertColumn(0, _T("##"), LVCFMT_CENTER, rect.Width() / numberOfListColumns, 0);
	homeList.InsertColumn(1, _T("姓名"), LVCFMT_CENTER, rect.Width() / numberOfListColumns * multiple, 1);
	homeList.InsertColumn(2, _T("联系电话1"), LVCFMT_CENTER, rect.Width() / numberOfListColumns * multiple, 2);
	homeList.InsertColumn(3, _T("联系电话2"), LVCFMT_CENTER, rect.Width() / numberOfListColumns * multiple, 2);

	// 在列表视图控件中插入列表项，并设置列表子项文本   

	// TODO: 在此添加控件通知处理程序代码

	OnBnClickedButtonDisplay();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAddressBookDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAddressBookDlg::OnPaint()
{
	//展示头像
	CBitmap bitmap;    // CBitmap对象，用于加载位图  
	HBITMAP hbmp;      // 保存CBitmap加载的位图句柄 
	bitmap.LoadBitmap(numberOfFace); //位图加载
	hbmp = (HBITMAP)bitmap.GetSafeHandle();// 获取bitmap位图句柄 
	homePicture.SetBitmap(hbmp);//设置图片控件要显示的位图：IDB_BITMAP2

	//设置头像提示文本
	CString Ctips;
	std::string stringTips = "我的头像，该头像序号为" + std::to_string(numberOfFace - 155);
	Ctips = stringTips.c_str();
	m_stat.AddTool(GetDlgItem(HOME_PICTURE), L"" + Ctips);

	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAddressBookDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//搜索按钮
void CAddressBookDlg::OnBnClickedButtonSearch()
{
	// TODO: 在此添加控件通知处理程序代码

	CString CdataToSearch;
	GetDlgItem(SEARCH_EDIT)->GetWindowText(CdataToSearch);
	USES_CONVERSION;
	std::string dataToSearch(W2A(CdataToSearch));
	Function f;
	int index = f.search(dataToSearch);
	if (index == -1)
		MessageBox(L"联系人不存在", L"搜索", MB_ICONEXCLAMATION);
	else {
		ShowOneOnList(index);
	}
	GetDlgItem(SEARCH_EDIT)->SetWindowText(L"");

}

//修改按钮
void CAddressBookDlg::OnBnClickedButtonModify()
{
	// TODO: 在此添加控件通知处理程序代码

	int nItem;
	nItem = homeList.GetSelectionMark();
	if (nItem == -1) {
		MessageBox(_T("请选择联系人！"));
	}
	else {
		CString CnameToModify;
		CnameToModify = homeList.GetItemText(nItem, 1);
		USES_CONVERSION;
		std::string nameToModify(W2A(CnameToModify));
		Function f;
		staticIndex = f.search(nameToModify);
		ModifyDlg md;
		md.DoModal();

		if (hasModified) {
			ShowOneOnList(staticIndex);
		}
	}
	

}

//显示按钮
void CAddressBookDlg::OnBnClickedButtonDisplay()
{
	// TODO: 在此添加控件通知处理程序代码

	//获取全局变量长度
	int length = addressBook.size();
	int size = topArray.size();
	//“List Control”控件有四列
	const int lengthOfDisplayArray = 4;
	CString CdisplayArray[lengthOfDisplayArray];

	Function f;
	//清空控件内容
	homeList.DeleteAllItems();

	std::string topStar = "**";
	CdisplayArray[0] = topStar.c_str();
	for (int i = 0; i < size; i++) {
		homeList.InsertItem(i, CdisplayArray[0]);
		for (int j = 1; j < lengthOfDisplayArray; j++) {
			CdisplayArray[j] = f.display(f.search(topArray[i]), j).c_str();
			homeList.SetItemText(i, j, CdisplayArray[j]);
		}
	}

	for (int i = 0; i < length; i++) {
		CdisplayArray[0] = std::to_string(i).c_str();
		homeList.InsertItem(i + size, CdisplayArray[0]);
		for (int j = 1; j < lengthOfDisplayArray; j++) {
			CdisplayArray[j] = f.display(i, j).c_str();
			homeList.SetItemText(i + size, j, CdisplayArray[j]);
		}
	}

}

//删除按钮
void CAddressBookDlg::OnBnClickedButtonDetach()
{
	// TODO: 在此添加控件通知处理程序代码

	int nItem;
	nItem = homeList.GetSelectionMark();
	CString CnameToDetach;
	if (nItem != -1) {
		if (MessageBox(L"确定删除该联系人吗？", L"删除", MB_OKCANCEL | MB_DEFBUTTON2) == 1) {
			CnameToDetach = homeList.GetItemText(nItem, 1);
			Function f;
			USES_CONVERSION;
			int indexToDetach = f.search((W2A(CnameToDetach)));
			f.detach(indexToDetach);
			MessageBox(L"删除成功");
			OnBnClickedButtonDisplay();
		}
	}
	else MessageBox(_T("请选择联系人"));

}

//重载，退出程序时执行此函数
void CAddressBookDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	Function f;
	f.dataExport();

	CDialogEx::OnCancel();
}

//右键菜单
void CAddressBookDlg::OnNMRClickList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->iItem != -1)
	{

		CPoint pt;
		GetCursorPos(&pt);
		CMenu menu;
		menu.LoadMenu(RCLICK_MENU);
		CMenu* popmenu;
		popmenu = menu.GetSubMenu(0);
		popmenu->TrackPopupMenu(TPM_RIGHTBUTTON, pt.x, pt.y, this);
	}

	*pResult = 0;
}

//右键复制
void CAddressBookDlg::On32771Copy()
{
	// TODO: 在此添加命令处理程序代码

	int nItem;
	CString strText;
	DWORD dwPos = GetMessagePos();
	CPoint point(LOWORD(dwPos), HIWORD(dwPos));
	homeList.ScreenToClient(&point);

	//定义结构体  
	LVHITTESTINFO lvinfo;
	lvinfo.pt = point;
	lvinfo.flags = LVHT_ABOVE;

	//获取行号信息  
	//nItem = homeListControl.HitTest(&lvinfo);
	nItem = homeList.SubItemHitTest(&lvinfo);
	nItem = homeList.GetSelectionMark();
	if (nItem != -1)
		strText = homeList.GetItemText(nItem, lvinfo.iSubItem);//获取对应单元格的内容

	//复制剪切板
	if (!strText.IsEmpty())
	{
		if (OpenClipboard())
		{
			EmptyClipboard();
			//TCHAR* pszData;
			wchar_t* pszData;
			HGLOBAL hClipboardData = GlobalAlloc(GMEM_DDESHARE, (strText.GetLength() + 1) * sizeof(TCHAR));
			if (hClipboardData)
			{
				pszData = (TCHAR*)GlobalLock(hClipboardData);
				wcscpy(pszData, strText);
				GlobalUnlock(hClipboardData);
				SetClipboardData(CF_UNICODETEXT, hClipboardData);//根据相应的数据选择第一个参数，（CF_TEXT）  
			}
			CloseClipboard();
		}
	}

}

//右键复制整行
void CAddressBookDlg::On32772CopyLine()
{
	// TODO: 在此添加命令处理程序代码;

	int nItem;
	CString strText(_T(""));

	//获取行号信息  
	nItem = homeList.GetSelectionMark();
	if (nItem != -1) {
		strText += L"姓名：" + homeList.GetItemText(nItem, 1) + L"；联系电话1：" + homeList.GetItemText(nItem, 2) + L"；联系电话2：" + homeList.GetItemText(nItem, 3) + L"；";
	}
	//获取对应单元格的内容

	//复制剪切板
	if (!strText.IsEmpty())
	{
		if (OpenClipboard())
		{
			EmptyClipboard();
			TCHAR* pszData;
			HGLOBAL hClipboardData = GlobalAlloc(GMEM_DDESHARE, (strText.GetLength() + 1) * sizeof(TCHAR));
			if (hClipboardData)
			{
				pszData = (TCHAR*)GlobalLock(hClipboardData);
				wcscpy(pszData, strText);
				GlobalUnlock(hClipboardData);
				SetClipboardData(CF_UNICODETEXT, hClipboardData);//根据相应的数据选择第一个参数，（CF_TEXT）  
			}
			CloseClipboard();
		}
	}

}

//右键编辑修改
void CAddressBookDlg::On32773Modify()
{
	// TODO: 在此添加命令处理程序代码

	int nItem;
	nItem = homeList.GetSelectionMark();
	USES_CONVERSION;
	std::string getName(W2A(homeList.GetItemText(nItem, 1)));
	Function f;
	staticIndex = f.search(getName);
	isModifying = true;
	AddDlg ad;
	ad.DoModal();
	OnBnClickedButtonDisplay();

}

//右键删除
void CAddressBookDlg::On32774Detach()
{
	// TODO: 在此添加命令处理程序代码

	OnBnClickedButtonDetach();

}

//添加联系人按钮
void CAddressBookDlg::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码

	AddDlg ad;
	ad.DoModal();

	if (hasAdded) {
		ShowOneOnList(staticIndex);
	}
	
}

//清空按钮
void CAddressBookDlg::OnBnClickedButtonClear()
{
	// TODO: 在此添加控件通知处理程序代码

	if (MessageBox(L"确定清空通讯录吗？\n清空后无法恢复", L"清空", MB_OKCANCEL | MB_DEFBUTTON2) == 1) {
		Function f;
		f.clear();
		MessageBox(L"清除成功", L"操作成功");
		homeList.DeleteAllItems();
	}

}

//显示单个联系人到"List Control"
void CAddressBookDlg::ShowOneOnList(int indexToShow)
{
	// TODO: 在此处添加实现代码.

	int length = addressBook.size();
	int size = topArray.size();
	const int lengthOfDisplayArray = 4;
	CString CdisplayArray[lengthOfDisplayArray];
	Function f;
	homeList.DeleteAllItems();

	std::string topStar = "**";
	CdisplayArray[0] = topStar.c_str();
	for (int i = 0; i < size; i++) {
		homeList.InsertItem(i, CdisplayArray[0]);
		for (int j = 1; j < lengthOfDisplayArray; j++) {
			CdisplayArray[j] = f.display(f.search(topArray[i]), j).c_str();
			homeList.SetItemText(i, j, CdisplayArray[j]);
		}
	}

	const int lengthOfShowArray = 7;
	CString showArray[lengthOfShowArray];
	for (int i = 1; i < lengthOfShowArray; i++) {
		showArray[i] = f.display(indexToShow, i).c_str();
	}
	CString CindexToShow;
	CindexToShow = std::to_string(indexToShow).c_str();
	homeList.InsertItem(size, CindexToShow);
	for (int i = 1; i < lengthOfShowArray; i++) {
		homeList.SetItemText(size, i, showArray[i]);
	}

}

//双击弹窗显示详细信息
void CAddressBookDlg::OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	int nItem;
	nItem = homeList.GetSelectionMark();
	CString CnameToModify;
	CnameToModify = homeList.GetItemText(nItem, 1);
	USES_CONVERSION;
	Function f;
	std::string nameToModify(W2A(CnameToModify));
	if (nameToModify == "") {

	}
	else {
		staticIndex = f.search(nameToModify);
		DetatilsDlg dd;
		dd.DoModal();
		OnBnClickedButtonDisplay();
	}
	
	*pResult = 0;
}

//重载函数，在搜索框输入后回车，可以直接搜索
BOOL CAddressBookDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	m_stat.RelayEvent(pMsg);

	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		OnBnClickedButtonSearch();
		UpdateData(false);
		return true;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


HBRUSH CAddressBookDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性


	if (pWnd->GetDlgCtrlID() == MY_STATIC)// IDC_Display为所选文本框ID

	{

		pDC->SetTextColor(staticColor);//设置字体颜色
		
		//pDC->SetBkColor(RGB(255, 0, 0));//设置背景颜色

		//pDC->SetBkMode(TRANSPARENT);//设置背景透明

	}

	if (pWnd->GetDlgCtrlID() == ADD_BUTTON)// IDC_Display为所选文本框ID

	{

		pDC->SetTextColor(RGB(255, 255, 255));//设置字体颜色

		//pDC->SetBkColor(RGB(255, 0, 0));//设置背景颜色

		//pDC->SetBkMode(TRANSPARENT);//设置背景透明

	}


	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

//菜单栏清空通讯录
void CAddressBookDlg::On32781Clear()
{
	// TODO: 在此添加命令处理程序代码

	OnBnClickedButtonClear();

}

//菜单栏修改账户信息
void CAddressBookDlg::On32784Reset()
{
	// TODO: 在此添加命令处理程序代码


	LoginDlg2 ld2;
	ld2.DoModal();
	if (loginCancal) {

	}
	else {
		Logindlg lg;
		lg.DoModal();
		OnPaint();
	}

}

//菜单栏重置账户
void CAddressBookDlg::On32785Reset()
{
	// TODO: 在此添加命令处理程序代码

	if (MessageBox(L"确定重置账户吗？\n此操作也将清空通讯录", L"重置", MB_OKCANCEL | MB_DEFBUTTON2) == 1) {
		isReseting = true;
		ResetDlg rd;
		rd.DoModal();
		if (rd.resetCancal) {
			
		}
		else {
			Function f;
			f.clear();
			MessageBox(L"通讯录清空成功！", L"操作成功");
			isNewUser = true;
			MessageBox(L"账户重置成功！", L"操作成功");
			OnCancel();
		}
		
		homeList.DeleteAllItems();
	}
	else {
		isReseting = false;
	}

}


void CAddressBookDlg::On32786ColorChange()
{
	// TODO: 在此添加命令处理程序代码

	R += 20;
	G += 20;
	B += 20;
	if (R > 255) {
		R %= 255;
	}
	if(G > 255) {
		R %= 255;
	}
	if(B > 255) {
		R %= 255;
	}

}


void CAddressBookDlg::On32787DefaultColor()
{
	// TODO: 在此添加命令处理程序代码

	/*R = 102;
	G = 171;
	B = 243;*/
	R = 255;
	G = 255;
	B = 255;

}


void CAddressBookDlg::OnPaletteIsChanging(CWnd* pRealizeWnd)
{
	CDialogEx::OnPaletteIsChanging(pRealizeWnd);

	// TODO: 在此处添加消息处理程序代码
}

//右键设置星标联系人
void CAddressBookDlg::On32789TopStar()
{
	// TODO: 在此添加命令处理程序代码

	int nItem;
	nItem = homeList.GetSelectionMark();
	CString CindexToTop;
	if (nItem != -1) {
		CindexToTop = homeList.GetItemText(nItem, 0);
		USES_CONVERSION;
		std::string stringIndexToTop(W2A(CindexToTop));
		Function f;
		if (stringIndexToTop == "**") {
			CindexToTop = homeList.GetItemText(nItem, 1);
			std::string stringNameTopCancal(W2A(homeList.GetItemText(nItem, 1)));
			int indexTopCancal = f.searchInTop(stringNameTopCancal);
			topArray.erase(topArray.begin() + indexTopCancal);
		}
		else {
			std::string stringNameToTop = f.display(atoi(stringIndexToTop.c_str()), 1);
			if (f.searchInTop(stringNameToTop) == -1) {
				topArray.push_back(stringNameToTop);
				MessageBox(L"置顶成功！", L"操作成功");
			}
			else {
				MessageBox(L"该联系人已置顶！", L"操作错误", MB_ICONEXCLAMATION);
			}
		}
		OnBnClickedButtonDisplay();
	}
	else MessageBox(_T("请选择联系人！"), L"操作错误", MB_ICONEXCLAMATION);

}

//菜单栏修改
void CAddressBookDlg::On32796ModifyMenu()
{
	// TODO: 在此添加命令处理程序代码

	int nItem;
	nItem = homeList.GetSelectionMark();
	if (nItem == -1) {
		MessageBox(L"请选择联系人", L"操作错误", MB_ICONEXCLAMATION);
	}
	else {
		USES_CONVERSION;
		std::string getName(W2A(homeList.GetItemText(nItem, 1)));
		Function f;
		staticIndex = f.search(getName);
		isModifying = true;
		AddDlg ad;
		ad.DoModal();
		OnBnClickedButtonDisplay();
	}

}

//菜单栏删除
void CAddressBookDlg::On32797DetachMenu()
{
	// TODO: 在此添加命令处理程序代码

	int nItem;
	nItem = homeList.GetSelectionMark();
	if (nItem == -1) {
		MessageBox(L"请选择联系人", L"操作错误", MB_ICONEXCLAMATION);
	}
	else {
		OnBnClickedButtonDetach();
	}

}

//菜单栏撤销
void CAddressBookDlg::On32798Revoke()
{
	// TODO: 在此添加命令处理程序代码

	if (numOfFace == -1) {
		MessageBox(L"未进行任何删除！", L"操作错误", MB_ICONEXCLAMATION);
	}
	else {
		Function f;
		f.add(numOfFace, name, number, number2, email, address, remarks);
		int indexRevoke = f.search(name);
		numOfFace = -1;
		name = "";
		number = "";
		number2 = "";
		email = "";
		address = "";
		remarks = "";
		ShowOneOnList(indexRevoke);
	}
	
}


void CAddressBookDlg::On32795Revoke()
{
	// TODO: 在此添加命令处理程序代码

	On32798Revoke();

}


void CAddressBookDlg::On32799About()
{
	// TODO: 在此添加命令处理程序代码

	CAboutDlg cad;
	cad.DoModal();

}




//BOOL CAddressBookDlg::PreCreateWindow(CREATESTRUCT& cs)
//{
//	// TODO: 在此添加专用代码和/或调用基类
//
//	if (!CFrameWnd::PreCreateWindow(cs))
//		return FALSE;
//	// TODO: 在此处通过修改
//	//  CREATESTRUCT cs 来修改窗口类或样式
//	cs.cx = 630;
//	cs.cy = 560;
//	cs.style &= ~WS_MAXIMIZEBOX;//禁止最大化
//	cs.style &= ~WS_THICKFRAME;//禁止调整大小
//	//cs.style &= ~WS_MINIMIZEBOX;禁止最小化
//	cs.lpszName = "算法收集器";
//	return TRUE;
//
//	return CDialogEx::PreCreateWindow(cs);
//}


void CAddressBookDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码

	if (nType != SIZE_MINIMIZED)
	{
		//IDC_STATIC_PLAY_SPEED    IDC_STATIC
		ChangeSize(HOME_LIST, cx, cy);
		ChangeSize(HOME_PICTURE, cx, cy);
		ChangeSize(MY_STATIC, cx, cy);
		ChangeSize(SEARCH_EDIT, cx, cy);
		ChangeSize(SEARCH_BUTTON, cx, cy);
		ChangeSize(ADD_BUTTON, cx, cy);
		ChangeSize(DISPLAY_BUTTON, cx, cy);

		ChangeSize(LOGIN_BUTTON2, cx, cy);
		ChangeSize(LOGIN_CHECK2, cx, cy);
		ChangeSize(LOGIN_PICTURE2, cx, cy);

		GetClientRect(&m_rect); // 将变化后的对话框大小设为旧大小，否则无法还原控件原始位置
	}

}


void CAddressBookDlg::ChangeSize(UINT nID, int cx, int cy) {

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


void CAddressBookDlg::On32800Add()
{
	// TODO: 在此添加命令处理程序代码

	OnBnClickedButtonAdd();

}


void CAddressBookDlg::On32801Display()
{
	// TODO: 在此添加命令处理程序代码

	OnBnClickedButtonDisplay();

}

//菜单栏置顶联系人
void CAddressBookDlg::On32802()
{
	// TODO: 在此添加命令处理程序代码

	On32789TopStar();

}
