// dlg_machine.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "dlg_machine.h"
#include "Dlg_KeyNumber.h"
#include "dlg_pass.h"
#include "dlg_galil.h"
#include "Dlg_Calculator.h"
#include "benderDlg.h"
#include "dlg_super.h"
#include "dlg_ustLimit.h"
#include "AdjustDouble.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// dlg_machine dialog


dlg_machine::dlg_machine(CWnd* pParent /*=NULL*/)
	: CDialog(dlg_machine::IDD, pParent)
{
	//{{AFX_DATA_INIT(dlg_machine)
	m_bkw = g_stu_pAxisD->l_Backlash;
	m_bkx = g_stu_pAxisA->l_Backlash;
	m_bky = g_stu_pAxisB->l_Backlash;
	m_bkz = g_stu_pAxisC->l_Backlash;
	m_puslw = g_stu_pAxisD->d_pulse_user;
	m_puslx = g_stu_pAxisA->d_pulse_user;
	m_pusly = g_stu_pAxisB->d_pulse_user;
	m_puslz = g_stu_pAxisC->d_pulse_user;
	m_machineX = g_stu_pAxisA->dSpareA;
	m_machineY = g_stu_pAxisB->dSpareA;
	m_handx = g_stu_pAxisA->d_handspeed;
	m_handy = g_stu_pAxisB->d_handspeed;
	m_handz = g_stu_pAxisC->d_handspeed;
	m_handw = g_stu_pAxisD->d_handspeed;
	m_zonex = g_stu_pAxisA->d_zerospeed;
	m_zoney = g_stu_pAxisB->d_zerospeed;
	m_zonez = g_stu_pAxisC->d_zerospeed;
	m_zonew = g_stu_pAxisD->d_zerospeed;
	m_journeypx = g_stu_pAxisA->l_Journey_positive;
	m_journeypw = g_stu_pAxisD->l_Journey_positive;
	m_journeypy = g_stu_pAxisB->l_Journey_positive;
	m_journeypz = g_stu_pAxisC->l_Journey_positive;
	m_journeyrw = g_stu_pAxisD->l_Journey_negative;
	m_journeyrx = g_stu_pAxisA->l_Journey_negative;
	m_journeyry = g_stu_pAxisB->l_Journey_negative;
	m_journeyrz = g_stu_pAxisC->l_Journey_negative;
	m_zerooffsetw = g_stu_pAxisD->d_ZeroOffset;
	m_zerooffsetx = g_stu_pAxisA->d_ZeroOffset;
	m_zerooffsety = g_stu_pAxisB->d_ZeroOffset;
	m_zerooffsetz = g_stu_pAxisC->d_ZeroOffset;
	m_dAccW = g_stu_pAxisD->d_acc;
	m_dAccX = g_stu_pAxisA->d_acc;
	m_dAccY = g_stu_pAxisB->d_acc;
	m_dAccZ = g_stu_pAxisC->d_acc;
	m_dDecW = g_stu_pAxisD->d_dec;
	m_dDecX = g_stu_pAxisA->d_dec;
	m_dDecY = g_stu_pAxisB->d_dec;
	m_dDecZ = g_stu_pAxisC->d_dec;
	m_machineZ = 0.0;
	m_machineW = 0.0;
	m_nX2Move = 0;
	m_nLabelX = GetPrivateProfileInt("PRINT","LABELPOSX",0,INIFILE_ADDEXTRA);
	m_nLabelY = GetPrivateProfileInt("PRINT","LABELPOSY",0,INIFILE_ADDEXTRA);
	m_nYGetLabel = GetPrivateProfileInt("PRINT","PAPERY",0,INIFILE_ADDEXTRA);
	//}}AFX_DATA_INIT
}


void dlg_machine::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(dlg_machine)
	DDX_Control(pDX, IDC_EDIT_TABELY, m_edtPosY);
	DDX_Control(pDX, IDC_EDIT_MACHLABELY, m_editLabelY);
	DDX_Control(pDX, IDC_EDIT_MACHLABELX, m_editLabelX);
	DDX_Control(pDX, IDC_EDIT_X2MOVE, m_editX2Move);
	DDX_Control(pDX, IDC_ACCZ, m_edtAccZ);
	DDX_Control(pDX, IDC_ACCY, m_edtAccY);
	DDX_Control(pDX, IDC_ACCX, m_edtAccX);
	DDX_Control(pDX, IDC_ACCW, m_edtAccW);
	DDX_Control(pDX, IDC_JOURNEYRD, m_edtJourneyRD);
	DDX_Control(pDX, IDC_JOURNEYRC, m_edtJourneyRC);
	DDX_Control(pDX, IDC_JOURNEYRB, m_edtJourneyRB);
	DDX_Control(pDX, IDC_JOURNEYRA, m_edtJourneyRA);
	DDX_Control(pDX, IDC_JOURNEYPD, m_edtJourneyPD);
	DDX_Control(pDX, IDC_JOURNEYPC, m_edtJourneyPC);
	DDX_Control(pDX, IDC_JOURNEYPB, m_edtJourneyPB);
	DDX_Control(pDX, IDC_JOURNEYPA, m_edtJourneyPA);
	DDX_Control(pDX, IDC_DECZ, m_edtDecZ);
	DDX_Control(pDX, IDC_DECY, m_edtDecY);
	DDX_Control(pDX, IDC_DECX, m_edtDecX);
	DDX_Control(pDX, IDC_DECW, m_edtDecW);
	DDX_Control(pDX, IDC_EDIT_PUSLZ, m_edtPuslZ);
	DDX_Control(pDX, IDC_EDIT_PUSLY, m_edtPuslY);
	DDX_Control(pDX, IDC_EDIT_PUSLX, m_edtPuslX);
	DDX_Control(pDX, IDC_EDIT_PUSLW, m_edtPuslW);
	DDX_Control(pDX, IDC_EDIT_MACHINEZ, m_edtMachineZ);
	DDX_Control(pDX, IDC_EDIT_MACHINEY, m_edtMachineY);
	DDX_Control(pDX, IDC_EDIT_MACHINEX, m_edtMachineX);
	DDX_Control(pDX, IDC_EDIT_MACHINEW, m_edtMachineW);
	DDX_Control(pDX, IDC_EDIT_BKZ, m_edtBKZ);
	DDX_Control(pDX, IDC_EDIT_BKY, m_edtBKY);
	DDX_Control(pDX, IDC_EDIT_BKX, m_edtBKX);
	DDX_Control(pDX, IDC_EDIT_BKW, m_edtBKW);
	DDX_Text(pDX, IDC_EDIT_BKW, m_bkw);
	DDX_Text(pDX, IDC_EDIT_BKX, m_bkx);
	DDX_Text(pDX, IDC_EDIT_BKY, m_bky);
	DDX_Text(pDX, IDC_EDIT_BKZ, m_bkz);
	DDX_Text(pDX, IDC_EDIT_PUSLW, m_puslw);
	DDX_Text(pDX, IDC_EDIT_PUSLX, m_puslx);
	DDX_Text(pDX, IDC_EDIT_PUSLY, m_pusly);
	DDX_Text(pDX, IDC_EDIT_PUSLZ, m_puslz);
	DDX_Text(pDX, IDC_EDIT_MACHINEX, m_machineX);
	DDX_Text(pDX, IDC_EDIT_MACHINEY, m_machineY);
	DDX_Control(pDX, IDC_DEMO10CTRL1, m_demo);
	DDX_Text(pDX, IDC_HANDSPEEDX, m_handx);
	DDX_Text(pDX, IDC_HANDSPEEDY, m_handy);
	DDX_Text(pDX, IDC_HANDSPEEDZ, m_handz);
	DDX_Text(pDX, IDC_HANDSPEEDW, m_handw);
	DDX_Text(pDX, IDC_ZEROSPEEDX, m_zonex);
	DDX_Text(pDX, IDC_ZEROSPEEDY, m_zoney);
	DDX_Text(pDX, IDC_ZEROSPEEDZ, m_zonez);
	DDX_Text(pDX, IDC_ZEROSPEEDW, m_zonew);
	DDX_Text(pDX, IDC_JOURNEYPA, m_journeypx);
	DDX_Text(pDX, IDC_JOURNEYPD, m_journeypw);
	DDX_Text(pDX, IDC_JOURNEYPB, m_journeypy);
	DDX_Text(pDX, IDC_JOURNEYPC, m_journeypz);
	DDX_Text(pDX, IDC_JOURNEYRD, m_journeyrw);
	DDX_Text(pDX, IDC_JOURNEYRA, m_journeyrx);
	DDX_Text(pDX, IDC_JOURNEYRB, m_journeyry);
	DDX_Text(pDX, IDC_JOURNEYRC, m_journeyrz);
	DDX_Text(pDX, IDC_ZEROOFFSETW, m_zerooffsetw);
	DDX_Text(pDX, IDC_ZEROOFFSETX, m_zerooffsetx);
	DDX_Text(pDX, IDC_ZEROOFFSETY, m_zerooffsety);
	DDX_Text(pDX, IDC_ZEROOFFSETZ, m_zerooffsetz);
	DDX_Control(pDX, IDC_COMBO_ZEROW, m_directionw);
	DDX_Control(pDX, IDC_COMBO_ZEROZ, m_directionz);
	DDX_Control(pDX, IDC_COMBO_ZEROY, m_directiony);
	DDX_Control(pDX, IDC_COMBO_ZEROX, m_directionx);
	DDX_Control(pDX, IDC_HANDSPEEDW, m_editHandW);
	DDX_Control(pDX, IDC_HANDSPEEDZ, m_editHandZ);
	DDX_Control(pDX, IDC_HANDSPEEDY, m_editHandY);
	DDX_Control(pDX, IDC_HANDSPEEDX, m_editHandX);
	DDX_Control(pDX, IDC_ZEROSPEEDW, m_edtZoneSpeedW);
	DDX_Control(pDX, IDC_ZEROSPEEDZ, m_edtZoneSpeedZ);
	DDX_Control(pDX, IDC_ZEROSPEEDY, m_edtZoneSpeedY);
	DDX_Control(pDX, IDC_ZEROSPEEDX, m_edtZoneSpeedX);
	DDX_Control(pDX, IDC_ZEROOFFSETZ, m_edtZoneOffsetZ);
	DDX_Control(pDX, IDC_ZEROOFFSETY, m_edtZoneOffsetY);
	DDX_Control(pDX, IDC_ZEROOFFSETX, m_edtZoneOffsetX);
	DDX_Control(pDX, IDC_ZEROOFFSETW, m_edtZoneOffsetW);
	DDX_Text(pDX, IDC_ACCW, m_dAccW);
	DDX_Text(pDX, IDC_ACCX, m_dAccX);
	DDX_Text(pDX, IDC_ACCY, m_dAccY);
	DDX_Text(pDX, IDC_ACCZ, m_dAccZ);
	DDX_Text(pDX, IDC_DECW, m_dDecW);
	DDX_Text(pDX, IDC_DECX, m_dDecX);
	DDX_Text(pDX, IDC_DECY, m_dDecY);
	DDX_Text(pDX, IDC_DECZ, m_dDecZ);
	DDX_Text(pDX, IDC_EDIT_MACHINEZ, m_machineZ);
	DDX_Text(pDX, IDC_EDIT_MACHINEW, m_machineW);
	DDX_Text(pDX, IDC_EDIT_X2MOVE, m_nX2Move);
	DDX_Text(pDX, IDC_EDIT_MACHLABELX, m_nLabelX);
	DDX_Text(pDX, IDC_EDIT_MACHLABELY, m_nLabelY);
	DDX_Text(pDX, IDC_EDIT_TABELY, m_nYGetLabel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(dlg_machine, CDialog)
	//{{AFX_MSG_MAP(dlg_machine)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_MESSAGE(WM_EDITDOUBLE,OnEditDouble)
	ON_MESSAGE(WM_SCALE,OnScale)
	ON_BN_CLICKED(IDC_BUTTON10, OnButton10)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// dlg_machine message handlers

BOOL dlg_machine::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    SetCtlFont(this);
	OnLanguage();
	InitButton();
	SetWindowPos(CWnd::GetOwner(),0,0,g_screen.x,g_screen.y,SWP_SHOWWINDOW);
	if (g_stu_pAxisH->sSpare==1)	/* 英制 */
		SendMessage(WM_SCALE,0,g_stu_pAxisH->sSpare);
	if(g_stu_pAxisF->bSpareA == TRUE)//龙门同步
	{
		CEdit *tmp;
		tmp = (CEdit *)GetDlgItem(IDC_EDIT_BKW);	
		tmp->EnableWindow(TRUE);
		m_nX2Move  = GetPrivateProfileInt("ADJUST","X2MOVE",0,INIFILE_ADDEXTRA);
        UpdateData(FALSE);	
	}
	else
	{		
		CStatic *tmp;
		tmp = (CStatic *)GetDlgItem(IDC_STATIC_WMOVE);	
		tmp->ShowWindow(SW_HIDE);
		CEdit *tmp1;
		tmp1 = (CEdit *)GetDlgItem(IDC_EDIT_X2MOVE);	
		tmp1->ShowWindow(SW_HIDE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void dlg_machine::OnButton1() 
{
	if(g_iPassgrade==2 || g_iPassgrade==3)
	{
		g_iPassgrade = 0;
		dlg_pass pass;
		if(pass.DoModal()==IDOK)
		{
			if(g_iPassgrade>=1)
			{
				dlg_galil	galil;
				galil.DoModal();
			}
		}
	}
	else
	{
		dlg_galil	galil;
		galil.DoModal();
	}
}

void dlg_machine::OnButton8() 
{
	SaveData();
	g_machinedll.ParameterSave((char*)((const char*)(g_strOriginalPathD + "machine.ini")));/* 保存机械参数信息 */
	CBenderDlg	*pdlg;
	pdlg = (CBenderDlg*)FindWindow(NULL, "PNC2000GC");
    pdlg->OnMachineBK();
	CDialog::OnOK();
}

void dlg_machine::OnButton10() 
{
	CDialog::OnOK();
}

void dlg_machine::OnLanguage()
{
	int		i;
	int		nIndex;
	nIndex = g_iLanguage + 1;
	for(i=0;i<AR_MACHINE;i++)
	{
		if(g_arr_strMachine[i][nIndex]=="NULL")		g_arr_strMachine[i][nIndex] = "";
		SetDlgItemText(atoi(g_arr_strMachine[i][0]),g_arr_strMachine[i][nIndex]);
	}
	if(!g_iLanguage)
	{
		m_directionx.AddString("反向");
		m_directionx.AddString("正向");
		m_directiony.AddString("反向");
		m_directiony.AddString("正向");
		m_directionz.AddString("反向");
		m_directionz.AddString("正向");
		m_directionw.AddString("反向");
		m_directionw.AddString("正向");
	}
	else
	{
		m_directionx.AddString("Reverse");
		m_directionx.AddString("Normal");
		m_directiony.AddString("Reverse");
		m_directiony.AddString("Normal");
		m_directionz.AddString("Reverse");
		m_directionz.AddString("Normal");
		m_directionw.AddString("Reverse");
		m_directionw.AddString("Normal");
	}
	m_directionx.SetCurSel(g_stu_pAxisA->l_zerodirection);
	m_directiony.SetCurSel(g_stu_pAxisB->l_zerodirection);
	m_directionz.SetCurSel(g_stu_pAxisC->l_zerodirection);
	m_directionw.SetCurSel(g_stu_pAxisD->l_zerodirection);
	if (g_iLanguage == 1)
	{
		SetDlgItemText(IDC_STATIC_WMOVE,"X2 Offset");
		SetDlgItemText(IDC_STATIC_MAC16,"Label Dis");
		SetDlgItemText(IDC_STATIC_MAC17,"Y Paper Pos");

	}
}

BOOL dlg_machine::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==0x50)
    {
     //   OnLimit();
		return(TRUE);
	}
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==0x4c)
    {
        OnSuper();
		return(TRUE);
	}
	if(pMsg->lParam==VK_ESCAPE || pMsg->wParam==VK_ESCAPE)
		return TRUE;
	if(pMsg->wParam == VK_RETURN || pMsg->wParam==VK_RETURN)
		return(TRUE);
	return CDialog::PreTranslateMessage(pMsg);
}

LRESULT dlg_machine::OnEditDouble(WPARAM wParam, LPARAM lParam) 
{
	CString				strTmp;
	CDlg_KeyNumber		KeyNum;
	
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

void dlg_machine::SaveData() 
{
	UpdateData(TRUE);
	g_stu_pAxisD->l_Backlash = m_bkw;
	g_stu_pAxisA->l_Backlash = m_bkx;
	g_stu_pAxisB->l_Backlash = m_bky;
	g_stu_pAxisC->l_Backlash = m_bkz;
	g_stu_pAxisD->d_pulse_user = m_puslw;
	g_stu_pAxisA->d_pulse_user = m_puslx;
	g_stu_pAxisB->d_pulse_user = m_pusly;
	g_stu_pAxisC->d_pulse_user = m_puslz;
	g_stu_pAxisA->dSpareA = m_machineX;
	g_stu_pAxisB->dSpareA = m_machineY;
//	g_stu_pAxisH->dSpareC = m_machineZ;/* 安全距离 */
	m_machineW = 0.0;
	m_machineZ = 0.0;
	g_stu_pAxisA->d_handspeed = m_handx;
	g_stu_pAxisB->d_handspeed = m_handy;
	g_stu_pAxisC->d_handspeed = m_handz;
	g_stu_pAxisD->d_handspeed = m_handw;
	g_stu_pAxisA->d_zerospeed = m_zonex;
	g_stu_pAxisB->d_zerospeed = m_zoney;
	g_stu_pAxisC->d_zerospeed = m_zonez;
	g_stu_pAxisD->d_zerospeed = m_zonew;
	g_stu_pAxisA->l_Journey_positive = m_journeypx;
	g_stu_pAxisD->l_Journey_positive = m_journeypw;
	g_stu_pAxisB->l_Journey_positive = m_journeypy;
	g_stu_pAxisC->l_Journey_positive = m_journeypz;
	g_stu_pAxisD->l_Journey_negative = m_journeyrw;
	g_stu_pAxisA->l_Journey_negative = m_journeyrx;
	g_stu_pAxisB->l_Journey_negative = m_journeyry;
	g_stu_pAxisC->l_Journey_negative = m_journeyrz;
	g_stu_pAxisD->d_ZeroOffset = m_zerooffsetw;
	g_stu_pAxisA->d_ZeroOffset = m_zerooffsetx;
	g_stu_pAxisB->d_ZeroOffset = m_zerooffsety;
	g_stu_pAxisC->d_ZeroOffset = m_zerooffsetz;
	g_stu_pAxisD->d_acc = m_dAccW;
	g_stu_pAxisA->d_acc = m_dAccX;
	g_stu_pAxisB->d_acc = m_dAccY;
	g_stu_pAxisC->d_acc = m_dAccZ;
	g_stu_pAxisD->d_dec = m_dDecW;
	g_stu_pAxisA->d_dec = m_dDecX;
	g_stu_pAxisB->d_dec = m_dDecY;
	g_stu_pAxisC->d_dec = m_dDecZ;
	g_stu_pAxisA->l_zerodirection = m_directionx.GetCurSel();
	g_stu_pAxisB->l_zerodirection = m_directiony.GetCurSel();
	g_stu_pAxisC->l_zerodirection = m_directionz.GetCurSel();
	g_stu_pAxisD->l_zerodirection = m_directionw.GetCurSel();
	if(g_stu_pAxisF->bSpareA == TRUE)//龙门同步
	{
		int nValue = m_nX2Move;
		CString strCheck;
		char szCmd[80];	
		strCheck.Format("%d",nValue);
		WritePrivateProfileString("ADJUST","X2MOVE",strCheck,INIFILE_ADDEXTRA);
		sprintf(szCmd,"M2=%d",nValue);
		g_Controller.Command(szCmd);

	}

    //标签离切割头距离	
	CString strCheck;
	strCheck.Format("%d",m_nLabelX);
	WritePrivateProfileString("PRINT","LABELPOSX",strCheck,INIFILE_ADDEXTRA);
	strCheck.Format("%d",m_nLabelY);
	WritePrivateProfileString("PRINT","LABELPOSY",strCheck,INIFILE_ADDEXTRA);
	//取标签的位置
	strCheck.Format("%d",m_nYGetLabel);
	WritePrivateProfileString("PRINT","PAPERY",strCheck,INIFILE_ADDEXTRA);
 
	g_Dmcgc.SetLabelPos(m_nLabelX,m_nLabelY,m_nYGetLabel);

	
	//修改软限位，并且回零后生效
	CString		strTemp;
	char szCmd[80]={0};

	strTemp.Format("nSFLX=%.0f;nSFLY=%.0f",
		g_stu_pAxisA->l_Journey_positive * g_stu_pAxisA->d_pulse_user,
		g_stu_pAxisB->l_Journey_positive * g_stu_pAxisB->d_pulse_user);
	strcpy(szCmd,LPCTSTR(strTemp));
	LONG l_Rec = g_Controller.Command(szCmd);
	if (l_Rec != 0)
	{
		CDlg_AfxMessage  Message;
		Message.bYesNo = FALSE;
		if(g_iLanguage==1)
		{
			Message.strAfxYES ="OK";
			Message.strAfxTitle ="Error";
			Message.strAfxMessage ="Control error !";
		}
		else
		{
			Message.strAfxYES ="确定";
			Message.strAfxTitle ="控制器错误";
			Message.strAfxMessage ="请全部断电，重新启动设备！";
		} 
		Message.DoModal(); 	
		return ;
	}
	strTemp.Format("nSBLX=%.0f;nSBLY=%.0f",
		g_stu_pAxisA->l_Journey_negative * g_stu_pAxisA->d_pulse_user,
		g_stu_pAxisB->l_Journey_negative * g_stu_pAxisB->d_pulse_user);
	strcpy(szCmd,LPCTSTR(strTemp));
	l_Rec = g_Controller.Command(szCmd);
    if (l_Rec != 0)
	{
		CDlg_AfxMessage  Message;
		Message.bYesNo = FALSE;
		if(g_iLanguage==1)
		{
			Message.strAfxYES ="OK";
			Message.strAfxTitle ="Error";
			Message.strAfxMessage ="Control error !";
		}
		else
		{
			Message.strAfxYES ="确定";
			Message.strAfxTitle ="控制器错误";
			Message.strAfxMessage ="请全部断电，重新启动设备！";
		} 
		Message.DoModal(); 	
		return ;
	}
	SendMessage(WM_SCALE,1,g_stu_pAxisH->sSpare);
}

LRESULT dlg_machine::OnScale(WPARAM wParam, LPARAM lParam) 
{
	if(lParam==0)/* 如果是公制则不处理 */
		return 0;
	if (wParam==0)	/* 初始化，将公制转化为英制显示 */
	{
		m_puslw = SaveNPoint(4, g_stu_pAxisD->d_pulse_user * MM_TO_IN);
		m_puslx = SaveNPoint(4, g_stu_pAxisA->d_pulse_user * MM_TO_IN);
		m_pusly = SaveNPoint(4, g_stu_pAxisB->d_pulse_user * MM_TO_IN);
		m_puslz = SaveNPoint(4, g_stu_pAxisC->d_pulse_user * MM_TO_IN);
		m_machineX = SaveNPoint(4, g_stu_pAxisA->dSpareA * MM_TO_IN);
		m_machineY = SaveNPoint(4, g_stu_pAxisB->dSpareA * MM_TO_IN);
		m_handx = SaveNPoint(4, g_stu_pAxisA->d_handspeed * MM_TO_IN);
		m_handy = SaveNPoint(4, g_stu_pAxisB->d_handspeed * MM_TO_IN);
		m_handz = SaveNPoint(4, g_stu_pAxisC->d_handspeed * MM_TO_IN);
		m_handw = SaveNPoint(4, g_stu_pAxisD->d_handspeed * MM_TO_IN);
		m_zonex = SaveNPoint(4, g_stu_pAxisA->d_zerospeed * MM_TO_IN);
		m_zoney = SaveNPoint(4, g_stu_pAxisB->d_zerospeed * MM_TO_IN);
		m_zonez = SaveNPoint(4, g_stu_pAxisC->d_zerospeed * MM_TO_IN);
		m_zonew = SaveNPoint(4, g_stu_pAxisD->d_zerospeed * MM_TO_IN);
		m_journeypx = (long)SaveNPoint(4, g_stu_pAxisA->l_Journey_positive * MM_TO_IN);
		m_journeypw = (long)SaveNPoint(4, g_stu_pAxisD->l_Journey_positive * MM_TO_IN);
		m_journeypy = (long)SaveNPoint(4, g_stu_pAxisB->l_Journey_positive * MM_TO_IN);
		m_journeypz = (long)SaveNPoint(4, g_stu_pAxisC->l_Journey_positive * MM_TO_IN);
		m_journeyrw = (long)SaveNPoint(4, g_stu_pAxisD->l_Journey_negative * MM_TO_IN);
		m_journeyrx = (long)SaveNPoint(4, g_stu_pAxisA->l_Journey_negative * MM_TO_IN);
		m_journeyry = (long)SaveNPoint(4, g_stu_pAxisB->l_Journey_negative * MM_TO_IN);
		m_journeyrz = (long)SaveNPoint(4, g_stu_pAxisC->l_Journey_negative * MM_TO_IN);
		m_zerooffsetw = SaveNPoint(4, g_stu_pAxisD->d_ZeroOffset * MM_TO_IN);
		m_zerooffsetx = SaveNPoint(4, g_stu_pAxisA->d_ZeroOffset * MM_TO_IN);
		m_zerooffsety = SaveNPoint(4, g_stu_pAxisB->d_ZeroOffset * MM_TO_IN);
		m_zerooffsetz = SaveNPoint(4, g_stu_pAxisC->d_ZeroOffset * MM_TO_IN);
		m_dAccW = SaveNPoint(4, g_stu_pAxisD->d_acc * MM_TO_IN);
		m_dAccX = SaveNPoint(4, g_stu_pAxisA->d_acc * MM_TO_IN);
		m_dAccY = SaveNPoint(4, g_stu_pAxisB->d_acc * MM_TO_IN);
		m_dAccZ = SaveNPoint(4, g_stu_pAxisC->d_acc * MM_TO_IN);
		m_dDecW = SaveNPoint(4, g_stu_pAxisD->d_dec * MM_TO_IN);
		m_dDecX = SaveNPoint(4, g_stu_pAxisA->d_dec * MM_TO_IN);
		m_dDecY = SaveNPoint(4, g_stu_pAxisB->d_dec * MM_TO_IN);
		m_dDecZ = SaveNPoint(4, g_stu_pAxisC->d_dec * MM_TO_IN);
		UpdateData(FALSE);
	}
	else			/* 保存，将英制数据转化为公制保存 */
	{
		UpdateData(TRUE);
		g_stu_pAxisD->d_pulse_user = m_puslw * IN_TO_MM;
		g_stu_pAxisA->d_pulse_user = m_puslx * IN_TO_MM;
		g_stu_pAxisB->d_pulse_user = m_pusly * IN_TO_MM;
		g_stu_pAxisC->d_pulse_user = m_puslz * IN_TO_MM;
		g_stu_pAxisA->dSpareA = m_machineX * IN_TO_MM;
		g_stu_pAxisB->dSpareA = m_machineY * IN_TO_MM;
		m_machineZ = 0.0;
		m_machineW = 0.0;
		g_stu_pAxisA->d_handspeed = m_handx * IN_TO_MM;
		g_stu_pAxisB->d_handspeed = m_handy * IN_TO_MM;
		g_stu_pAxisC->d_handspeed = m_handz * IN_TO_MM;
		g_stu_pAxisD->d_handspeed = m_handw * IN_TO_MM;
		g_stu_pAxisA->d_zerospeed = m_zonex * IN_TO_MM;
		g_stu_pAxisB->d_zerospeed = m_zoney * IN_TO_MM;
		g_stu_pAxisC->d_zerospeed = m_zonez * IN_TO_MM;
		g_stu_pAxisD->d_zerospeed = m_zonew * IN_TO_MM;
		g_stu_pAxisA->l_Journey_positive = (long)(m_journeypx * IN_TO_MM);
		g_stu_pAxisD->l_Journey_positive = (long)(m_journeypw * IN_TO_MM);
		g_stu_pAxisB->l_Journey_positive = (long)(m_journeypy * IN_TO_MM);
		g_stu_pAxisC->l_Journey_positive = (long)(m_journeypz * IN_TO_MM);
		g_stu_pAxisD->l_Journey_negative = (long)(m_journeyrw * IN_TO_MM);
		g_stu_pAxisA->l_Journey_negative = (long)(m_journeyrx * IN_TO_MM);
		g_stu_pAxisB->l_Journey_negative = (long)(m_journeyry * IN_TO_MM);
		g_stu_pAxisC->l_Journey_negative = (long)(m_journeyrz * IN_TO_MM);
		g_stu_pAxisD->d_ZeroOffset = m_zerooffsetw * IN_TO_MM;
		g_stu_pAxisA->d_ZeroOffset = m_zerooffsetx * IN_TO_MM;
		g_stu_pAxisB->d_ZeroOffset = m_zerooffsety * IN_TO_MM;
		g_stu_pAxisC->d_ZeroOffset = m_zerooffsetz * IN_TO_MM;
		g_stu_pAxisD->d_acc = m_dAccW * IN_TO_MM;
		g_stu_pAxisA->d_acc = m_dAccX * IN_TO_MM;
		g_stu_pAxisB->d_acc = m_dAccY * IN_TO_MM;
		g_stu_pAxisC->d_acc = m_dAccZ * IN_TO_MM;
		g_stu_pAxisD->d_dec = m_dDecW * IN_TO_MM;
		g_stu_pAxisA->d_dec = m_dDecX * IN_TO_MM;
		g_stu_pAxisB->d_dec = m_dDecY * IN_TO_MM;
		g_stu_pAxisC->d_dec = m_dDecZ * IN_TO_MM;
	}
	return 0;
}

void dlg_machine::OnButton5() 
{
	CDlg_Calculator	dlgCal;
	dlgCal.DoModal();
}

void dlg_machine::OnPaint() 
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

void dlg_machine::InitButton()
{
	HRGN c;
	
	c = CreateRectRgn(0, 0, 0, 0);	
	GetBitMapRgn(GetDC(),c,IDB_BITMAP_ZEOR1);
	//控制器
	m_pButton[0].SetFont(&g_fontStatic);
	m_pButton[0].SetBitMapID(IDB_BITMAP_CONTROL1,IDB_BITMAP_CONTROL2);	
	m_pButton[0].Create(g_arr_strMachine[6][g_iLanguage+1], WS_CHILD | WS_VISIBLE, CPoint(30, 705), c, this, IDC_BUTTON1); 
		//计算器
	m_pButton[2].SetFont(&g_fontStatic);
	m_pButton[2].SetBitMapID(IDB_BITMAP_CLU1,IDB_BITMAP_CLU2);	
	m_pButton[2].Create(g_arr_strMachine[8][g_iLanguage+1], WS_CHILD | WS_VISIBLE, CPoint(380, 705), c, this, IDC_BUTTON5); 	
	
	//保存
	m_pButton[3].SetFont(&g_fontEdit);
	m_pButton[3].SetBitMapID(IDB_BITMAP_SAVE1,IDB_BITMAP_SAVE2);	
	m_pButton[3].Create(g_arr_strMachine[10][g_iLanguage+1], WS_CHILD | WS_VISIBLE, CPoint(700, 705), c, this, IDC_BUTTON8); 
	
	//返回	
	m_pButton[1].SetFont(&g_fontEdit);
	m_pButton[1].SetBitMapID(IDB_BITMAP_BACK1,IDB_BITMAP_BACK2);	
	m_pButton[1].Create(g_arr_strMachine[7][g_iLanguage+1], WS_CHILD | WS_VISIBLE, CPoint(870, 705), c, this, IDC_BUTTON10); 

	//龙门
	if(g_stu_pAxisF->bSpareA == TRUE)//龙门同步
	{
		m_pButton[4].SetFont(&g_fontStatic);
		m_pButton[4].HaveBitmap(1);
		m_pButton[4].SetBitMapID(IDB_BITMAP1,IDB_BITMAP2);
		if (g_iLanguage == 0)
		{
			g_arr_strMachine[9][g_iLanguage+1] = "龙门同步";
		} 
		else
		{
			g_arr_strMachine[9][g_iLanguage+1] = "Adjust";
		}
		m_pButton[4].Create(g_arr_strMachine[9][g_iLanguage+1], WS_CHILD | WS_VISIBLE, CPoint(200, 705), c, this, IDC_BUTTON4); 

	}    
	DeleteObject(c);  
}

void dlg_machine::OnLimit() 
{
   	if(GetKeyState(VK_CONTROL) < 0 && GetKeyState(VK_SHIFT) < 0)
	{		
		int n = ((CBenderDlg*)AfxGetMainWnd())->HardDogCheck();
		if (n == 1)
		{
			CDialog::OnOK();
			return;
		}
		if(g_iPassgrade==1)
		{
			dlg_ustLimit  limit;
			limit.DoModal();
		}
		else
		{
			dlg_pass pass;
			if(pass.DoModal()==IDOK)
			{
				if(g_iPassgrade==1)
				{
					dlg_ustLimit  limit;
					limit.DoModal();
				}
			}
		}
	}
}	

void dlg_machine::OnSuper() 
{
   	if(GetKeyState(VK_CONTROL) < 0 && GetKeyState(VK_SHIFT) < 0)
	{
		int n = ((CBenderDlg*)AfxGetMainWnd())->HardDogCheck();
		if (n == 1)
		{
			CDialog::OnOK();
			return;
		}
		dlg_pass pass;
		if(g_iPassgrade==1)
		{
			dlg_super super;
			super.DoModal();
		}
		else
		{
			if(pass.DoModal()==IDOK)
			{
				if(g_iPassgrade==1)
				{
					dlg_super super;
					super.DoModal();
				}
			}
		}
	}
}

void dlg_machine::OnButton4()
{
	g_iMode = MODE_A;
    CAdjustDouble dlg;
	dlg.DoModal();
	g_iMode = MODE_MAIN;
	g_Controller.Command("ST");
	Sleep(50);
	g_Controller.Command("GA,,,CX;GR0,,,1;GM1,,,1");
    Sleep(50);
}

HBRUSH dlg_machine::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
