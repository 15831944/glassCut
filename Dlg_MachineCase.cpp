// Dlg_MachineCase.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "benderDlg.h"
#include "Dlg_MachineCase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_MachineCase dialog


CDlg_MachineCase::CDlg_MachineCase(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_MachineCase::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_MachineCase)
	//}}AFX_DATA_INIT
}


void CDlg_MachineCase::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_MachineCase)
	DDX_Control(pDX, IDC_LIST_ALARM, m_lstAlarm);
	DDX_Control(pDX, IDC_DEMO10CTRL1, m_ocxDemo);
	//}}AFX_DATA_MAP
	
}


BEGIN_MESSAGE_MAP(CDlg_MachineCase, CDialog)
	//{{AFX_MSG_MAP(CDlg_MachineCase)
	ON_BN_CLICKED(IDC_BUTTON_CS1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON_CS3, OnButton3)
	ON_MESSAGE(WM_ALMINPUT,OnStateInput)
	ON_MESSAGE(WM_ALMOUTPUT,OnStateOutput)
	ON_BN_CLICKED(IDC_BUTTON_CS4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON_CS10, OnButtonCs10)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_MachineCase message handlers

BOOL CDlg_MachineCase::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetWindowText("CASE");
	OnLanguage();
	InitButton();
	OnInitList();
	OnInitDisplay();	
	OnFirstInput();
	OnButton2();
	SetWindowPos(&CWnd::wndTopMost,0,0,g_screen.x,g_screen.y,SWP_SHOWWINDOW);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/* 初始化列表框 */
void CDlg_MachineCase::OnInitList() 
{
	m_lstAlarm.ShowWindow(FALSE);
	m_lstAlarm.SetFont(&g_fontList);
	m_lstAlarm.InsertColumn(0, "Time", LVCFMT_LEFT, 220, 3);
	m_lstAlarm.InsertColumn(1, "Code", LVCFMT_LEFT, 80, 0);
	m_lstAlarm.InsertColumn(2, "Grade", LVCFMT_LEFT, 80, 1);
	m_lstAlarm.InsertColumn(3, "Content", LVCFMT_LEFT, 150, 2);
	m_lstAlarm.InsertColumn(4, "State", LVCFMT_LEFT, 150, 2);

	g_AlarmDll.SetLanguage(g_iLanguage);
}

/* 初始化报警 */
void CDlg_MachineCase::OnInitAlarmList(BOOL bCurrAlarm) 
{
	int nCurltem = 0;
	CString strItem1, strItem2, strItem3, strItem4, strItem5;

	m_lstAlarm.DeleteAllItems();
	
	if(bCurrAlarm)
	{
		m_nAlarmCounts = g_AlarmDll.GetAlarmCounts();
		m_pRTAlarm = g_AlarmDll.GetAlarm();
		for(int i=0;i<m_nAlarmCounts;i++)
		{
			strItem1.Format("%s", m_pRTAlarm->chTime);
			strItem2.Format("%d", m_pRTAlarm->nCode);
			strItem3.Format("%d", m_pRTAlarm->nGrade);
			strItem4.Format("%s", m_pRTAlarm->Context);			
			nCurltem = m_lstAlarm.InsertItem(m_lstAlarm.GetItemCount(), strItem1);
			m_lstAlarm.SetItemText(nCurltem, 1, strItem2);
			m_lstAlarm.SetItemText(nCurltem, 2, strItem3);
			m_lstAlarm.SetItemText(nCurltem, 3, strItem4);
			m_pRTAlarm = g_AlarmDll.GetNextAlarm();
		}
	}
	else
	{
		pALARM		 m_pTempAlarm;
		pPARAALARM	 pTempPara;
		m_pHistoryAlarm = g_AlarmDll.GetHistoryAlarm();
		for(m_pTempAlarm=m_pHistoryAlarm; m_pTempAlarm; m_pTempAlarm = m_pTempAlarm->pNext)
		{
			strItem1.Format("%s", m_pTempAlarm->chTime);
			strItem2.Format("%d", m_pTempAlarm->nCode);
			pTempPara = g_AlarmDll.GetSpecifyAlarm(m_pTempAlarm->nCode);
			strItem3.Format("%d", pTempPara->nGrade);
			strItem4.Format("%s", pTempPara->Context);
			
			if(!g_iLanguage)
			{
				if(m_pTempAlarm->nState == 0)
					strItem5 = "清除";
				else
					strItem5 = "报警";
			}
			else
			{
				if(m_pTempAlarm->nState == 0)
					strItem5 = "Clear";
				else
					strItem5 = "Alarm";
			}

			nCurltem = m_lstAlarm.InsertItem(m_lstAlarm.GetItemCount(), strItem1);
			m_lstAlarm.SetItemText(nCurltem, 1, strItem2);
			m_lstAlarm.SetItemText(nCurltem, 2, strItem3);
			m_lstAlarm.SetItemText(nCurltem, 3, strItem4);
			m_lstAlarm.SetItemText(nCurltem, 4, strItem5);
		}
	}
}

/* 初始化显示控件 */
void CDlg_MachineCase::OnInitDisplay() 
{
	DWORD crBK = BACKCOLOR;
#ifdef POWERLAND
    crBK = RGB(165,198,248);
#endif   
	for(int index=0; index<=IDC_DISPLAY4-IDC_DISPLAY1; index++)
	{
		m_ocxDisplay[index].SubclassDlgItem(IDC_DISPLAY1+index, this);
		m_ocxDisplay[index].SetBackColor(crBK);
		m_ocxDisplay[index].SetDisplayCount(16);
	}
	if(!g_iLanguage)
	{
		m_ocxDisplay[0].SetDisplayName(1,"定位块");
		m_ocxDisplay[0].SetDisplayName(2,"切割油");
		m_ocxDisplay[0].SetDisplayName(3,"上片台启动");
		m_ocxDisplay[0].SetDisplayName(4,"风机启停");
		m_ocxDisplay[0].SetDisplayName(5,"注煤油");
		m_ocxDisplay[0].SetDisplayName(6,"传送带升降");
		m_ocxDisplay[0].SetDisplayName(7,"传送带正向");
		m_ocxDisplay[0].SetDisplayName(8,"传送带反向");
		m_ocxDisplay[0].SetDisplayName(9,"快速/慢速");
		m_ocxDisplay[0].SetDisplayName(10,"C轴下刀");
		m_ocxDisplay[0].SetDisplayName(11,"启动灯");
		m_ocxDisplay[0].SetDisplayName(12,"停止灯");
		m_ocxDisplay[0].SetDisplayName(13,"贴标签");
		m_ocxDisplay[0].SetDisplayName(14,"标签真空泵");
		m_ocxDisplay[0].SetDisplayName(15,"");
		m_ocxDisplay[0].SetDisplayName(16,"");
		
		m_ocxDisplay[1].SetDisplayName(1,"X+");
		m_ocxDisplay[1].SetDisplayName(2,"X-");
		m_ocxDisplay[1].SetDisplayName(3,"Y+");
		m_ocxDisplay[1].SetDisplayName(4,"Y-");
		m_ocxDisplay[1].SetDisplayName(5,"标签感应");
		m_ocxDisplay[1].SetDisplayName(6,"风机");
		m_ocxDisplay[1].SetDisplayName(7,"安全光栅");
		m_ocxDisplay[1].SetDisplayName(8,"");
		m_ocxDisplay[1].SetDisplayName(9,"");
		m_ocxDisplay[1].SetDisplayName(10,"");
		m_ocxDisplay[1].SetDisplayName(11,"");
		m_ocxDisplay[1].SetDisplayName(12,"");
		m_ocxDisplay[1].SetDisplayName(13,"");//
		m_ocxDisplay[1].SetDisplayName(14,"");
		m_ocxDisplay[1].SetDisplayName(15,"");
		m_ocxDisplay[1].SetDisplayName(16,"");
		if (g_stu_pAxisA->sSpare==0 || g_stu_pAxisA->sSpare==2)//位置方式\串口
		{
			m_ocxDisplay[2].SetDisplayName(1,"X伺服报警");
			m_ocxDisplay[2].SetDisplayName(2,"Y伺服报警");
			m_ocxDisplay[2].SetDisplayName(3,"Z伺服报警");
			//龙门同步
			if(g_stu_pAxisF->bSpareA == TRUE)
			{
				m_ocxDisplay[2].SetDisplayName(4,"W伺服报警");
			}
			else
			{
				m_ocxDisplay[2].SetDisplayName(4,"");
			}
		}
		else
		{
			m_ocxDisplay[2].SetDisplayName(1,"");
			m_ocxDisplay[2].SetDisplayName(2,"");
			m_ocxDisplay[2].SetDisplayName(3,"");
			m_ocxDisplay[2].SetDisplayName(4,"");
		}
		m_ocxDisplay[2].SetDisplayName(5,"");
		m_ocxDisplay[2].SetDisplayName(6,"");
		m_ocxDisplay[2].SetDisplayName(7,"");
		m_ocxDisplay[2].SetDisplayName(8,"");
		m_ocxDisplay[2].SetDisplayName(9,"");
		m_ocxDisplay[2].SetDisplayName(10,"");
		m_ocxDisplay[2].SetDisplayName(11,"");
		m_ocxDisplay[2].SetDisplayName(12,"");
		m_ocxDisplay[2].SetDisplayName(13,"X 轴回零");
		m_ocxDisplay[2].SetDisplayName(14,"Y 轴回零");
		m_ocxDisplay[2].SetDisplayName(15,"C 轴回零");
		if (g_stu_pAxisA->sSpare==0 || g_stu_pAxisA->sSpare==2)//位置方式\串口
		{
			//龙门同步
			if(g_stu_pAxisF->bSpareA == TRUE)
				m_ocxDisplay[2].SetDisplayName(16,"W轴回零");
			else
				m_ocxDisplay[2].SetDisplayName(16,"");
		}
		else
			m_ocxDisplay[2].SetDisplayName(16,"伺服报警");
		m_ocxDisplay[3].SetDisplayName(1,"X 正限位");
		m_ocxDisplay[3].SetDisplayName(2,"Y 正限位");
		m_ocxDisplay[3].SetDisplayName(3,"C 正限位");
		m_ocxDisplay[3].SetDisplayName(4,"W 正限位");
		m_ocxDisplay[3].SetDisplayName(5,"X 负限位");
		m_ocxDisplay[3].SetDisplayName(6,"Y 负限位");
		m_ocxDisplay[3].SetDisplayName(7,"C 负限位");
		m_ocxDisplay[3].SetDisplayName(8,"W 负限位");
		m_ocxDisplay[3].SetDisplayName(9,"光电定位");
		m_ocxDisplay[3].SetDisplayName(10,"系统用");
		m_ocxDisplay[3].SetDisplayName(11,"启动");
		m_ocxDisplay[3].SetDisplayName(12,"停止");
		m_ocxDisplay[3].SetDisplayName(13,"传送玻璃");
		m_ocxDisplay[3].SetDisplayName(14,"桌面开关");
		m_ocxDisplay[3].SetDisplayName(15,"上片台准备信号");
		m_ocxDisplay[3].SetDisplayName(16,"下刀保护");
	}
	else
	{		
		m_ocxDisplay[0].SetDisplayName(1,"Fixed Position");
		m_ocxDisplay[0].SetDisplayName(2,"Cut Oil");
		m_ocxDisplay[0].SetDisplayName(3,"Platform Start");
		m_ocxDisplay[0].SetDisplayName(4,"Fan Start & Stop");
		m_ocxDisplay[0].SetDisplayName(5,"Oiling");
		m_ocxDisplay[0].SetDisplayName(6,"Conveyer Belt Rise & Fal");
		m_ocxDisplay[0].SetDisplayName(7,"Conveyer Belt Forward");
		m_ocxDisplay[0].SetDisplayName(8,"Conveyer Belt Reverse");
		m_ocxDisplay[0].SetDisplayName(9,"Start");
		m_ocxDisplay[0].SetDisplayName(10,"Stop");
		m_ocxDisplay[0].SetDisplayName(11,"Label");
		m_ocxDisplay[0].SetDisplayName(12,"Label Pump");
		m_ocxDisplay[0].SetDisplayName(13,"");
		m_ocxDisplay[0].SetDisplayName(14,"");
		m_ocxDisplay[0].SetDisplayName(15,"");
		m_ocxDisplay[0].SetDisplayName(16,"");
		
		m_ocxDisplay[1].SetDisplayName(1,"X+");
		m_ocxDisplay[1].SetDisplayName(2,"X-");
		m_ocxDisplay[1].SetDisplayName(3,"Y+");
		m_ocxDisplay[1].SetDisplayName(4,"Y-");
		m_ocxDisplay[1].SetDisplayName(5,"Label Input");
		m_ocxDisplay[1].SetDisplayName(6,"Fan");
		m_ocxDisplay[1].SetDisplayName(7,"Safe");
		m_ocxDisplay[1].SetDisplayName(8,"");
		m_ocxDisplay[1].SetDisplayName(9,"");
		m_ocxDisplay[1].SetDisplayName(10,"");
		m_ocxDisplay[1].SetDisplayName(11,"");
		m_ocxDisplay[1].SetDisplayName(12,"");
		m_ocxDisplay[1].SetDisplayName(13,"");
		m_ocxDisplay[1].SetDisplayName(14,"");
		m_ocxDisplay[1].SetDisplayName(15,"");
		m_ocxDisplay[1].SetDisplayName(16,"");
		
		m_ocxDisplay[2].SetDisplayName(1,"Sevor Alarm X");
		m_ocxDisplay[2].SetDisplayName(2,"Sevor Alarm Y");
		m_ocxDisplay[2].SetDisplayName(3,"Sevor Alarm Z");
		m_ocxDisplay[2].SetDisplayName(4,"Standby");
		m_ocxDisplay[2].SetDisplayName(5,"Cutting Start");
		m_ocxDisplay[2].SetDisplayName(6,"Cutting Stop");
		m_ocxDisplay[2].SetDisplayName(7,"X +");
		m_ocxDisplay[2].SetDisplayName(8,"X -");
		m_ocxDisplay[2].SetDisplayName(9,"Standby");
		m_ocxDisplay[2].SetDisplayName(10,"Standby");
		m_ocxDisplay[2].SetDisplayName(11,"Standby");
		m_ocxDisplay[2].SetDisplayName(12,"Standby");
		m_ocxDisplay[2].SetDisplayName(13,"X-axis Home");
		m_ocxDisplay[2].SetDisplayName(14,"Y-axis Home");
		m_ocxDisplay[2].SetDisplayName(15,"C-axis Home");
		if (g_stu_pAxisA->sSpare==0 || g_stu_pAxisA->sSpare==2)//位置方式\串口
			m_ocxDisplay[2].SetDisplayName(16,"W-axis Home");
		else
			m_ocxDisplay[2].SetDisplayName(16,"Server Alarm");
		
		m_ocxDisplay[3].SetDisplayName(1,"X Positive Limit");
		m_ocxDisplay[3].SetDisplayName(2,"Y Positive Limit");
		m_ocxDisplay[3].SetDisplayName(3,"C Positive Limit");
		m_ocxDisplay[3].SetDisplayName(4,"W Positive Limit");
		m_ocxDisplay[3].SetDisplayName(5,"X Negative Limit");
		m_ocxDisplay[3].SetDisplayName(6,"Y Negative Limit");
		m_ocxDisplay[3].SetDisplayName(7,"C Negative Limit");
		m_ocxDisplay[3].SetDisplayName(8,"W Negative Limit");
		m_ocxDisplay[3].SetDisplayName(9,"System Use");
		m_ocxDisplay[3].SetDisplayName(10,"System Use");
		m_ocxDisplay[3].SetDisplayName(11,"System Use");
		m_ocxDisplay[3].SetDisplayName(12,"System Use");
		m_ocxDisplay[3].SetDisplayName(13,"X-axis Alarm");
		m_ocxDisplay[3].SetDisplayName(14,"Y-axis Alarm");
		m_ocxDisplay[3].SetDisplayName(15,"C-axis Alarm");
		m_ocxDisplay[3].SetDisplayName(16,"Photoelectric Sensor Input");
	}
}

void CDlg_MachineCase::OnButtonCs10() 
{
	CDialog::OnOK();
}

void CDlg_MachineCase::OnButton1() /* 输入点 */
{
	CBenderDlg	*pdlg;
	pdlg = (CBenderDlg*)FindWindow(NULL, "PNC2000GC");

	
	for(int i=0;i<8;i++)
	{
		nData[i] = 255 - pdlg->nNewInput[i];/* 灯的状态取反 */
	}
	m_lstAlarm.ShowWindow(FALSE);
	for(int index=0; index<=IDC_DISPLAY4-IDC_DISPLAY1; index++)
	{
		m_ocxDisplay[index].ShowWindow(TRUE);
	}
	OnFirstInput();
	OnButton2();

}

void CDlg_MachineCase::OnButton2() /* 输出点 */
{
	CBenderDlg	*pdlg;
	pdlg = (CBenderDlg*)FindWindow(NULL, "PNC2000GC");

	
	nData[0] = pdlg->nNewOutput[0];
	nData[1] = pdlg->nNewOutput[1];
	nData[2] = 0;
	OnReceiveOut(0, nData[0], nOutput);
	OnReceiveOut(16, nData[1], nOutput);
	OnDisplayOutput();	
	m_ocxDisplay[0].SetFocus();
}

void CDlg_MachineCase::OnButton3() /* 当前报警 */
{
	CRect	rc;
	rc = CRect(10, 40, 788, 533);
	rc = OnReSetRectV(rc);
	m_lstAlarm.MoveWindow(rc.left, rc.top, (rc.right-rc.left), (rc.bottom-rc.top), TRUE);
	m_lstAlarm.ShowWindow(TRUE);
	for(int index=0; index<=IDC_DISPLAY4-IDC_DISPLAY1; index++)
	{
		m_ocxDisplay[index].ShowWindow(FALSE);
	}
	OnInitAlarmList(TRUE);
}

void CDlg_MachineCase::OnButton4() /* 历史报警 */
{
	CRect	rc;
	rc = CRect(10, 40, 788, 533);
	rc = OnReSetRectV(rc);
	m_lstAlarm.MoveWindow(rc.left, rc.top, (rc.right-rc.left), (rc.bottom-rc.top), TRUE);
	m_lstAlarm.ShowWindow(TRUE);
	for(int index=0; index<=IDC_DISPLAY4-IDC_DISPLAY1; index++)
	{
		m_ocxDisplay[index].ShowWindow(FALSE);
	}
	OnInitAlarmList(FALSE);
}

LRESULT CDlg_MachineCase::OnStateInput(WPARAM wParam, LPARAM lParam) 
{
	OnReceiveIn((int)(wParam), (int)(lParam));
	OnDisplayInput();
	return 0;
}

LRESULT CDlg_MachineCase::OnStateOutput(WPARAM wParam, LPARAM lParam) 
{
	OnReceiveOut((int)(wParam), (int)(lParam), nOutput);
	OnDisplayOutput();		
	return 0;
}

void CDlg_MachineCase::OnFirstInput() /* 输入点 */
{
	int		nGetIn[16];
	int		i;
	long	lDisplay;
	CString	str;
	str.Empty();
	
	for(i=0;i<8;i++)
	{
		nGetIn[i] = OnGetBinaryInt(i+1, nData[3]);		
		nInput[i] = nGetIn[i];		
	}
	lDisplay = 0;
	for(i=0; i<7; i++)//扩展输出41-47		
	{
		lDisplay += (long)(pow(2,i)*nGetIn[i]);
	}	
	m_ocxDisplay[1].SetDisplayData(lDisplay);
	
	for(i=0;i<8;i++)
	{
		nGetIn[i] = OnGetBinaryInt(i+1, nData[4]);
		nGetIn[8+i] = OnGetBinaryInt(i+1, nData[5]);
		nInput[32+i] = nGetIn[i];
		nInput[40+i] = nGetIn[8+i];
	}
	lDisplay = 0;
	for(i=0; i<4; i++)		
	{
		lDisplay += (long)(pow(2,i)*nGetIn[i]);
	}
	for(i=12; i<16; i++)		
	{
		lDisplay += (long)(pow(2,i)*nGetIn[i]);
	}
	m_ocxDisplay[2].SetDisplayData(lDisplay);
	
	for(i=0;i<8;i++)
	{
		nGetIn[i] = OnGetBinaryInt(i+1, nData[6]);
		nGetIn[8+i] = OnGetBinaryInt(i+1, nData[7]);
		nInput[48+i] = nGetIn[i];
		nInput[56+i] = nGetIn[8+i];
	}
	lDisplay = 0;
	for(i=0; i<16; i++)	
	{
		lDisplay += (long)(pow(2,i)*nGetIn[i]);
	}
	m_ocxDisplay[3].SetDisplayData(lDisplay);
}

void CDlg_MachineCase::OnReceiveOut(int base, long nValue, int nGetOut[48])
{
	CString		strP;
	int		i,nPosition;
	char	chP[20];
	if(nValue<0||nValue>65535)
		return;
	nPosition = nValue;
	itoa(nPosition + 65536, chP, 2);
	for(i=1;i<17;i++)
	{
		if(chP[i]=='1')
			nGetOut[base + 16 - i] = 1;
		else
			nGetOut[base + 16 - i] = 0;
	}
}

void CDlg_MachineCase::OnReceiveIn(int nBase, int nNum)
{
	CString		strP;
	int		i;
	int		nIndex;
	char	chP[10];
	if(nNum<0||nNum>255)
		return;
	itoa(nNum + 256, chP, 2);
	switch(nBase) 
	{
	case 40:	
		nIndex = 8;
		break;
	case 48:
		nIndex = 16;
		break;
	case 56:
		nIndex = 40;
		break;
	case  12:   //伺服报警回零
		nIndex = 48;
		break;
	case IN_SERVOX_LIMIT - 1:
		nIndex = 56;
		break;
	case 0:		/* 改为通用输入点1-8 */
		nIndex = 64;
		break;
	default:
		return;
		break;
	}
	for(i=1;i<9;i++)
	{
		if(chP[i]=='1')
			nInput[nIndex-i] = 1;
		else
			nInput[nIndex-i] = 0;
	}
}

int CDlg_MachineCase::OnGetBinaryInt(int nByte, int nNum)
{
	CString		strP;
	char	chP[10];
	if(nNum<0||nNum>255)
		return 0;
	itoa(nNum + 256, chP, 2);
	if(chP[9-nByte]=='1')
		return 1;
	else
		return 0;
}

void CDlg_MachineCase::OnDisplayOutput() /* 输出点 */
{
	int		nGetIn[16];
	int		i;
	long	lDisplay;
	
	for(i=0;i<8;i++)
		nGetIn[i] = nOutput[i];
	for(i=8;i<14;i++)
		nGetIn[i] = nOutput[i+8];

	lDisplay = 0;
	for(i=0; i<14; i++)		lDisplay += (long)(pow(2,i)*nGetIn[i]);
	m_ocxDisplay[0].SetDisplayData(lDisplay);
}

void CDlg_MachineCase::OnDisplayInput() /* 输入点 */
{
	int		nGetIn[16];
	int		i;
	long	lDisplay;
	
	lDisplay = 0;
	for(i=0; i<7; i++)		
	{
		lDisplay += (long)(pow(2,i)*nInput[i]);
	}	
	m_ocxDisplay[1].SetDisplayData(lDisplay);
	
	for(i=0;i<16;i++)
		nGetIn[i] = nInput[32 + i];
	lDisplay = 0;
	for(i=0; i<4; i++)		
	{
		lDisplay += (long)(pow(2,i)*nGetIn[i]);
	}
	for(i=12; i<16; i++)		
	{
		lDisplay += (long)(pow(2,i)*nGetIn[i]);
	}
	m_ocxDisplay[2].SetDisplayData(lDisplay);
	
	for(i=0;i<16;i++)
		nGetIn[i] = nInput[48 + i];
	lDisplay = 0;
	for(i=0; i<16; i++)		
	{
		lDisplay += (long)(pow(2,i)*nGetIn[i]);
	}
	m_ocxDisplay[3].SetDisplayData(lDisplay);
}

BEGIN_EVENTSINK_MAP(CDlg_MachineCase, CDialog)
    //{{AFX_EVENTSINK_MAP(CDlg_MachineCase)
	ON_EVENT(CDlg_MachineCase, IDC_DISPLAY1, -601 /* DblClick */, OnDblClickDisplay1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CDlg_MachineCase::OnDblClickDisplay1() 
{
	int	nNumber=0;
	nNumber = m_ocxDisplay[0].GetDbClickNum();
	if(nNumber<9)
		g_handdll.SwitchOutput(nNumber);
	else
	{
		g_handdll.SwitchOutput(nNumber+8);
		if (nNumber == 9)
		{
            g_handdll.SwitchOutput(OUT_TRANSDUCER_SPEED);
		}
		if (nNumber == 10)
		{
            g_handdll.SwitchOutput(OUT_ZAXIS_DN);
		}	
	}
}

BOOL CDlg_MachineCase::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if( pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_UP)
	{
		switch(GetFocus()->GetDlgCtrlID()) 
		{
		case IDC_DISPLAY1:
			m_ocxDisplay[0].MovePrior();
			break;
		case IDC_DISPLAY2:
			m_ocxDisplay[1].MovePrior();
			break;
		case IDC_DISPLAY3:
			m_ocxDisplay[2].MovePrior();
			break;
		case IDC_DISPLAY4:
			m_ocxDisplay[3].MovePrior();
			break;
		default:
			break;
		}
		return TRUE;
	}
	else if( pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_DOWN)
	{
		switch(GetFocus()->GetDlgCtrlID()) 
		{
		case IDC_DISPLAY1:
			m_ocxDisplay[0].MoveNext();
			break;
		case IDC_DISPLAY2:
			m_ocxDisplay[1].MoveNext();
			break;
		case IDC_DISPLAY3:
			m_ocxDisplay[2].MoveNext();
			break;
		case IDC_DISPLAY4:
			m_ocxDisplay[3].MoveNext();
			break;
		default:
			break;
		}
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlg_MachineCase::OnLanguage()
{
	int		nIndex;
	nIndex = g_iLanguage + 1;

	for(int i=0;i<AR_STATE;i++)
	{
		if(g_arr_strState[i][nIndex]=="NULL")		g_arr_strState[i][nIndex] = "";
		SetDlgItemText(atoi(g_arr_strState[i][0]),g_arr_strState[i][nIndex]);
	}
}

CString CDlg_MachineCase::OnChangeLange(CString str) 
{
	if(!g_iLanguage)
	{
		if(strcmp(str, "Standby")==0)
			str = "备用";
	}
	else
	{
		if(strcmp(str, "备用")==0)
			str = "Standby";
	}
	return str;
}

void CDlg_MachineCase::InitButton()
{
	HRGN c;
	
	c = CreateRectRgn(0, 0, 0, 0);	
	GetBitMapRgn(GetDC(),c,IDB_BITMAP_ALARM1);
	//输入点	
	m_pButton[0].SetFont(&g_fontStatic);
	m_pButton[0].SetBitMapID(IDB_BITMAP_INPUT1,IDB_BITMAP_INPUT2);	
	m_pButton[0].Create(g_arr_strState[1][g_iLanguage+1], WS_CHILD | WS_VISIBLE, CPoint(30, 700), c, this, IDC_BUTTON_CS1); 
	//报警	
	m_pButton[1].SetFont(&g_fontEdit);
	m_pButton[1].SetBitMapID(IDB_BITMAP_ALARM1,IDB_BITMAP_ALARM2);	
	m_pButton[1].Create(g_arr_strState[2][g_iLanguage+1], WS_CHILD | WS_VISIBLE, CPoint(350, 700), c, this, IDC_BUTTON_CS3); 
	//历史报警	
	m_pButton[2].SetFont(&g_fontStatic);
	m_pButton[2].SetBitMapID(IDB_BITMAP_HISTORY1,IDB_BITMAP_HISTORY2);	
	m_pButton[2].Create(g_arr_strState[3][g_iLanguage+1], WS_CHILD | WS_VISIBLE, CPoint(655, 700), c, this, IDC_BUTTON_CS4); 
	//返回	
	m_pButton[3].SetFont(&g_fontEdit);
	m_pButton[3].SetBitMapID(IDB_BITMAP_BACK1,IDB_BITMAP_BACK2);	
	m_pButton[3].Create(g_arr_strState[4][g_iLanguage+1], WS_CHILD | WS_VISIBLE, CPoint(890, 700), c, this, IDC_BUTTON_CS10); 
    DeleteObject(c);

}

void CDlg_MachineCase::OnPaint() 
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
