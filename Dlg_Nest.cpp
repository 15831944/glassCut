// Dlg_Nest.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "Dlg_Nest.h"
#include "Dlg_NestSave.h"
#include "Dlg_NestSize.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_Nest dialog


CDlg_Nest::CDlg_Nest(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Nest::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_Nest)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	CNestNodeHead *pNestNodeHead = new CNestNodeHead();
	pNestNodeHead->pNext = NULL;
	pNestNodeHead->pPrev = NULL;
	
	m_pHead = pNestNodeHead;
	m_pTail = pNestNodeHead;
	CString strBorder;
	GetPrivateProfileString("NESTPARA","BORDER","0.0",strBorder.GetBuffer(MAX_PATH),MAX_PATH
		, g_strGCodePath + "NestPara.ini");
	m_fBorder = atof(strBorder);
	m_nBoardX = GetPrivateProfileInt("NESTPARA", "SIZEX", 1000, g_strGCodePath + "NestPara.ini");
	m_nBoardY = GetPrivateProfileInt("NESTPARA", "SIZEY", 1000, g_strGCodePath + "NestPara.ini");
	m_rgnBoard.CreateRectRgn(0, 0, m_nBoardX, m_nBoardY);
	m_rgMove.CreateRectRgn(0, 0, 1, 1);
	
	m_nAddTime = 0;
	m_nModifyMode = 0;		//初始的修改方式是移动
	

	m_nNestBaseX = m_nNestBaseY = (int)m_fBorder;//2009-4-10
}


void CDlg_Nest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Nest)
	DDX_Control(pDX, IDC_LIST2, m_pListNest);
	DDX_Control(pDX, IDC_LIST1, m_pList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_Nest, CDialog)
	//{{AFX_MSG_MAP(CDlg_Nest)
	ON_BN_CLICKED(IDC_BUTTON1, OnMoveUP)
	ON_BN_CLICKED(IDC_BUTTON12, OnMoveDOWN)
	ON_BN_CLICKED(IDC_BUTTON10, OnMoveLEFT)
	ON_BN_CLICKED(IDC_BUTTON11, OnMoveRight)
	ON_WM_PAINT()
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList1)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_CS1, OnButtonCs1)
	ON_BN_CLICKED(IDC_BUTTON_CS2, OnButtonCs2)
	ON_BN_CLICKED(IDC_BUTTON_CS3, OnButtonCs3)
	ON_BN_CLICKED(IDC_BUTTON_CS4, OnButtonCs4)
	ON_BN_CLICKED(IDC_BUTTON_CS6, OnButtonCs6)
	ON_BN_CLICKED(IDC_BUTTON_CS8, OnButtonCs8)
	ON_BN_CLICKED(IDC_BUTTON_CS5, OnButtonCs5)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_CS10, OnButtonCs10)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
CDlg_Nest::~CDlg_Nest()
{
	FreeNestNode();
	delete m_pHead;
}
// CDlg_Nest message handlers

BOOL CDlg_Nest::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here	
	addY = 0.0;
	addX = 0.0;	
	Showpart();
	m_nSelect =0;
	SelectParaName=0;
	numberfile=0;
	
	SetDlgItemText(IDC_EDIT2,"0");
	SetDlgItemText(IDC_EDIT3,"0");
	
	m_nSelect = -1;
	
	InitPara();

	
	HRGN c;
	
	c = CreateRectRgn(0, 0, 0, 0);	
	GetBitMapRgn(GetDC(),c,IDB_BITMAP_BACK1);
	//添加    
	m_pButton[0].SetFont(&g_fontEdit);
	m_pButton[0].SetBitMapID(IDB_BITMAP_ADD1,IDB_BITMAP_ADD2);	
	m_pButton[0].Create(g_strNester[0][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(2, 705), c, this, IDC_BUTTON_CS1); 
	//删除	
	m_pButton[1].SetFont(&g_fontEdit);
	m_pButton[1].SetBitMapID(IDB_BITMAP_DELETE1,IDB_BITMAP_DELETE2);	
	m_pButton[1].Create(g_strNester[1][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(127, 705), c, this, IDC_BUTTON_CS2); 
	//移动	
	m_pButton[2].SetFont(&g_fontEdit);
	m_pButton[2].SetBitMapID(IDB_BITMAP_MOVE1,IDB_BITMAP_MOVE2);	
	m_pButton[2].Create(g_strNester[2][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(260, 705), c, this, IDC_BUTTON_CS3); 
	//旋转
	m_pButton[3].SetFont(&g_fontEdit);
	m_pButton[3].SetBitMapID(IDB_BITMAP_REMATE1,IDB_BITMAP_REMATE2);	
	m_pButton[3].Create(g_strNester[3][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(385, 705), c, this, IDC_BUTTON_CS4); 
	//清除套料	
	m_pButton[4].SetFont(&g_fontStatic);
	m_pButton[4].SetBitMapID(IDB_BITMAP_DELGRAP1,IDB_BITMAP_DELGRAP2);	
	m_pButton[4].Create(g_strNester[4][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(510, 705), c, this, IDC_BUTTON_CS5); 
	
	//参数
	m_pButton[5].SetFont(&g_fontEdit);
	m_pButton[5].SetBitMapID(IDB_BITMAP_PARA1,IDB_BITMAP_PARA2);	
	m_pButton[5].Create(g_strNester[5][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(643, 705), c, this, IDC_BUTTON_CS6); 
	//保存	
	m_pButton[6].SetFont(&g_fontEdit);
	m_pButton[6].SetBitMapID(IDB_BITMAP_SAVE1,IDB_BITMAP_SAVE2);	
	m_pButton[6].Create(g_strNester[6][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(770, 705), c, this, IDC_BUTTON_CS8); 
	
	//返回	
	m_pButton[7].SetFont(&g_fontEdit);
	m_pButton[7].SetBitMapID(IDB_BITMAP_BACK1,IDB_BITMAP_BACK2);	
	m_pButton[7].Create(g_strNester[7][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(900, 705), c, this, IDC_BUTTON_CS10); 
	
    DeleteObject(c);

	SetWindowPos(CWnd::GetOwner(),0,0,g_screen.x,g_screen.y,SWP_SHOWWINDOW);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg_Nest::Ondelpart() 
{
	// TODO: Add your control notification handler code here
	int nSelect = m_pList.GetCurSel();
	m_pList.DeleteString(nSelect);
	CNestNodeHead *pHead = m_pHead->pNext;
	int nCurrent =0;
	for(; pHead; pHead=pHead->pNext)
	{
		CNestNode *pNode = pHead->pDown;
		CNestNode *pLastNode;
		pLastNode = pHead->pDown;
		int nNode=0;
		for(; pNode; pNode=pNode->pNext)
		{
			if(nCurrent==nSelect)
			{
				if( nNode == 0)
				{
					pHead->pDown=pNode->pNext;
				}
				else
				{
					pLastNode->pNext=pNode->pNext;
				}
				m_rgnBoard.CombineRgn(&m_rgnBoard,&pNode->rgnRect,RGN_XOR);
				delete pNode;
				pHead->nNum--;
				OnPaint();
				return ;
			}
			nCurrent++;
			nNode++;
		}
	}
}

void CDlg_Nest::SaveGCode()		//保存G代码
{
	// TODO: Add your control notification handler code here
	CString strText;
	CString	strUp, strDn;
	CStdioFile Gcode;
	CDlg_NestSave dlg;
	dlg.DoModal();
	if( strstr(g_strSavefile,".g") == NULL && strstr(g_strSavefile,".G")==NULL)
		g_strSavefile += ".g";
	CString strFileName = g_strOriginalPathD + "gcode\\"+g_strSavefile;
	if(g_stu_pAxisA->bSpareA)	/* 注油 */
	{
		strDn = "M13\n";
		strUp = "M14\n";
	}
	else						/* 不注油 */
	{
		strDn = "M09\n";
		strUp = "M10\n";
	}

				
	if( !Gcode.Open(strFileName,CFile::modeCreate|CFile::modeWrite) )
		return ;
	
	Gcode.WriteString("M25\n");
	Gcode.WriteString("M23\n");
	Gcode.WriteString("G90\n");

	int m,i=0,j=0;
	int k,nCurrentDraw=0;
	double sunx=0.0,suny=0.0,thisOx=0.0,thisOy=0.0,maxx=83.0,maxy=83.0,line=580.0,hight=514.0,maxly=0.0;
	CString sming;
	CNestNodeHead *pNodeHead = m_pHead->pNext;

	int nHollow = -1;
	for(k=0;k<m_nAddTime;k++)
	{
		CNestNode *pNode = pNodeHead->pDown;
		int nNum;
		nNum = pNodeHead->nNum;
		CStdioFile paraf;
		CString strPath,sqr1,pdcstr;
		CString strCmd;
		int nPos;

		for(m=0;m<nNum;m++)
		{
			strCmd.Format("%s",pNode->szCmd);
			int nOffsetX, nOffsetY;
			nOffsetX = pNode->ptOffset.x;
			nOffsetY = pNode->ptOffset.y;
			
			if((maxx>line) && (maxy<=hight-maxy))
			{
				line=580;
				hight=hight-maxly-5;
				suny=suny+maxly+5;
				sunx=0;
				i++;
				j=0;
				maxly = maxy;
			}
			if(1)
			{
//////////////////////////////////////////////////////////////////////////////画图
				nPos = strCmd.FindOneOf(";");
				strCmd = strCmd.Mid(nPos+1);
				nPos = strCmd.FindOneOf(";");
				while( nPos != -1)
				{
					CString pdcpoint;
					pdcstr = strCmd.Left(nPos);
					strCmd = strCmd.Mid(nPos+1);
					nPos = strCmd.FindOneOf(";");					
					if(pdcstr.GetAt(0)=='0')
					{
						pdcpoint = pdcstr.Mid(1);
						int nPos;
						double pointx,pointy;
						nPos = pdcpoint.FindOneOf(",");
						pointx = atof(pdcpoint.Left(nPos));
						pointy = atof(pdcpoint.Mid(nPos+1));
						if( nHollow == -1 || nHollow == 0)
						{
							Gcode.WriteString(strUp);
							nHollow = 1;
						}
						strText.Format("G00 X%.4f Y%.4f\n", (double)(nOffsetX+pointx), (double)(nOffsetY+pointy));
						Gcode.WriteString(strText);
						thisOx=sunx+pointx;
						thisOy=suny+pointy;
					}
					if(pdcstr.GetAt(0)=='1')
					{
						pdcpoint = pdcstr.Mid(1);
						int nPos;
						double pointx,pointy;
						nPos = pdcpoint.FindOneOf(",");
						pointx = atof(pdcpoint.Left(nPos));
						pointy = atof(pdcpoint.Mid(nPos+1));
						if( nHollow == -1 || nHollow == 1)
						{
							Gcode.WriteString(strDn);
							nHollow = 0;
						}
						strText.Format("G01 X%.4f Y%.4f\n",(double)(nOffsetX+pointx), (double)(nOffsetY+pointy));
						Gcode.WriteString(strText);
						thisOx=sunx+pointx;
						thisOy=suny+pointy;
					}
					if(pdcstr.GetAt(0)=='2')
					{
						pdcpoint = pdcstr.Mid(1);
						int nPos;
						double pointx,pointy,pointR,pointQ,pointD,Gendx,Gendy;
//						double PI = 3.1415926535;
						nPos = pdcpoint.FindOneOf(",");
						pointx = atof(pdcpoint.Left(nPos));
						pdcpoint = pdcpoint.Mid(nPos+1);
						nPos = pdcpoint.FindOneOf(",");
						pointy = atof(pdcpoint.Left(nPos));
						pdcpoint = pdcpoint.Mid(nPos+1);
						nPos = pdcpoint.FindOneOf(",");
						pointR = atof(pdcpoint.Left(nPos));
						pdcpoint = pdcpoint.Mid(nPos+1);
						nPos = pdcpoint.FindOneOf(",");
						pointQ = atof(pdcpoint.Left(nPos));
						pointD = atof(pdcpoint.Mid(nPos+1));
						Gendx=pointR*cos((pointQ+pointD)*PI/180)+nOffsetX+pointx;
						Gendy=pointR*sin((pointQ+pointD)*PI/180)+nOffsetY+pointy;
						double fI=-pointR*cos(pointQ*PI/180);
						double fJ=-pointR*sin(pointQ*PI/180);
						if( nHollow == -1 || nHollow == 1)
						{
							Gcode.WriteString(strDn);
							nHollow = 0;
						}
						
						if(pointD>0)
						{
							strText.Format("G03 X%f Y%f I%f J%f\n",Gendx,Gendy,fI,fJ);
						}
						else
						{
							strText.Format("G02 X%f Y%f I%f J%f\n",Gendx,Gendy,fI,fJ);
						}
						Gcode.WriteString(strText);

						thisOx=Gendx;
						thisOy=Gendy;
					}
				}
				nCurrentDraw++;
				line=line-maxx-5;
				sunx=sunx+maxx+5;
				j++;
				if(maxy>=maxly)
				{maxly=maxy;}
			}
			pNode = pNode->pNext;
		}
		pNodeHead = pNodeHead->pNext;
	}
	Gcode.WriteString(strUp);
	Gcode.WriteString("M24\n");
	Gcode.WriteString("M26\n");
	Gcode.WriteString("G90G00X0Y0Z0\n");
	if(g_stu_pAxisG->bSpare)
		Gcode.WriteString("M99\n");
	Gcode.WriteString("M30\n");
	Gcode.Close();

	CDialog::OnOK();
}

void CDlg_Nest::Showpart()
{
	int nLine = 0;
	CString string;
	CNestNodeHead *pNodeHead = m_pHead->pNext;
	for(int i=0; i<m_nAddTime; i++)
	{
		for(int j=1;j<=pNodeHead->nNum;j++)
		{
			m_pList.InsertString(nLine++,pNodeHead->chName);
		}
		pNodeHead = pNodeHead->pNext;
	}
	m_pList.SetCurSel(0);
}

void CDlg_Nest::OnMoveUP() 
{
	// TODO: Add your control notification handler code here
	CString buffer;
	CEdit *PEdit1 = (CEdit*)GetDlgItem(IDC_EDIT3);
	PEdit1->GetWindowText(buffer);
	addY = atof(buffer); 
	addX=0;
	OnMovePicture();
}

void CDlg_Nest::OnMoveDOWN() 
{
	// TODO: Add your control notification handler code here
	CString buffer;
	CEdit *PEdit1 = (CEdit*)GetDlgItem(IDC_EDIT3);
	PEdit1->GetWindowText(buffer);
	addY = -atof(buffer); 
	addX=0;
	OnMovePicture();	
}

void CDlg_Nest::OnMoveLEFT() 
{
	// TODO: Add your control notification handler code here
	CString buffer;
	CEdit *PEdit = (CEdit*)GetDlgItem(IDC_EDIT2);
	PEdit->GetWindowText(buffer);
	addX = -atof(buffer);   
	addY=0;
	OnMovePicture();
}

void CDlg_Nest::OnMoveRight() 
{
	// TODO: Add your control notification handler code here
	CString buffer;
	CEdit *PEdit = (CEdit*)GetDlgItem(IDC_EDIT2);
	PEdit->GetWindowText(buffer);
	addX = atof(buffer);   
//	addY=0;
	OnMovePicture();	
}

BOOL CDlg_Nest::PreTranslateMessage(MSG* pMsg)
{	
	if(pMsg->lParam==VK_TAB||pMsg->wParam==VK_TAB)
		return TRUE;
	if(pMsg->lParam==VK_RETURN||pMsg->wParam==VK_RETURN)
		return TRUE;

	return CDialog::PreTranslateMessage(pMsg);
}

void CDlg_Nest::OnMovePicture()
{
	KillTimer(1);
	Invalidate(TRUE);
	CStdioFile filePara;
	CString strPath,strbuf,strpara,pdcstr;
	strPath.Format(g_strGCodePath + "para\\%d.pdc",numberfile);
	if( !filePara.Open(strPath,CFile::modeRead) )
		return ; 
	filePara.SeekToBegin();
	filePara.ReadString(pdcstr);
	strbuf=pdcstr+"\n";
	strpara=strbuf;
	while(filePara.ReadString(pdcstr))
	{
		CString pdcpoint;
		if(pdcstr.GetAt(0)=='0')
		{
			pdcpoint = pdcstr.Mid(1);
			int point;
			double pointx,pointy;
			point = pdcpoint.FindOneOf(",");
			pointx = atof(pdcpoint.Left(point));
			pointy = atof(pdcpoint.Mid(point+1));
			strbuf.Format("0 %f,%f",addX+pointx,addY+pointy);
			strpara=strpara+strbuf+"\n";
		}
		if(pdcstr.GetAt(0)=='1')
		{
			pdcpoint = pdcstr.Mid(1);
			int point;
			double pointx,pointy;
			point = pdcpoint.FindOneOf(",");
			pointx = atof(pdcpoint.Left(point));
			pointy = atof(pdcpoint.Mid(point+1));
			strbuf.Format("1 %f,%f",addX+pointx,addY+pointy);
			strpara=strpara+strbuf+"\n";
		}
		if(pdcstr.GetAt(0)=='2')
		{
			pdcpoint = pdcstr.Mid(1);
			int nPos;
			double pointx,pointy,pointR,pointQ,pointD;
//			double PI = 3.1415926535;
			nPos = pdcpoint.FindOneOf(",");
			pointx = atoi(pdcpoint.Left(nPos));
			pdcpoint = pdcpoint.Mid(nPos+1);
			nPos = pdcpoint.FindOneOf(",");
			pointy = atoi(pdcpoint.Left(nPos));
			pdcpoint = pdcpoint.Mid(nPos+1);
			nPos = pdcpoint.FindOneOf(",");
			pointR = atoi(pdcpoint.Left(nPos));
			pdcpoint = pdcpoint.Mid(nPos+1);
			nPos = pdcpoint.FindOneOf(",");
			pointQ = atoi(pdcpoint.Left(nPos));
			pointD = atoi(pdcpoint.Mid(nPos+1));
			strbuf.Format("2 %f,%f,%f,%f,%f",addX+pointx,addY+pointy,pointR,pointQ,pointD);
			strpara=strpara+strbuf+"\n";
		}
	}
	filePara.Close();
	strPath.Format(g_strGCodePath + "para\\%d.pdc",numberfile);
	if( !filePara.Open(strPath,CFile::modeCreate|CFile::modeWrite) )
		return ;
	filePara.WriteString(strpara);
	filePara.Close();
	Invalidate(FALSE);
}

void CDlg_Nest::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	Draw();
	// Do not call CDialog::OnPaint() for painting messages
}

void CDlg_Nest::Draw()
{

	CDC *dc=GetDC();
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_LIST2);
	CRect rect;
	pWnd->GetWindowRect(rect);

//////////////////////////计算画图比例
	m_fDrawRate = min(rect.Width()*1.0/m_nBoardX, rect.Height()*1.0/m_nBoardY);
//////////////////////////计算画图比例

	CDC pDc;
	CBitmap bitmap,bitmap2;
	
	pDc.CreateCompatibleDC(dc);
	bitmap.CreateCompatibleBitmap(dc,rect.Width(),rect.Height());
	CBitmap *oldBit = pDc.SelectObject(&bitmap);	

	pDc.FillSolidRect(0,0,rect.Width(),rect.Height(),RGB(255,255,255));

	/////////////////////////////////画钢板
	CPen penBorder;
	penBorder.CreatePen(PS_DOT,1,RGB(255,0,0));
	pDc.SelectObject(&penBorder);
	pDc.MoveTo(0,rect.Height()-2);
	pDc.LineTo((int)(m_nBoardX*m_fDrawRate),rect.Height()-2);
	pDc.LineTo((int)(m_nBoardX*m_fDrawRate),rect.Height()-(int)(m_nBoardY*m_fDrawRate)+2);
	pDc.LineTo(0,rect.Height()-(int)(m_nBoardY*m_fDrawRate)+2);
	pDc.LineTo(0,rect.Height()-2);
	/////////////////////////////////画钢板
	int m,i=0,j=0;
	int k,nCurrentDraw=0;
	double sunx=0.0,suny=0.0,thisOx=0.0,thisOy=0.0,maxx=83.0,maxy=83.0,line=580.0,hight=514.0,maxly=0.0;
	CString sming;
	CNestNodeHead *pNodeHead = m_pHead->pNext;
	pDc.MoveTo(0,rect.Height());
	CPen pensel[3];
	pensel[0].CreatePen(PS_DOT,1,RGB(0,255,0));
	pensel[1].CreatePen(PS_SOLID,2,RGB(0,0,128));
	pensel[2].CreatePen(PS_SOLID,2,RGB(255,0,0));
	int nAddOffSetX = 30;
	int nAddOffSetY = 30;
	for(k=0;k<m_nAddTime;k++)
	{
		CNestNode *pNode = pNodeHead->pDown;
		int nNum;
		nNum = pNodeHead->nNum;
		CStdioFile paraf;
		CString strPath,sqr1,pdcstr;

		CString strCmd;
		int nPos;		
		pDc.SelectObject(&pensel[1]);
		for(m=0;m<nNum;m++)
		{
			strCmd.Format("%s",pNode->szCmd);
			int nOffsetX, nOffsetY;
			nOffsetX = pNode->ptOffset.x;
			nOffsetY = pNode->ptOffset.y;
			
			if((maxx>line) && (maxy<=hight-maxy))
			{
				line=580;
				hight=hight-maxly-5;
				suny=suny+maxly+5;
				sunx=0;
				i++;
				j=0;
				maxly = maxy;
			}
			if(nCurrentDraw==m_nSelect)
			{
				pDc.SelectObject(&pensel[2]);
			}
			nPos = strCmd.FindOneOf(";");
			strCmd = strCmd.Mid(nPos+1);
			nPos = strCmd.FindOneOf(";");
			while( nPos != -1)
			{
				CString pdcpoint;
				pdcstr = strCmd.Left(nPos);
				strCmd = strCmd.Mid(nPos+1);
				nPos = strCmd.FindOneOf(";");
				if(pdcstr.GetAt(0)=='0')
				{
					pdcpoint = pdcstr.Mid(1);
					int nPos;
					double pointx,pointy;
					nPos = pdcpoint.FindOneOf(",");
					pointx = atof(pdcpoint.Left(nPos));
					pointy = atof(pdcpoint.Mid(nPos+1));
					CPen *OldPen = pDc.SelectObject(&pensel[0]);
					pDc.LineTo((int)((nOffsetX+nAddOffSetX+pointx)*m_fDrawRate), 
						rect.Height()-(int)((nOffsetY+nAddOffSetY+pointy)*m_fDrawRate));
					pDc.SelectObject(OldPen);
					thisOx=sunx+pointx;
					thisOy=suny+pointy;
				}
				if(pdcstr.GetAt(0)=='1')
				{
					pdcpoint = pdcstr.Mid(1);
					int nPos;
					double pointx,pointy;
					nPos = pdcpoint.FindOneOf(",");
					pointx = atof(pdcpoint.Left(nPos));
					pointy = atof(pdcpoint.Mid(nPos+1));
					pDc.LineTo((int)((nOffsetX+nAddOffSetX+pointx)*m_fDrawRate), 
						rect.Height()-(int)((nOffsetY+nAddOffSetY+pointy)*m_fDrawRate));
					thisOx=sunx+pointx;
					thisOy=suny+pointy;
				}
				if(pdcstr.GetAt(0)=='2')
				{
					pdcpoint = pdcstr.Mid(1);
					int nPos;
					double pointx,pointy,pointR,pointQ,pointD,Gendx,Gendy;
					nPos = pdcpoint.FindOneOf(",");
					pointx = atof(pdcpoint.Left(nPos));
					pdcpoint = pdcpoint.Mid(nPos+1);
					nPos = pdcpoint.FindOneOf(",");
					pointy = atof(pdcpoint.Left(nPos));
					pdcpoint = pdcpoint.Mid(nPos+1);
					nPos = pdcpoint.FindOneOf(",");
					pointR = atof(pdcpoint.Left(nPos));
					pdcpoint = pdcpoint.Mid(nPos+1);
					nPos = pdcpoint.FindOneOf(",");
					pointQ = atof(pdcpoint.Left(nPos));
					pointD = atof(pdcpoint.Mid(nPos+1));
					pDc.AngleArc((int)((nAddOffSetX+nOffsetX+pointx)*m_fDrawRate), 
						rect.Height()-(int)((nAddOffSetX+nOffsetY+pointy)*m_fDrawRate),
						(int)(pointR*m_fDrawRate),(float)pointQ,(float)pointD);
					
					Gendx=pointR*cos((pointQ+pointD)*PI/180)+sunx+pointx;
					Gendy=pointR*sin((pointQ+pointD)*PI/180)+suny+pointy;
					
					thisOx=Gendx;
					thisOy=Gendy;
				}
			}
			nCurrentDraw++;
			pDc.SelectObject(&pensel[1]);
			line=line-maxx-5;
			sunx=sunx+maxx+5;
			j++;
			if(maxy>=maxly)
			{maxly=maxy;}
			pNode = pNode->pNext;
		}
		pNodeHead = pNodeHead->pNext;
	}
	
	pensel[0].DeleteObject();
	pensel[1].DeleteObject();
	pensel[2].DeleteObject();
	dc->BitBlt(0,0,rect.Width(),rect.Height(),&pDc,0,0,SRCCOPY);
	bitmap.DeleteObject();
	ReleaseDC(dc);
}

void CDlg_Nest::AddNest(CString strType, int nNum, CString strCmd)
{	
//nType 是花样，nNum是数量
	CNestNodeHead *pNestNodeHead;
	pNestNodeHead = new CNestNodeHead();
	pNestNodeHead->nNum = nNum;
	sprintf(pNestNodeHead->chName, strType);
	pNestNodeHead->pNext = NULL;
//	sprintf(pNestNode->szCmd, strCmd);

	m_pTail->pNext = pNestNodeHead;
	pNestNodeHead->pPrev = m_pTail;
	pNestNodeHead->pDown = NULL;
	pNestNodeHead->pNext = NULL;
	m_pTail = pNestNodeHead;
	

	InitPara();
	
	//////////////////////////计算画图比例
	m_fDrawRate = min(866.0/m_nBoardX, 866.0/m_nBoardY);
	//////////////////////////计算画图比例

	CRgn rgnLib;

	GetLibRange(&rgnLib);
	int nNestReturn = Nest(nNum, &rgnLib);
	pNestNodeHead->nNum = nNum;			//将添加成功的个数放到头链表里
	if( nNestReturn == -1)		//超过尺寸，一个也没有添加
	{
		if (!g_iLanguage) 
		{
			MessageBox("超出范围,添加图形失败!","Error",MB_OK|MB_ICONWARNING);
		}
		else 
		{
			MessageBox("Out of range, add graphics failure!","Error",MB_OK|MB_ICONWARNING);
			
		}
		
	}
	else
	{
		if( nNestReturn == 1)	//超过尺寸，添加了图形，并未完全添加
		{
			if (!g_iLanguage) 
			{
				MessageBox("超出范围,添加图形失败!","Error",MB_OK|MB_ICONWARNING);
			}
			else 
			{
				MessageBox("Out of range, add graphics failure!","Error",MB_OK|MB_ICONWARNING);
				
			}
		
		}
		CNestNode *pNode = m_pTail->pDown;
		while(pNode)
		{
			sprintf(pNode->szCmd,strCmd);
			pNode = pNode->pNext;
		}
		
		m_nAddTime++;
	}
	
}

void CDlg_Nest::OnSelchangeList1() 
{
	// TODO: Add your control notification handler code here
	
	m_nSelect = m_pList.GetCaretIndex();
	OnPaint();
}

int CDlg_Nest::Nest(int& nNum, CRgn *rgnNest)	//套料计算,添加图形
{
	int nBorder = 0;	//存储各个图形间的间距
	CRect rcBoard;
	CRect rcNest;
	m_rgnBoard.GetRgnBox(rcBoard);
	rgnNest->GetRgnBox(rcNest);

	CRgn rgnTotal;
	CRgn rgnTempNest;
	CRgn rgnTemp;
	rgnTempNest.CreateRectRgn(0,0,1,1);
	rgnTemp.CreateRectRgn(0,0,1,1);
	rgnTotal.CreateRectRgn(0,0,m_nBoardX,m_nBoardY);
	int nLoopRangX, nLoopRangY;
	nLoopRangX = rcBoard.Width() - rcNest.Width();
	nLoopRangY = rcBoard.Height() - rcNest.Height();
	if( nLoopRangY<0 || nLoopRangX<0)
	{
		nNum = 0;
		return -1;
	}
	int nLoopX, nLoopY;
/*	if()//2009-4-10
		nLoopX = nLoopY = (int)(m_fBorder);
	else
	{
		nLoopX = m_nNestBaseX;//2009-4-10
		nLoopY = m_nNestBaseY;//2009-4-10
	}*/
	nLoopX = m_nNestBaseX;
	nLoopY = m_nNestBaseY;
	for(int index=0; index<nNum;)
	{
		CRgn rgnTempBoard;
		rgnTempBoard.CreateRectRgn(0,0,1,1);
		rgnTempBoard.CombineRgn(&rgnTotal,&m_rgnBoard,RGN_DIFF);		//对钢板取反
		
		for(; nLoopY<=nLoopRangY; nLoopY++)
		{
			if( nLoopX>= nLoopRangX)
			{
				nLoopX = (int)m_fBorder;
				nLoopY += 0;
			}
			for(;nLoopX<=nLoopRangX ;nLoopX++)
			{
				CRgn rgnNestCopy;
				rgnNestCopy.CreateRectRgn(0,0,1,1);
				rgnNestCopy.CopyRgn(rgnNest);
				rgnNestCopy.OffsetRgn(nLoopX,nLoopY);
				int nCombineResult;
				nCombineResult = rgnTemp.CombineRgn(&rgnTempBoard,&rgnNestCopy,RGN_AND);
				if( nCombineResult == NULLREGION)			//和新加入的没有相交的区域，则可插入
				{
					CNestNode *pNode = m_pTail->pDown;
					while(index!=0 && pNode->pNext)
					{
						pNode = pNode->pNext;
					}
					CNestNode *pNewNode = new CNestNode();
					pNewNode->pNext = NULL;
					if( index== 0)
						pNewNode->pPrev = NULL;
					else
						pNewNode->pPrev = pNode;
					CString strName;
					strName.Format("aa%d",index);
					pNewNode->strName = strName;
					pNewNode->rgnRect.CreateRectRgn(0,0,1,1);
					pNewNode->rgnRect.CombineRgn(&rgnNestCopy,NULL,RGN_COPY);
					pNewNode->ptCenter.x = nLoopX+rcNest.Width()/2;
					pNewNode->ptCenter.y = nLoopY+rcNest.Height()/2;
					pNewNode->ptOffset.x = nLoopX;
					pNewNode->ptOffset.y = nLoopY;
					
					if( index == 0)
					{
						m_pTail->pDown = pNewNode;
						//rgnNestCopy.OffsetRgn(1,0);
						nLoopX += rcNest.Width()/*+1*/;
					}
					else
					{
						pNode->pNext = pNewNode;
						nLoopX += rcNest.Width();
					}
					
					nCombineResult = m_rgnBoard.CombineRgn(&m_rgnBoard,&rgnNestCopy,RGN_DIFF);

					index++;
					m_pTail->nNum = index;
					if( index == nNum)
					{
						nNum = index;
//						m_nNestBaseX = nLoopX;//2009-4-10
//						m_nNestBaseY = nLoopY;//2009-4-10
						return 0;
					}
					goto Next;
				}
			}
		}
		nNum = index;
		return 1;
Next:
		;
	}
	m_nNestBaseX = nLoopX;//2009-4-10
	m_nNestBaseY = nLoopY;//2009-4-10
	
	nNum = index;
	return 1;
}

void CDlg_Nest::GetLibRange(CRgn *rgnLib)	//取得新加入图形的区域
{

	int nOffsetX, nOffsetY;	//记录各个图形之间的偏移量
	nOffsetX = nOffsetY = 0/*2*/;	
	int nMaxx, nMaxy;
	nMaxx = m_p2DRect.x;
	nMaxy = m_p2DRect.y;
	double nRgnX = nMaxx+nOffsetX+(int)(m_fBorder);
	double nRgnY = nMaxy+nOffsetY+(int)(m_fBorder);
	rgnLib->CreateRectRgn(0,0, (int)nRgnX, (int)nRgnY);
}

void CDlg_Nest::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	filePoint.Open("C:\\point.txt",CFile::modeCreate|CFile::modeWrite);
	CPoint	ptMouse;
	CRect	rctList;
	m_pListNest.GetClientRect(rctList);
	ptMouse.x = (LONG)(point.x/m_fDrawRate);
	ptMouse.y = (LONG)((rctList.Height()-point.y)/m_fDrawRate);
	m_nSelect = -1;
	int nSelect=0;
	CNestNodeHead	*pHead = m_pHead->pNext;
	for(;pHead; )
	{
		CNestNode		*pNode = pHead->pDown;
		for(;pNode;)
		{
			if( pNode->rgnRect.PtInRegion(ptMouse) )
			{
				CRect rcBoard;
				m_pListNest.GetWindowRect(rcBoard);
				m_nSelect = nSelect;
				m_pList.SetCurSel(m_nSelect);
				m_pNodeSelect = pNode;
				m_ptCatch = point;
//				m_ptCatch.y = rcBoard.Height()-point.y;

				m_rgMove.CombineRgn(&m_pNodeSelect->rgnRect,NULL,RGN_COPY);
				OnPaint();
				return ;
			}
			nSelect++;
			if(pNode->pNext)
				pNode = pNode->pNext;
			else
				break ;
		}
		if( pHead->pNext !=NULL )
		{
			pHead=pHead->pNext;
		}
		else
		{
			return ;
		}
	}
	CDialog::OnLButtonDown(nFlags, point);
}

void CDlg_Nest::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if( MK_LBUTTON == nFlags && m_nSelect !=-1)
	{
		if( m_nModifyMode == 0)		//移动
		{
			int nOffsetX, nOffsetY;
			nOffsetX = (int)((point.x-m_ptCatch.x)/m_fDrawRate);
			nOffsetY = (int)((m_ptCatch.y-point.y)/m_fDrawRate);
			m_pNodeSelect->rgnRect.OffsetRgn(nOffsetX, nOffsetY);
			m_pNodeSelect->ptOffset.x += nOffsetX;
			m_pNodeSelect->ptOffset.y += nOffsetY;
			
			m_pNodeSelect->ptCenter.x += nOffsetX;
			m_pNodeSelect->ptCenter.y += nOffsetY;
			
			OnPaint();
			m_ptCatch = point;
		}
		else						//旋转
		{
			CRect rcBoard;
			m_pListNest.GetWindowRect(rcBoard);
			CPoint ptMove;
			ptMove.x = point.x;
			ptMove.y = rcBoard.Height()-point.y;
			double fRotateAngle, fBeginAngle;
			GetRotateAngle(ptMove, fBeginAngle, fRotateAngle);

			CString str;
			str.Format("%f,%f\n",fBeginAngle, fRotateAngle);
//			filePoint.WriteString(str);
			RotateSelect(fBeginAngle, fRotateAngle);
			
			m_ptCatch = point;
			OnPaint();
		}
	}
	CDialog::OnMouseMove(nFlags, point);
}

void CDlg_Nest::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if( m_nModifyMode == 0)		//移动
	{
		if( m_nSelect != -1)
		{
			m_rgnBoard.CombineRgn(&m_rgnBoard,&m_rgMove,RGN_XOR);
			m_rgnBoard.CombineRgn(&m_rgnBoard,&m_pNodeSelect->rgnRect,RGN_DIFF);
			OnPaint();
		}
		
		m_nSelect = -1;
	}
	else if( m_nModifyMode == 1)	//旋转
	{
		if( m_nSelect != -1)
		{
			CRect rcBoard;
			m_pListNest.GetWindowRect(rcBoard);
			CPoint ptUp;
			ptUp.x = point.x;
			ptUp.y = rcBoard.Height()-point.y;

			double fRotateAngle, fBeginAngle;
			GetRotateAngle(ptUp, fBeginAngle, fRotateAngle);
			RotateSelect(fBeginAngle, fRotateAngle);
			CString str;
			str.Format("%f,%f\n",fBeginAngle, fRotateAngle);
//			filePoint.WriteString(str);		
//			filePoint.Close();
			OnPaint();
			m_nSelect = -1;
		}
	}
	CDialog::OnLButtonUp(nFlags, point);
}

void CDlg_Nest::GetCurrentNode(int nNode,CNestNode *pNode)
{
	CNestNodeHead *pHead = m_pHead->pNext;
	CNestNode *pNestNode;

	int nIndex = 0;
	for(; pHead; pHead=pHead->pNext)
	{
		pNestNode = pHead->pDown;
		for(; pNestNode; pNestNode=pNestNode->pNext)
		{
			if( nIndex==nNode)
			{
				pNode = pNestNode;
				return ;
			}
			nIndex++;
		}
	}
}

void CDlg_Nest::RotateSelect(double fBeginAngle, double fRotateAngel)		//旋转
{
//	double PI = acos(-1);
	int nPos;
	CString strCmd;			//原来的命令行
	CString strLine;		//单个命令
	CString strResult = "";		//运算结果
	CString strLineResult = "";	

	CRect rcRgn;
	m_pNodeSelect->rgnRect.GetRgnBox(rcRgn);
	CPoint ptCenter;
	ptCenter.x = rcRgn.Width()/2;
	ptCenter.y = rcRgn.Height()/2;

	strCmd.Format("%s",m_pNodeSelect->szCmd);
	nPos = strCmd.FindOneOf(";");
	strLine = strCmd.Left(nPos);
	strCmd = strCmd.Mid(nPos+1);
	
	strResult += strLine+";";
	
	double fDeltaAngle = 1.0;//fRotateAngel - fBeginAngle;
	while(nPos != -1)
	{
		nPos = strCmd.FindOneOf(";");
		strLine = strCmd.Left(nPos);
		strCmd = strCmd.Mid(nPos+1);
		if(strLine.GetAt(0)=='0')
		{
			strLine = strLine.Mid(1);
			int point;
			double pointx,pointy,pointx01,pointy01;
			point = strLine.FindOneOf(",");
			pointx = atof(strLine.Left(point));
			pointy = atof(strLine.Mid(point+1));
			double fDeltaX, fDeltaY;
			fDeltaY = pointy - ptCenter.y;
			fDeltaX = pointx - ptCenter.x;
			if( fDeltaX == 0)
			{
				if( fDeltaY > 0)
					fBeginAngle = 90.0;
				else
					fBeginAngle = 270.0;
			}
			else if( fDeltaX < 0)
			{
				fBeginAngle = atan(fDeltaY*1.0/fDeltaX)*180.0/PI + 180.0;
			}
			else
			{
				fBeginAngle = atan(fDeltaY*1.0/fDeltaX)*180.0/PI;
			}
			fRotateAngel = fBeginAngle + fDeltaAngle;
			double fLenth;
			fLenth = sqrt((pointx-ptCenter.x)*(pointx-ptCenter.x)+(pointy-ptCenter.y)*(pointy-ptCenter.y));
			
			pointx01 = fLenth*cos(fRotateAngel*PI/180)-fLenth*cos(fBeginAngle*PI/180);
			pointy01 = fLenth*sin(fRotateAngel*PI/180)-fLenth*sin(fBeginAngle*PI/180);			
			strLineResult.Format("0 %f,%f",pointx01+pointx,pointy01+pointy);

			strResult += strLineResult;
		}
		if(strLine.GetAt(0)=='1')
		{
			strLine = strLine.Mid(1);
			int point;
			double pointx,pointy,pointx01,pointy01;
			point = strLine.FindOneOf(",");
			pointx = atof(strLine.Left(point));
			pointy = atof(strLine.Mid(point+1));
						
			double fDeltaX, fDeltaY;
			fDeltaY = pointy - ptCenter.y;
			fDeltaX = pointx - ptCenter.x;
			if( fDeltaX == 0)
			{
				if( fDeltaY > 0)
					fBeginAngle = 90.0;
				else
					fBeginAngle = 270.0;
			}
			else if( fDeltaX < 0)
			{
				fBeginAngle = atan(fDeltaY*1.0/fDeltaX)*180.0/PI + 180.0;
			}
			else
			{
				fBeginAngle = atan(fDeltaY*1.0/fDeltaX)*180.0/PI;
			}
			fRotateAngel = fBeginAngle + fDeltaAngle;

			double fLenth;
			fLenth = sqrt((pointx-ptCenter.x)*(pointx-ptCenter.x)+(pointy-ptCenter.y)*(pointy-ptCenter.y));
			pointx01 = fLenth*cos(fRotateAngel*PI/180)-fLenth*cos(fBeginAngle*PI/180);
			pointy01 = fLenth*sin(fRotateAngel*PI/180)-fLenth*sin(fBeginAngle*PI/180);				
			strLineResult.Format("1 %f,%f",pointx01+pointx,pointy01+pointy);
			
			strResult += strLineResult;
		}
		if(strLine.GetAt(0)=='2')
		{
			strLine = strLine.Mid(1);
			int point;
			double pointx,pointy,pointR,pointQ,pointD,pointx01,pointy01;
			point = strLine.FindOneOf(",");
			pointx = atof(strLine.Left(point));
			strLine = strLine.Mid(point+1);
			point = strLine.FindOneOf(",");
			pointy = atof(strLine.Left(point));
			strLine = strLine.Mid(point+1);
			point = strLine.FindOneOf(",");
			pointR = atof(strLine.Left(point));
			strLine = strLine.Mid(point+1);
			point = strLine.FindOneOf(",");
			pointQ = atof(strLine.Left(point));
			pointD = atof(strLine.Mid(point+1));


			double fDeltaX, fDeltaY;
			fDeltaY = pointy - ptCenter.y;
			fDeltaX = pointx - ptCenter.x;
			if( fDeltaX == 0)
			{
				if( fDeltaY > 0)
					fBeginAngle = 90.0;
				else
					fBeginAngle = 270.0;
			}
			else if( fDeltaX < 0)
			{
				fBeginAngle = atan(fDeltaY*1.0/fDeltaX)*180.0/PI + 180.0;
			}
			else
			{
				fBeginAngle = atan(fDeltaY*1.0/fDeltaX)*180.0/PI;
			}
			fRotateAngel = fBeginAngle + fDeltaAngle;

			double fLenth;
			fLenth = sqrt((pointx-ptCenter.x)*(pointx-ptCenter.x)+(pointy-ptCenter.y)*(pointy-ptCenter.y));
			pointx01 = fLenth*cos(fRotateAngel*PI/180)-fLenth*cos(fBeginAngle*PI/180);
			pointy01 = fLenth*sin(fRotateAngel*PI/180)-fLenth*sin(fBeginAngle*PI/180);		
			
			strLineResult.Format("2 %f,%f,%f,%f,%f",pointx01+pointx,pointy01+pointy,pointR,pointQ+fDeltaAngle,pointD);
			
			strResult += strLineResult;
		}
		if( strstr(strLine,"@") != NULL )
		{
			nPos = strLine.FindOneOf("@");
			strLineResult = strLine.Mid(nPos);
			strResult += strLineResult;
		}
		strResult += ";";
		nPos = strCmd.FindOneOf(";");
	}
	
//	MessageBox(strResult);
	sprintf(m_pNodeSelect->szCmd,strResult);
}

double CDlg_Nest::GetRotateAngle(CPoint ptMouse, double &fBeginAngle, double &fRotateAngle)
{
//	double PI = acos(-1);

//	double fBeginAngle, fRotateAngle; //开始旋转时的角度和旋转到的角度		
	CRect rcBoard;
	m_pListNest.GetWindowRect(rcBoard);
	CPoint ptUp;
	ptUp.x = m_ptCatch.x;
	ptUp.y = rcBoard.Height()-m_ptCatch.y;

	int nDeltaX, nDeltaY;
	nDeltaX = ptUp.x-m_pNodeSelect->ptCenter.x;
	nDeltaY = ptUp.y-m_pNodeSelect->ptCenter.y;
	if( nDeltaX == 0)
	{
		if( nDeltaY > 0)
			fBeginAngle = 90.0;
		else
			fBeginAngle = 270.0;
	}
	else if( nDeltaX < 0)
	{
		fBeginAngle = atan(nDeltaY*1.0/nDeltaX)*180.0/PI + 180.0;
	}
	else
	{
		fBeginAngle = atan(nDeltaY*1.0/nDeltaX)*180.0/PI;
	}
	
	ptMouse.y = rcBoard.Height() - ptMouse.y;
	nDeltaX = ptMouse.x-m_pNodeSelect->ptCenter.x;
	nDeltaY = ptMouse.y-m_pNodeSelect->ptCenter.y;
	if( nDeltaX == 0)
	{
		if( nDeltaY > 0)
			fRotateAngle = 90.0;
		else
			fRotateAngle = 270.0;
	}
	else if( nDeltaX < 0)
	{
		fRotateAngle = atan(nDeltaY*1.0/nDeltaX)*180.0/PI + 180.0;
	}
	else
	{
		fRotateAngle = atan(nDeltaY*1.0/nDeltaX)*180.0/PI;
	}

	return 0.0;
}

void CDlg_Nest::InitPara()
{
	CString strPara;
	BOOL bBoardChange = FALSE;

	GetPrivateProfileString("NESTPARA","BORDER","0.00",strPara.GetBuffer(MAX_PATH),MAX_PATH,g_strGCodePath+"NestPara.ini");
	m_fBorder = atof(strPara);
	
	GetPrivateProfileString("NESTPARA","SIZEX","0.00",strPara.GetBuffer(MAX_PATH),MAX_PATH,g_strGCodePath+"NestPara.ini");
	if( m_nBoardX != atoi(strPara) )
		bBoardChange = TRUE;
	m_nBoardX = atoi(strPara);

	GetPrivateProfileString("NESTPARA","SIZEY","0.00",strPara.GetBuffer(MAX_PATH),MAX_PATH,g_strGCodePath+"NestPara.ini");
	if( m_nBoardY != atoi(strPara) )
		bBoardChange = TRUE;
	m_nBoardY = atoi(strPara);

	if( bBoardChange )
	{
		OnButtonCs5();
		m_rgnBoard.Detach();
		m_rgnBoard.CreateRectRgn(0,0,m_nBoardX,m_nBoardY);
	}
}

void CDlg_Nest::OnButtonCs1() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CDlg_Nest::OnButtonCs2() 
{
	// TODO: Add your control notification handler code here
	int nSelect = m_pList.GetCurSel();
	m_pList.DeleteString(nSelect);
	CNestNodeHead *pHead = m_pHead->pNext;
	int nCurrent =0;
	for(; pHead; pHead=pHead->pNext)
	{
		CNestNode *pNode = pHead->pDown;
		CNestNode *pLastNode;
		pLastNode = pHead->pDown;
		int nNode=0;
		for(; pNode; pNode=pNode->pNext)
		{
			if(nCurrent==nSelect)
			{
				if( nNode == 0)
				{
					pHead->pDown=pNode->pNext;
				}
				else
				{
					pLastNode->pNext=pNode->pNext;
				}
				m_rgnBoard.CombineRgn(&m_rgnBoard,&pNode->rgnRect,RGN_XOR);
				delete pNode;
				pHead->nNum--;
				OnPaint();
				return ;
			}
			pLastNode = pNode;
			nCurrent++;
			nNode++;
		}
	}
}

void CDlg_Nest::OnButtonCs3() 
{
	// TODO: Add your control notification handler code here
	
	m_nModifyMode = 0;
}

void CDlg_Nest::OnButtonCs4() 
{
	// TODO: Add your control notification handler code here
	m_nModifyMode = 1;
}

void CDlg_Nest::OnButtonCs6()	//套料参数
{
	// TODO: Add your control notification handler code here
	CDlg_NestSize dlg;
	dlg.DoModal();
	
	InitPara();
}

void CDlg_Nest::OnButtonCs8() 
{
	SaveGCode();
}

void CDlg_Nest::OnButtonCs10() 
{
	CDialog::OnCancel();
}

void CDlg_Nest::OnButtonCs5() 
{
	// TODO: Add your control notification handler code here
	CNestNodeHead *pHead = m_pHead->pNext;
	CNestNodeHead *pTempHead;
	for(; pHead;)
	{
		CNestNode *pNode = pHead->pDown;
		CNestNode *pTempNode;
		for(; pNode;)
		{
			m_rgnBoard.CombineRgn(&m_rgnBoard,&pNode->rgnRect,RGN_XOR);

			pTempNode = pNode->pNext;
			delete pNode;

			pNode = pTempNode;
		}
		pTempHead = pHead->pNext;
		delete pHead; 
		pHead=pTempHead;
	}
	m_pHead->pNext = NULL;

	m_nAddTime = 0;
	m_pTail = m_pHead;
	OnPaint();
	m_rgnBoard.Detach();
	m_rgnBoard.CreateRectRgn(0,0,m_nBoardX, m_nBoardY);
	m_pList.ResetContent();
}

void CDlg_Nest::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnTimer(nIDEvent);
}

void CDlg_Nest::FreeNestNode() 
{
	// TODO: Add your control notification handler code here
	CNestNodeHead *pHead = m_pHead->pNext;
	CNestNodeHead *pTempHead;
	for(; pHead;)
	{
		CNestNode *pNode = pHead->pDown;
		CNestNode *pTempNode;
		for(; pNode;)
		{
			m_rgnBoard.CombineRgn(&m_rgnBoard,&pNode->rgnRect,RGN_XOR);

			pTempNode = pNode->pNext;
			delete pNode;

			pNode = pTempNode;
		}
		pTempHead = pHead->pNext;
		delete pHead; 
		pHead=pTempHead;
	}
	m_pHead->pNext = NULL;
}
