// dlg_manager.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "dlg_manager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// dlg_manager dialog


dlg_manager::dlg_manager(CWnd* pParent /*=NULL*/)
	: CDialog(dlg_manager::IDD, pParent)
{
	//{{AFX_DATA_INIT(dlg_manager)
	//}}AFX_DATA_INIT
}


void dlg_manager::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(dlg_manager)
	DDX_Control(pDX, IDC_LISTREMOVE, m_remove);
	DDX_Control(pDX, IDC_LISTDISK, m_disk);
	DDX_Control(pDX, IDC_DEMO10CTRL1, m_demo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(dlg_manager, CDialog)
	//{{AFX_MSG_MAP(dlg_manager)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_NOTIFY(NM_CLICK, IDC_LISTDISK, OnClickListdisk)
	ON_NOTIFY(NM_CLICK, IDC_LISTREMOVE, OnClickListremove)
	ON_BN_CLICKED(IDC_BUTTON10, OnButton10)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// dlg_manager message handlers

BOOL dlg_manager::OnInitDialog() 
{
	CDialog::OnInitDialog();

/*======================================================================*/	
	BOOL      bWorking1;
    CFileFind finder1;
	int i = 0;

	InitButton();
	SetWindowPos(CWnd::GetOwner(),0,0,1024,768,SWP_SHOWWINDOW);

    OnLanguage();
	g_iIsDxf = 0;//0：参数文件；1：DXF；2：G代码；
	focus = 0;     /* 焦点为硬盘文件夹 */
	
    OnFileShow();	                                       //显示优盘文件
	m_remove.SetFont(&g_fontList);
	m_disk.SetFont(&g_fontList);
	m_disk.DeleteAllItems();
    bWorking1 = finder1.FindFile(_T("C:\\Program Files\\GlassCutter\\glass\\*.c*"));
	
    while (bWorking1)
    {
        bWorking1 = finder1.FindNextFile();
		
        m_disk.InsertItem(i,(LPCTSTR) finder1.GetFileName());
		i++;
    }
	m_disk.SetFocus();
	m_disk.SetItemState(0,3,0xffff);                      //SetFocus();
	m_disk.SetFocus();
	//===============================================================
	int l,iState;
	long lengh;
	CString len;
	
	int nItemSelected=m_disk.GetSelectedCount();	       //如果没有选择，不用处理
	if(nItemSelected<1)		
		return TRUE;
	l = m_disk.GetItemCount();	                           //列表单项目的个数
	for(i=l-1;i>=0;i--)
	{
		iState=m_disk.GetItemState(i,LVIS_SELECTED);
		if(iState!=0)
            filename = m_disk.GetItemText(i,0);
	}
	
    bWorking1 = finder1.FindFile(_T("C:\\Program Files\\GlassCutter\\glass\\"+filename));
    while (bWorking1)
    {
        bWorking1 = finder1.FindNextFile();
        lengh = finder1.GetLength();
		len.Format("%d",lengh);
    }
	
	m_remove.SetItemState(0,3,0xffff);
	m_disk.SetItemState(0,3,0xffff);
	m_disk.SetFocus();
	m_disk.SetItemState(0,3,0xffff);                      //SetFocus();
	m_disk.SetFocus();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void dlg_manager::OnButton1() 
{
	m_disk.SetFocus();
	m_disk.SetItemState(0,3,0xffff);                      //SetFocus();
	m_disk.SetFocus();
	focus = 0;
}

void dlg_manager::OnButton2() 
{
	m_remove.SetFocus();
	m_remove.SetItemState(0,3,0xffff);                      //SetFocus();
	m_remove.SetFocus();
	focus = 1;
}

void dlg_manager::OnButton3() 
{

	CString        strDir;
	if(g_iIsDxf==0)               strDir = g_strOriginalPathD + "glass\\";
	else if(g_iIsDxf==1)          strDir = g_strOriginalPathD + "dxf\\";
	else if(g_iIsDxf==2)          strDir = g_strOriginalPathD + "gcode\\";
	
	if(focus==0)
	{
		DeleteFile(strDir + FindFile1());
		m_disk.SetFocus();
		focus = 0;
	}
	else
	{
		if(movediskdir().IsEmpty())
		{
			OnShowMessageBox(26,g_iLanguage,FALSE);
		}
		else
		{
			DeleteFile(movediskdir() + FindFile2());
			m_remove.SetFocus();
			focus = 1;
		}
	}
	OnButtonRefresh();

}

void dlg_manager::OnButton4() 
{

	CString        strDir;
	if(g_iIsDxf==0)               strDir = g_strOriginalPathD + "glass\\";
	else if(g_iIsDxf==1)          strDir = g_strOriginalPathD + "dxf\\";
	else if(g_iIsDxf==2)          strDir = g_strOriginalPathD + "gcode\\";
	if(movediskdir().IsEmpty())
	{
		OnShowMessageBox(26,g_iLanguage,FALSE);
		return;
	}
	CopyFile(strDir + FindFile1(),movediskdir() + FindFile1(),TRUE);
	m_disk.SetFocus();
	focus = 0;
	OnButtonRefresh();

}

void dlg_manager::OnButton5() 
{
	CString        strDir;
	if(g_iIsDxf==0)               strDir = g_strOriginalPathD + "glass\\";
	else if(g_iIsDxf==1)          strDir = g_strOriginalPathD + "dxf\\";
	else if(g_iIsDxf==2)          strDir = g_strOriginalPathD + "gcode\\";
	if(movediskdir().IsEmpty())
	{
		OnShowMessageBox(26,g_iLanguage,FALSE);
		return;
	}
	CopyFile(movediskdir() + FindFile2(),strDir + FindFile2(),TRUE);
	m_remove.SetFocus();
	focus = 1;
	OnButtonRefresh();
}

void dlg_manager::OnButton6() 
{
	m_remove.DeleteAllItems();
	m_disk.SetFocus();
	focus = 0;
}

void dlg_manager::OnButton7() 
{
	
	BOOL      bWorking1;
	CFileFind finder1;
	int       i;
	if(g_iIsDxf==0)           g_iIsDxf = 1;//参数文件
	else if(g_iIsDxf==1)      g_iIsDxf = 2;//DXF文件
	else if(g_iIsDxf==2)      g_iIsDxf = 0;//G代码文件
	OnFileShow();	                                       //显示优盘文件
	m_disk.DeleteAllItems();
	
	if(g_iIsDxf==0)	          bWorking1 = finder1.FindFile(_T(g_strOriginalPathD + "glass\\*.c*"));         /* 获取指定目录硬盘文件 */
	else if(g_iIsDxf==1)      bWorking1 = finder1.FindFile(_T(g_strOriginalPathD + "dxf\\*.dxf"));         /* 获取指定目录硬盘文件 */
	else if(g_iIsDxf==2)      bWorking1 = finder1.FindFile(_T(g_strOriginalPathD + "gcode\\*.g"));         /* 获取指定目录硬盘文件 */
	
	i = 0;
	while (bWorking1)
	{
		bWorking1 = finder1.FindNextFile();
		
		m_disk.InsertItem(i,(LPCTSTR) finder1.GetFileName());
		i++;
		//		if (finder.MatchesMask(FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM))
		//           _tprintf(_T("%s\n"), (LPCTSTR) finder.GetFileName());
	}
	//====================================================================
	int l,iState;
	long lengh;
	CString len;
	
	int nItemSelected=m_disk.GetSelectedCount();	       //如果没有选择，不用处理
	if(nItemSelected<1)		
		return;
	l = m_disk.GetItemCount();	                           //列表单项目的个数
	for(i=l-1;i>=0;i--)
	{
		iState=m_disk.GetItemState(i,LVIS_SELECTED);
		if(iState!=0)
			filename = m_disk.GetItemText(i,0);
	}
	
	bWorking1 = finder1.FindFile(_T("D:\\Program Files\\bender\\dmm\\"+filename));
	while (bWorking1)
	{
		bWorking1 = finder1.FindNextFile();
		lengh = finder1.GetLength();
		len.Format("%d",lengh);
	}
	
	m_remove.SetItemState(0,3,0xffff);
	m_disk.SetItemState(0,3,0xffff);
	m_disk.SetFocus();
	
}

CString dlg_manager::FindFile1()
{
	int i,n,iState;
    CFileFind finder;
	CString file = "";
	
	int nItemSelected=m_disk.GetSelectedCount();	       //如果没有选择，不用处理
	if(nItemSelected<1)		
		return file;
	n = m_disk.GetItemCount();	                           //列表单项目的个数
	for(i=n-1;i>=0;i--)
	{
		iState=m_disk.GetItemState(i,LVIS_SELECTED);
		if(iState!=0)
            file = m_disk.GetItemText(i,0);
	}
    return file;
}

CString dlg_manager::FindFile2()
{
	int         n,iState,i = 0;
	CString     ss,cpy,strfile = "";

	cpy = movediskdir();
	if(cpy=="")             return strfile;
	
	int nItemSelected=m_remove.GetSelectedCount();	       //如果没有选择，不用处理
	if(nItemSelected<1)		return strfile;
	
	n = m_remove.GetItemCount();	                           //列表单项目的个数
	for(i=n-1;i>=0;i--)
	{
		iState=m_remove.GetItemState(i,LVIS_SELECTED);
		if(iState!=0)
            strfile = m_remove.GetItemText(i,0);
	}
	return strfile;
}

void dlg_manager::OnLanguage()
{
	int		i;
	int		nIndex;
	nIndex = g_iLanguage + 1;
	for(i=0;i<AR_MANAGER;i++)
	{
		if(g_arr_strManager[i][nIndex] == "NULL")
			g_arr_strManager[i][nIndex] = "";
		CWnd::SetDlgItemText(atoi(g_arr_strManager[i][0]),g_arr_strManager[i][nIndex]);
	}
}

BOOL dlg_manager::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->lParam==VK_RETURN||pMsg->wParam==VK_RETURN)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

void dlg_manager::OnButtonRefresh() 
{
	BOOL      bWorking1;
    CFileFind finder1;
	int       i;
    OnFileShow();	                                       //显示优盘文件
	m_disk.DeleteAllItems();
	
	if(g_iIsDxf==0)	          bWorking1 = finder1.FindFile(_T(g_strOriginalPathD + "glass\\*.c*"));         /* 获取指定目录硬盘文件 */
	else if(g_iIsDxf==1)      bWorking1 = finder1.FindFile(_T(g_strOriginalPathD + "dxf\\*.dxf"));         /* 获取指定目录硬盘文件 */
	else if(g_iIsDxf==2)      bWorking1 = finder1.FindFile(_T(g_strOriginalPathD + "gcode\\*.g"));         /* 获取指定目录硬盘文件 */
	
	i = 0;
    while (bWorking1)
    {
        bWorking1 = finder1.FindNextFile();
		
        m_disk.InsertItem(i,(LPCTSTR) finder1.GetFileName());
		i++;
    }
	//====================================================================
	int l,iState;
	long lengh;
	CString len;
	
	int nItemSelected=m_disk.GetSelectedCount();	       //如果没有选择，不用处理
	if(nItemSelected<1)		
		return;
	l = m_disk.GetItemCount();	                           //列表单项目的个数
	for(i=l-1;i>=0;i--)
	{
		iState=m_disk.GetItemState(i,LVIS_SELECTED);
		if(iState!=0)
            filename = m_disk.GetItemText(i,0);
	}
	
	if(g_iIsDxf==0)	          bWorking1 = finder1.FindFile(_T(g_strOriginalPathD + "glass\\*.c*"));         /* 获取指定目录硬盘文件 */
	else if(g_iIsDxf==1)      bWorking1 = finder1.FindFile(_T(g_strOriginalPathD + "dxf\\*.dxf"));         /* 获取指定目录硬盘文件 */
	else if(g_iIsDxf==2)      bWorking1 = finder1.FindFile(_T(g_strOriginalPathD + "gcode\\*.g"));         /* 获取指定目录硬盘文件 */
    while (bWorking1)
    {
        bWorking1 = finder1.FindNextFile();
        lengh = finder1.GetLength();
		len.Format("%d",lengh);
    }
	
	m_remove.SetItemState(0,3,0xffff);
	m_disk.SetItemState(0,3,0xffff);	
}

void dlg_manager::OnClickListdisk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_disk.SetFocus();
	focus = 0;
	*pResult = 0;
}

void dlg_manager::OnClickListremove(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_remove.SetFocus();
	focus = 1;
	*pResult = 0;
}

void dlg_manager::OnFileShow()                             //显示优盘文件
{
    BOOL        bWorking;
    CFileFind   finder;
    int         i = 0;
	CString     cpy;
	
	cpy = movediskdir();
	
	m_remove.DeleteAllItems();

	if(g_iIsDxf==0)	          	bWorking = finder.FindFile(_T(cpy+"*.c*"));         /* 获取指定目录硬盘文件 */
	else if(g_iIsDxf==1)      	bWorking = finder.FindFile(_T(cpy+"*.dxf"));         /* 获取指定目录硬盘文件 */
	else if(g_iIsDxf==2)      	bWorking = finder.FindFile(_T(cpy+"*.g"));         /* 获取指定目录硬盘文件 */
	
	i = 0;
    while (bWorking)
    {
        bWorking = finder.FindNextFile();
        m_remove.InsertItem(i,(LPCTSTR) finder.GetFileName());
		i++;
    }
	//====================================================================
	m_remove.SetItemState(0,3,0xffff);                      //SetFocus();
	//===============================================================
	int l,iState;
	long lengh;
	CString len;
	
	int nItemSelected=m_remove.GetSelectedCount();	       //如果没有选择，不用处理
	if(nItemSelected<1)		
		return;
	l = m_remove.GetItemCount();	                           //列表单项目的个数
	for(i=l-1;i>=0;i--)
	{
		iState=m_remove.GetItemState(i,LVIS_SELECTED);
		if(iState!=0)
            filename = m_remove.GetItemText(i,0);
	}
	
    bWorking = finder.FindFile(_T("D:\\Program Files\\bender\\dmm\\"+filename));
    while (bWorking)
    {
        bWorking = finder.FindNextFile();
        lengh = finder.GetLength();
		len.Format("%d",lengh);
    }
}

void dlg_manager::OnButton10() 
{
	CDialog::OnOK();
}

void dlg_manager::InitButton()
{

	HRGN c;
	
	c = CreateRectRgn(0, 0, 0, 0);	
	GetBitMapRgn(GetDC(),c,IDB_BITMAP_SETPRE1);
	//系统	
	m_pButton[0].SetFont(&g_fontEdit);
	m_pButton[0].HaveBitmap(1);
	m_pButton[0].SetBitMapID(IDB_BITMAP1,IDB_BITMAP2);	
	m_pButton[0].Create(g_arr_strMotion[4][g_iLanguage+1], WS_CHILD | WS_VISIBLE, CPoint(5, 705), c, this, IDC_BUTTON1); 
	//可移动盘
	m_pButton[1].HaveBitmap(1);
	m_pButton[1].SetFont(&g_fontEdit);
	m_pButton[1].SetBitMapID(IDB_BITMAP1,IDB_BITMAP2);
	m_pButton[1].Create(g_arr_strMotion[8][g_iLanguage+1], WS_CHILD | WS_VISIBLE, CPoint(130, 705), c, this, IDC_BUTTON2); 
	//删除文件
	m_pButton[2].HaveBitmap(1);
	m_pButton[2].SetFont(&g_fontEdit);
	m_pButton[2].SetBitMapID(IDB_BITMAP1,IDB_BITMAP2);
	m_pButton[2].Create(g_arr_strMotion[9][g_iLanguage+1], WS_CHILD | WS_VISIBLE, CPoint(255, 705), c, this, IDC_BUTTON3); 
	//读出
	m_pButton[3].HaveBitmap(1);
	m_pButton[3].SetFont(&g_fontEdit);
	m_pButton[3].SetBitMapID(IDB_BITMAP1,IDB_BITMAP2);	
	m_pButton[3].Create(g_arr_strMotion[7][g_iLanguage+1], WS_CHILD | WS_VISIBLE, CPoint(380, 705), c, this, IDC_BUTTON4); 	
	//写入	
	m_pButton[4].HaveBitmap(1);
	m_pButton[4].SetFont(&g_fontEdit);
	m_pButton[4].SetBitMapID(IDB_BITMAP1,IDB_BITMAP2);
	m_pButton[4].Create("", WS_CHILD | WS_VISIBLE, CPoint(505, 705), c, this, IDC_BUTTON5); 	
	//关闭优盘
	m_pButton[5].HaveBitmap(1);
	m_pButton[5].SetFont(&g_fontEdit);
	m_pButton[5].SetBitMapID(IDB_BITMAP1,IDB_BITMAP2);
	m_pButton[5].Create("", WS_CHILD | WS_VISIBLE, CPoint(630, 705), c, this, IDC_BUTTON6); 
	
	//手动刷新
	m_pButton[6].HaveBitmap(1);
	m_pButton[6].SetFont(&g_fontEdit);
	m_pButton[6].SetBitMapID(IDB_BITMAP1,IDB_BITMAP2);
	m_pButton[6].Create(g_arr_strMotion[11][g_iLanguage+1], WS_CHILD | WS_VISIBLE, CPoint(765, 705), c, this, IDC_BUTTON7); 
	
	//返回	
	m_pButton[7].SetFont(&g_fontEdit);
	m_pButton[7].SetBitMapID(IDB_BITMAP_BACK1,IDB_BITMAP_BACK2);	
	m_pButton[7].Create(g_arr_strMotion[15][g_iLanguage+1], WS_CHILD | WS_VISIBLE, CPoint(900, 705), c, this, IDC_BUTTON10); 
    
	DeleteObject(c);  
}

void dlg_manager::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	//贴背景图片
	CDC  MemDc;
	CBitmap bitmap;	
	MemDc.CreateCompatibleDC(&dc);
	bitmap.LoadBitmap(IDB_BITMAP_DIALOG);
	CBitmap *pOldBit = MemDc.SelectObject(&bitmap);
	dc.BitBlt(0,0,1024,768,&MemDc,0,0,SRCCOPY);
	MemDc.SelectObject(pOldBit);
	bitmap.DeleteObject();
	MemDc.DeleteDC();
	CDialog::OnPaint();			
	// Do not call CDialog::OnPaint() for painting messages
}


HBRUSH dlg_manager::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);	
	if (nCtlColor==CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)GetStockObject(NULL_BRUSH);		
	}
	return hbr;
}
