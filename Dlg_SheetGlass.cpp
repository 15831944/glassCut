// Dlg_SheetGlass.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "Dlg_SheetGlass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_SheetGlass dialog


CDlg_SheetGlass::CDlg_SheetGlass(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_SheetGlass::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_SheetGlass)
	m_oleTimeStart = 0;
	m_oleTimeEnd = 0;
	//}}AFX_DATA_INIT
	m_pConSheet = NULL;
	m_oleTimeEnd = CTime::GetCurrentTime();
	CTimeSpan  SpanTime(7,0,0,0);	
	m_oleTimeStart = m_oleTimeEnd - SpanTime;
}
CDlg_SheetGlass::~CDlg_SheetGlass()
{
	if (m_pConSheet != NULL)
	{
		m_pConSheet->Close();
		m_pConSheet = NULL;
		::CoUninitialize();//释放COM环境
	}
	m_vtGlassSheet.clear();
}

void CDlg_SheetGlass::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_SheetGlass)
	DDX_GridControl(pDX, IDC_GRID_SHEET, m_GridSheet);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_oleTimeStart);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_oleTimeEnd);
	//}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CDlg_SheetGlass, CDialog)
	//{{AFX_MSG_MAP(CDlg_SheetGlass)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON10, OnButton10)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_SheetGlass message handlers

void CDlg_SheetGlass::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
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

BOOL CDlg_SheetGlass::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetCtlFont(this);
	OnLanguage();
	InitButton();
	InitDataAdo();
	OnInitGrid();
	SetWindowPos(CWnd::GetOwner(),0,0,g_screen.x,g_screen.y,SWP_SHOWWINDOW);	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg_SheetGlass::OnInitGrid()
{
	TRY {
		m_GridSheet.SetRowCount(m_vtGlassSheet.size()+1);
		m_GridSheet.SetColumnCount(4);
		m_GridSheet.SetFixedRowCount(1);
		m_GridSheet.SetFixedColumnCount(1);		
	}
	CATCH (CMemoryException, e)
	{
		e->ReportError();
		e->Delete();
		return;
	}
    END_CATCH
	
	for (int row = 0; row < m_GridSheet.GetRowCount(); row++)//行
	{
		for (int col = 0; col < m_GridSheet.GetColumnCount(); col++)//列
		{ 			
			GV_ITEM Item;
			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = row;
			Item.col = col;
			Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE;
			if (row < 1)/* 固定行 第一行表头*/
			{
				if(col==0)
				{
					if (g_iLanguage == 0)
					{
						Item.szText="编号";
					}
					else
					{
						Item.szText = "NO.";
					}
				}	
				else if (col==1)
				{
					if (g_iLanguage == 0)
					{
						Item.szText="时间";
					} 
					else
					{
						Item.szText="TIME";
					}
				} 
				else if(col==2)
				{
					if (g_iLanguage == 0)
					{
						Item.szText="原片";
					} 
					else
					{
						Item.szText="SHEET";
					}
				}
				else if(col==3)
				{
					if (g_iLanguage == 0)
					{
						Item.szText="数量";
					} 
					else
					{
						Item.szText="COUNT";
					}
				}			
				
			}
			else
			{
				if(col==0)
				{
					Item.szText.Format("%d",row);
				}	
				else if (col==1)
				{
					COleDateTime time = m_vtGlassSheet[m_vtGlassSheet.size()-row].timeCut;
					Item.szText.Format("%.4d-%.2d-%.2d",time.GetYear(),time.GetMonth(),time.GetDay());
				} 
				else if(col==2)
				{
					Item.szText=m_vtGlassSheet[m_vtGlassSheet.size()-row].strRect;
				}
				else if(col==3)
				{
					Item.szText.Format("%d",m_vtGlassSheet[m_vtGlassSheet.size()-row].nNum);
				}
			}
			m_GridSheet.SetItem(&Item);
		}
	}
	m_GridSheet.SetColumnWidth(0, 50);
	m_GridSheet.SetColumnWidth(1, 110);
	m_GridSheet.SetColumnWidth(2, 110);
	m_GridSheet.SetColumnWidth(3, 110);
}

void CDlg_SheetGlass::OnLanguage()
{
	if (g_iLanguage == 1)
	{
		SetDlgItemText(IDC_CAPTION_SHEET,"Sheet Statistik");
		SetDlgItemText(IDC_STATIC_START,"Start Date");
		SetDlgItemText(IDC_STATIC_END,"End Date");
	}
}

void CDlg_SheetGlass::InitDataAdo()
{
	::CoInitialize(NULL);
	int i = 0;
	HRESULT hr;  
	try
	{
		hr = m_pConSheet.CreateInstance(__uuidof(Connection));
		if(SUCCEEDED(hr))
		{
			m_pConSheet->Open("Provider=MSDASQL.1;Persist Security Info=False;Data Source=sheet","","",NULL);			
			ReadDatabase();
		}
	}	
	catch(_com_error e)
	{
		CString strErrorMessage;
		strErrorMessage.Format("连接数据库失败！\r\n错误信息%s",e.ErrorMessage());
		MessageBox(strErrorMessage);
		return ;
	}
}

void CDlg_SheetGlass::InitButton()
{
	HRGN c;
	
	c = CreateRectRgn(0, 0, 0, 0);	
	GetBitMapRgn(GetDC(),c,IDB_BITMAP_ZEOR1);
	
	//清除
	CString str;
	if (g_iLanguage == 0)
		str = "清除";
	else
		str = "Clear";
	m_pButton[0].SetFont(&g_fontEdit);
	m_pButton[0].SetBitMapID(IDB_BITMAP_DELGRAP1,IDB_BITMAP_DELGRAP2);	
	m_pButton[0].Create(str, WS_CHILD | WS_VISIBLE, CPoint(745, 705), c, this, IDC_BUTTON8); 
	
	//返回	
	m_pButton[1].SetFont(&g_fontEdit);
	m_pButton[1].SetBitMapID(IDB_BITMAP_BACK1,IDB_BITMAP_BACK2);	
	m_pButton[1].Create(g_arr_strMotion[10][g_iLanguage+1], WS_CHILD | WS_VISIBLE, CPoint(900, 705), c, this, IDC_BUTTON10); 

	//查询	
	if (g_iLanguage == 0)
		str = "查询";
	else
		str = "Query";
	m_pButton[2].SetFont(&g_fontEdit);
	m_pButton[2].SetBitMapID(IDB_BITMAP_QUREY1,IDB_BITMAP_QUREY2);
	m_pButton[2].Create(str, WS_CHILD | WS_VISIBLE, CPoint(850, 325), c, this, IDC_BUTTON1); 

	//删除	
	if (g_iLanguage == 0)
		str = "删除";
	else
		str = "Delete";
	m_pButton[3].SetFont(&g_fontEdit);
	m_pButton[3].SetBitMapID(IDB_BITMAP_DELGRAP1,IDB_BITMAP_DELGRAP1);
	m_pButton[3].Create(str, WS_CHILD | WS_VISIBLE, CPoint(850, 425), c, this, IDC_BUTTON2); 

	
	DeleteObject(c);
}

//返回
void CDlg_SheetGlass::OnButton10()
{
	if (m_pConSheet != NULL)
	{
		m_pConSheet->Close();
		m_pConSheet = NULL;
 		::CoUninitialize();//释放COM环境
	}
	m_vtGlassSheet.clear();
	CDialog::OnOK();
}

//清除
void CDlg_SheetGlass::OnButton8()
{
	try
	{
		m_pConSheet->Execute("delete * from sheet",NULL,adCmdText);
		m_vtGlassSheet.clear();
		OnInitGrid();
	}
	catch(_com_error e)
	{
		CString strErrorMessage;
		strErrorMessage.Format("删除记录失败!\r\n错误信息%s",e.ErrorMessage());
		MessageBox(strErrorMessage);		
	}
}

//读数据库记录
void CDlg_SheetGlass::ReadDatabase()
{
	_RecordsetPtr  pRecSheet;   
	CString str;
	str.Format("select * from sheet where [date] between format('%d-%d-%d','yyyy-mm-dd') and format('%d-%d-%d 23:59:59','yyyy-mm-dd hh:mm:ss')",
		m_oleTimeStart.GetYear(),m_oleTimeStart.GetMonth(),m_oleTimeStart.GetDay(),m_oleTimeEnd.GetYear(),m_oleTimeEnd.GetMonth(),m_oleTimeEnd.GetDay());
    char ch[200]={0};
	strcpy(ch,str);
	pRecSheet=SearchRec(ch);//建立记录集，查找记录
	if (pRecSheet==NULL||pRecSheet->adoEOF)
	{
		if (g_iLanguage == 0)
		{
			MessageBox("数据库中没有找到所查信息");
		}
		else
		{
			MessageBox("No Data");
		}
		m_vtGlassSheet.clear();
		return;
	}
	m_vtGlassSheet.clear();
	while(pRecSheet!=NULL&&!pRecSheet->adoEOF)
	{
		_variant_t var;
		stuSheetGlass stuData;
		var = pRecSheet->GetCollect("date");
		stuData.timeCut = var.date;	
		var = pRecSheet->GetCollect("glass");
		stuData.strRect = var.bstrVal;
		var = pRecSheet->GetCollect("num");
		stuData.nNum = var.lVal;
		m_vtGlassSheet.push_back((stuSheetGlass)stuData);
		pRecSheet->MoveNext();
	}
	pRecSheet->Close();
	pRecSheet = NULL;	
}

_RecordsetPtr CDlg_SheetGlass::SearchRec(char *chRec)
{
	
	_RecordsetPtr  pRec;   //表//创建并打开记录集对象	
	try
	{
		pRec.CreateInstance(__uuidof(Recordset));
		pRec->Open(chRec,m_pConSheet.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch(_com_error e)
	{
		CString strErrorMessage;
		strErrorMessage.Format("查询取得记录集失败!\r\n错误信息%s",e.ErrorMessage());
		MessageBox(strErrorMessage);
		return 0;
	}
	
	//****************************************************************	
	return pRec;	
}

//数据库排序
void CDlg_SheetGlass::SortData()
{
	_RecordsetPtr  pRec;   //表//创建并打开记录集对象	
	try
	{
		pRec.CreateInstance(__uuidof(Recordset));
		pRec->CursorLocation= adUseClient; //创建以后才能使用。不使用无法排序、、、、、、、、
		pRec->Open("select* from sheet order by date DESC",m_pConSheet.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch(_com_error e)
	{
		CString strErrorMessage;
		strErrorMessage.Format("查询取得记录集失败!\r\n错误信息%s",e.ErrorMessage());
		MessageBox(strErrorMessage);
		return ;
	}
	pRec->Close();
	pRec = NULL;
}

//查询
void CDlg_SheetGlass::OnButton1()
{
    UpdateData();
	ReadDatabase();
	OnInitGrid();
}

//删除
void CDlg_SheetGlass::OnButton2()
{
	_RecordsetPtr  pRecSheet;   
	CString str;
    UpdateData(TRUE);
	str.Format("select * from sheet where [date] between format('%d-%d-%d','yyyy-mm-dd') and format('%d-%d-%d 23:59:59','yyyy-mm-dd hh:mm:ss')",
		m_oleTimeStart.GetYear(),m_oleTimeStart.GetMonth(),m_oleTimeStart.GetDay(),m_oleTimeEnd.GetYear(),m_oleTimeEnd.GetMonth(),m_oleTimeEnd.GetDay());
    char ch[200]={0};
	strcpy(ch,str);
	pRecSheet=SearchRec(ch);//建立记录集，查找记录
	if (pRecSheet==NULL||pRecSheet->adoEOF)
	{
		if (g_iLanguage == 0)
		{
			MessageBox("数据库中没有找到所查信息");
		}
		else
		{
			MessageBox("No Data");
		}
		return;
	}
	while(pRecSheet!=NULL&&!pRecSheet->adoEOF)
	{
		pRecSheet->Delete(adAffectCurrent);///删除当前记录
		pRecSheet->MoveNext();
	}
	m_vtGlassSheet.clear();
	pRecSheet->Close();
	pRecSheet = NULL;	
	OnInitGrid();
}

HBRUSH CDlg_SheetGlass::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
#ifdef POWERLAND
	if (nCtlColor==CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)GetStockObject(NULL_BRUSH);		
	}
#endif	
	return hbr;
}
