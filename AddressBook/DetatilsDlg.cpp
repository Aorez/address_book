// DetatilsDlg.cpp: 实现文件
//

#include "pch.h"
#include "AddressBook.h"
#include "DetatilsDlg.h"
#include "afxdialogex.h"

#include<vector>

#include"Person.h"
#include"Function.h"
#include"AddDlg.h"

extern std::vector<Person> addressBook;
extern int staticIndex;
extern CFont tipsFont;
extern bool isModifying;

// DetatilsDlg 对话框

IMPLEMENT_DYNAMIC(DetatilsDlg, CDialogEx)

DetatilsDlg::DetatilsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DETAILS_DIALOG, pParent)
{

}

DetatilsDlg::~DetatilsDlg()
{
}

void DetatilsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, DETAILS_LIST, detailsList);
	DDX_Control(pDX, DETAILS_PICTURE, detailsPicture);
}


BEGIN_MESSAGE_MAP(DetatilsDlg, CDialogEx)
	ON_WM_PAINT()
	ON_COMMAND(ID_32779, &DetatilsDlg::On32779DetailsMenu)
	ON_NOTIFY(NM_RCLICK, DETAILS_LIST, &DetatilsDlg::OnNMRClickList)
	ON_COMMAND(ID_32790, &DetatilsDlg::On32790Copy)
	ON_COMMAND(ID_32791, &DetatilsDlg::On32791CopyAll)
END_MESSAGE_MAP()


// DetatilsDlg 消息处理程序


BOOL DetatilsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	detailsList.SetFont(&tipsFont);

	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	detailsList.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	detailsList.SetExtendedStyle(detailsList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 为列表视图控件添加三列   
	const int numberOfListColumns = 4;
	const int multiple = 3;
	detailsList.InsertColumn(0, _T("##"), LVCFMT_CENTER, rect.Width() / numberOfListColumns, 0);
	detailsList.InsertColumn(1, _T("左上角修改信息"), LVCFMT_CENTER, rect.Width() / numberOfListColumns * multiple, 1);

	// 在列表视图控件中插入列表项，并设置列表子项文本  

	const int lengthOfDetailsArray = 7;
	CString CdetailArray[lengthOfDetailsArray];
	CString CitemArray[lengthOfDetailsArray] = { L"", L"姓名", L"联系电话1", L"联系电话2", L"邮箱", L"地址", L"备注" };
	Function f;
	detailsList.DeleteAllItems();
	for (int i = 1; i < lengthOfDetailsArray; i++) {
		CdetailArray[i] = f.display(staticIndex, i).c_str();
		detailsList.InsertItem(i-1, CitemArray[i]);
		detailsList.SetItemText(i-1, 1, CdetailArray[i]);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void DetatilsDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()

	CBitmap bitmap;    // CBitmap对象，用于加载位图  
	HBITMAP hbmp;      // 保存CBitmap加载的位图句柄  
	Function f;
	bitmap.LoadBitmap(atoi(f.display(staticIndex, 0).c_str()));//位图加载
	hbmp = (HBITMAP)bitmap.GetSafeHandle();// 获取bitmap位图句柄 
	detailsPicture.SetBitmap(hbmp);//设置图片控件要显示的位图：IDB_BITMAP2

}

//菜单栏修改
void DetatilsDlg::On32779DetailsMenu()
{
	// TODO: 在此添加命令处理程序代码

	isModifying = true;
	AddDlg ad;
	ad.DoModal();
	const int lengthOfDetailsArray = 7;
	CString CdetailArray[lengthOfDetailsArray];
	CString CitemArray[lengthOfDetailsArray] = { L"", L"姓名", L"联系电话1", L"联系电话2", L"邮箱", L"地址", L"备注" };
	Function f;
	detailsList.DeleteAllItems();
	for (int i = 1; i < lengthOfDetailsArray; i++) {
		CdetailArray[i] = f.display(staticIndex, i).c_str();
		detailsList.InsertItem(i - 1, CitemArray[i]);
		detailsList.SetItemText(i - 1, 1, CdetailArray[i]);
	}
	OnPaint();

}

//右键菜单
void DetatilsDlg::OnNMRClickList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->iItem != -1)
	{

		CPoint pt;
		GetCursorPos(&pt);
		CMenu menu;
		menu.LoadMenu(DETAILS_MENU2);
		CMenu* popmenu;
		popmenu = menu.GetSubMenu(0);
		popmenu->TrackPopupMenu(TPM_RIGHTBUTTON, pt.x, pt.y, this);
	}

	*pResult = 0;
}

//右键复制
void DetatilsDlg::On32790Copy()
{
	// TODO: 在此添加命令处理程序代码

	int nItem;
	CString strText;
	DWORD dwPos = GetMessagePos();
	CPoint point(LOWORD(dwPos), HIWORD(dwPos));
	detailsList.ScreenToClient(&point);

	//定义结构体  
	LVHITTESTINFO lvinfo;
	lvinfo.pt = point;
	lvinfo.flags = LVHT_ABOVE;

	//获取行号信息  
	//nItem = homeListControl.HitTest(&lvinfo);
	nItem = detailsList.SubItemHitTest(&lvinfo);
	nItem = detailsList.GetSelectionMark();
	if (nItem != -1)
		strText = detailsList.GetItemText(nItem, lvinfo.iSubItem);//获取对应单元格的内容

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


void DetatilsDlg::On32791CopyAll()
{
	// TODO: 在此添加命令处理程序代码

	int nItem;
	CString strText(_T(""));

	//获取行号信息  
	for (int i = 0; i < 6; i++) {
		strText += detailsList.GetItemText(i, 0) + _T("：") + detailsList.GetItemText(i, 1) + L"；";
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
