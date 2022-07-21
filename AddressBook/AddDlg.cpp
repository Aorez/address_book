// AddDlg.cpp: 实现文件
//

#include "pch.h"
#include "AddressBook.h"
#include "AddDlg.h"
#include "afxdialogex.h"

#include<string>
#include<vector>

#include"AddressBookDlg.h"
#include"Function.h"
#include"Person.h"

extern bool hasAdded;
extern int staticIndex;
extern std::vector<Person> addressBook;
extern CFont tipsFont;
extern bool isModifying;

// AddDlg 对话框

IMPLEMENT_DYNAMIC(AddDlg, CDialogEx)

AddDlg::AddDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(ADD_DIALOG, pParent)
{

}

AddDlg::~AddDlg()
{
}

void AddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ADD_LIST, addList);
	DDX_Control(pDX, ADD_EDIT, addEdit);
	DDX_Control(pDX, ADD_BUTTON2, addButton2);
	DDX_Control(pDX, ADD_CANCEL, addCancel);
	DDX_Control(pDX, ADD_BUTTON3, addButton3);
	DDX_Control(pDX, ADD_PICTURE, addPicture);
}


BEGIN_MESSAGE_MAP(AddDlg, CDialogEx)
	ON_BN_CLICKED(ADD_BUTTON2, &AddDlg::OnBnClickedButtonAdd)
	ON_NOTIFY(NM_DBLCLK, ADD_LIST, &AddDlg::OnNMDblclkList)
	ON_EN_KILLFOCUS(ADD_EDIT, &AddDlg::OnEnKillfocusEdit)
	ON_BN_CLICKED(ADD_BUTTON3, &AddDlg::OnBnClickedButton3)
	ON_WM_PAINT()
	ON_BN_CLICKED(ADD_CANCEL, &AddDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// AddDlg 消息处理程序

//添加按钮
void AddDlg::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码

	const int lengthOfAddArray = 7;
	CString CaddArray[lengthOfAddArray];

	USES_CONVERSION;
	std::string addArray[7];
	for (int i = 1; i < lengthOfAddArray; i++) {
		CaddArray[i] = addList.GetItemText(i - 1, 1);
		addArray[i] = W2A(CaddArray[i]);
	}
	if (addArray[1] == "" || addArray[2] == "") {
		MessageBox(L"姓名和联系电话1不能为空！", L"输入错误", MB_ICONEXCLAMATION);
	}
	else {
		Function f;
		if (isModifying) {
			int indexReturn = f.modify(staticIndex, numOfFace2, addArray[1], addArray[2], addArray[3], addArray[4], addArray[5], addArray[6]);
			if (indexReturn == -1) {
				MessageBox(L"姓名或联系电话重复！", L"输入错误", MB_ICONEXCLAMATION);
			}
			else {
				staticIndex = indexReturn;
				isModifying = false;
				MessageBox(L"保存成功！", L"操作成功", MB_OK);
				CDialogEx::OnOK();
			}
		}
		else {
			int indexReturn = f.add(numOfFace2, addArray[1], addArray[2], addArray[3], addArray[4], addArray[5], addArray[6]);
			if (indexReturn == -1) {
				MessageBox(L"姓名或联系电话重复！", L"输入错误", MB_ICONEXCLAMATION);
			}
			else {
				staticIndex = indexReturn;
				hasAdded = true;
				MessageBox(L"保存成功！", L"操作成功", MB_OK);
				CDialogEx::OnOK();
			}
		}
	}
	
}


void AddDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	hasAdded = false;
	isModifying = false;

	CDialogEx::OnCancel();
}


BOOL AddDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	if (isModifying) {
		Function f;
		numOfFace2 = atoi(f.display(staticIndex, 0).c_str());
	}
	else numOfFace2 = 156;

	addEdit.ShowWindow(SW_HIDE);

	addEdit.SetFont(&tipsFont);
	addEdit.SetFont(&tipsFont);
	addList.SetFont(&tipsFont);
	addButton2.SetFont(&tipsFont);
	addButton3.SetFont(&tipsFont);
	addCancel.SetFont(&tipsFont);

	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	addList.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	addList.SetExtendedStyle(addList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 为列表视图控件添加三列   
	const int numberOfListColumns = 4;
	const int multiple = 3;
	addList.InsertColumn(0, _T("##"), LVCFMT_CENTER, rect.Width() / numberOfListColumns, 0);
	addList.InsertColumn(1, _T("双击修改信息"), LVCFMT_CENTER, rect.Width() / numberOfListColumns * multiple, 1);

	// 在列表视图控件中插入列表项，并设置列表子项文本  

	const int lengthOfDetailsArray = 7;
	CString CdetailArray[lengthOfDetailsArray];
	CString CitemArray[lengthOfDetailsArray] = { L"", L"姓名", L"联系电话1", L"联系电话2", L"邮箱", L"地址", L"备注" };
	Function f;
	addList.DeleteAllItems();
	for (int i = 1; i < lengthOfDetailsArray; i++) {
		addList.InsertItem(i - 1, CitemArray[i]);
		if (isModifying) {
			CdetailArray[i] = f.display(staticIndex, i).c_str();
			addList.SetItemText(i - 1, 1, CdetailArray[i]);
		}		
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

//双击“List Control”控件输入信息
void AddDlg::OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CRect rc;

	m_Row = pNMListView->iItem;//获得选中的行
	m_Col = pNMListView->iSubItem;//获得选中列
	int n = addList.GetItemCount();//获取当前一共多少行
	if (pNMListView->iSubItem != 0) //如果选择的是子项;
	{
		addList.GetSubItemRect(m_Row, m_Col, LVIR_LABEL, rc);//获得子项的RECT；
		addList.SetParent(&addList);//转换坐标为列表框中的坐标
		addList.ClientToScreen(&rc);
		ScreenToClient(&rc);
		addEdit.MoveWindow(rc);//移动Edit到RECT坐在的位置;
		addEdit.SetWindowText(addList.GetItemText(m_Row, m_Col));//将该子项中的值放在Edit控件中；
		addEdit.ShowWindow(SW_SHOW);//显示Edit控件；
		addEdit.SetFocus();//设置Edit焦点
		addEdit.ShowCaret();//显示光标
		addEdit.SetSel(-1);//将光标移动到最后

		if (m_Row == n - 1)
		{
			addList.InsertItem(m_Row + 1, _T(""));
		}

	}

	*pResult = 0;

}


void AddDlg::OnEnKillfocusEdit()
{
	// TODO: 在此添加控件通知处理程序代码

	CString tem;
	addEdit.GetWindowText(tem); //得到用户输入的新的内容
	addList.SetItemText(m_Row, m_Col, tem); //设置编辑框的新内容
	addEdit.ShowWindow(SW_HIDE); //应藏编辑框

}


void AddDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码

	CBitmap bitmap;    // CBitmap对象，用于加载位图  
	HBITMAP hbmp;      // 保存CBitmap加载的位图句柄  

	numOfFace2++;
	if (numOfFace2 > 243) numOfFace2 -= 87;
	bitmap.LoadBitmap(numOfFace2); //位图加载
	hbmp = (HBITMAP)bitmap.GetSafeHandle();// 获取bitmap位图句柄 
	addPicture.SetBitmap(hbmp);//设置图片控件要显示的位图：IDB_BITMAP2

}


void AddDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()

	CBitmap bitmap;    // CBitmap对象，用于加载位图  
	HBITMAP hbmp;      // 保存CBitmap加载的位图句柄  

	bitmap.LoadBitmap(numOfFace2); //位图加载
	hbmp = (HBITMAP)bitmap.GetSafeHandle();// 获取bitmap位图句柄 
	addPicture.SetBitmap(hbmp);//设置图片控件要显示的位图：IDB_BITMAP2

}


void AddDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码

	OnCancel();

}


BOOL AddDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		OnEnKillfocusEdit();
		UpdateData(false);
		return true;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
