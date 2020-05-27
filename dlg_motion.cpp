// dlg_motion.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "dlg_motion.h"
#include "dlg_pass.h"
#include "Dlg_glass.h"
#include "Dlg_KeyNumber.h"
#include "Dlg_config.h"
#include "benderDlg.h"
#include "Dlg_BackUp.h"
#include "Dlg_SheetGlass.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// dlg_motion dialog


dlg_motion::dlg_motion(CWnd* pParent /*=NULL*/)
	: CDialog(dlg_motion::IDD, pParent)
{
	//{{AFX_DATA_INIT(dlg_motion)
	m_vt = g_stu_pAxisG->dSpareD;
	m_dLocationACC = 0.0;
	m_dLocationDCC = 0.0;
	m_dPlineSp = 0.0;
	//}}AFX_DATA_INIT
}

void dlg_motion::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(dlg_motion)
	DDX_Control(pDX, IDC_EDIT_MAXRADIUS, m_editMaxRadius);
	DDX_Control(pDX, IDC_FEEDMOVE5, m_editLocationDCC);
	DDX_Control(pDX, IDC_FEEDMOVE4, m_editLocationACC);
	DDX_Control(pDX, IDC_FEEDVDEC2, m_editFeedDec);
	DDX_Control(pDX, IDC_FEEDVACC2, m_editFeedAcc2);
	DDX_Control(pDX, IDC_FEEDMOVE2, m_EditFeed);
	DDX_Control(pDX, IDC_EDIT_VT, m_edtvt);
	DDX_Control(pDX, IDC_EDIT_ELipseSpeed, m_edtEllispeScale);
	DDX_Control(pDX, IDC_RAPIDMOVE, m_edtRapidMove);
	DDX_Control(pDX, IDC_FEEDVDEC, m_edtFeedVdec);
	DDX_Control(pDX, IDC_FEEDVACC, m_edtFeedVacc);
	DDX_Control(pDX, IDC_FEEDMOVE, m_edtFeedMove);
	DDX_Control(pDX, IDC_EDIT_TANGENT, m_edtTangent);
	DDX_Control(pDX, IDC_EDIT_MINRADIUS, m_edtMinRadius);
	DDX_Control(pDX, IDC_EDIT_MINCORNERSP, m_edtMinCornerSp);
	DDX_Control(pDX, IDC_EDIT_MINCORNER, m_edtMinCorner);
	DDX_Control(pDX, IDC_EDIT_MINARCSP, m_edtMinArcSp);
	DDX_Control(pDX, IDC_EDIT_MAXCORNER, m_edtMaxCorner);
	DDX_Control(pDX, IDC_CENTERY, m_edtCenterY);
	DDX_Control(pDX, IDC_CENTERX, m_edtCenterX);
	DDX_Text(pDX, IDC_FEEDMOVE, m_dFeedMove);
	DDX_Text(pDX, IDC_FEEDVACC, m_dFeedVacc);
	DDX_Text(pDX, IDC_FEEDVDEC, m_dFeedVdec);
	DDX_Text(pDX, IDC_RAPIDMOVE, m_dRapidMove);
	DDX_Text(pDX, IDC_EDIT_VT, m_vt);
	DDV_MinMaxDouble(pDX, m_vt, 4.e-003, 1.);
	DDX_Text(pDX, IDC_FEEDMOVE2, m_dFeed);
	DDX_Text(pDX, IDC_FEEDVACC2, m_dFeedAcc2);
	DDX_Text(pDX, IDC_FEEDVDEC2, m_dFeedDec2);
	DDX_Text(pDX, IDC_FEEDMOVE4, m_dLocationACC);
	DDX_Text(pDX, IDC_FEEDMOVE5, m_dLocationDCC);
	DDX_Text(pDX, IDC_EDIT_ELipseSpeed, m_dPlineSp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(dlg_motion, CDialog)
	//{{AFX_MSG_MAP(dlg_motion)
	ON_BN_CLICKED(IDC_BUTTON8, OnButtonOk)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_MESSAGE(WM_EDITDOUBLE,OnEditDouble)
	ON_MESSAGE(WM_SCALE,OnScale)
	ON_BN_CLICKED(IDC_BUTTON10, OnButton10)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// dlg_motion message handlers

BOOL dlg_motion::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->lParam==VK_ESCAPE||pMsg->wParam==VK_ESCAPE)
		return TRUE;

	if(pMsg->wParam == VK_DOWN || pMsg->wParam==VK_RETURN)
	{
		if(pMsg->message==WM_KEYUP)
		{
			ChangeFocusEdit();
		}
		return(TRUE);
	}
	else
	{
		return CDialog::PreTranslateMessage(pMsg);
	}
	return CDialog::PreTranslateMessage(pMsg);
}

/* �������ݺ��л�����һ��EDIT�� */
void dlg_motion::ChangeFocusEdit() 
{
	keybd_event(VK_TAB, 0, 0, 0);                 //����
	keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);		
}

BOOL dlg_motion::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetCtlFont(this);
	CString  szStr;
	OnLanguage();
	iLanguage = g_iLanguage;	
	PostMessage(WM_SCALE,0,g_stu_pAxisH->sSpare);	
	
	szStr.Format("%.2f",g_stu_pAxisF->dSpareD);	SetDlgItemText(IDC_EDIT_TANGENT,szStr);
	szStr.Format("%.2f",g_stu_pAxisA->dSpareD);	SetDlgItemText(IDC_EDIT_MAXCORNER,szStr);
	szStr.Format("%.2f",g_stu_pAxisB->dSpareD);	SetDlgItemText(IDC_EDIT_MINCORNER,szStr);
	m_vt = g_stu_pAxisG->dSpareD;//���ٶ�ƽ��ϵ��
    InitButton();
	SetWindowPos(CWnd::GetOwner(),0,0,g_screen.x,g_screen.y,SWP_SHOWWINDOW);	
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void dlg_motion::OnButton10() 
{
	g_iPassgrade = 0;
	g_iLanguage =iLanguage ;
	CDialog::OnCancel();
}

void dlg_motion::OnButtonOk() 
{
    OnChange();
	g_machinedll.ParameterSave((char*)((const char*)(g_strOriginalPathD + "machine.ini")));/* �����е������Ϣ */
 	g_iPassgrade = 0;
	GetParent()->PostMessage(WM_SCALE,0,g_stu_pAxisH->sSpare);	
	CString sz;
	char szRes[80]={0};
	sz.Format("VT%.3f",g_stu_pAxisG->dSpareD);
	strcpy(szRes, LPCTSTR(sz));
	g_Controller.Command(szRes);

	CDialog::OnOK();
}

void dlg_motion::OnButton1() 
{
	if(g_iPassgrade==0)
	{
		dlg_pass pass;
		if(pass.DoModal()==IDOK)
		{
			if(g_iPassgrade>0)
			{
				CDlg_config	config;
				config.DoModal();
			}
		}
	}
}

void dlg_motion::OnButton4() 
{
	g_nProduct = 0;
	WritePrivateProfileString("FILE","PRODUCT","0",INIFILE_LASTINF);
}

void dlg_motion::OnLanguage()
{
	int   i;
	int		nIndex;
	nIndex = g_iLanguage + 1;
	for(i=0;i<AR_MOTION;i++)
	{
		if(g_arr_strMotion[i][nIndex]=="NULL")		g_arr_strMotion[i][nIndex] = "";
			SetDlgItemText(atoi(g_arr_strMotion[i][0]),g_arr_strMotion[i][nIndex]);
	}
	if (g_iLanguage) 
	{
		SetDlgItemText(IDC_STATIC_ELipse, "Speed factor"); 
		SetDlgItemText(IDC_STATIC_VT, "Vector Time");
		SetDlgItemText(IDC_STATIC_MAXRADIU,"Max Arc Radius");
	}
}

void dlg_motion::OnChange()
{
	double    num[8];
	CString   szStr;
	int       i;
	CPoint		pMax;
	for(i=0;i<8;i++)    num[i] = 0.0;

	UpdateData(true);
	pMax = ReadMaxSpeed();
	
	if(m_dFeedMove>pMax.x)
		m_dFeedMove = pMax.x;
	if(m_dFeed>pMax.x)
		m_dFeed = pMax.x;

	if(m_dRapidMove>pMax.y)
		m_dRapidMove = pMax.y;
	
	if(g_stu_pAxisH->sSpare==0)
	{
		for(i=0;i<4;i++)    num[i] = m_dFeedMove;
		num[1] = m_dFeed;
		g_machinedll.SetMachine_d(4,FEED_RATE,num);

		for(i=0;i<4;i++)    num[i] = m_dFeedVacc;
		num[1] = m_dFeedAcc2;
		num[2] = m_dLocationACC;
		g_machinedll.SetMachine_d(4,VACC,num);

		for(i=0;i<4;i++)    num[i] = m_dFeedVdec;
		num[1] = m_dFeedDec2;
		num[2] = m_dLocationDCC;
		g_machinedll.SetMachine_d(4,VDEC,num);

		for(i=0;i<4;i++)    num[i] = m_dRapidMove;
		g_machinedll.SetMachine_d(4,RAPID_MOVE,num);

		GetDlgItemText(IDC_CENTERX,szStr);				g_stu_pAxisG->dSpareA = atof(szStr);    /*����ƫ�Ĳ���*/
		GetDlgItemText(IDC_CENTERY,szStr);				g_stu_pAxisH->dSpareA = atof(szStr);    /*����ƫ�Ĳ���*/
		GetDlgItemText(IDC_EDIT_MINCORNERSP,szStr);		g_stu_pAxisC->dSpareD = atof(szStr);    /*��С�ս��ٶ�*/
		GetDlgItemText(IDC_EDIT_MINARCSP,szStr);		g_stu_pAxisD->dSpareD = atof(szStr);    /*��СԲ���ٶ�*/
		GetDlgItemText(IDC_EDIT_MINRADIUS,szStr);		g_stu_pAxisE->dSpareD = atof(szStr);    /*��С�뾶*/
		//���Բ���뾶	
		CString szStr;
		GetDlgItemText(IDC_EDIT_MAXRADIUS,szStr);	
		szStr.Format("%.2f",atof(szStr));
		WritePrivateProfileString("MOTION","MAXRADIUS",szStr,INIFILE_ADDEXTRA);
		g_Dmcgc.SetMaxRadius(atof(szStr));

	}
	else
	{

		for(i=0;i<4;i++)    num[i] = m_dFeedMove * IN_TO_MM;
		num[1] = m_dFeed * IN_TO_MM;
		g_machinedll.SetMachine_d(4,FEED_RATE,num);

		for(i=0;i<4;i++)    num[i] = m_dFeedVacc * IN_TO_MM;
		num[1] = m_dFeedAcc2 * IN_TO_MM;
		num[2] = m_dLocationACC * IN_TO_MM;
		g_machinedll.SetMachine_d(4,VACC,num);


		for(i=0;i<4;i++)    num[i] = m_dFeedVdec * IN_TO_MM;
		num[1] = m_dFeedDec2 * IN_TO_MM;
		num[2] = m_dLocationDCC * IN_TO_MM;
		g_machinedll.SetMachine_d(4,VDEC,num);

		for(i=0;i<4;i++)    num[i] = m_dRapidMove * IN_TO_MM;
		g_machinedll.SetMachine_d(4,RAPID_MOVE,num);

		GetDlgItemText(IDC_CENTERX,szStr);				g_stu_pAxisG->dSpareA = atof(szStr) * IN_TO_MM;    /*����ƫ�Ĳ���*/
		GetDlgItemText(IDC_CENTERY,szStr);				g_stu_pAxisH->dSpareA = atof(szStr) * IN_TO_MM;    /*����ƫ�Ĳ���*/
		GetDlgItemText(IDC_EDIT_MINCORNERSP,szStr);		g_stu_pAxisC->dSpareD = atof(szStr) * IN_TO_MM;    /*��С�ս��ٶ�*/
		GetDlgItemText(IDC_EDIT_MINARCSP,szStr);		g_stu_pAxisD->dSpareD = atof(szStr) * IN_TO_MM;    /*��СԲ���ٶ�*/
		GetDlgItemText(IDC_EDIT_MINRADIUS,szStr);		g_stu_pAxisE->dSpareD = atof(szStr) * IN_TO_MM;    /*��С�뾶*/
        //���Բ���뾶		
		GetDlgItemText(IDC_EDIT_MAXRADIUS,szStr);
		szStr.Format("%.2f",atof(szStr) * IN_TO_MM);
		WritePrivateProfileString("MOTION","MAXRADIUS",szStr,INIFILE_ADDEXTRA);
		g_Dmcgc.SetMaxRadius(atof(szStr) * IN_TO_MM);
	
	}

	GetDlgItemText(IDC_EDIT_MAXCORNER,szStr);		g_stu_pAxisA->dSpareD = atof(szStr);
	GetDlgItemText(IDC_EDIT_MINCORNER,szStr);		g_stu_pAxisB->dSpareD = atof(szStr);
	GetDlgItemText(IDC_EDIT_TANGENT,szStr);			g_stu_pAxisF->dSpareD = atof(szStr);/*  */
	
	
	GetDlgItemText(IDC_EDIT_VT,szStr);//���ٶ�ƽ������
	g_stu_pAxisG->dSpareD = atof(szStr);

	
	g_stu_pAxisC->dSpareE=m_dPlineSp;//ǰհ����			

	
}

void dlg_motion::OnButton5() 
{
	CDlg_glass  glass;
	glass.DoModal();
}

//��������
void dlg_motion::OnButton6() 
{
    CDlg_BackUp dlg;
	dlg.DoModal();
}

LRESULT dlg_motion::OnEditDouble(WPARAM wParam, LPARAM lParam) 
{
	CString				strTmp;
	CDlg_KeyNumber		KeyNum;

	if(lParam==1)/* �д����� */
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

LRESULT dlg_motion::OnScale(WPARAM wParam, LPARAM lParam) 
{
	CString  szStr;
	if (lParam==0)	/* ���� */
	{
		m_dFeedMove = g_stu_pAxisA->d_feedrate;//�岹
		m_dFeed = g_stu_pAxisB->d_feedrate;//����
		m_dFeedVacc = g_stu_pAxisA->d_vacc;//�и�岹���ٶ�
		m_dFeedVdec = g_stu_pAxisA->d_vdec;//�и�岹���ٶ�
		m_dFeedAcc2 = g_stu_pAxisB->d_vacc;//�и�������ٶ�
		m_dFeedDec2 = g_stu_pAxisB->d_vdec;//�и�������ٶ�

		m_dRapidMove = g_stu_pAxisA->d_rapid;//��λ�ٶ�
        m_dLocationACC = g_stu_pAxisC->d_vacc;//��λ���ٶ�
        m_dLocationDCC = g_stu_pAxisC->d_vdec;//��λ���ٶ�
 		m_dPlineSp = g_stu_pAxisC->dSpareE;//ǰհ����
        
		szStr.Format("%.2f",g_stu_pAxisC->dSpareD);		SetDlgItemText(IDC_EDIT_MINCORNERSP,szStr);
		szStr.Format("%.2f",g_stu_pAxisD->dSpareD);		SetDlgItemText(IDC_EDIT_MINARCSP,szStr);
		szStr.Format("%.2f",g_stu_pAxisE->dSpareD);		SetDlgItemText(IDC_EDIT_MINRADIUS,szStr);
		szStr.Format("%.2f",g_stu_pAxisG->dSpareA);		SetDlgItemText(IDC_CENTERX,szStr);
		szStr.Format("%.2f",g_stu_pAxisH->dSpareA);		SetDlgItemText(IDC_CENTERY,szStr);

		//���Բ���뾶
		CString strPara;		
		GetPrivateProfileString("MOTION","MAXRADIUS","0.00",strPara.GetBuffer(MAX_PATH),MAX_PATH,INIFILE_ADDEXTRA);
        szStr.Format("%.2f",atof(strPara));
		SetDlgItemText(IDC_EDIT_MAXRADIUS,szStr);	


		

	}
	else			/* Ӣ�� */
	{
		m_dFeedMove = g_stu_pAxisA->d_feedrate * MM_TO_IN;//�岹
		m_dFeed = g_stu_pAxisB->d_feedrate * MM_TO_IN;//X����
		m_dFeedVacc = g_stu_pAxisA->d_vacc * MM_TO_IN;
		m_dFeedVdec = g_stu_pAxisA->d_vdec * MM_TO_IN;

		m_dFeedAcc2 = g_stu_pAxisB->d_vacc * MM_TO_IN;  
		m_dFeedDec2 = g_stu_pAxisB->d_vdec * MM_TO_IN;


		m_dRapidMove = g_stu_pAxisA->d_rapid * MM_TO_IN;//��λ�ٶ�
        m_dLocationACC = g_stu_pAxisB->d_rapid * MM_TO_IN;//��λ���ٶ�
        m_dLocationDCC = g_stu_pAxisC->d_rapid * MM_TO_IN;//��λ���ٶ�
		m_dPlineSp = g_stu_pAxisC->dSpareE * MM_TO_IN;//ǰհ����

		szStr.Format("%.2f",g_stu_pAxisC->dSpareD * MM_TO_IN);	SetDlgItemText(IDC_EDIT_MINCORNERSP,szStr);
		szStr.Format("%.2f",g_stu_pAxisD->dSpareD * MM_TO_IN);	SetDlgItemText(IDC_EDIT_MINARCSP,szStr);
		szStr.Format("%.2f",g_stu_pAxisE->dSpareD * MM_TO_IN);	SetDlgItemText(IDC_EDIT_MINRADIUS,szStr);
		szStr.Format("%.2f",g_stu_pAxisG->dSpareA * MM_TO_IN);	SetDlgItemText(IDC_CENTERX,szStr);
		szStr.Format("%.2f",g_stu_pAxisH->dSpareA * MM_TO_IN);	SetDlgItemText(IDC_CENTERY,szStr);
		//���Բ���뾶
		CString strPara;		
		GetPrivateProfileString("MOTION","MAXRADIUS","0.00",strPara.GetBuffer(MAX_PATH),MAX_PATH,INIFILE_ADDEXTRA);
        szStr.Format("%.2f",atof(strPara) * MM_TO_IN);
		SetDlgItemText(IDC_EDIT_MAXRADIUS,szStr);	
	}
	UpdateData(FALSE);
	return 0;
}

void dlg_motion::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	//������ͼƬ
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


void dlg_motion::InitButton()
{
	HRGN c;
	
	c = CreateRectRgn(0, 0, 0, 0);	
	GetBitMapRgn(GetDC(),c,IDB_BITMAP_ZEOR1);
	//ϵͳ����	
	m_pButton[0].SetFont(&g_fontStatic);
	m_pButton[0].SetBitMapID(IDB_BITMAP_SYSTEM1,IDB_BITMAP_SYSTEM2);	
	m_pButton[0].Create(g_arr_strMotion[4][g_iLanguage+1], WS_CHILD | WS_VISIBLE, CPoint(20, 705), c, this, IDC_BUTTON1); 
	//��ѹ����	
	m_pButton[1].SetFont(&g_fontStatic);
	m_pButton[1].SetBitMapID(IDB_BITMAP_SETPRE1,IDB_BITMAP_SETPRE2);	
	m_pButton[1].Create(g_arr_strMotion[6][g_iLanguage+1], WS_CHILD | WS_VISIBLE, CPoint(160, 705), c, this, IDC_BUTTON5); 
	//��������
	m_pButton[2].SetFont(&g_fontStatic);
	m_pButton[2].SetBitMapID(IDB_BITMAP_PARABU1,IDB_BITMAP_PARABU2);	
	m_pButton[2].Create(g_arr_strMotion[7][g_iLanguage+1], WS_CHILD | WS_VISIBLE, CPoint(460, 705), c, this, IDC_BUTTON6); 
	//�������	
	m_pButton[3].SetFont(&g_fontStatic);
	m_pButton[3].SetBitMapID(IDB_BITMAP_ZEOR1,IDB_BITMAP_ZEOR2);	
	m_pButton[3].Create(g_arr_strMotion[5][g_iLanguage+1], WS_CHILD | WS_VISIBLE, CPoint(610, 705), c, this, IDC_BUTTON4); 	

	//����
	m_pButton[4].SetFont(&g_fontEdit);
	m_pButton[4].SetBitMapID(IDB_BITMAP_SAVE1,IDB_BITMAP_SAVE2);	
	m_pButton[4].Create(g_arr_strMotion[8][g_iLanguage+1], WS_CHILD | WS_VISIBLE, CPoint(765, 705), c, this, IDC_BUTTON8); 
	
	//����	
	m_pButton[5].SetFont(&g_fontEdit);
	m_pButton[5].SetBitMapID(IDB_BITMAP_BACK1,IDB_BITMAP_BACK2);	
	m_pButton[5].Create(g_arr_strMotion[10][g_iLanguage+1], WS_CHILD | WS_VISIBLE, CPoint(900, 705), c, this, IDC_BUTTON10); 
  

	//ԭƬͳ��	
	CString str;
	if (g_iLanguage==0)
	{
		str = "ԭƬͳ��";
	}
	else
	{
		str = "Sheet";
	}
	m_pButton[6].SetFont(&g_fontStatic);
	m_pButton[6].SetBitMapID(IDB_BITMAP_SHEET1,IDB_BITMAP_SHEET2);	
	m_pButton[6].Create(str, WS_CHILD | WS_VISIBLE, CPoint(300, 705), c, this, IDC_BUTTON3); 


	DeleteObject(c);
}

//ԭƬͳ��
void dlg_motion::OnButton3() 
{
    CDlg_SheetGlass dlg;
	dlg.DoModal();
}

HBRUSH dlg_motion::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if (nCtlColor==CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)GetStockObject(NULL_BRUSH);		
	}
	return hbr;
}
