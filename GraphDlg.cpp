// GraphDlg.cpp : implementation file

#include "stdafx.h"
#include "bender.h"
#include "GraphDlg.h"
#include "benderDlg.h"
#include "Dlg_NestNum.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CGraphDlg dialog
CGraphDlg::CGraphDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGraphDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGraphDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
//	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pGrEditor=NULL;
	m_bBottero = false;
	m_bRectEdit = false;
	m_bRtOpt = false;
}

void CGraphDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGraphDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGraphDlg, CDialog)
	//{{AFX_MSG_MAP(CGraphDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_F1, OnButtonF1)
	ON_BN_CLICKED(IDC_BUTTON_F2, OnButtonF2)
	ON_BN_CLICKED(IDC_BUTTON_F3, OnButtonF3)
	ON_BN_CLICKED(IDC_BUTTON_F6, OnButtonF6)
	ON_BN_CLICKED(IDC_BUTTON_F10, OnButtonF10)
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_LISTWND_MSG, UsermsgListWndMsg)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphDlg message handlers

BOOL CGraphDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(m_wndPicClass.Create(WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_EX_CLIENTEDGE, CRect(0,0,0,0), this))
	{
		m_wndPicClass.Initialize(1);
		m_wndPicClass.ShowWindow(SW_SHOW);
	}
	else
		AfxMessageBox("Error", MB_OK|MB_ICONERROR);
	
	if(m_wndPicBrowse.Create(WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_EX_CLIENTEDGE, CRect(0,0,0,0), this))
	{
		m_wndPicBrowse.Initialize(4);
		m_wndPicBrowse.ShowWindow(SW_SHOW);
	}
	else
		AfxMessageBox("Error", MB_OK|MB_ICONERROR);
	
	m_pGrEditor = new CGrEditor;
	if(m_pGrEditor->Create(NULL, "GrEditor", WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_EX_CLIENTEDGE, CRect(0,0,0,0), this, 0))
	{
		m_pGrEditor->ShowWindow(SW_SHOW);
	}
	else
		AfxMessageBox("Error", MB_OK|MB_ICONERROR);

	SendMessage(WM_SIZE, 0,0);
	InitButton();
    CWnd::SetWindowPos(&CWnd::wndTop, 0, 0, 1024, 768, SWP_SHOWWINDOW);

	return TRUE;  // return TRUE  unless you set the focus to a control
}
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGraphDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

void CGraphDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	CRect rc, rect;
	GetClientRect(&rect);
	rect.DeflateRect(0,0,0,60);

	if(m_wndPicClass.m_hWnd)
	{
		rc = rect;
		rc.right = rc.left + rect.Width()/8;
 		rc.DeflateRect(2,2,2,2);
		m_wndPicClass.MoveWindow(&rc, TRUE);

		rect.left += rc.Width()+2;
	}

	if(m_wndPicBrowse.m_hWnd)
	{
		rc = rect;
		rc.right = rc.left + rect.Width()*2/3;
 		rc.DeflateRect(2,2,2,2);
		m_wndPicBrowse.MoveWindow(&rc, TRUE);
		
		rect.left += rc.Width()+2;
	}
	
	if(m_pGrEditor && m_pGrEditor->m_hWnd)
	{
		rc = rect;
		rc.DeflateRect(2,2,2,2);
		//rc.bottom -= 20;
		m_pGrEditor->MoveWindow(&rc, TRUE);
		
		rect.left += rc.Width()+2;
	}	

	SetTimer(1, 10, NULL);
}

void CGraphDlg::OnTimer(UINT nIDEvent) 
{
	if(1==nIDEvent)
	{
		int nFocusIndex;
		PIC_ATTR picAttr;
		CString strWorkDir;
		UINT picType[N_TOTAL_GTYPEs]=
		{
			GTYPE_CIRCLE, GTYPE_TRIANGLE, GTYPE_RECTANGLE, GTYPE_PENTAGON,
			GTYPE_HEXAGON, GTYPE_YIXING_1, GTYPE_YIXING_2, GTYPE_YIXING_3,
            GTYPE_DXF,
		};
		
		KillTimer(1);

		nFocusIndex = m_wndPicClass.PicWndGetFocus();
		m_wndPicClass.PicWndRemoveAll();

		strWorkDir=g_strOriginalPathD+"grLib\\目录";
		

		for(int i=0; i<N_TOTAL_GTYPEs-1; i++)
		{
			memset(&picAttr, 0, sizeof(PIC_ATTR));
			picAttr.nPicType = picType[i];
			picAttr.nIndex = i+1;
			sprintf(picAttr.szPicName, "PS%02d", i+1);
			sprintf(picAttr.szFilePath, "%s\\%s.bmp", strWorkDir, picAttr.szPicName);
			m_wndPicClass.PicWndAddNew(picAttr);
		}

		if(nFocusIndex<0)
			nFocusIndex=0;

		m_wndPicClass.PicWndSetFocus(nFocusIndex);
		UsermsgListWndMsg(PICWND_LBUTTONDOWN, (LPARAM)m_wndPicClass.GetPicListWnd());
	}
	CDialog::OnTimer(nIDEvent);
}

LRESULT CGraphDlg::UsermsgListWndMsg(WPARAM wParam, LPARAM lParam)
{
	if(PICWND_LBUTTONDOWN==wParam)
	{
		int nFocusIndex;
		UINT nPicType;
		CPicListWnd *pListWnd=(CPicListWnd*)lParam;
		CPicWnd *pPicWnd=NULL;
		if(pListWnd==m_wndPicClass.GetPicListWnd())
		{
			CString strWorkDir;
			strWorkDir = g_strOriginalPathD+"grLib";
			pPicWnd=pListWnd->ListPicWndGetFocusWnd();
			nFocusIndex=m_wndPicBrowse.PicWndGetFocus();
			m_wndPicBrowse.Clean();
			if(!pPicWnd)
				return 0;
			nPicType = pPicWnd->GetPicType();
			switch(nPicType)
			{
			case GTYPE_CIRCLE:		strWorkDir += "\\圆";		break;
			case GTYPE_TRIANGLE:	strWorkDir += "\\三角形";	break;
			case GTYPE_RECTANGLE:	strWorkDir += "\\矩形";		break;
			case GTYPE_PENTAGON:	strWorkDir += "\\五边形";	break;
			case GTYPE_HEXAGON:		strWorkDir += "\\六边形";	break;
			case GTYPE_YIXING_1:	strWorkDir += "\\异形1";	break;
			case GTYPE_YIXING_2:	strWorkDir += "\\异形2";	break;
			case GTYPE_YIXING_3:	strWorkDir += "\\异形3";	break;
			case GTYPE_DXF:	        strWorkDir += "\\dxf";	break;
			case GTYPE_NONE:
			default:
				strWorkDir="";
				break;
			}
			LoadPictures(strWorkDir, nPicType);
			if(!m_wndPicBrowse.PicWndGetAt(nFocusIndex))
				nFocusIndex=0;
			m_wndPicBrowse.PicWndSetFocus(nFocusIndex);
			UsermsgListWndMsg(PICWND_LBUTTONDOWN, (LPARAM)m_wndPicBrowse.GetPicListWnd());
		}
		else if(pListWnd==m_wndPicBrowse.GetPicListWnd())
		{
			m_pGrEditor->Clean();
			pPicWnd=pListWnd->ListPicWndGetFocusWnd();
			if(!pPicWnd)
				return 0;
			const PIC_ATTR *pPicAttr=pPicWnd->GetPicAttribute();
			m_pGrEditor->SetGraph(pPicAttr);
		}
	}
	return 0;
}

void CGraphDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if(m_pGrEditor)
	{
		delete m_pGrEditor;
		m_pGrEditor=NULL;
	}
}

BOOL CGraphDlg::LoadPictures(LPCTSTR lpszDir, UINT nPicType)
{
	CPicWnd *pPicWnd=NULL;
	PIC_ATTR picAttr;
	
	if (nPicType == GTYPE_DXF)
	{
		BOOL bWorking;
		CFileFind cFinder;
		CString strDxfName;
		bWorking = cFinder.FindFile(_T((CString)lpszDir+"\\*.dxf"));  //工件文件的后缀名
		
		while (bWorking)
		{
			bWorking = cFinder.FindNextFile();			
			strDxfName = cFinder.GetFileName();
			memset(&picAttr, 0, sizeof(PIC_ATTR));
			picAttr.nPicType = nPicType;
			picAttr.nIndex = 301;
			sprintf(picAttr.szPicName, "%s", strDxfName);
			sprintf(picAttr.szFilePath, "%s\\%s", lpszDir,strDxfName);
			pPicWnd = m_wndPicBrowse.PicWndAddNew(picAttr);
			if(!pPicWnd)
				continue;
			m_pGrEditor->InitUISetting(picAttr.szPicName);
		} 
		return TRUE;
	}
	for(int i=0; i<300; i++)
	{
		memset(&picAttr, 0, sizeof(PIC_ATTR));
		picAttr.nPicType = nPicType;
		picAttr.nIndex = i+1;
		sprintf(picAttr.szPicName, "%03d", i+1);
		sprintf(picAttr.szFilePath, "%s\\%s.bmp", lpszDir, picAttr.szPicName);
		pPicWnd = m_wndPicBrowse.PicWndAddNew(picAttr);
		if(!pPicWnd)
			continue;
		m_pGrEditor->InitUISetting(picAttr.szPicName);
	}
	return TRUE;
}

void CGraphDlg::InitButton()
{

	HRGN c;
	c = CreateRectRgn(0, 0, 0, 0);	
	GetBitMapRgn(GetDC(),c,IDB_BITMAP_EDITSET1);
	//返回	
	m_pButton[0].SetFont(&g_fontEdit);
	m_pButton[0].SetBitMapID(IDB_BITMAP_BACK1,IDB_BITMAP_BACK2);	
	m_pButton[0].Create(g_strBottero[7][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(900, 714), c, this, IDC_BUTTON_F10); 
	
	
	//保存G
	m_pButton[1].SetFont(&g_fontEdit);
	m_pButton[1].SetBitMapID(IDB_BITMAP_SAVEG1,IDB_BITMAP_SAVEG2);	
	m_pButton[1].Create("G CODE", WS_CHILD | WS_VISIBLE, CPoint(500, 714), c, this, IDC_BUTTON_F6); 	
	
    
	//发送
	m_pButton[2].SetFont(&g_fontEdit);
	m_pButton[2].SetBitMapID(IDB_BITMAP_SAVEPAR1,IDB_BITMAP_SAVEPAR2);	
	m_pButton[2].Create(g_strBottero[0][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(680, 714), c, this, IDC_BUTTON_F2); 
	
	//添加
	m_pButton[3].SetFont(&g_fontEdit);
	m_pButton[3].SetBitMapID(IDB_BITMAP_ADD1,IDB_BITMAP_ADD2);	
	m_pButton[3].Create(g_strPartPara[0][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(250, 714), c, this, IDC_BUTTON_F3); 

	//套料
	m_pButton[4].SetFont(&g_fontEdit);
	m_pButton[4].SetBitMapID(IDB_BITMAP_NEST1,IDB_BITMAP_NEST2);	
	m_pButton[4].Create(g_strGraphLib[2][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(50, 714), c, this, IDC_BUTTON_F1); 


	DeleteObject(c);  

}

//返回
void CGraphDlg::OnButtonF10() 
{
	CDialog::OnCancel();
}

//保存G
void CGraphDlg::OnButtonF6() 
{
	if(!m_bBottero && !m_bRectEdit)
	{
		if(m_pGrEditor)
		{		
			m_pGrEditor->MakeGCodeFile(0);
		}
	}
}


//套料
void CGraphDlg::OnButtonF1()
{
	if(!m_bBottero  && !m_bRectEdit)
	{
		m_NestDlg.DoModal();
	}
}

//发送
void CGraphDlg::OnButtonF2() 
{
	if(!m_bBottero  && !m_bRectEdit)
	{
		if(m_pGrEditor)
		{		
			m_pGrEditor->MakeGCodeFile(1);
			((CBenderDlg *)AfxGetMainWnd())->DrawBottero();
			CDialog::OnOK();	
		}
	}
}

//添加
void CGraphDlg::OnButtonF3()
{
	if(m_bBottero)//编辑
	{
		if(m_pGrEditor)
		{	
			int nNum = atoi(m_pGrEditor->m_picAttr.szPicName);
			if (nNum==3||nNum==4||nNum==5||nNum==250||nNum==262)
			{
				if(g_iLanguage==0)
					AfxMessageBox("图形类型不对，不能插入矩形!");
				else
					AfxMessageBox("Graphic type is wrong, can't insert the rectangle!");
				return;
			}
			CString strCmd = m_pGrEditor->MakeNestCode();
			POINT2D p2D = OnGetBaseRect(strCmd);
			if(p2D.x<=m_Rect.x && p2D.y<=m_Rect.y)
			{
				CWnd *pDlg;
				COPYDATASTRUCT   cpd;  
				pDlg = FindWindow(NULL, "ABC");
				CString strPath;
				strPath.Format("%d-%d.pdc",m_pGrEditor->m_picAttr.nPicType,nNum);
				cpd.dwData   =   0;   
				cpd.cbData   =   strCmd.GetLength();//为了在mid中显示正常，加上一个'\0' 
				cpd.lpData   =   (void*)((const char*)strPath);   
				pDlg->SendMessage(WM_COPYDATA, (WPARAM)GetSafeHwnd(), (LPARAM)&cpd);/* 如何将字符串传出 */
				cpd.dwData   =   1;   
				cpd.cbData   =   strCmd.GetLength();//为了在mid中显示正常，加上一个'\0' 
				cpd.lpData   =   (void*)((const char*)strCmd);   
				pDlg->SendMessage(WM_COPYDATA, (WPARAM)GetSafeHwnd(), (LPARAM)&cpd);/* 如何将字符串传出 */
			}
			else
			{
				AfxMessageBox("图形太大，不能插入矩形!");
				CDialog::OnCancel();
				return;
			}
		}
		CDialog::OnOK();		
	}
	else if (m_bRectEdit)//矩形
	{
		if(m_pGrEditor)
		{	
			int nNum = atoi(m_pGrEditor->m_picAttr.szPicName);
			if (nNum==3||nNum==4||nNum==5||nNum==250||nNum==262)
			{
				if(g_iLanguage==0)
					AfxMessageBox("图形类型不对，不能插入矩形!");
				else
					AfxMessageBox("Graphic type is wrong, can't insert the rectangle!");
				return;
			}
			CString strCmd = m_pGrEditor->MakeNestCode();
			POINT2D p2D = OnGetBaseRect(strCmd);
			if(p2D.x<=m_Rect.x && p2D.y<=m_Rect.y)
			{
				CWnd *pDlg;
				COPYDATASTRUCT   cpd;  
				pDlg = FindWindow(NULL, "RECTEDIT");
				CString strPath;
				strPath.Format("%d-%d",m_pGrEditor->m_picAttr.nPicType,nNum);
				cpd.dwData   =   0;   
				cpd.cbData   =   strCmd.GetLength();//为了在mid中显示正常，加上一个'\0' 
				cpd.lpData   =   (void*)((const char*)strPath);   
				pDlg->SendMessage(WM_COPYDATA, (WPARAM)GetSafeHwnd(), (LPARAM)&cpd);/* 如何将字符串传出 */
				cpd.dwData   =   1;   
				cpd.cbData   =   strCmd.GetLength();//为了在mid中显示正常，加上一个'\0' 
				cpd.lpData   =   (void*)((const char*)strCmd);   
				pDlg->SendMessage(WM_COPYDATA, (WPARAM)GetSafeHwnd(), (LPARAM)&cpd);/* 如何将字符串传出 */
			}
			else
			{
				if(g_iLanguage==0)
					MessageBox("图形太大，不能插入矩形!");
				else
					MessageBox("Graphic is too big, can't insert the rectangle!");
				CDialog::OnCancel();
				return;
			}
		}
		CDialog::OnOK();
	}
	else //套料
	{
		if (m_bRtOpt) 
		{
			m_bRtOpt = false;
			CDlg_NestNum dlg;
			if( dlg.DoModal() == IDOK)
			{
				int nNum = dlg.GetNum();
				CString strCmd = m_pGrEditor->MakeNestCode();
				POINT2D p2D = OnGetBaseRect(strCmd);
				m_p2DRect = p2D;
				//创建异形图形信息字符串，传回矩形优化对话框
				sprintf(m_cShape, "%lf-%lf-%d-%d-%s-%lf-%lf-%lf-%lf-%s", m_p2DRect.x, m_p2DRect.y, nNum, \
					m_pGrEditor->m_picAttr.nPicType, m_pGrEditor->m_picAttr.szPicName, m_pGrEditor->GetClip().X1, \
					m_pGrEditor->GetClip().X2, m_pGrEditor->GetClip().Y1, m_pGrEditor->GetClip().Y2, strCmd);
				CDialog::OnOK();
			}
		}
		else
		{
			CDlg_NestNum dlg;
			if( dlg.DoModal() == IDOK)
			{
				int nNum = dlg.GetNum();
				CString strCmd = m_pGrEditor->MakeNestCode();
				POINT2D p2D = OnGetBaseRect(strCmd);
				m_NestDlg.m_p2DRect = p2D;
				CString strPath;
				strPath.Format("%d-%s",m_pGrEditor->m_picAttr.nPicType,m_pGrEditor->m_picAttr.szPicName);
				m_NestDlg.AddNest(strPath, nNum, strCmd);
				m_NestDlg.DoModal();
			}
		}	
	}	
	
}

/*返回异形的矩形的大小，即长乘宽*/
POINT2D CGraphDlg::OnGetBaseRect(CString strText)
{
	POINT2D	p2D;
	double		dMaxx, dMaxy;
	dMaxx = atof(strText);
	int nPos = strText.FindOneOf(",");
	strText = strText.Mid(nPos+1);
	dMaxy = atof(strText);
	
	p2D.x = dMaxx;
	p2D.y = dMaxy;
	return p2D;
}