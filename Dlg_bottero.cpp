// Dlg_bottero.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "Dlg_bottero.h"
#include "GraphDlg.h"/* 图库界面 */
#include "Dlg_CuttingSize.h"
#include "dlg_save.h"
#include "Dlg_KeyChar.h"
#include "benderDlg.h"
#include "RectEditDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_bottero dialog


CDlg_bottero::CDlg_bottero(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_bottero::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_bottero)
	m_strCommValue = _T("");
	//}}AFX_DATA_INIT
	
	bModifyFlag = FALSE;
}


void CDlg_bottero::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_bottero)
	DDX_Control(pDX, IDC_EDIT_VALUE, m_edtValue);
	DDX_Control(pDX, IDC_BUTTON_UPDATE, m_btnUpdate);
	DDX_Control(pDX, IDC_LIST_BOTTERO, m_lstBottero);
	DDX_Text(pDX, IDC_EDIT_VALUE, m_strCommValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_bottero, CDialog)
	//{{AFX_MSG_MAP(CDlg_bottero)
	ON_NOTIFY(NM_CLICK, IDC_LIST_BOTTERO, OnClickListBottero)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdateA)
	ON_BN_CLICKED(IDC_BUTTON_F1, OnButtonF1)
	ON_BN_CLICKED(IDC_BUTTON_F2, OnButtonF2)
	ON_BN_CLICKED(IDC_BUTTON_F3, OnButtonF3)
	ON_BN_CLICKED(IDC_BUTTON_F4, OnButtonF4)
	ON_BN_CLICKED(IDC_BUTTON_F5, OnButtonF5)
	ON_BN_CLICKED(IDC_BUTTON_F6, OnButtonF6)
	ON_WM_COPYDATA()
	ON_MESSAGE(WM_EDITDOUBLE,OnEditDouble)
	ON_BN_CLICKED(IDC_BUTTON_F10, OnButtonF10)
	ON_MESSAGE(WM_EDITDOUBLE,OnEditDouble)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_bottero message handlers

BOOL CDlg_bottero::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetWindowText("ABC");
	OnCutWindow();
	OnLanguage();
	InitButton();
	// TODO: Add extra initialization here
	strCommand.Empty();
	strOldComm.Empty();
	InitBtro();	
	g_nRemainderX = stuBtro.lMaterialX - stuBtro.lModifyX;
	g_nRemainderY = stuBtro.lMaterialY - stuBtro.lModifyY;
    m_nRemainderZ = 0;
	m_nRemainderW = 0;
	m_nRemainderQ = 0;
	m_nRemainderR = 0;
	SetWindowPos(&CWnd::wndTop,0,0,g_screen.x,g_screen.y,SWP_SHOWWINDOW);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg_bottero::InitButton()
{

	HRGN c;
	
	c = CreateRectRgn(0, 0, 0, 0);	
	GetBitMapRgn(GetDC(),c,IDB_BITMAP_EDITSET1);
	//编辑设置	
	m_pButton[0].SetFont(&g_fontStatic);
	m_pButton[0].SetBitMapID(IDB_BITMAP_EDITSET1,IDB_BITMAP_EDITSET2);	
	m_pButton[0].Create(g_strBottero[4][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(5, 714), c, this, IDC_BUTTON_F1); 
	//新建
	m_pButton[1].SetFont(&g_fontEdit);
	m_pButton[1].SetBitMapID(IDB_BITMAP_NEW1,IDB_BITMAP_NEW2);
	m_pButton[1].Create(g_strBottero[6][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(300, 714), c, this, IDC_BUTTON_F4); 
	//删除
	m_pButton[2].SetFont(&g_fontEdit);
	m_pButton[2].SetBitMapID(IDB_BITMAP_DELETE1,IDB_BITMAP_DELETE2);
	m_pButton[2].Create(g_strBottero[5][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(740, 714), c, this, IDC_BUTTON_F5); 
	//保存G
	m_pButton[3].SetFont(&g_fontEdit);
	m_pButton[3].SetBitMapID(IDB_BITMAP_SAVEG1,IDB_BITMAP_SAVEG2);	
	m_pButton[3].Create("G CODE", WS_CHILD | WS_VISIBLE, CPoint(460, 714), c, this, IDC_BUTTON_F6); 	

	//返回	
	m_pButton[4].SetFont(&g_fontEdit);
	m_pButton[4].SetBitMapID(IDB_BITMAP_BACK1,IDB_BITMAP_BACK2);	
	m_pButton[4].Create(g_strBottero[7][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(900, 714), c, this, IDC_BUTTON_F10); 
    
	//发送
	m_pButton[5].SetFont(&g_fontEdit);
	m_pButton[5].SetBitMapID(IDB_BITMAP_SAVEPAR1,IDB_BITMAP_SAVEPAR2);	
	m_pButton[5].Create(g_strBottero[0][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(600, 714), c, this, IDC_BUTTON_F2); 

	//矩形编辑
	CString str;
	if (g_iLanguage == 0)
	{
		str = "矩形编辑";
	}
	else
	{
		str = "Rect Edit";
	}
	m_pButton[6].SetFont(&g_fontStatic);
	m_pButton[6].SetBitMapID(IDB_BITMAP_NEST1,IDB_BITMAP_NEST2);	
	m_pButton[6].Create(str, WS_CHILD | WS_VISIBLE, CPoint(150, 714), c, this, IDC_BUTTON_F3); 

	DeleteObject(c);  	
 
	m_edtValue.SetFont(&g_fontEdit);
	m_btnUpdate.SetIconOption(IDI_ICON_COMOK);
	SetWindowPos(CWnd::GetOwner(),0,0,1024,768,SWP_SHOWWINDOW);
}

void CDlg_bottero::InitBtro()
{
	nCountComm = 0;
	pFirstComm = pCurrComm = pLastComm = NULL;
	pCommX = pCommY = pCommZ = pCommW = pCommQ = pCommR = NULL;
	fValueX = fValueY = fValueZ = fValueW = fValueQ = fValueR = 0.0;
	fOldValue = 0.0;
	/* 初始化命令总结构 */
	memset(&stuBtro,0,sizeof(stuBottero));
	stuBtro.lMaterialX = g_stu_pAxisB->sSpareA;	/* 长 */
	stuBtro.lMaterialY = g_stu_pAxisB->sSpareB;	/* 宽 */
	stuBtro.lModifyX = g_stu_pAxisB->sSpareC;	/* 长_修边 */
	stuBtro.lModifyY = g_stu_pAxisB->sSpareD;	/* 宽_修边 */
	stuBtro.fLeft = stuBtro.fRight = (float)stuBtro.lModifyX;
	stuBtro.fBottom = (float)stuBtro.lModifyY;
	stuBtro.fTop = (float)stuBtro.lMaterialY - stuBtro.fBottom;
	/* 初始化命令总结构 */
	CString	strTempM, strTempG, strTempB;

	if(!g_iLanguage)
	{
		strTempM.Format("机床 %.0f*%.0f", g_stu_pAxisA->dSpareA, g_stu_pAxisB->dSpareA);
		strTempG.Format("玻璃 %d*%d", g_stu_pAxisB->sSpareA, g_stu_pAxisB->sSpareB);
		strTempB.Format("修边 %d*%d", g_stu_pAxisB->sSpareC, g_stu_pAxisB->sSpareD);
	}
	else
	{
		strTempM.Format("Machine  %.0f*%.0f", g_stu_pAxisA->dSpareA, g_stu_pAxisB->dSpareA);
		strTempG.Format("Glass	  %d*%d", g_stu_pAxisB->sSpareA, g_stu_pAxisB->sSpareB);
		strTempB.Format("Trimming %d*%d", g_stu_pAxisB->sSpareC, g_stu_pAxisB->sSpareD);
	}
	SetDlgItemText(IDC_STATIC_MACHINE, strTempM);
	SetDlgItemText(IDC_STATIC_GLASS, strTempG);
	SetDlgItemText(IDC_STATIC_BORDER, strTempB);

	CString str;
	str.Format("%d",stuBtro.lMaterialX-stuBtro.lModifyX);
	SetDlgItemText(IDC_STATICXMAX,str);
	SetDlgItemText(IDC_STATICXREMAIN,str);
	str.Format("%d",stuBtro.lMaterialY-stuBtro.lModifyY);
	SetDlgItemText(IDC_STATICYMAX,str);	
}

void CDlg_bottero::OnClickListBottero(NMHDR* pNMHDR, LRESULT* pResult) 
{
	POSITION p = m_lstBottero.GetFirstSelectedItemPosition();
	*pResult = 0;
}

pSegment CDlg_bottero::OnAddSegment(pSegment stuCurrSegment) 
{
	pSegment	stuTempSegment;
	stuTempSegment = new Segment;
	memset(stuTempSegment,0,sizeof(Segment));
	stuTempSegment->Prev = stuCurrSegment;
	if(stuCurrSegment)	stuCurrSegment->Next = stuTempSegment;
	else				stuCurrSegment = stuTempSegment;
	return stuTempSegment;
}

p_Command CDlg_bottero::OnAddBotteroCommand(p_Command stuCurrCurr) 
{
	p_Command	stuTempCommand;
	stuTempCommand = new stuBotteroCommand;
	memset(stuTempCommand,0,sizeof(stuBotteroCommand));
	stuTempCommand->Prev = stuCurrCurr;
	if(stuCurrCurr)
	{
		stuCurrCurr->Next = stuTempCommand;
		stuTempCommand->nIndex = stuCurrCurr->nIndex + 1;
	}
	else
	{
		stuCurrCurr = stuTempCommand;
		stuTempCommand->nIndex = 0;
	}
	stuTempCommand->nMultiple = 1;
	return stuTempCommand;
}

POINT2D CDlg_bottero::OnGetBiasEndValue(char chCom,pSegment stu_pSegmentX,pSegment stu_pSegmentY,p_Command pCommX,p_Command pCommY,float fValue) /* 获取斜线端点值 */
{
	POINT2D	p;
	switch(chCom) 
	{
	case 'A':
		p.x = stu_pSegmentX->fBeginX - pCommX->nValue + fValue;
		p.y = stu_pSegmentY->fBeginY - pCommY->nValue;
		break;
	case 'B':
		p.x = stu_pSegmentX->fBeginX;
		p.y = stu_pSegmentY->fBeginY  - pCommY->nValue + fValue;
		break;
	case 'C':
		p.x = stu_pSegmentX->fBeginX - pCommX->nValue;
		p.y = stu_pSegmentY->fBeginY - pCommY->nValue + fValue;
		break;
	case 'D':
		p.x = stu_pSegmentX->fBeginX - pCommX->nValue + fValue;
		p.y = stu_pSegmentY->fBeginY;
		break;
	default:
		break;
	}
	return p;
}

POINT2D CDlg_bottero::OnGetBaseRectPoint(pSegment stu_pSegmentX,pSegment stu_pSegmentY,p_Command pCommX,p_Command pCommY) /* 获取斜线端点值 */
{
	POINT2D	p;
	p.x = stu_pSegmentX->fBeginX - pCommX->nValue;
	p.y = stu_pSegmentY->fBeginY - pCommY->nValue;
	return p;
}

/*返回异形的矩形的大小，即长乘宽，暂时未用aaa,在图库参数里使用了 */
POINT2D CDlg_bottero::OnGetBaseRect(CString strText) /* 获取斜线端点值 */
{
	POINT2D	p2D;
	int		nMaxx, nMaxy;
	nMaxx = atoi(strText);
	int nPos = strText.FindOneOf(",");
	strText = strText.Mid(nPos+1);
	nMaxy = atoi(strText);
	
	p2D.x = nMaxx + g_stu_pAxisC->sSpareA + g_stu_pAxisC->sSpareB;
	p2D.y = nMaxy + g_stu_pAxisC->sSpareD + g_stu_pAxisC->sSpareC;
	return p2D;
}

BOOL CDlg_bottero::CombinationLines(int n,pSegment stu_pSegment)	//合并重刀线
{
	p_Command	tempComm;
	pSegment	tempSegt;
	BOOL	bCombin = FALSE;
	if(stu_pSegment==NULL)	return bCombin;
	if(n==0)		/* X方向直线 */
	{
		long bx0,bx1,bx2,bx3;
		bx0 = (long)(stu_pSegment->fBeginX*1000);
		bx1 = (long)(stu_pSegment->fEndX*1000);
		for(tempComm = stuBtro.BtroComm;tempComm;tempComm=tempComm->Next)
		{
			if(tempComm->chCom=='Y'||tempComm->chCom=='W'||tempComm->chCom=='R')
			{
				for(tempSegt = tempComm->pStuSegment;tempSegt;tempSegt=tempSegt->Next)
				{
					if(!tempSegt->bDirect && stu_pSegment!=tempSegt)
					{
						bx2 = (long)(tempSegt->fBeginX*1000);
						bx3 = (long)(tempSegt->fEndX*1000);
						if((long)(stu_pSegment->fBeginY*1000)==(long)(tempSegt->fBeginY*1000))
						{
							if(bx0>bx1)
							{
								if((bx2<=bx0 && bx2>=bx1) || (bx3<=bx0 && bx3>=bx1))
									CombinationLineX(stu_pSegment,tempSegt);
							}
							else
							{
								if((bx2>=bx0 && bx2<=bx1) || (bx3>=bx0 && bx3<=bx1))
									CombinationLineX(stu_pSegment,tempSegt);
							}
							if(bx2>bx3)
							{
								if((bx0<=bx2 && bx0>=bx3) || (bx1<=bx2 && bx1>=bx3))
									CombinationLineX(stu_pSegment,tempSegt);
							}
							else
							{
								if((bx0>=bx2 && bx0<=bx3) || (bx1>=bx2 && bx1<=bx3))
									CombinationLineX(stu_pSegment,tempSegt);
							}
						}
					}
					/* 比较Y值，接近于原片尺寸，此刀路不切 */
					if((tempSegt->fEndY + g_stu_pAxisH->dSpareC)>=stuBtro.lMaterialY)
						tempSegt->bDirect = TRUE;
				}	/* 线段循环体 */
			}
		}		/* 命令循环体 */
	}
	else if(n==1)		/* Y方向直线 */
	{
		long by0,by1,by2,by3;
		by0 = (long)(stu_pSegment->fBeginY*1000);
		by1 = (long)(stu_pSegment->fEndY*1000);
		for(tempComm = stuBtro.BtroComm;tempComm;tempComm=tempComm->Next)
		{
			if(tempComm->chCom=='X'||tempComm->chCom=='Z'||tempComm->chCom=='Q')
			{
				for(tempSegt = tempComm->pStuSegment;tempSegt;tempSegt=tempSegt->Next)
				{					
					if(!tempSegt->bDirect && stu_pSegment!=tempSegt)
					{
						by2 = (long)(tempSegt->fBeginY*1000);
						by3 = (long)(tempSegt->fEndY*1000);
						if((long)(stu_pSegment->fBeginX*1000)==(long)(tempSegt->fBeginX*1000))
						{
							if(by0>by1)
							{
								if((by2<=by0 && by2>=by1) || (by3<=by0 && by3>=by1))
									CombinationLineY(stu_pSegment,tempSegt);
							}
							else
							{
								if((by2>=by0 && by2<=by1) || (by3>=by0 && by3<=by1))
									CombinationLineY(stu_pSegment,tempSegt);
							}
							if(by2>by3)
							{
								if((by0<=by2 && by0>=by3) || (by1<=by2 && by1>=by3))
									CombinationLineY(stu_pSegment,tempSegt);
							}
							else
							{
								if((by0>=by2 && by0<=by3) || (by1>=by2 && by1<=by3))
									CombinationLineY(stu_pSegment,tempSegt);
							}
						}
					}
					/* 比较X值，接近于原片尺寸，此刀路不切 */
					if((tempSegt->fEndX + g_stu_pAxisH->dSpareC)>=stuBtro.lMaterialX)
						tempSegt->bDirect = TRUE;
				}	/* 线段循环体 */
			}
		}		/* 命令循环体 */
	}
	return bCombin;
}

void CDlg_bottero::CombinationLineX(pSegment pSegment1,pSegment pSegment2)	//向前合并X方向的线
{
	float dMax,dMin;
	if(pSegment1->fBeginX>pSegment1->fEndX)		{	dMax = pSegment1->fBeginX;	dMin = pSegment1->fEndX; }
	else										{	dMax = pSegment1->fEndX;	dMin = pSegment1->fBeginX; }
	if(pSegment2->fBeginX>dMax)		dMax = pSegment2->fBeginX;
	if(pSegment2->fEndX>dMax)		dMax = pSegment2->fEndX;
	if(pSegment2->fBeginX<dMin)		dMin = pSegment2->fBeginX;
	if(pSegment2->fEndX<dMin)		dMin = pSegment2->fEndX;
	if(pSegment1->fBeginX>pSegment1->fEndX)
	{
		pSegment1->fBeginX = dMax;
		pSegment1->fEndX = dMin;
	}
	else
	{
		pSegment1->fBeginX = dMin;
		pSegment1->fEndX = dMax;
	}
	pSegment2->bDirect = TRUE;
}

void CDlg_bottero::CombinationLineY(pSegment pSegment1,pSegment pSegment2)	//向前合并X方向的线
{
	float dMax,dMin;
	if(pSegment1->fBeginY>pSegment1->fEndY)		{	dMax = pSegment1->fBeginY;	dMin = pSegment1->fEndY; }
	else										{	dMax = pSegment1->fEndY;	dMin = pSegment1->fBeginY; }
	if(pSegment2->fBeginY>dMax)		dMax = pSegment2->fBeginY;
	if(pSegment2->fEndY>dMax)		dMax = pSegment2->fEndY;
	if(pSegment2->fBeginY<dMin)		dMin = pSegment2->fBeginY;
	if(pSegment2->fEndY<dMin)		dMin = pSegment2->fEndY;
	if(pSegment1->fBeginY>pSegment1->fEndY)
	{
		pSegment1->fBeginY = dMax;
		pSegment1->fEndY = dMin;
	}
	else
	{
		pSegment1->fBeginY = dMin;
		pSegment1->fEndY = dMax;
	}
	pSegment2->bDirect = TRUE;
}

void CDlg_bottero::CombinationAllLines()	//合并重刀线
{
	p_Command	tempComm;
	pSegment	tempSegt;
	for(tempComm = stuBtro.BtroComm;tempComm;tempComm=tempComm->Next)
	{
		if(tempComm->chCom=='Y'||tempComm->chCom=='W'||tempComm->chCom=='R')
		{
			for(tempSegt = tempComm->pStuSegment;tempSegt;tempSegt=tempSegt->Next)
			{
				if(!tempSegt->bDirect)
				CombinationLines(0,tempSegt);
			}
		}
		else if(tempComm->chCom=='X'||tempComm->chCom=='Z'||tempComm->chCom=='Q')
		{
			for(tempSegt = tempComm->pStuSegment;tempSegt;tempSegt=tempSegt->Next)
			{
				if(!tempSegt->bDirect)
					CombinationLines(1,tempSegt);
			}
		}
	}
}

void CDlg_bottero::CommandCovAutocadScript()//保存为Autocad的脚本文件
{
	p_Command	tempComm;
	pSegment	tempSegt;
    dlg_save  dlgSave;
	
	dlgSave.strExtName = ".cxf";
	if (IDC_BUTTON8 == dlgSave.DoModal())  return;
	begin();
    g_strSavefile = "";
	
	limits(0, 0, 3000, 2000);
	zooma();
	CombinationAllLines();
	/* 判断是否有修边 */
	if(stuBtro.lModifyX>2)
	{
	//	line(g_stu_pAxisH->dSpareC, (float)(stuBtro.lModifyY), (float)(stuBtro.lMaterialX), (float)(stuBtro.lModifyY));
		line((float)g_stu_pAxisH->dSpareC, (float)(stuBtro.lModifyY), (float)(stuBtro.lMaterialX) - (float)g_stu_pAxisH->dSpareC, (float)(stuBtro.lModifyY));
	}
	if(stuBtro.lModifyY>2)
	{
		line((float)(stuBtro.lModifyX), (float)g_stu_pAxisH->dSpareC, (float)(stuBtro.lModifyX), (float)(stuBtro.lMaterialY) - (float)g_stu_pAxisH->dSpareC);
	}
	for(tempComm = stuBtro.BtroComm;tempComm;tempComm=tempComm->Next)
	{
		for(tempSegt = tempComm->pStuSegment;tempSegt;tempSegt=tempSegt->Next)
		{
			if(tempSegt->bIsLine)
			{
				if(!tempSegt->bDirect)
				{
					if(tempComm->chCom=='X'|| tempComm->chCom=='Z'|| tempComm->chCom=='Q')
					{
						if(g_stu_pAxisH->dSpareC > tempSegt->fBeginY)
							line(tempSegt->fBeginX, (float)g_stu_pAxisH->dSpareC, tempSegt->fEndX, tempSegt->fEndY);
						else
							line(tempSegt->fBeginX, tempSegt->fBeginY, tempSegt->fEndX, tempSegt->fEndY);
					}
					else if(tempComm->chCom=='Y'|| tempComm->chCom=='W'|| tempComm->chCom=='R')
					{
						if(g_stu_pAxisH->dSpareC > tempSegt->fBeginX)
							line((float)g_stu_pAxisH->dSpareC, tempSegt->fBeginY, tempSegt->fEndX, tempSegt->fEndY);
						else
							line(tempSegt->fBeginX, tempSegt->fBeginY, tempSegt->fEndX, tempSegt->fEndY);
					}
					else
					{
						line(tempSegt->fBeginX, tempSegt->fBeginY, tempSegt->fEndX, tempSegt->fEndY);
					}
				}
			}
			else 
			{
				if(!tempSegt->bDirect)/* 圆心、起点、终点 */
				{
					Arc(tempSegt->pSegArc->fCenterX, tempSegt->pSegArc->fCenterY, tempSegt->fBeginX, tempSegt->fBeginY, tempSegt->fEndX, tempSegt->fEndY);
				}
				else
				{
					Arc(tempSegt->pSegArc->fCenterX, tempSegt->pSegArc->fCenterY, tempSegt->fEndX, tempSegt->fEndY, tempSegt->fBeginX, tempSegt->fBeginY);
				}
			}
		}
	}
	gend();
}

void CDlg_bottero::gend()
{
	//	//关闭文件
	file.close();
}

void CDlg_bottero::line(float x0, float y0, float x3, float y3)
{
	file<<"LINE"<<' '<<x0<<','<<y0<<' '<<x3<<','<<y3<<' '<<'\n';
}

/* 圆心、起点、终点 */
void CDlg_bottero::Arc(float x0, float y0, float x2, float y2, float x3, float y3)
{
	file<<"ARC C"<<' '<<x0<<','<<y0<<' '<<x2<<','<<y2<<' '<<x3<<','<<y3<<'\n';
}

void CDlg_bottero::zooma()
{
	//全屏显示
	file<<"ZOOM"<<' '<<"A"<<'\n';
}

void CDlg_bottero::limits(float x, float y, float x4, float y4)
{
	//确定绘图界限
	file<<"LIMITS"<<' '<<x<<','<<y<<' '<<x4<<','<<y4<<'\n';
}

void CDlg_bottero::begin()
{
	file.open(g_strOriginalPathD + "glass\\" + g_strSavefile, ios::out);//生成或打开文件
}

void CDlg_bottero::OnButtonF1() 
{
	if(!pCommX)
	{
		CDlg_CuttingSize	dlg_size;
		dlg_size.DoModal();
		InitBtro();
		((CBenderDlg *)GetParent())->DrawBottero();
	}
}

void CDlg_bottero::OnButtonF2() 
{
	if(stuBtro.BtroComm)
	{
		CommandCovGcode(1);
		bModifyFlag = FALSE;
		((CBenderDlg *)GetParent())->DrawBottero();
		OnFreeCommand(stuBtro.BtroComm);
	    CDialog::OnOK();
	}	
}

void CDlg_bottero::OnButtonF3()
{
	CRectEditDlg dlg;
	if (IDOK == dlg.DoModal())
	{
		((CBenderDlg *)GetParent())->DrawBottero();
		CDialog::OnOK();
	}
}
void CDlg_bottero::OnButtonF4() 
{
	OnFreeCommand(stuBtro.BtroComm);
	strCommand.Empty();
	strOldComm.Empty();
	InitBtro();
	m_lstBottero.DeleteAllItems();
	((CBenderDlg *)GetParent())->DrawBottero();
}

void CDlg_bottero::OnButtonF5() /* 删除，释放数据结构 */
{
	if(!strOldComm.IsEmpty())
	{
		strOldComm.Empty();
		fOldValue = 0.0;
		m_lstBottero.DeleteItem(m_lstBottero.GetItemCount() - 1);
	}
	else if(pLastComm && pLastComm->Prev)
	{
		p_Command	pComm;
		char		ch;
		double		dValueTemp;
		int			nMulti;
		ch = pLastComm->chCom;
		dValueTemp = pLastComm->nValue;
		pCurrComm = pLastComm->Prev;
		nMulti = pLastComm->nMultiple;
		switch(ch) 
		{
		case 'X':
			fValueX = (float)(stuBtro.fRight - dValueTemp);
			stuBtro.fRight = fValueX;
			stuBtro.fLeft = stuBtro.fRight - pCurrComm->nValue;
			break;
		case 'Y':
			fValueY = (float)(stuBtro.fTop - dValueTemp);
			stuBtro.fTop = fValueY;
			stuBtro.fBottom = stuBtro.fTop - pCurrComm->nValue;
			break;
		default:
			break;
		}
		OnFreeLastCommand(pLastComm);
		pLastComm = pCurrComm;
		pLastComm->Next = NULL;

		/* 更新LIST框 */
		m_lstBottero.DeleteItem(m_lstBottero.GetItemCount() - 1);
		if(ch=='A' || ch=='B' || ch=='C' || ch=='D' || nMulti>1)
			m_lstBottero.DeleteItem(m_lstBottero.GetItemCount() - 1);
		
		for(pComm=stuBtro.BtroComm; pComm; pComm=pComm->Next)
		{
			switch(pComm->chCom) 
			{
			case 'X':
				pCommX = pComm;
				break;
			case 'Y':
				pCommY = pComm;
				break;
			case 'Z':
				pCommZ = pComm;
				break;
			case 'W':
				pCommW = pComm;
				break;
			case 'Q':
				pCommQ = pComm;
				break;
			case 'R':
				pCommR = pComm;
				break;
			default:
				break;
			}
		}
		if (pCurrComm->pRect != NULL)
		{
			pCurrComm->pRect->nDraw = 1;
		}
		CString str;
		pSegment	stuTempSegment;
		stuTempSegment = pCurrComm->pStuSegment;
		double dValueX=.0;
		double dValueY=.0;
		switch(pLastComm->chCom) 
		{
		case 'X':
			pCommY = NULL;
			pCommZ = NULL;
			pCommW = NULL;
			pCommQ = NULL;
			pCommR = NULL;
			DataShowClear();
			dValueX = (pCommX->pStuSegment->fBeginX + (pCommX->nMultiple-1) * pCommX->nValue);//x剩余
			str.Format("%.f",stuBtro.lMaterialX-dValueX);					
			SetDlgItemText(IDC_STATICXREMAIN,str);
			g_nRemainderX = (int)(stuBtro.lMaterialX-dValueX);

			str.Format("%d",stuBtro.lMaterialY-stuBtro.lModifyY);//Y剩余
			SetDlgItemText(IDC_STATICYREMAIN,str);
			g_nRemainderY = (int)(stuBtro.lMaterialY-stuBtro.lModifyY);
		    break;
		case 'Y':
			pCommZ = NULL;
			pCommW = NULL;
			pCommQ = NULL;
			pCommR = NULL;
			DataShowClear();
			dValueX = pCommX->pStuSegment->fBeginX + (pCommX->nMultiple-1) * pCommX->nValue;//x剩余
 			str.Format("%.f",stuBtro.lMaterialX - dValueX);					
			SetDlgItemText(IDC_STATICXREMAIN,str);
            g_nRemainderX = int(stuBtro.lMaterialX - dValueX);

            dValueY = pCommY->pStuSegment->fBeginY + (pCommY->nMultiple-1)*pCommY->nValue;//Y剩余
			str.Format("%.f",stuBtro.lMaterialY-dValueY);
			SetDlgItemText(IDC_STATICYREMAIN,str);				
			g_nRemainderY = int(stuBtro.lMaterialY-dValueY);

			str.Format("%.f",pCommX->nValue);					
			SetDlgItemText(IDC_STATICZMAX,str);//Z最大
			SetDlgItemText(IDC_STATICZREMAIN,str);//Z剩余
			
			str.Format("%.f",pCommY->nValue);					
			SetDlgItemText(IDC_STATICWMAX,str);//W最大			
 
			break;
		case 'Z':
			pCommW = NULL;
			pCommQ = NULL;
			pCommR = NULL;
			DataShowClear();
			dValueX = pCommX->pStuSegment->fBeginX + (pCommX->nMultiple-1) * pCommX->nValue;//x剩余
			str.Format("%.f",stuBtro.lMaterialX - dValueX);					
			SetDlgItemText(IDC_STATICXREMAIN,str);
            g_nRemainderX = int(stuBtro.lMaterialX - dValueX);
			
            dValueY = pCommY->pStuSegment->fBeginY + (pCommY->nMultiple-1)*pCommY->nValue;//Y剩余
			str.Format("%.f",stuBtro.lMaterialY-dValueY);
			SetDlgItemText(IDC_STATICYREMAIN,str);				
			g_nRemainderY = int(stuBtro.lMaterialY-dValueY);

			str.Format("%.f",pCommX->nValue);					
			SetDlgItemText(IDC_STATICZMAX,str);//Z最大

			if (pCommX)
			{					
				str.Format("%.f",pCommX->nValue-pCommZ->fTotalDis);					
				SetDlgItemText(IDC_STATICZREMAIN,str);//Z剩余
				m_nRemainderZ = (int)pCommX->nValue-pCommZ->fTotalDis;
			}			
			str.Format("%.f",pCommY->nValue);					
			SetDlgItemText(IDC_STATICWMAX,str);//W最大
			break;
		case 'W':
			pCommQ = NULL;
			pCommR = NULL;

            DataShowClear();
			dValueX = pCommX->pStuSegment->fBeginX + (pCommX->nMultiple-1) * pCommX->nValue;//x剩余
			str.Format("%.f",stuBtro.lMaterialX - dValueX);					
			SetDlgItemText(IDC_STATICXREMAIN,str);
            g_nRemainderX = int(stuBtro.lMaterialX - dValueX);
			
            dValueY = pCommY->pStuSegment->fBeginY + (pCommY->nMultiple-1)*pCommY->nValue;//Y剩余
			str.Format("%.f",stuBtro.lMaterialY-dValueY);
			SetDlgItemText(IDC_STATICYREMAIN,str);				
			g_nRemainderY = int(stuBtro.lMaterialY-dValueY);

			str.Format("%.f",pCommX->nValue);					
			SetDlgItemText(IDC_STATICZMAX,str);//Z最大
			
			if (pCommX)
			{					
				str.Format("%.f",pCommX->nValue-pCommZ->fTotalDis);					
				SetDlgItemText(IDC_STATICZREMAIN,str);//Z剩余
				m_nRemainderZ = int(pCommX->nValue-pCommZ->fTotalDis);
			}			
			str.Format("%.f",pCommY->nValue);					
			SetDlgItemText(IDC_STATICWMAX,str);//W最大

			if(pCommY)
			{
				str.Format("%.f",pCommY->nValue-pCommW->fTotalDis);
				SetDlgItemText(IDC_STATICWREMAIN,str);//W剩余	
				m_nRemainderW = int(pCommY->nValue-pCommW->fTotalDis);
			}
			if (pCommZ)
			{
				str.Format("%.f",pCommZ->nValue);
				SetDlgItemText(IDC_STATICQMAX,str);//Q最大
				SetDlgItemText(IDC_STATICQREMAIN,str);//Q剩余
			} 
			break;
		case 'Q':
			pCommR = NULL;
			//
			DataShowClear();
            dValueX = pCommX->pStuSegment->fBeginX + (pCommX->nMultiple-1) * pCommX->nValue;//x剩余
 			str.Format("%.f",stuBtro.lMaterialX - dValueX);					
			SetDlgItemText(IDC_STATICXREMAIN,str);
            g_nRemainderX = int(stuBtro.lMaterialX - dValueX);

            dValueY = pCommY->pStuSegment->fBeginY + (pCommY->nMultiple-1)*pCommY->nValue;//Y剩余
			str.Format("%.f",stuBtro.lMaterialY-dValueY);
			SetDlgItemText(IDC_STATICYREMAIN,str);				
			g_nRemainderY = int(stuBtro.lMaterialY-dValueY);
			str.Format("%.f",pCommX->nValue);					
			SetDlgItemText(IDC_STATICZMAX,str);//Z最大

			
			if (pCommX)
			{					
				str.Format("%.f",pCommX->nValue-pCommZ->fTotalDis);					
				SetDlgItemText(IDC_STATICZREMAIN,str);//Z剩余	
				m_nRemainderZ = int(pCommX->nValue-pCommZ->fTotalDis);
			}			
			str.Format("%.f",pCommY->nValue);					
			SetDlgItemText(IDC_STATICWMAX,str);//W最大
			
			
			if(pCommY)
			{
				str.Format("%.f",pCommY->nValue-pCommW->fTotalDis);
				SetDlgItemText(IDC_STATICWREMAIN,str);//W剩余
				m_nRemainderW = int(pCommY->nValue-pCommW->fTotalDis);
			}
			if (pCommZ)
			{
				str.Format("%.f",pCommZ->nValue);
				SetDlgItemText(IDC_STATICQMAX,str);//Q最大				
			} 

			if (pCommZ)
			{
				str.Format("%.f",pCommZ->nValue - pCommQ->fTotalDis);
				SetDlgItemText(IDC_STATICQREMAIN,str);//Q剩余
				m_nRemainderQ = int(pCommZ->nValue - pCommQ->fTotalDis);
			}
			
			if (pCommW)
			{
				str.Format("%.f",pCommW->nValue);
				SetDlgItemText(IDC_STATICRMAX,str);//R最大					
			}
			//
			break;
		case 'R':
			//
			DataShowClear();
			dValueX = pCommX->pStuSegment->fBeginX + (pCommX->nMultiple-1) * pCommX->nValue;//x剩余
			str.Format("%.f",stuBtro.lMaterialX - dValueX);					
			SetDlgItemText(IDC_STATICXREMAIN,str);
            g_nRemainderX = int(stuBtro.lMaterialX - dValueX);
			
            dValueY = pCommY->pStuSegment->fBeginY + (pCommY->nMultiple-1)*pCommY->nValue;//Y剩余
			str.Format("%.f",stuBtro.lMaterialY-dValueY);
			SetDlgItemText(IDC_STATICYREMAIN,str);				
			g_nRemainderY = int(stuBtro.lMaterialY-dValueY);
			str.Format("%.f",pCommX->nValue);					
			SetDlgItemText(IDC_STATICZMAX,str);//Z最大
			
			if (pCommX)
			{					
				str.Format("%.f",pCommX->nValue-pCommZ->fTotalDis);					
				SetDlgItemText(IDC_STATICZREMAIN,str);//Z剩余
				m_nRemainderZ = int(pCommX->nValue-pCommZ->fTotalDis);
			}			
			str.Format("%.f",pCommY->nValue);					
			SetDlgItemText(IDC_STATICWMAX,str);//W最大		
	

			if(pCommY)
			{
				str.Format("%.f",pCommY->nValue-pCommW->fTotalDis);
				SetDlgItemText(IDC_STATICWREMAIN,str);//W剩余
				m_nRemainderW = int(pCommY->nValue-pCommW->fTotalDis);
			}
			if (pCommZ)
			{
				str.Format("%.f",pCommZ->nValue);
				SetDlgItemText(IDC_STATICQMAX,str);//Q最大				
			} 
			
			if (pCommZ)
			{
				str.Format("%.f",pCommZ->nValue - pCommQ->fTotalDis);
				SetDlgItemText(IDC_STATICQREMAIN,str);//Q剩余
				m_nRemainderQ = int(pCommZ->nValue - pCommQ->fTotalDis);
			}
			
			if (pCommW)
			{
				str.Format("%.f",pCommW->nValue);
				SetDlgItemText(IDC_STATICRMAX,str);//R最大					
			}
			if (pCommW)
			{
				str.Format("%.f",pCommW->nValue-pCommR->fTotalDis);
				SetDlgItemText(IDC_STATICRREMAIN,str);//R剩余
				m_nRemainderR = int(pCommW->nValue-pCommR->fTotalDis);
			}
			//
			break;
		default:
			break;
		}
	}
	else
	{
		OnFreeCommand(stuBtro.BtroComm);
		strCommand.Empty();
		strOldComm.Empty();
		InitBtro();
		m_lstBottero.DeleteAllItems();
	}
	((CBenderDlg *)GetParent())->DrawBottero();
}

void CDlg_bottero::OnButtonF6() 
{
	if(stuBtro.BtroComm)
	{
		CommandCovGcode(0);
		bModifyFlag = FALSE;	    
	}
}

void CDlg_bottero::OnButtonF10() 
{
	if(bModifyFlag)
	{
		int	nRe;
		nRe = OnShowMessageBox(19, g_iLanguage);
		if(nRe==IDYES)
		{
			return;
		}
		else
		{
			OnFreeCommand(stuBtro.BtroComm);
			CDialog::OnCancel();
		}
	}
	OnFreeCommand(stuBtro.BtroComm);
	CDialog::OnOK();
}

BOOL CDlg_bottero::OnValidCommand(char ch,float fValue) 
{
	pSegment	pLastSegt;
	double		dTemp;
	POINT2D		pdRect;
	int			nMulti = 1;

	BOOL	bValid = TRUE;/* 是否是有效命令 */
	if(pCurrComm)
	{
		if(pCurrComm->nMultiple>1 && pCurrComm->chCom==0)
			nMulti = pCurrComm->nMultiple;
	}

	switch(ch) 
	{
	case 'X':
		if(pCommX)
		{
			pLastSegt = GetLastSegment(pCommX);
			dTemp = pLastSegt->fEndX;
			if((pLastSegt->fEndX + nMulti * fValue)>(stuBtro.lMaterialX - stuBtro.lModifyX))	
				bValid = FALSE;
		}
		else/* 数值大于原片大小 */
		{
			if((nMulti * fValue)>(stuBtro.lMaterialX - stuBtro.lModifyX))		
				bValid = FALSE;		
		}
        
		break;
	case 'Y':
		if(!pCommX)
		{
			bValid = FALSE;
			break;
		}
		if(pCommY)
		{
			pLastSegt = GetLastSegment(pCommY);
			dTemp = pLastSegt->fEndY;
			if((pLastSegt->fEndY+nMulti * fValue)>(stuBtro.lMaterialY - stuBtro.lModifyY))	
				bValid = FALSE;
		}
		else/* 数值大于原片大小 */
		{
			if((nMulti * fValue)>(stuBtro.lMaterialY - stuBtro.lModifyY))		
				bValid = FALSE;
		}
		break;
	case 'Z':
		if(!pCommY)
		{
			bValid = FALSE;
			break;
		}
		if(pCommZ)
		{
			if((long)((nMulti * fValue - pCommX->nValue + pCommZ->fTotalDis) * 1000)>=0)	
				bValid = FALSE;
		}
		else/* 数值大于原片大小 */
		{
			if((long)((nMulti * fValue-pCommX->nValue) * 1000)>=0)	
				bValid = FALSE;
		}
		break;
	case 'W':
		if(!pCommZ)
		{
			bValid = FALSE;
			break;
		}
		if(pCommW)
		{
			if((long)((nMulti * fValue - pCommY->nValue + pCommW->fTotalDis) * 1000)>=0)	
				bValid = FALSE;
		}
		else/* 数值大于原片大小 */
		{
			if((long)((nMulti * fValue-pCommY->nValue) * 1000)>=0)	
				bValid = FALSE;
		}
		break;
	case 'Q':
		if(!pCommW)
		{
			bValid = FALSE;
			break;
		}
		if(pCommQ)
		{
			if((long)((nMulti * fValue - pCommZ->nValue + pCommQ->fTotalDis) * 1000)>=0)	
				bValid = FALSE;
		}
		else/* 数值大于原片大小 */
		{
			if((long)((nMulti * fValue-pCommZ->nValue) * 1000)>=0)	
				bValid = FALSE;
		}
		break;
	case 'R':
		if(!pCommQ)
		{
			bValid = FALSE;
			break;
		}
		if(pCommR)
		{
			if((long)((nMulti * fValue - pCommW->nValue + pCommR->fTotalDis) * 1000)>=0)	
				bValid = FALSE;
		}
		else/* 数值大于原片大小 */
		{
			if((long)((nMulti * fValue-pCommW->nValue) * 1000)>=0)	
				bValid = FALSE;
		}
		break;
	case 'A':
	case 'D':
		if(!pCommY)
		{
			bValid = FALSE;
			break;
		}
		pdRect = GetCurrRect();
		if(fValue>pdRect.x)
			bValid = FALSE;
		break;
	case 'B':
	case 'C':
		if(!pCommY)
		{
			bValid = FALSE;
			break;
		}
		pdRect = GetCurrRect();
		if(fValue>pdRect.y)
			bValid = FALSE;
		break;
	case 'M':
		if((long)fValue<=1)		
			bValid = FALSE;
		break;
	case 'P':
		if(!pCommY)
			bValid = FALSE;
		break;
	default:
		bValid = FALSE;
		break;
	}
	return bValid;
}

pSegment CDlg_bottero::GetLastSegment(p_Command pComm)//获得最后一个数据段
{
	pSegment	tempSegt,pLastSegt;
	for(tempSegt = pComm->pStuSegment;tempSegt;tempSegt=tempSegt->Next)
	{
		if(tempSegt)
		{
			pLastSegt = tempSegt;
		}
	}
	return pLastSegt;
}

POINT2D CDlg_bottero::GetCurrRect()//获得最后一个数据段
{
	POINT2D		pPoint;
	if(pCommR)
	{
		pPoint.x = pCommQ->nValue;
		pPoint.y = pCommR->nValue;
	}
	else if(pCommQ)
	{
		pPoint.x = pCommQ->nValue;
		pPoint.y = pCommW->nValue;
	}
	else if(pCommW)
	{
		pPoint.x = pCommZ->nValue;
		pPoint.y = pCommW->nValue;
	}
	else if(pCommZ)
	{
		pPoint.x = pCommZ->nValue;
		pPoint.y = pCommY->nValue;
	}
	else if(pCommY)
	{
		pPoint.x = pCommX->nValue;
		pPoint.y = pCommY->nValue;
	}
	return pPoint;
}

/*-----------------------------------------------
CString strCmd：从图库传过来的异形信息
-----------------------------------------------*/
void CDlg_bottero::GetOtherGraph(CString strCmd)//从异形图形获得数据，转成异形段
{
	int			nOffsetX, nOffsetY;
	int			nPos;
	BOOL		bFirstP = TRUE;
	CString		pdcstr;
	CString		strText;
	CString		strRect = strCmd;
	int			nHollow = -1;
	pSegment	stuOtherSgt, stuCurrSgt, strHeadSgt;		/* 申请命令数据中的数据段结构 */
	
	stuOtherSgt = stuCurrSgt = NULL;
	nOffsetX = g_stu_pAxisC->sSpareA;/* 左 */
	nOffsetY = g_stu_pAxisC->sSpareD;/* 下 */
	
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
				nHollow = 1;
			}
			strText.Format("G00 X%.4f Y%.4f\n", (double)(nOffsetX+pointx), (double)(nOffsetY+pointy));
			if(stuOtherSgt==NULL)
			{
				stuOtherSgt = OnAddSegment(NULL);		/* 申请命令数据中的数据段结构 */
				stuCurrSgt = stuOtherSgt;
				strHeadSgt = stuOtherSgt;
				stuCurrSgt->fBeginX = (float)(nOffsetX+pointx);
				stuCurrSgt->fBeginY = (float)(nOffsetY+pointy);
			}
		}
		else if(pdcstr.GetAt(0)=='1')
		{
			pdcpoint = pdcstr.Mid(1);
			int nPos;
			double pointx,pointy;
			nPos = pdcpoint.FindOneOf(",");
			pointx = atof(pdcpoint.Left(nPos));
			pointy = atof(pdcpoint.Mid(nPos+1));
			if( nHollow == -1 || nHollow == 1)
			{
				nHollow = 0;
			}
			strText.Format("G01 X%.4f Y%.4f\n",(double)(nOffsetX+pointx), (double)(nOffsetY+pointy));
			stuCurrSgt->bIsLine = TRUE;
			stuCurrSgt->fEndX = (float)(nOffsetX+pointx);
			stuCurrSgt->fEndY = (float)(nOffsetY+pointy);
//			if(stuCurrSgt->Prev!=NULL)
			{
				stuOtherSgt = OnAddSegment(stuCurrSgt);		/* 申请命令数据中的数据段结构 */
				stuCurrSgt = stuOtherSgt;
				stuCurrSgt->fBeginX = stuCurrSgt->Prev->fEndX;
				stuCurrSgt->fBeginY = stuCurrSgt->Prev->fEndY;
			}
		}
		else if(pdcstr.GetAt(0)=='2')
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

			if(fabs(pointR)<1)
				continue;
			
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
			stuCurrSgt->bIsLine = FALSE;
			stuCurrSgt->fEndX = (float)(Gendx);
			stuCurrSgt->fEndY = (float)(Gendy);
			stuCurrSgt->pSegArc = new tagSegmentARC;
			stuCurrSgt->pSegArc->fCenterX = (float)(nOffsetX+pointx);
			stuCurrSgt->pSegArc->fCenterY = (float)(nOffsetY+pointy);
			stuCurrSgt->pSegArc->fRadius = (float)(pointR);
			stuCurrSgt->pSegArc->fBeginAngle = (float)(pointQ);
			stuCurrSgt->pSegArc->fSweepAngle = (float)(pointD);

			if(pointD>0)	/* 逆时针 */
			{
				stuCurrSgt->bDirect = FALSE;
				stuCurrSgt->pSegArc->fSweepAngle *= 1;
			}
			else			/* 顺时针 */
			{
				stuCurrSgt->bDirect = TRUE;
				stuCurrSgt->pSegArc->fSweepAngle *= 1;
			}
//			if(stuCurrSgt->Prev!=NULL)
			{
				stuOtherSgt = OnAddSegment(stuCurrSgt);		/* 申请命令数据中的数据段结构 */
				stuCurrSgt = stuOtherSgt;
				stuCurrSgt->fBeginX = stuCurrSgt->Prev->fEndX;
				stuCurrSgt->fBeginY = stuCurrSgt->Prev->fEndY;
			}
		}
	}
	/* 将最后多出的块删除掉 */
	stuCurrSgt = stuCurrSgt->Prev;
	delete stuCurrSgt->Next;
	stuCurrSgt->Next = NULL;
	/*----------------------------------------------------------------------*/
	
	OnGetBaseRect(strRect);
	/*----------------------------------------------------------------------*/
	pSegment	stu_pSegmentX,stu_pSegmentY/*,stu_pTempSeg*/;
	p_Command	pBtroComm = pCurrComm;
	POINT2D		p;
	pSegment	stuTempSegment,stuCurrSegment;

	stuTempSegment = OnAddSegment(NULL);		/* 申请命令数据中的数据段结构 */
	stuCurrSegment = stuTempSegment;
	pBtroComm->pStuSegment = stuTempSegment;
	
	if(pCommR)
	{
		for(stu_pSegmentX = pCommQ->pStuSegment;stu_pSegmentX;stu_pSegmentX = stu_pSegmentX->Next)
		{
			for(stu_pSegmentY = pCommR->pStuSegment;stu_pSegmentY;stu_pSegmentY = stu_pSegmentY->Next)
			{
				p = OnGetBaseRectPoint(stu_pSegmentX,stu_pSegmentY,pCommQ,pCommR);
				stuTempSegment->fBeginX = (float)p.x;
				stuTempSegment->fBeginY = (float)p.y;
				OnAddOtherGraph(p, stuCurrSegment, strHeadSgt); 
				if(stu_pSegmentY->Next)
				{
					stuTempSegment = OnAddSegment(stuCurrSegment);
					stuCurrSegment = stuTempSegment;
				}
			}
			if(stu_pSegmentX->Next)
			{
				stuTempSegment = OnAddSegment(stuCurrSegment);
				stuCurrSegment = stuTempSegment;
			}
		}
		strOldComm.Empty();							/* 将老的命令清空 */
	}
	else if(pCommQ)
	{
		for(stu_pSegmentX = pCommQ->pStuSegment;stu_pSegmentX;stu_pSegmentX = stu_pSegmentX->Next)
		{
			for(stu_pSegmentY = pCommW->pStuSegment;stu_pSegmentY;stu_pSegmentY = stu_pSegmentY->Next)
			{
				p = OnGetBaseRectPoint(stu_pSegmentX,stu_pSegmentY,pCommQ,pCommW);
				stuTempSegment->fBeginX = (float)p.x;
				stuTempSegment->fBeginY = (float)p.y;
				OnAddOtherGraph(p, stuCurrSegment, strHeadSgt); 
				if(stu_pSegmentY->Next)
				{
					stuTempSegment = OnAddSegment(stuCurrSegment);
					stuCurrSegment = stuTempSegment;
				}
			}
			if(stu_pSegmentX->Next)
			{
				stuTempSegment = OnAddSegment(stuCurrSegment);
				stuCurrSegment = stuTempSegment;
			}
		}
		strOldComm.Empty();							/* 将老的命令清空 */
	}
	else if(pCommW)
	{
		for(stu_pSegmentX = pCommZ->pStuSegment;stu_pSegmentX;stu_pSegmentX = stu_pSegmentX->Next)
		{
			for(stu_pSegmentY = pCommW->pStuSegment;stu_pSegmentY;stu_pSegmentY = stu_pSegmentY->Next)
			{
				p = OnGetBaseRectPoint(stu_pSegmentX,stu_pSegmentY,pCommZ,pCommW);
				stuTempSegment->fBeginX = (float)p.x;
				stuTempSegment->fBeginY = (float)p.y;
				OnAddOtherGraph(p, stuCurrSegment, strHeadSgt); 
				if(stu_pSegmentY->Next)
				{
					stuTempSegment = OnAddSegment(stuCurrSegment);
					stuCurrSegment = stuTempSegment;
				}
			}
			if(stu_pSegmentX->Next)
			{
				stuTempSegment = OnAddSegment(stuCurrSegment);
				stuCurrSegment = stuTempSegment;
			}
		}
		strOldComm.Empty();							/* 将老的命令清空 */
	}
	else if(pCommZ)
	{
		for(stu_pSegmentX = pCommZ->pStuSegment;stu_pSegmentX;stu_pSegmentX = stu_pSegmentX->Next)
		{
			for(stu_pSegmentY = pCommY->pStuSegment;stu_pSegmentY;stu_pSegmentY = stu_pSegmentY->Next)
			{
				p = OnGetBaseRectPoint(stu_pSegmentX,stu_pSegmentY,pCommZ,pCommY);
				stuTempSegment->fBeginX = (float)p.x;
				stuTempSegment->fBeginY = (float)p.y;
				OnAddOtherGraph(p, stuCurrSegment, strHeadSgt); 
				if(stu_pSegmentY->Next)
				{
					stuTempSegment = OnAddSegment(stuCurrSegment);
					stuCurrSegment = stuTempSegment;
				}
			}
			if(stu_pSegmentX->Next)
			{
				stuTempSegment = OnAddSegment(stuCurrSegment);
				stuCurrSegment = stuTempSegment;
			}
		}
		strOldComm.Empty();							/* 将老的命令清空 */
	}
	else if(pCommY)
	{
		for(stu_pSegmentX = pCommX->pStuSegment;stu_pSegmentX;stu_pSegmentX = stu_pSegmentX->Next)
		{
			for(stu_pSegmentY = pCommY->pStuSegment;stu_pSegmentY;stu_pSegmentY = stu_pSegmentY->Next)
			{
				p = OnGetBaseRectPoint(stu_pSegmentX,stu_pSegmentY,pCommX,pCommY);
				stuTempSegment->fBeginX = (float)p.x;
				stuTempSegment->fBeginY = (float)p.y;
				stuTempSegment->bIsLine = TRUE;
				stuCurrSegment = OnAddOtherGraph(p, stuCurrSegment, strHeadSgt); 
				if(stu_pSegmentY->Next)
				{
					stuTempSegment = OnAddSegment(stuCurrSegment);
					stuCurrSegment = stuTempSegment;
				}
			}
			if(stu_pSegmentX->Next)
			{
				stuTempSegment = OnAddSegment(stuCurrSegment);
				stuCurrSegment = stuTempSegment;
			}
		}
		strOldComm.Empty();							/* 将老的命令清空 */
	}
}

/*--------------------------------------------------
POINT2D p：图形的偏移距离
pSegment stuNowSegment：指定拷贝的首结点
pSegment stuGraphSegment：指定图形链表的首结点
--------------------------------------------------*/
pSegment CDlg_bottero::OnAddOtherGraph(POINT2D p, pSegment stuNowSegment, pSegment stuGraphSegment) 
{
	BOOL		bFirst = TRUE;
	pSegment	stuTmpSgt;
	pSegment	stuTmpCurrSgt = stuNowSegment;
	for(stuTmpSgt = stuGraphSegment; stuTmpSgt; )
	{
		if(bFirst)
			bFirst = FALSE;
		else
			stuTmpCurrSgt = OnAddSegment(stuTmpCurrSgt);
		
		stuTmpCurrSgt->bIsLine = stuTmpSgt->bIsLine;
		stuTmpCurrSgt->bDirect = stuTmpSgt->bDirect;
		stuTmpCurrSgt->fBeginX = stuTmpSgt->fBeginX + (float)p.x;
		stuTmpCurrSgt->fBeginY = stuTmpSgt->fBeginY + (float)p.y;
		stuTmpCurrSgt->fEndX = stuTmpSgt->fEndX + (float)p.x;
		stuTmpCurrSgt->fEndY = stuTmpSgt->fEndY + (float)p.y;
		if(!stuTmpCurrSgt->bIsLine)
		{
			stuTmpCurrSgt->pSegArc = new tagSegmentARC;
			stuTmpCurrSgt->pSegArc->fCenterX = stuTmpSgt->pSegArc->fCenterX + (float)p.x;
			stuTmpCurrSgt->pSegArc->fCenterY = stuTmpSgt->pSegArc->fCenterY + (float)p.y;
			stuTmpCurrSgt->pSegArc->fRadius = stuTmpSgt->pSegArc->fRadius;
			stuTmpCurrSgt->pSegArc->fBeginAngle = stuTmpSgt->pSegArc->fBeginAngle;
			stuTmpCurrSgt->pSegArc->fSweepAngle = stuTmpSgt->pSegArc->fSweepAngle;
		}
		stuTmpSgt = stuTmpSgt->Next;
	}
	return stuTmpCurrSgt;
}

/*--------------------------------------------------
pSegment stuGraphSegment：指定图形链表的首结点
--------------------------------------------------*/
void CDlg_bottero::OnFreeGraph(pSegment stuGraphSegment) 
{
	pSegment    pBlock,pTempBlock;                 //  
	for (pBlock = stuGraphSegment; pBlock;)
	{
		pTempBlock = pBlock->Next;
		delete pBlock;                        //DMC_FFREEA
		pBlock = pTempBlock;
		if(!pBlock)  break;
	}
}

/*--------------------------------------------------
p_stuBottero stuCommand：命令开始节点
--------------------------------------------------*/
void CDlg_bottero::OnFreeCommand(p_Command stuCommand) 
{
	p_Command    pBlock,pTempBlock;                 //  
	for (pBlock = stuBtro.BtroComm; pBlock;)
	{
		if(pBlock->pStuSegment)
		{
			pSegment pBlockSegment, pTempSegment;
			for(pBlockSegment = pBlock->pStuSegment; pBlockSegment;)
			{
				pTempSegment = pBlockSegment->Next;
				delete pBlockSegment;                        //DMC_FFREEA
				pBlockSegment = pTempSegment;
				if(!pBlockSegment)  break;
			}
			pRectDraw pBlockRect, pTempRect;
			for(pBlockRect = pBlock->pRect; pBlockRect;)
			{
				pTempRect = pBlockRect->Next;
				delete pBlockRect;                        //DMC_FFREEA
				pBlockRect = pTempRect;
				if(!pBlockRect)  break;
			}
		}
		pTempBlock = pBlock->Next;
		delete pBlock;                        //DMC_FFREEA stuBottero
		pBlock = pTempBlock;
		if(!pBlock)  break;
	}
	memset(&stuBtro, 0, sizeof(stuBottero));
}

/*--------------------------------------------------
p_stuBottero stuCommand：命令开始节点
--------------------------------------------------*/
void CDlg_bottero::OnFreeLastCommand(p_Command stuCommand) 
{
	if(stuCommand->pStuSegment)
	{
		pSegment pBlockSegment, pTempSegment;
		for(pBlockSegment = stuCommand->pStuSegment; pBlockSegment;)
		{
			pTempSegment = pBlockSegment->Next;
			delete pBlockSegment;                        //DMC_FFREEA
			pBlockSegment = pTempSegment;
			if(!pBlockSegment)  break;
		}
		pRectDraw pBlock, pTemp;
		for(pBlock = stuCommand->pRect; pBlock;)
		{
			pTemp = pBlock->Next;
			delete pBlock;                        //DMC_FFREEA
			pBlock = pTemp;
			if(!pBlock)  break;
		}
	}
	delete stuCommand;                        //DMC_FFREEA stuBottero
	stuCommand = NULL;
}

BOOL CDlg_bottero::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
	// TODO: Add your message handler code here and/or call default
	CString	strTemp;
	strTemp.Format("%s", (char*)pCopyDataStruct->lpData);
//	AfxMessageBox(strTemp);
	if(pCopyDataStruct->dwData==0)
	{
		m_lstBottero.SetColumnWidth(nCountComm,100);
		m_lstBottero.InsertItem(nCountComm,strTemp);
		strcpy(pCurrComm->chName,LPCTSTR(strTemp));
	}
	else
		GetOtherGraph(strTemp);
	return CDialog::OnCopyData(pWnd, pCopyDataStruct);
}

void CDlg_bottero::CommandCovGcode(int nStyle)//保存为G代码文件
{
	p_Command	tempComm;
	pSegment	tempSegt;
	POINT2D		pCurrPoint;
	FILE		*fileG;
	CString		strUp,strDown;
	CString		strFilename;	
	if (nStyle==0)
	{
		dlg_save  dlgSave;
		dlgSave.strExtName = ".g";
		if (IDCANCEL == dlgSave.DoModal())	return;
		if(g_strSavefile.IsEmpty())			return;
	} 
	else
	{
		g_strSavefile = "Edit.g";
	}
	strFilename = g_strOriginalPathD+"gcode\\"+g_strSavefile;
	memset(&pCurrPoint, 0, sizeof(POINT2D));
	g_strShowName = g_strSavefile;
	g_strGfile = strFilename;
    g_strSavefile = "";
	
	if (!(fileG = fopen(strFilename, "wt")))
	{
		MessageBox("Could not open file!","error",MB_OK|MB_ICONINFORMATION);
		return;
	}
	if(g_stu_pAxisA->bSpareA)	/* 注油 */
	{
		strUp = "M14\n";
		strDown = "M13\n";
	}
	else						/* 不注油 */
	{
		strUp = "M10\n";
		strDown = "M09\n";
	}
	
	WriteLittleInf(fileG);
    bool l_bFirstX = false;//修改刀路，先画x再画y;
	fprintf(fileG, "G90\n");
	/* 判断是否有修边 */
	if(stuBtro.lModifyY>2)
	{
		fprintf(fileG, strUp);
		fprintf(fileG, "G00X%.2f,Y%.2f\n", (float)(stuBtro.lModifyX), g_stu_pAxisH->dSpareC/*(float)(stuBtro.lModifyY - 2)*/);
		fprintf(fileG, strDown);
		fprintf(fileG, "G01X%.2f,Y%.2f\n", (float)(stuBtro.lModifyX), (float)(stuBtro.lMaterialY));
	}	
	CombinationAllLines();
	for(tempComm = stuBtro.BtroComm;tempComm;tempComm=tempComm->Next)
	{
		if (!l_bFirstX && tempComm->chCom == 'Y')//修改刀路，先画x再画y;
		{
			l_bFirstX = true;
			if(stuBtro.lModifyX>2)
			{
				fprintf(fileG, strUp);
				fprintf(fileG, "G00X%.2f,Y%.2f\n", g_stu_pAxisH->dSpareC, (float)(stuBtro.lModifyY));
				fprintf(fileG, strDown);
				fprintf(fileG, "G01X%.2f,Y%.2f\n", (float)(stuBtro.lMaterialX), (float)(stuBtro.lModifyY));
			}
		}
		for(tempSegt = tempComm->pStuSegment;tempSegt;tempSegt=tempSegt->Next)
		{
			if(!CommandIsOnePoint(pCurrPoint, tempSegt))
			{
				if((!tempSegt->bDirect && tempSegt->bIsLine) || !tempSegt->bIsLine)
				{
					fprintf(fileG, strUp);
					pCurrPoint = CommandToolDn(fileG, 0, tempSegt, tempComm);
					fprintf(fileG, strDown);
				}
			}
			if(tempSegt->bIsLine)
			{
				if((!tempSegt->bDirect && tempSegt->bIsLine) || !tempSegt->bIsLine)
					pCurrPoint = CommandToolDn(fileG, 1, tempSegt, tempComm);
			}
			else 
			{
				if((!tempSegt->bDirect && tempSegt->bIsLine) || !tempSegt->bIsLine)
					pCurrPoint = CommandToolDn(fileG, 2, tempSegt, tempComm);
			}
		}
	}
	fprintf(fileG, strUp);
	fprintf(fileG, "G90G00X0Y0Z0\n");
	if(g_stu_pAxisG->bSpare)
		fprintf(fileG, "M99\n");
	fprintf(fileG, "M30\n");
	fclose(fileG);	
}

POINT2D CDlg_bottero::CommandToolDn(FILE *fileG, int nIndex, pSegment pSegt, p_Command pComm)//保存为G代码文件
{
	POINT2D	p2d;
	if(nIndex==2)
	{
		if(pSegt->bDirect)
			nIndex++;
	}
	switch(nIndex) 
	{
	case 0:
		{
			if(pComm->chCom=='X'||pComm->chCom=='Z'||pComm->chCom=='Q')
			{
				if(g_stu_pAxisH->dSpareC > pSegt->fBeginY)
					fprintf(fileG, "G00X%.2f Y%.2f\n", pSegt->fBeginX, g_stu_pAxisH->dSpareC);
				else
					fprintf(fileG, "G00X%.2f Y%.2f\n", pSegt->fBeginX, pSegt->fBeginY);
			}
			else if(pComm->chCom=='Y'||pComm->chCom=='W'||pComm->chCom=='R')
			{
				if(g_stu_pAxisH->dSpareC > pSegt->fBeginX)
					fprintf(fileG, "G00X%.2f Y%.2f\n", g_stu_pAxisH->dSpareC, pSegt->fBeginY);
				else
					fprintf(fileG, "G00X%.2f Y%.2f\n", pSegt->fBeginX, pSegt->fBeginY);
			}
			else
			{
				fprintf(fileG, "G00X%.2f Y%.2f\n", pSegt->fBeginX, pSegt->fBeginY);
			}
		}
		break;
	case 1:
		fprintf(fileG, "G01X%.2f Y%.2f\n", pSegt->fEndX, pSegt->fEndY);
		break;
	case 2:
		fprintf(fileG, "G03X%.2f Y%.2f I%.2f J%.2f\n", pSegt->fEndX, pSegt->fEndY, pSegt->pSegArc->fCenterX - pSegt->fBeginX, pSegt->pSegArc->fCenterY - pSegt->fBeginY);
		break;
	case 3:
		fprintf(fileG, "G02X%.2f Y%.2f I%.2f J%.2f\n", pSegt->fEndX, pSegt->fEndY, pSegt->pSegArc->fCenterX - pSegt->fBeginX, pSegt->pSegArc->fCenterY - pSegt->fBeginY);
		break;
	default:
		break;
	}
	p2d.x = pSegt->fEndX;
	p2d.y = pSegt->fEndY;
	return p2d;
}

BOOL CDlg_bottero::CommandIsOnePoint(POINT2D pOld, pSegment pSegt)//保存为G代码文件
{
	double	dDis;
	dDis = sqrt((pOld.x - pSegt->fBeginX)*(pOld.x - pSegt->fBeginX) + (pOld.y - pSegt->fBeginY)*(pOld.y - pSegt->fBeginY));
	if(dDis<0.0005)
		return TRUE;
	else
		return FALSE;
}

void CDlg_bottero::OnLanguage()
{
	for(int i=0;i<AR_BOTTERO;i++)
	{
		if(strstr(g_strBottero[i][g_iLanguage], "NULL"))
			SetDlgItemText(atoi(g_strBottero[i][2]), "");
		else
			SetDlgItemText(atoi(g_strBottero[i][2]), g_strBottero[i][g_iLanguage]);
	}
	if (g_iLanguage == 1)
	{
		SetDlgItemText(IDC_STATICORDER,"Order");
		SetDlgItemText(IDC_STATICMAX,"MAX");
		SetDlgItemText(IDC_STATICREMAIN,"Residue");
	}
}

LRESULT CDlg_bottero::OnEditDouble(WPARAM wParam, LPARAM lParam) 
{
	CString				strTmp;
	CDlg_KeyChar		KeyNum;
	
	if(lParam==1)/* 有触摸屏 */
	{
		((CEdit *)GetDlgItem(wParam))->SetSel(0,-1);
		return 0;
	}
	
	CWnd::GetDlgItemText(wParam,strTmp);
	KeyNum.m_strNew = KeyNum.m_strOld = strTmp;	
	if(KeyNum.DoModal()==IDOK)
		CWnd::SetDlgItemText(wParam,KeyNum.m_strNew);
	
	return 0;
}

BOOL CDlg_bottero::PreTranslateMessage(MSG* pMsg) 
{
/*
    if(pMsg->message==WM_SYSKEYDOWN || pMsg->message==WM_SYSKEYUP)
		return(TRUE);
*/
	if(pMsg->lParam==VK_ESCAPE||pMsg->wParam==VK_ESCAPE)
		return TRUE;		
    if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN)
	{
		OnButtonUpdateA();
		return(TRUE);
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlg_bottero::OnButtonUpdateA() 
{
	CString str;	
	float		m_fValue;
	pSegment	stu_pSegmentX,stu_pSegmentY;
	p_Command	pBtroComm;
	CString		strValue;
	CString		m_strCbo;
	UpdateData(TRUE);
				
	if(m_strCommValue.IsEmpty())
		return;
	strupr((char*)((const char*)m_strCommValue));

	m_strCbo = m_strCommValue.GetAt(0);
	strValue = m_strCommValue.Right(m_strCommValue.GetLength() - 1);
	m_fValue = (float)atof(strValue);

	strCommand.Format("%.2f",m_fValue);
	strCommand = m_strCbo + strCommand;
	if(m_strCbo.IsEmpty())
		return;
	if(!OnValidCommand(m_strCbo.GetAt(0),m_fValue))
	{
		if(!g_iLanguage)
			AfxMessageBox("命令超出范围或无效！");
		else
			AfxMessageBox("Command Out Of Range!");
		((CEdit *)GetDlgItem(IDC_EDIT_VALUE))->SetSel(0,-1);
		return;
	}
	if(!strstr(m_strCbo,"P"))	/* 如果不是异形 */
	{
		m_lstBottero.SetColumnWidth(nCountComm,100);
		m_lstBottero.InsertItem(nCountComm,strCommand);
	}
	/* 建立BOTTERO数据结构 */
	if(!(strstr(m_strCbo,"A")||strstr(m_strCbo,"B")||strstr(m_strCbo,"C")||strstr(m_strCbo,"D")||strstr(m_strCbo,"P")))
	{
		if(pCurrComm && pCurrComm->nMultiple>0 && pCurrComm->chCom == 0)
		{
			pBtroComm = pCurrComm;
		}
		else
		{
			pBtroComm = OnAddBotteroCommand(pCurrComm);
			pCurrComm = pBtroComm;
			pLastComm = pCurrComm;
			if(nCountComm==0)
			{
				stuBtro.BtroComm = pBtroComm;
				pCurrComm = pFirstComm = pBtroComm;
			}
		}
		if(strstr(m_strCbo,"M"))
		{
			pCurrComm->nMultiple = (int)m_fValue;
		}
		else
		{
			pSegment	stuTempSegment,stuCurrSegment;
			int			i;
			pCurrComm->chCom = m_strCbo.GetAt(0);
			pCurrComm->nValue = m_fValue;
			stuCurrSegment = NULL;
			stuTempSegment = OnAddSegment(stuCurrSegment);
			pCurrComm->pStuSegment = stuTempSegment;
			stuCurrSegment = stuTempSegment;
			/* 加入圆弧或直线段 */
			switch(pCurrComm->chCom) 
			{
			case 'X':
				{
					pCommX = pCurrComm;
					pCommY = pCommZ = pCommW = pCommQ = pCommR = NULL;
					stuBtro.fLeft = stuBtro.fRight;
					stuBtro.fRight = pCurrComm->nMultiple * pCurrComm->nValue + stuBtro.fLeft;
					fValueX = stuBtro.fRight;
					fValueY = fValueZ = fValueW = fValueQ = fValueR = 0.0;
					
					for(i=1;i<= pCurrComm->nMultiple;i++)
					{
						stuTempSegment->bIsLine = TRUE;
						stuTempSegment->fBeginX = pCurrComm->nValue * i + stuBtro.fLeft;
						stuTempSegment->fBeginY = (float)stuBtro.lModifyY;
						stuTempSegment->fEndX = pCurrComm->nValue * i + stuBtro.fLeft;
						
						// X命令另外一方无修边 // 
						stuTempSegment->fEndY = (float)stuBtro.lMaterialY - (float)g_stu_pAxisH->dSpareC;
						if(i<pCurrComm->nMultiple)
						{
							stuTempSegment = OnAddSegment(stuCurrSegment);
							stuCurrSegment = stuTempSegment;
						}
					}
					DataShowClear();
					str.Format("%.f",stuBtro.lMaterialX-stuTempSegment->fEndX);					
					SetDlgItemText(IDC_STATICXREMAIN,str);//x剩余
					g_nRemainderX = (int)(stuBtro.lMaterialX-stuTempSegment->fEndX);

					str.Format("%d",stuBtro.lMaterialY-stuBtro.lModifyY);
					SetDlgItemText(IDC_STATICYREMAIN,str);//y剩余					
					break;					
				}
			case 'Y':
				{
					pCommY = pCurrComm;
					pCommZ = pCommW = pCommQ = pCommR = NULL;
					if(pCurrComm->Prev->chCom=='X')		stuBtro.fBottom = (float)stuBtro.lModifyY;
					else								stuBtro.fBottom = stuBtro.fTop;
					stuBtro.fTop = pCurrComm->nMultiple * pCurrComm->nValue + stuBtro.fBottom;
					fValueY = stuBtro.fTop;
					fValueZ = fValueW = fValueQ = fValueR = 0.0;
					int n=1;
					pRectDraw	pTempRect = NULL;
					pRectDraw   pCurrRect = NULL;
					for(i=1;i<= pCurrComm->nMultiple;i++)
					{
						stuTempSegment->bIsLine = TRUE;
						stuTempSegment->fBeginX = stuBtro.fLeft;
						stuTempSegment->fBeginY =pCurrComm->nValue * i +  stuBtro.fBottom;
						
						stuTempSegment->fEndX = stuBtro.fRight;
						if (stuTempSegment->fEndX > (stuBtro.lMaterialX - g_stu_pAxisH->dSpareC)) 
						{
							stuTempSegment->fEndX = stuBtro.lMaterialX - (float)g_stu_pAxisH->dSpareC;
						}
						
						stuTempSegment->fEndY = pCurrComm->nValue * i + stuBtro.fBottom;
						//生成画图矩形
						if(pCommX->nMultiple>1)//pCurrComm->Prev->chCom=='X'||pCurrComm->Prev->chCom=='Y'
						{						
							for(n=1;n<=pCommX->nMultiple;n++)
							{							
								pTempRect = AddBotteroRect(pCurrRect);
								pCurrRect = pTempRect;
								if (pCurrRect != NULL)
								{
									pCurrRect->nDraw = 1;
									pCurrRect->rect.left = stuTempSegment->fBeginX + pCommX->nValue*(n-1);
									pCurrRect->rect.right = stuTempSegment->fBeginX + pCommX->nValue*n;				
									pCurrRect->rect.bottom = stuTempSegment->fBeginY-pCurrComm->nValue;
									pCurrRect->rect.top = stuTempSegment->fEndY;							
								}
							}
						}
						else
						{
							pTempRect = AddBotteroRect(pCurrRect);
							pCurrRect = pTempRect;
							if (pCurrRect!=NULL)
							{
								pCurrRect->nDraw = 1;
								pCurrRect->rect.left = stuTempSegment->fBeginX + pCommX->nValue*(n-1);
								pCurrRect->rect.right = stuTempSegment->fBeginX + pCommX->nValue*n;				
								pCurrRect->rect.bottom = stuTempSegment->fBeginY-pCurrComm->nValue;
								pCurrRect->rect.top = stuTempSegment->fEndY;							
							}
						}
						//生成画图矩形
						if(i<pCurrComm->nMultiple)
						{
							stuTempSegment = OnAddSegment(stuCurrSegment);
							stuCurrSegment = stuTempSegment;
						}
					}
					
					str.Format("%.f",stuBtro.lMaterialY-stuTempSegment->fEndY);					
					SetDlgItemText(IDC_STATICYREMAIN,str);//y剩余				
					g_nRemainderY = (int)(stuBtro.lMaterialY-stuTempSegment->fEndY);
					str.Format("%.f",pCommX->nValue);					
					SetDlgItemText(IDC_STATICZMAX,str);//Z最大
					SetDlgItemText(IDC_STATICZREMAIN,str);//Z剩余
					m_nRemainderZ = pCommX->nValue;
					str.Format("%.f",pCommY->nValue);					
					SetDlgItemText(IDC_STATICWMAX,str);//W最大					
				}
				break;
			case 'Z':
				{
					int m = 0;
					pRectDraw	pTempRect = NULL;
					pRectDraw   pCurrRect = NULL;
					stu_pSegmentX = pCommX->pStuSegment;
					for(stu_pSegmentX = pCommX->pStuSegment;stu_pSegmentX;stu_pSegmentX = stu_pSegmentX->Next)
					{
						for(i=0;i<pCurrComm->nMultiple;i++)
						{
							stuTempSegment->bIsLine = TRUE;
							/* 前面一个是Z命令或是乘法器的非第一个 */
							if(i>0)
							{
								stuTempSegment->fBeginX = stuTempSegment->Prev->fBeginX + pCurrComm->nValue;
								stuTempSegment->fEndX = stuTempSegment->Prev->fBeginX + pCurrComm->nValue;
							}
							else if(pCommZ&&i==0)
							{
								stuTempSegment->fBeginX = stu_pSegmentX->fBeginX - pCommX->nValue + pCommZ->fTotalDis + pCurrComm->nValue * (i+1);
								stuTempSegment->fEndX = stuTempSegment->fBeginX;
							}
							else
							{
								stuTempSegment->fBeginX = stu_pSegmentX->fBeginX - (pCommX->nValue - pCurrComm->nValue);
								stuTempSegment->fEndX = stu_pSegmentX->fBeginX - (pCommX->nValue - pCurrComm->nValue);							
							}
							stuTempSegment->fBeginY = stuBtro.fBottom;
							stuTempSegment->fEndY = stuBtro.fTop;
							if (pCommZ == NULL)//前面不是Z命令
							{
								//生成画图矩形
								if(pCurrComm->Prev->chCom=='Y'&& pCommY->nMultiple>1)
								{						
									for(m=1;m<=pCommY->nMultiple;m++)
									{							
										pTempRect = AddBotteroRect(pCurrRect);
										pCurrRect = pTempRect;
										pCommY->pRect->nDraw = 0;
										if (pCurrRect != NULL)
										{
											pCurrRect->nDraw = 1;
											pCurrRect->rect.left = stuTempSegment->fBeginX - pCurrComm->nValue;
											pCurrRect->rect.right = stuTempSegment->fBeginX;				
											pCurrRect->rect.bottom = stuTempSegment->fBeginY + pCommY->nValue*(m-1);
											pCurrRect->rect.top = stuTempSegment->fBeginY + pCommY->nValue*m;								
										}
									}
								}
								else
								{
									pTempRect = AddBotteroRect(pCurrRect);
									pCurrRect = pTempRect;
									pCommY->pRect->nDraw = 0;
									if (pCurrRect != NULL)
									{
										pCurrRect->nDraw = 1;
										pCurrRect->rect.left = stuTempSegment->fBeginX - pCurrComm->nValue;
										pCurrRect->rect.right = stuTempSegment->fBeginX;				
										pCurrRect->rect.bottom = stuBtro.fBottom;
										pCurrRect->rect.top = stuBtro.fTop;							
									}		
								}
								//生成画图矩形
							}
							else//前面是Z命令
							{	
								//生成画图矩形
								if(pCommZ != NULL && pCommY->nMultiple>1)
								{						
									for(m=1;m<=pCommY->nMultiple;m++)
									{							
										pTempRect = AddBotteroRect(pCurrRect);
										pCurrRect = pTempRect;										
										if (pCurrRect != NULL)
										{
											pCurrRect->nDraw = 1;
											pCurrRect->rect.left = stuTempSegment->fBeginX - pCurrComm->nValue;
											pCurrRect->rect.right = stuTempSegment->fBeginX;				
											pCurrRect->rect.bottom = stuTempSegment->fBeginY + pCommY->nValue*(m-1);
											pCurrRect->rect.top = stuTempSegment->fBeginY + pCommY->nValue*m;								
										}
									}
								}
								else
								{
									pTempRect = AddBotteroRect(pCurrRect);
									pCurrRect = pTempRect;
									if (pCurrRect != NULL)
									{
										pCurrRect->nDraw = 1;
										pCurrRect->rect.left = stuTempSegment->fBeginX - pCurrComm->nValue;
										pCurrRect->rect.right = stuTempSegment->fBeginX;				
										pCurrRect->rect.bottom = stuBtro.fBottom;
										pCurrRect->rect.top = stuBtro.fTop;							
									}
								}
								//生成画图矩形
							}			
							
						
							if(stu_pSegmentX->Next||i<pCurrComm->nMultiple-1)
							{
								stuTempSegment = OnAddSegment(stuCurrSegment);
								stuCurrSegment = stuTempSegment;								
							}

						}
					}
					if(pCommZ==NULL)
					{
						pCurrComm->fTotalDis = pCurrComm->nMultiple * pCurrComm->nValue;
						pCommZ = pCurrComm;
					}
					else					
					{
						pCurrComm->fTotalDis = pCommZ->fTotalDis + pCurrComm->nMultiple * pCurrComm->nValue;
						pCommZ = pCurrComm;
					}
					pCommW = pCommQ = pCommR = NULL;
					
					if (pCommX)
					{					
						str.Format("%.f",pCommX->nValue-pCommZ->fTotalDis);					
						SetDlgItemText(IDC_STATICZREMAIN,str);//Z剩余
						m_nRemainderZ = (int)(pCommX->nValue-pCommZ->fTotalDis);
					}
					
					str.Format("%.f",pCommY->nValue);					
					SetDlgItemText(IDC_STATICWMAX,str);//W最大
					
					if(pCommY)
					{
						str.Format("%.f",pCommY->nValue);
						SetDlgItemText(IDC_STATICWREMAIN,str);//W剩余
						m_nRemainderW = (int)pCommY->nValue;
					}				
					
					SetDlgItemText(IDC_STATICQMAX,"");//Q最大
					SetDlgItemText(IDC_STATICQREMAIN,"");//Q剩余
					SetDlgItemText(IDC_STATICRMAX,"");//Q最大
					SetDlgItemText(IDC_STATICRREMAIN,"");//Q剩余	
				}
				break;
			case 'W':
				{
					int m = 0;
					pRectDraw	pTempRect = NULL;
					pRectDraw   pCurrRect = NULL;
					for(stu_pSegmentY = pCommY->pStuSegment;stu_pSegmentY;stu_pSegmentY = stu_pSegmentY->Next)
					{
						for(i=0;i<pCurrComm->nMultiple;i++)
						{
							stuTempSegment->bIsLine = TRUE;
							/* 前面一个是Z命令或是乘法器的非第一个 */
							if(i>0)
							{
								stuTempSegment->fBeginY = stuTempSegment->Prev->fBeginY + pCurrComm->nValue;
								stuTempSegment->fEndY = stuTempSegment->Prev->fBeginY + pCurrComm->nValue;
							}
							else if(pCommW&&i==0)
							{
								stuTempSegment->fBeginY = stu_pSegmentY->fBeginY - pCommY->nValue + pCommW->fTotalDis + pCurrComm->nValue * (i+1);
								stuTempSegment->fEndY = stuTempSegment->fBeginY;
							}
							else
							{
								stuTempSegment->fBeginY = stu_pSegmentY->fBeginY - (pCommY->nValue - pCurrComm->nValue);
								stuTempSegment->fEndY = stu_pSegmentY->fBeginY - (pCommY->nValue - pCurrComm->nValue);
							}
							for(stu_pSegmentX = pCommX->pStuSegment;stu_pSegmentX;stu_pSegmentX = stu_pSegmentX->Next)
							{
								if(pCommZ)
								{
									stuTempSegment->fBeginX = stu_pSegmentX->fBeginX - pCommX->nValue + pCommZ->fTotalDis - pCommZ->nValue * pCommZ->nMultiple;
									stuTempSegment->fEndX = stu_pSegmentX->fBeginX - pCommX->nValue + pCommZ->fTotalDis;
								}
								else
								{
									stuTempSegment->fBeginX = stuBtro.fLeft;
									stuTempSegment->fEndX = stuBtro.fRight;
								}
								//生成画图矩形
								if (pCommW == NULL)//前面不是w命令
								{
									
									if(pCommZ->nMultiple>1)//前面多个Z
									{						
										for(m=1;m<=pCommZ->nMultiple;m++)
										{							
											pTempRect = AddBotteroRect(pCurrRect);
											pCurrRect = pTempRect;
											pCommZ->pRect->nDraw = 0;
											if (pCurrRect != NULL)
											{
												pCurrRect->nDraw = 1;
												pCurrRect->rect.left = stuTempSegment->fBeginX + pCommZ->nValue*(m-1);
												pCurrRect->rect.right = stuTempSegment->fBeginX + pCommZ->nValue*m;				
												pCurrRect->rect.bottom = stuTempSegment->fBeginY  - pCurrComm->nValue;
												pCurrRect->rect.top = stuTempSegment->fBeginY;								
											}
										}
									}
									else//前面一个Z
									{
										pTempRect = AddBotteroRect(pCurrRect);
										pCurrRect = pTempRect;
										pCommZ->pRect->nDraw = 0;
										if (pCurrRect != NULL)
										{
											pCurrRect->nDraw = 1;
											pCurrRect->rect.left = stuTempSegment->fBeginX;
											pCurrRect->rect.right = stuTempSegment->fEndX ;				
											pCurrRect->rect.bottom = stuTempSegment->fBeginY-pCurrComm->nValue;
											pCurrRect->rect.top = stuTempSegment->fEndY;							
										}		
									}
									//生成画图矩形
								}
								else//前面是w命令
								{	
									//生成画图矩形
									if(pCommW != NULL && pCommZ->nMultiple>1)
									{						
										for(m=1;m<=pCommZ->nMultiple;m++)
										{							
											pTempRect = AddBotteroRect(pCurrRect);
											pCurrRect = pTempRect;										
											if (pCurrRect != NULL)
											{
												pCurrRect->nDraw = 1;
												pCurrRect->rect.left = stuTempSegment->fBeginX + pCommZ->nValue*(m-1);
												pCurrRect->rect.right = stuTempSegment->fBeginX + pCommZ->nValue*m;				
												pCurrRect->rect.bottom = stuTempSegment->fBeginY  - pCurrComm->nValue;
												pCurrRect->rect.top = stuTempSegment->fBeginY;								
											}
										}
									}
									else
									{
										pTempRect = AddBotteroRect(pCurrRect);
										pCurrRect = pTempRect;
										if (pCurrRect != NULL)
										{
											pCurrRect->nDraw = 1;
											pCurrRect->rect.left = stuTempSegment->fBeginX;
											pCurrRect->rect.right = stuTempSegment->fEndX;				
											pCurrRect->rect.bottom = stuTempSegment->fBeginY-pCurrComm->nValue;
											pCurrRect->rect.top = stuTempSegment->fEndY;							
										}
									}
									//生成画图矩形
								}				
								
								
								
								if(stu_pSegmentX->Next)
								{
									stuTempSegment = OnAddSegment(stuCurrSegment);
									stuTempSegment->bIsLine = stuCurrSegment->bIsLine;
									stuTempSegment->fBeginY = stuCurrSegment->fBeginY;
									stuTempSegment->fEndY = stuCurrSegment->fEndY;
									stuCurrSegment = stuTempSegment;
								}
							}
							if(stu_pSegmentY->Next||i<pCurrComm->nMultiple-1)
							{
								stuTempSegment = OnAddSegment(stuCurrSegment);
								stuCurrSegment = stuTempSegment;
							}
						}
					}
					if(pCommW==NULL)
					{
						pCurrComm->fTotalDis = pCurrComm->nMultiple * pCurrComm->nValue;
						pCommW = pCurrComm;
					}
					else					
					{
						pCurrComm->fTotalDis = pCommW->fTotalDis + pCurrComm->nMultiple * pCurrComm->nValue;
						pCommW = pCurrComm;
					}
					pCommQ = pCommR = NULL;
					//
					if(pCommY)
					{
						str.Format("%.f",pCommY->nValue-pCommW->fTotalDis);
						SetDlgItemText(IDC_STATICWREMAIN,str);//W剩余
						m_nRemainderW = (int)(pCommY->nValue-pCommW->fTotalDis);
					}
					if (pCommZ)
					{
						str.Format("%.f",pCommZ->nValue);
						SetDlgItemText(IDC_STATICQMAX,str);//Q最大
						SetDlgItemText(IDC_STATICQREMAIN,str);//Q剩余
					} 
				}
				break;
			case 'Q':/* Q 命令未完成，将最后的X、Y都找出来 */
				{				
					if(pCommW==NULL)	break;		/* 如果没有W方向刀线，此命令不成立 */
					int m = 0;
					pRectDraw	pTempRect = NULL;
					pRectDraw   pCurrRect = NULL;
					for(stu_pSegmentX = pCommZ->pStuSegment;stu_pSegmentX;stu_pSegmentX = stu_pSegmentX->Next)
					{
						for(i=0;i<pCurrComm->nMultiple;i++)
						{
							stuTempSegment->bIsLine = TRUE;
							/* 前面一个是Z命令或是乘法器的非第一个 */
							if(i>0)
							{
								stuTempSegment->fBeginX = stuTempSegment->Prev->fBeginX + pCurrComm->nValue;
								stuTempSegment->fEndX = stuTempSegment->Prev->fBeginX + pCurrComm->nValue;
							}
							else if(pCommQ&&i==0)
							{
								stuTempSegment->fBeginX = stu_pSegmentX->fBeginX - pCommZ->nValue + pCommQ->fTotalDis + pCurrComm->nValue * (i+1);
								stuTempSegment->fEndX = stuTempSegment->fBeginX;
							}
							else
							{
								stuTempSegment->fBeginX = stu_pSegmentX->fBeginX - (pCommZ->nValue - pCurrComm->nValue);
								stuTempSegment->fEndX = stu_pSegmentX->fBeginX - (pCommZ->nValue - pCurrComm->nValue);
							}
							for(stu_pSegmentY = pCommY->pStuSegment;stu_pSegmentY;stu_pSegmentY = stu_pSegmentY->Next)
							{
								stuTempSegment->fBeginY = stu_pSegmentY->fBeginY - pCommY->nValue + pCommW->fTotalDis - pCommW->nValue * pCommW->nMultiple;
								stuTempSegment->fEndY = stu_pSegmentY->fBeginY - pCommY->nValue + pCommW->fTotalDis;

								if (pCommQ == NULL)//前面不是Q命令
								{
									//生成画图矩形
									if(pCurrComm->Prev->chCom=='W'&& pCommW->nMultiple>1)
									{						
										for(m=1;m<=pCommW->nMultiple;m++)
										{							
											pTempRect = AddBotteroRect(pCurrRect);
											pCurrRect = pTempRect;
											pCommW->pRect->nDraw = 0;
											if (pCurrRect != NULL)
											{
												pCurrRect->nDraw = 1;
												pCurrRect->rect.left = stuTempSegment->fBeginX - pCurrComm->nValue;
												pCurrRect->rect.right = stuTempSegment->fBeginX;				
												pCurrRect->rect.bottom = stuTempSegment->fBeginY + pCommW->nValue*(m-1);
												pCurrRect->rect.top = stuTempSegment->fBeginY + pCommW->nValue*m;								
											}
										}
									}
									else//前面一个W
									{
										pTempRect = AddBotteroRect(pCurrRect);
										pCurrRect = pTempRect;
										pCommW->pRect->nDraw = 0;
										if (pCurrRect != NULL)
										{
											pCurrRect->nDraw = 1;
											pCurrRect->rect.left = stuTempSegment->fBeginX - pCurrComm->nValue;
											pCurrRect->rect.right = stuTempSegment->fBeginX;				
											pCurrRect->rect.bottom = stuTempSegment->fBeginY;
											pCurrRect->rect.top = stuTempSegment->fEndY;							
										}		
									}
									//生成画图矩形
								}
								else//前面是Q命令
								{	
									//生成画图矩形
									if(pCommQ != NULL && pCommW->nMultiple>1)
									{						
										for(m=1;m<=pCommW->nMultiple;m++)
										{							
											pTempRect = AddBotteroRect(pCurrRect);
											pCurrRect = pTempRect;										
											if (pCurrRect != NULL)
											{
												pCurrRect->nDraw = 1;
												pCurrRect->rect.left = stuTempSegment->fBeginX - pCurrComm->nValue;
												pCurrRect->rect.right = stuTempSegment->fBeginX;				
												pCurrRect->rect.bottom = stuTempSegment->fBeginY + pCommW->nValue*(m-1);
												pCurrRect->rect.top = stuTempSegment->fBeginY + pCommW->nValue*m;								
											}
										}
									}
									else//前面一个Q
									{
										pTempRect = AddBotteroRect(pCurrRect);
										pCurrRect = pTempRect;
										if (pCurrRect != NULL)
										{
											pCurrRect->nDraw = 1;
											pCurrRect->rect.left = stuTempSegment->fBeginX - pCurrComm->nValue;
											pCurrRect->rect.right = stuTempSegment->fBeginX;				
											pCurrRect->rect.bottom = stuTempSegment->fBeginY;
											pCurrRect->rect.top = stuTempSegment->fEndY;							
										}
									}
									//生成画图矩形
								}

								if(stu_pSegmentY->Next)
								{
									stuTempSegment = OnAddSegment(stuCurrSegment);
									stuTempSegment->bIsLine = stuCurrSegment->bIsLine;
									stuTempSegment->fBeginX = stuCurrSegment->fBeginX;
									stuTempSegment->fEndX = stuCurrSegment->fEndX;
									stuCurrSegment = stuTempSegment;
								}

							}
							if(stu_pSegmentX->Next||i<pCurrComm->nMultiple-1)
							{
								stuTempSegment = OnAddSegment(stuCurrSegment);
								stuCurrSegment = stuTempSegment;
							}
						}
					}
					if(pCommQ==NULL)
					{
						pCurrComm->fTotalDis = pCurrComm->nMultiple * pCurrComm->nValue;
						pCommQ = pCurrComm;
					}
					else					
					{
						pCurrComm->fTotalDis = pCommQ->fTotalDis + pCurrComm->nMultiple * pCurrComm->nValue;
						pCommQ = pCurrComm;
					}
					pCommQ = pCurrComm;
					//
					if (pCommZ)
					{
						str.Format("%.f",pCommZ->nValue - pCommQ->fTotalDis);
						SetDlgItemText(IDC_STATICQREMAIN,str);//Q剩余
						m_nRemainderQ = int(pCommZ->nValue - pCommQ->fTotalDis);
					}

					if (pCommW)
					{
						str.Format("%.f",pCommW->nValue);
						SetDlgItemText(IDC_STATICRMAX,str);//R最大					
						str.Format("%.f",pCommW->nValue);
						SetDlgItemText(IDC_STATICRREMAIN,str);//R剩余					
					}
                }
				break;
			case 'R':
				{					
					if(pCommQ==NULL)	break;		/* 如果没有Q方向刀线，此命令不成立 */
					int m = 0;
					pRectDraw	pTempRect = NULL;
					pRectDraw   pCurrRect = NULL;
					for(stu_pSegmentY = pCommW->pStuSegment;stu_pSegmentY;stu_pSegmentY = stu_pSegmentY->Next)
					{
						for(i=0;i<pCurrComm->nMultiple;i++)
						{
							stuTempSegment->bIsLine = TRUE;
							/* 前面一个是Z命令或是乘法器的非第一个 */
							if(i>0)
							{
								stuTempSegment->fBeginY = stuTempSegment->Prev->fBeginY + pCurrComm->nValue;
								stuTempSegment->fEndY = stuTempSegment->Prev->fBeginY + pCurrComm->nValue;
							}
							else if(pCommR&&i==0)
							{
								stuTempSegment->fBeginY = stu_pSegmentY->fBeginY - pCommW->nValue + pCommR->fTotalDis + pCurrComm->nValue * (i+1);
								stuTempSegment->fEndY = stuTempSegment->fBeginY;
							}
							else
							{
								stuTempSegment->fBeginY = stu_pSegmentY->fBeginY - (pCommW->nValue - pCurrComm->nValue);
								stuTempSegment->fEndY = stu_pSegmentY->fBeginY - (pCommW->nValue - pCurrComm->nValue);
							}
							for(stu_pSegmentX = pCommZ->pStuSegment;stu_pSegmentX;stu_pSegmentX = stu_pSegmentX->Next)
							{
								stuTempSegment->fBeginX = stu_pSegmentX->fBeginX - pCommZ->nValue + pCommQ->fTotalDis - pCommQ->nValue * pCommQ->nMultiple;
								stuTempSegment->fEndX = stu_pSegmentX->fBeginX - pCommZ->nValue + pCommQ->fTotalDis;
							
								//生成画图矩形
								if (pCommR == NULL)//前面不是w命令
								{
									
									if(pCommQ->nMultiple>1)//前面多个Q
									{						
										for(m=1;m<=pCommQ->nMultiple;m++)
										{							
											pTempRect = AddBotteroRect(pCurrRect);
											pCurrRect = pTempRect;
											pCommQ->pRect->nDraw = 0;
											if (pCurrRect != NULL)
											{
												pCurrRect->nDraw = 1;
												pCurrRect->rect.left = stuTempSegment->fBeginX + pCommQ->nValue*(m-1);
												pCurrRect->rect.right = stuTempSegment->fBeginX + pCommQ->nValue*m;				
												pCurrRect->rect.bottom = stuTempSegment->fBeginY  - pCurrComm->nValue;
												pCurrRect->rect.top = stuTempSegment->fBeginY;								
											}
										}
									}
									else//前面一个Q
									{
										pTempRect = AddBotteroRect(pCurrRect);
										pCurrRect = pTempRect;
										pCommQ->pRect->nDraw = 0;
										if (pCurrRect != NULL)
										{
											pCurrRect->nDraw = 1;
											pCurrRect->rect.left = stuTempSegment->fBeginX;
											pCurrRect->rect.right = stuTempSegment->fEndX ;				
											pCurrRect->rect.bottom = stuTempSegment->fBeginY-pCurrComm->nValue;
											pCurrRect->rect.top = stuTempSegment->fEndY;							
										}		
									}
									//生成画图矩形
								}
								else//前面是R命令
								{	
									//生成画图矩形
									if(pCommR != NULL && pCommQ->nMultiple>1)
									{						
										for(m=1;m<=pCommQ->nMultiple;m++)
										{							
											pTempRect = AddBotteroRect(pCurrRect);
											pCurrRect = pTempRect;										
											if (pCurrRect != NULL)
											{
												pCurrRect->nDraw = 1;
												pCurrRect->rect.left = stuTempSegment->fBeginX + pCommQ->nValue*(m-1);
												pCurrRect->rect.right = stuTempSegment->fBeginX + pCommQ->nValue*m;				
												pCurrRect->rect.bottom = stuTempSegment->fBeginY  - pCurrComm->nValue;
												pCurrRect->rect.top = stuTempSegment->fBeginY;								
											}
										}
									}
									else
									{
										pTempRect = AddBotteroRect(pCurrRect);
										pCurrRect = pTempRect;
										if (pCurrRect != NULL)
										{
											pCurrRect->nDraw = 1;
											pCurrRect->rect.left = stuTempSegment->fBeginX;
											pCurrRect->rect.right = stuTempSegment->fEndX;				
											pCurrRect->rect.bottom = stuTempSegment->fBeginY-pCurrComm->nValue;
											pCurrRect->rect.top = stuTempSegment->fEndY;							
										}
									}
									//生成画图矩形
								}				

								if(stu_pSegmentX->Next)
								{
									stuTempSegment = OnAddSegment(stuCurrSegment);
									stuTempSegment->bIsLine = stuCurrSegment->bIsLine;
									stuTempSegment->fBeginY = stuCurrSegment->fBeginY;
									stuTempSegment->fEndY = stuCurrSegment->fEndY;
									stuCurrSegment = stuTempSegment;
								}
							}
							if(stu_pSegmentY->Next||i<pCurrComm->nMultiple-1)
							{
								stuTempSegment = OnAddSegment(stuCurrSegment);
								stuCurrSegment = stuTempSegment;
							}
						}
					}
					if(pCommR==NULL)
					{
						pCurrComm->fTotalDis = pCurrComm->nMultiple * pCurrComm->nValue;
						pCommR = pCurrComm;
					}
					else					
					{
						pCurrComm->fTotalDis = pCommR->fTotalDis + pCurrComm->nMultiple * pCurrComm->nValue;
						pCommR = pCurrComm;
					}
					//
					if (pCommW)
					{
						str.Format("%.f",pCommW->nValue-pCommR->fTotalDis);
						SetDlgItemText(IDC_STATICRREMAIN,str);//R剩余
						m_nRemainderR =  (int)(pCommW->nValue-pCommR->fTotalDis);
					}
					
					break;
				}
			default:
				break;
			}
		}
	}
	else if(strstr(m_strCbo,"P"))	/* 处理异形 P 命令 */
	{/*a;*/
		if(pCurrComm->chCom!='P')
		{
			CGraphDlg	dlg_graphLib;
			pBtroComm = OnAddBotteroCommand(pCurrComm);
			pCurrComm = pBtroComm;
			pLastComm = pCurrComm;
			pCurrComm->chCom = 'P';
			dlg_graphLib.m_bBottero = true;
			dlg_graphLib.m_Rect = GetCurrRect();
			dlg_graphLib.DoModal();
		}
		else if(!pCurrComm->chName[0])
		{
			CGraphDlg	dlg_graphLib;
			dlg_graphLib.m_bBottero = true;
			dlg_graphLib.m_Rect = GetCurrRect();
			dlg_graphLib.DoModal();
		}
	}
	else	/* 处理A、B、C、D命令 */
	{/*b;*/
		if(strOldComm.IsEmpty())
		{
			strOldComm = strCommand;
			fOldValue = m_fValue;
		}
		else
		{
			POINT2D		p;
			pSegment	stuTempSegment,stuCurrSegment;
			pBtroComm = OnAddBotteroCommand(pCurrComm);	/* 申请一项命令数据 */
			pCurrComm = pBtroComm;
			pLastComm = pCurrComm;
			pBtroComm->chCom = m_strCbo.GetAt(0);
			pBtroComm->nValue = m_fValue;
			stuTempSegment = OnAddSegment(NULL);		/* 申请命令数据中的数据段结构 */
			stuCurrSegment = stuTempSegment;
			pBtroComm->pStuSegment = stuTempSegment;
			pBtroComm->pStuSegment->bIsLine = TRUE;

			if(pCommR)
			{
				for(stu_pSegmentX = pCommQ->pStuSegment;stu_pSegmentX;stu_pSegmentX = stu_pSegmentX->Next)
				{
					for(stu_pSegmentY = pCommR->pStuSegment;stu_pSegmentY;stu_pSegmentY = stu_pSegmentY->Next)
					{
						p = OnGetBiasEndValue(strOldComm.GetAt(0),stu_pSegmentX,stu_pSegmentY,pCommQ,pCommR,fOldValue);
						stuTempSegment->fBeginX = (float)p.x;
						stuTempSegment->fBeginY = (float)p.y;
						p = OnGetBiasEndValue(pBtroComm->chCom,stu_pSegmentX,stu_pSegmentY,pCommQ,pCommR,pCurrComm->nValue);
						stuTempSegment->fEndX = (float)p.x;
						stuTempSegment->fEndY = (float)p.y;
						if(stu_pSegmentY->Next)
						{
							stuTempSegment = OnAddSegment(stuCurrSegment);
							stuCurrSegment = stuTempSegment;
							stuCurrSegment->bIsLine = TRUE;
						}
					}
					if(stu_pSegmentX->Next)
					{
						stuTempSegment = OnAddSegment(stuCurrSegment);
						stuCurrSegment = stuTempSegment;
						stuCurrSegment->bIsLine = TRUE;
					}
				}
				strOldComm.Empty();							/* 将老的命令清空 */
			}
			else if(pCommQ)
			{
				for(stu_pSegmentX = pCommQ->pStuSegment;stu_pSegmentX;stu_pSegmentX = stu_pSegmentX->Next)
				{
					for(stu_pSegmentY = pCommW->pStuSegment;stu_pSegmentY;stu_pSegmentY = stu_pSegmentY->Next)
					{
						p = OnGetBiasEndValue(strOldComm.GetAt(0),stu_pSegmentX,stu_pSegmentY,pCommQ,pCommW,fOldValue);
						stuTempSegment->fBeginX = (float)p.x;
						stuTempSegment->fBeginY = (float)p.y;
						p = OnGetBiasEndValue(pBtroComm->chCom,stu_pSegmentX,stu_pSegmentY,pCommQ,pCommW,pCurrComm->nValue);
						stuTempSegment->fEndX = (float)p.x;
						stuTempSegment->fEndY = (float)p.y;
						if(stu_pSegmentY->Next)
						{
							stuTempSegment = OnAddSegment(stuCurrSegment);
							stuCurrSegment = stuTempSegment;
							stuCurrSegment->bIsLine = TRUE;
						}
					}
					if(stu_pSegmentX->Next)
					{
						stuTempSegment = OnAddSegment(stuCurrSegment);
						stuCurrSegment = stuTempSegment;
						stuCurrSegment->bIsLine = TRUE;
					}
				}
				strOldComm.Empty();							/* 将老的命令清空 */
			}
			else if(pCommW)
			{
				for(stu_pSegmentX = pCommZ->pStuSegment;stu_pSegmentX;stu_pSegmentX = stu_pSegmentX->Next)
				{
					for(stu_pSegmentY = pCommW->pStuSegment;stu_pSegmentY;stu_pSegmentY = stu_pSegmentY->Next)
					{
						p = OnGetBiasEndValue(strOldComm.GetAt(0),stu_pSegmentX,stu_pSegmentY,pCommZ,pCommW,fOldValue);
						stuTempSegment->fBeginX = (float)p.x;
						stuTempSegment->fBeginY = (float)p.y;
						p = OnGetBiasEndValue(pBtroComm->chCom,stu_pSegmentX,stu_pSegmentY,pCommZ,pCommW,pCurrComm->nValue);
						stuTempSegment->fEndX = (float)p.x;
						stuTempSegment->fEndY = (float)p.y;
						if(stu_pSegmentY->Next)
						{
							stuTempSegment = OnAddSegment(stuCurrSegment);
							stuCurrSegment = stuTempSegment;
							stuCurrSegment->bIsLine = TRUE;
						}
					}
					if(stu_pSegmentX->Next)
					{
						stuTempSegment = OnAddSegment(stuCurrSegment);
						stuCurrSegment = stuTempSegment;
						stuCurrSegment->bIsLine = TRUE;
					}
				}
				strOldComm.Empty();							/* 将老的命令清空 */
			}
			else if(pCommZ)
			{
				for(stu_pSegmentX = pCommZ->pStuSegment;stu_pSegmentX;stu_pSegmentX = stu_pSegmentX->Next)
				{
					for(stu_pSegmentY = pCommY->pStuSegment;stu_pSegmentY;stu_pSegmentY = stu_pSegmentY->Next)
					{
						p = OnGetBiasEndValue(strOldComm.GetAt(0),stu_pSegmentX,stu_pSegmentY,pCommZ,pCommY,fOldValue);
						stuTempSegment->fBeginX = (float)p.x;
						stuTempSegment->fBeginY = (float)p.y;
						p = OnGetBiasEndValue(pBtroComm->chCom,stu_pSegmentX,stu_pSegmentY,pCommZ,pCommY,pCurrComm->nValue);
						stuTempSegment->fEndX = (float)p.x;
						stuTempSegment->fEndY = (float)p.y;
						if(stu_pSegmentY->Next)
						{
							stuTempSegment = OnAddSegment(stuCurrSegment);
							stuCurrSegment = stuTempSegment;
							stuCurrSegment->bIsLine = TRUE;
						}
					}
					if(stu_pSegmentX->Next)
					{
						stuTempSegment = OnAddSegment(stuCurrSegment);
						stuCurrSegment = stuTempSegment;
						stuCurrSegment->bIsLine = TRUE;
					}
				}
				strOldComm.Empty();							/* 将老的命令清空 */
			}
			else if(pCommY)
			{
				for(stu_pSegmentX = pCommX->pStuSegment;stu_pSegmentX;stu_pSegmentX = stu_pSegmentX->Next)
				{
					for(stu_pSegmentY = pCommY->pStuSegment;stu_pSegmentY;stu_pSegmentY = stu_pSegmentY->Next)
					{
						p = OnGetBiasEndValue(strOldComm.GetAt(0),stu_pSegmentX,stu_pSegmentY,pCommX,pCommY,fOldValue);
						stuTempSegment->fBeginX = (float)p.x;
						stuTempSegment->fBeginY = (float)p.y;
						p = OnGetBiasEndValue(pBtroComm->chCom,stu_pSegmentX,stu_pSegmentY,pCommX,pCommY,pCurrComm->nValue);
						stuTempSegment->fEndX = (float)p.x;
						stuTempSegment->fEndY = (float)p.y;
						if(stu_pSegmentY->Next)
						{
							stuTempSegment = OnAddSegment(stuCurrSegment);
							stuCurrSegment = stuTempSegment;
							stuCurrSegment->bIsLine = TRUE;
						}
					}
					if(stu_pSegmentX->Next)
					{
						stuTempSegment = OnAddSegment(stuCurrSegment);
						stuCurrSegment = stuTempSegment;
						stuCurrSegment->bIsLine = TRUE;
					}
				}
				strOldComm.Empty();							/* 将老的命令清空 */
			}
		}
	}
	nCountComm++;
	bModifyFlag = TRUE;
	((CBenderDlg *)GetParent())->DrawBottero();
	((CEdit *)GetDlgItem(IDC_EDIT_VALUE))->SetSel(0,-1);
}

void CDlg_bottero::DataShowClear()//显示剩余信息的数据全部清空。
{
	SetDlgItemText(IDC_STATICWMAX,"");
	SetDlgItemText(IDC_STATICZMAX,"");
	SetDlgItemText(IDC_STATICQMAX,"");
	SetDlgItemText(IDC_STATICRMAX,"");
	SetDlgItemText(IDC_STATICXREMAIN,"");
	SetDlgItemText(IDC_STATICYREMAIN,"");
	SetDlgItemText(IDC_STATICZREMAIN,"");
	SetDlgItemText(IDC_STATICWREMAIN,"");
	SetDlgItemText(IDC_STATICQREMAIN,"");
	SetDlgItemText(IDC_STATICRREMAIN,"");
}

//添加矩形
pRectDraw CDlg_bottero::AddBotteroRect(pRectDraw pRectCurr)
{
    if(pCurrComm != NULL)
	{
		pRectDraw	pTemp;
		pTemp = new RectDraw;
		memset(pTemp,0,sizeof(RectDraw));
        if (pRectCurr == NULL)
        {
			pCurrComm->pRect = pTemp;
			pTemp->nNum = 1;
        }
		else
		{
			pTemp->nNum = pRectCurr->nNum + 1;
			pRectCurr->Next = pTemp;
		}
	    return pTemp;
	}
	else
	{
		return NULL;
	}
}

//写小片信息
void CDlg_bottero::WriteLittleInf(FILE *file)
{
	FILE *fileG = file;
	int nNO = 0;
	CString strWrite;
	fprintf(fileG, "N%02d   P%4d=%d\n",nNO,3000+nNO,stuBtro.lMaterialX);//原片X方向尺寸
	nNO++;
	fprintf(fileG, "N%02d   P%4d=%d\n",nNO,3000+nNO,stuBtro.lMaterialY);//原片Y方向尺寸
	nNO++;
	fprintf(fileG, "N%02d   P%4d=%d\n",nNO,3000+nNO,stuBtro.lModifyX);//代表原片X1修边
	nNO++;
	fprintf(fileG, "N%02d   P%4d=%d\n",nNO,3000+nNO,stuBtro.lModifyY);//代表原片Y1修边
	nNO++;
	fprintf(fileG, "N%02d   P%4d=%d\n",nNO,3000+nNO,stuBtro.lModifyX);//代表原片X2修边
	nNO++;
	fprintf(fileG, "N%02d   P%4d=%d\n",nNO,3000+nNO,stuBtro.lModifyY);//代表原片Y2修边
	nNO++;
	fprintf(fileG, "N%02d   P%4d=%d\n",nNO,3000+nNO,1);//代表原片数量
	nNO++;
	p_Command	stu_pCommand;
    nNO = 11;
	for(stu_pCommand=stuBtro.BtroComm;stu_pCommand;stu_pCommand=stu_pCommand->Next)
	{
		for (pRectDraw pDraw = stu_pCommand->pRect; pDraw!=NULL; pDraw=pDraw->Next)
		{
			if (stu_pCommand->pRect->nDraw ==1)
			{				
				fprintf(fileG, "N%2d   P%4d=%d_%d_%d_%d_%d_%d___\n",nNO,4000+nNO,pDraw->rect.Width(),-(pDraw->rect.Height()),pDraw->rect.left,pDraw->rect.bottom,pDraw->rect.Width(),-(pDraw->rect.Height()));//原片X方向尺寸
				nNO++;				
			}			
		}
	}
}

void CDlg_bottero::OnCutWindow()
{
	CPaintDC dc(this); // device context for painting
	dc.BeginPath();	
	dc.MoveTo(4, 711);
	dc.LineTo(720, 711); 
	dc.LineTo(720, 207);  	
	dc.LineTo(1024, 207);	
	dc.LineTo(1024, 768);	
	dc.LineTo(4, 768);
	dc.LineTo(4, 711);
	dc.EndPath();	
	CRgn	rgnWin;
	rgnWin.CreateFromPath(&dc);
	SetWindowRgn((HRGN)rgnWin, TRUE);
	if(rgnWin.m_hObject != NULL)
		rgnWin.DeleteObject();
	DeleteDC(dc);
}