// Dlg_affirm.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "Dlg_affirm.h"
#include "Dlg_AfxMessage.h"
#include "Dlg_KeyNumber.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_affirm dialog


CDlg_affirm::CDlg_affirm(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_affirm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_affirm)
	m_strInfo = _T("");
	//}}AFX_DATA_INIT
}


void CDlg_affirm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_affirm)
	DDX_Text(pDX, IDC_STATIC_INFO, m_strInfo);
	DDX_Control(pDX, IDC_LAMP_LIGHT, m_ocxDisplay);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_affirm, CDialog)
	//{{AFX_MSG_MAP(CDlg_affirm)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_affirm message handlers

BOOL CDlg_affirm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	if (g_nTestRun == 1)
	{
		SetWindowPos(&CWnd::wndTopMost,722,365,294,110,SWP_SHOWWINDOW);
    }
	else
	{
		SetWindowPos(CWnd::GetOwner(),722,365,294,110,SWP_SHOWWINDOW);
	}
	DWORD crBK = BACKCOLOR;
	CString		szStr;
	
	OnLanguage();


	// TODO: Add extra initialization here
	m_ocxDisplay.SetBackColor(crBK);
	if(g_stu_pAxisG->sSpare==0 || g_stu_pAxisG->sSpare==2)
	{
		m_lCoorX1 = g_stu_pAxisA->lSpare;
		m_lCoorX2 = g_stu_pAxisB->lSpare;
		m_lCoorY = g_stu_pAxisC->lSpare;
	}
	else if(g_stu_pAxisG->sSpare==1 || g_stu_pAxisG->sSpare==3)/*纵向寻两点*/
	{
		m_lCoorX1 = g_stu_pAxisD->lSpare;
		m_lCoorX2 = g_stu_pAxisE->lSpare;
		m_lCoorY = g_stu_pAxisF->lSpare;
	}
	pCoor.x = pCoor.y = 0;
	dSlantingAngle = 0;
	/* 只有公制数据进入 */
	dHeight = m_dHeight;
	dLength = m_dLength;
	SetTimer(2,50,NULL);
	Sleep(50);
	OnBeginFind();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg_affirm::OnLanguage()
{
	int   i;
	int		nIndex;
	nIndex = g_iLanguage + 1;
	
	for(i=0;i<AR_LIGHTPOS;i++)
	{
		if(g_arr_lightpos[i][nIndex]=="NULL")		g_arr_lightpos[i][nIndex] = "";
		SetDlgItemText(atoi(g_arr_lightpos[i][0]),g_arr_lightpos[i][nIndex]);
	}
}

void CDlg_affirm::OnEndFind() /* 停止寻边 */
{
	KillTimer(1);
	g_Controller.Command("ST;STXY;STS;CSS");
	m_strInfo = "定位失败，请检查玻璃是否放置!";
	UpdateData(false);
	OnShowMessageBox(9,g_iLanguage,FALSE);
	pCoorx.x = 0;		pCoorx.y = 1;
	pCoor.x = 0;		pCoor.y = 0;
	pCoory.x = 1;		pCoory.y = 0;
	if (this->GetSafeHwnd()!=0)
	{
        CDialog::DestroyWindow();	
	}	
}

POINT2D CDlg_affirm::OnCalcPoint(POINT2D p1,POINT2D p2,POINT2D p3) /* 计算点垂直于直线的交点 */
{
	CString		strCmd;
	POINT2D		p;
	
	p.x = p.y = 0;

	if(p2.x == p1.x && p2.y == p1.y)
	{
		OnShowMessageBox(10,g_iLanguage,FALSE);
		return p;
	}
	else if(p2.x == p1.x)
	{
		p.x = p1.x;
		p.y = p3.y;
	}
	else if(p2.y == p1.y)
	{
		p.x = p3.x;
		p.y = p1.y;
	}
	else
	{
		double		k0;
		k0 = (p2.y - p1.y)/(p2.x - p1.x);
		/* (p3.x-p.x)/(p3.y-p.y) = -k0 关键算法*/
		p.y = (k0*k0*p3.y+p2.y-k0*(p2.x-p3.x))/(k0*k0+1);
		p.x = p3.x+k0*(p3.y-p.y);
	}
//  strCmd.Format("( %.2f, %.2f)",p.x/g_stu_pAxisA->d_pulse_user,p.y/g_stu_pAxisA->d_pulse_user);
	return p;
}

void CDlg_affirm::OnBeginFind() 
{
	/* 光电定位前检查 */
	UpdateData(TRUE);
	dHeight = m_dHeight;
	dLength = m_dLength;
	if(dHeight<10||dLength<10)
	{
		OnShowMessageBox(11,g_iLanguage,TRUE);
		return;
	}
	memset(&p1,'\0',sizeof(POINT2D));
	memset(&p2,'\0',sizeof(POINT2D));
	memset(&p3,'\0',sizeof(POINT2D));
	/* 光电定位前检查 */
	m_strInfo = "正在寻边... ...";
	UpdateData(false);
	
	CString		strCmd;
	CString  	strtmp[12] = {"nx1=","ny1=","nx2=","ny2=","nx3=","ny3=","sx=","sy=","spx=","spy=","nx0=","ny0="};
	CPoint		pos[6];
	int         i = 0;
	CString     filename=g_strOriginalPathC+"light.dmc";	
    if(g_stu_pAxisG->sSpare==2 || g_stu_pAxisG->sSpare==0)//x轴反向两点
	{
		//巡边第一点
		pos[0].x = (long)((dLength*(double)m_lCoorX1/100.0 - g_stu_pAxisA->dSpareE) * g_stu_pAxisB->d_pulse_user);
		pos[0].y = (long)((g_stu_pAxisH->lSpare-g_stu_pAxisB->dSpareE) * g_stu_pAxisA->d_pulse_user);
        
		//巡边第二点
		pos[1].x = (long)((dLength*(double)m_lCoorX2/100.0 - g_stu_pAxisA->dSpareE) * g_stu_pAxisB->d_pulse_user);
		pos[1].y = (long)((g_stu_pAxisH->lSpare-g_stu_pAxisB->dSpareE) * g_stu_pAxisA->d_pulse_user);

		//巡边第三点
		pos[2].x = (long)((g_stu_pAxisG->lSpare-g_stu_pAxisA->dSpareE) * g_stu_pAxisA->d_pulse_user);
		pos[2].y = (long)((dHeight*(double)m_lCoorY/100.0 - g_stu_pAxisB->dSpareE) * g_stu_pAxisB->d_pulse_user);
		
		//迎玻璃点
		pos[5].x = (long)((g_stu_pAxisG->lSpare-g_stu_pAxisA->dSpareE) * g_stu_pAxisA->d_pulse_user);
		pos[5].y = (long)((g_stu_pAxisH->lSpare-g_stu_pAxisB->dSpareE) * g_stu_pAxisA->d_pulse_user);
		if(g_stu_pAxisG->sSpare==2)
			filename=g_strOriginalPathC+"Rlight.dmc";
		else
			filename=g_strOriginalPathC+"light.dmc";
	}
	else if(g_stu_pAxisG->sSpare==3 || g_stu_pAxisG->sSpare==1)
	{
		pos[0].x = (long)((g_stu_pAxisG->lSpare-g_stu_pAxisA->dSpareE) * g_stu_pAxisA->d_pulse_user);
		pos[0].y = (long)((dHeight*m_lCoorX1/100 - g_stu_pAxisB->dSpareE) * g_stu_pAxisB->d_pulse_user);
		
		pos[1].x = (long)((g_stu_pAxisG->lSpare-g_stu_pAxisA->dSpareE) * g_stu_pAxisA->d_pulse_user);
		pos[1].y = (long)((dHeight*m_lCoorX2/100 - g_stu_pAxisB->dSpareE) * g_stu_pAxisB->d_pulse_user);
		
		pos[2].x = (long)((dLength*m_lCoorY/100 - g_stu_pAxisA->dSpareE) * g_stu_pAxisB->d_pulse_user);
		pos[2].y = (long)((g_stu_pAxisH->lSpare-g_stu_pAxisB->dSpareE) * g_stu_pAxisA->d_pulse_user);
		
		pos[5].x = (long)((g_stu_pAxisG->lSpare-g_stu_pAxisA->dSpareE) * g_stu_pAxisA->d_pulse_user);
		pos[5].y = (long)((g_stu_pAxisH->lSpare-g_stu_pAxisB->dSpareE) * g_stu_pAxisA->d_pulse_user);
		if(g_stu_pAxisG->sSpare==2)
			filename=g_strOriginalPathC+"Rlighty.dmc";
		else
            filename=g_strOriginalPathC+"lighty.dmc";
	}
	pos[3].x = (long)(g_stu_pAxisA->d_handspeed*g_stu_pAxisA->d_pulse_user/10);
	pos[3].y = (long)(g_stu_pAxisB->d_handspeed*g_stu_pAxisB->d_pulse_user/10);
	pos[4].x = (long)(g_stu_pAxisA->d_handspeed*g_stu_pAxisA->d_pulse_user);//手动速度当巡边的定位速度
	pos[4].y = (long)(g_stu_pAxisB->d_handspeed*g_stu_pAxisB->d_pulse_user);
	char szCmd[80] = {0};
	LONG l_Rec=0;
	for(i=0;i<6;i++)
	{
		strCmd.Format("%d",pos[i].x);
		strcpy(szCmd,LPCTSTR(strtmp[2*i] + strCmd));
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
		strCmd.Format("%d",pos[i].y);
		strcpy(szCmd,LPCTSTR(strtmp[2*i+1] + strCmd));
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
		Sleep(20);
	}
	g_Controller.Command("ST");
	g_Controller.Command("run=1");
	SetTimer(1,500,NULL);
	if (g_nTestRun == 1)
	{
		filename=g_strOriginalPathC+"RlightTest.dmc";
	}
	char szDmc[80]={0};
	strcpy(szDmc,filename);
    LONG lRc = 0;
	lRc = g_Controller.DownloadFile(szDmc);
	if (lRc != 0)
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
	g_Controller.Command("ST;WT20;XQ#LIGHT");	
}

CPoint CDlg_affirm::SetGlassPointPos(CPoint p) 
{
	CPoint  ptmp;
	double	dTmpAngle,dLength;
	ptmp.x = 0;
	ptmp.y = 0;
	dTmpAngle = PointToPointAngle(ptmp.x,ptmp.y, p.x,p.y);
	dTmpAngle = dTmpAngle + dSlantingAngle;
	dLength = sqrt(p.x * p.x + p.y * p.y);
	ptmp.x = (long)( dLength * cos(dTmpAngle * 3.141593 / 180) + pCoor.x / lScale * g_dScale.x );
	ptmp.y = (long)( dLength * sin(dTmpAngle * 3.141593 / 180) + pCoor.y / lScale * g_dScale.y );
	return ptmp;
}

void CDlg_affirm::OnButtonTimer() 
{
	CString	strCmd;
	Sleep(50);
	char l_szRes[80]={0};
	g_Controller.Command("MG_XQ",l_szRes,sizeof(l_szRes));
	while (atoi(l_szRes)>=0) 
	{
		Sleep(20);
		g_Controller.Command("MG_XQ",l_szRes,sizeof(l_szRes));
	}
	p1.x = g_handdll.GetCommandFloat((char *)((const char*)"posx1=")) + g_stu_pAxisA->dSpareE * g_stu_pAxisA->d_pulse_user;
	p1.y = g_handdll.GetCommandFloat((char *)((const char*)"posy1=")) + g_stu_pAxisB->dSpareE * g_stu_pAxisB->d_pulse_user;
	p2.x = g_handdll.GetCommandFloat((char *)((const char*)"posx2=")) + g_stu_pAxisA->dSpareE * g_stu_pAxisA->d_pulse_user;
	p2.y = g_handdll.GetCommandFloat((char *)((const char*)"posy2=")) + g_stu_pAxisB->dSpareE * g_stu_pAxisB->d_pulse_user;
	p3.x = g_handdll.GetCommandFloat((char *)((const char*)"posx3=")) + g_stu_pAxisA->dSpareE * g_stu_pAxisA->d_pulse_user;
	p3.y = g_handdll.GetCommandFloat((char *)((const char*)"posy3=")) + g_stu_pAxisB->dSpareE * g_stu_pAxisB->d_pulse_user;
	
	pCoor = OnCalcPoint(p1,p2,p3);

	if(g_stu_pAxisG->sSpare==0 || g_stu_pAxisG->sSpare==2)
	{
		dSlantingAngle = PointToPointAngle(pCoor.x,pCoor.y,p2.x,p2.y);
	}
	else if(g_stu_pAxisG->sSpare==1 || g_stu_pAxisG->sSpare==3)/*纵向寻两点*/
	{
		dSlantingAngle = PointToPointAngle(pCoor.x,pCoor.y,p3.x,p3.y);
	}
	if(g_stu_pAxisH->sSpare==0)	/* 公制 */	
		strCmd.Format("寻边完成  原点: (%.2f,%.2f),倾斜角度: %.2f",pCoor.x/g_stu_pAxisA->d_pulse_user,pCoor.y/g_stu_pAxisB->d_pulse_user,dSlantingAngle);
	else
		strCmd.Format("寻边完成  原点: (%.2f,%.2f),倾斜角度: %.2f",pCoor.x/g_stu_pAxisA->d_pulse_user * MM_TO_IN,pCoor.y/g_stu_pAxisB->d_pulse_user * MM_TO_IN,dSlantingAngle);
	
	m_strInfo = strCmd;
	UpdateData(false);

	pCoor.x = pCoor.x / g_stu_pAxisA->d_pulse_user;		pCoor.y = pCoor.y / g_stu_pAxisB->d_pulse_user;
	if(g_stu_pAxisG->sSpare==0 || g_stu_pAxisG->sSpare==2)
	{
		pCoorx.x = p3.x / g_stu_pAxisA->d_pulse_user;		pCoorx.y = p3.y / g_stu_pAxisA->d_pulse_user;
		pCoory.x = p1.x / g_stu_pAxisA->d_pulse_user;		pCoory.y = p1.y / g_stu_pAxisA->d_pulse_user;
	}
	else if(g_stu_pAxisG->sSpare==1 || g_stu_pAxisG->sSpare==3)/*纵向寻两点*/
	{
		pCoorx.x = p1.x / g_stu_pAxisA->d_pulse_user;		pCoorx.y = p1.y / g_stu_pAxisA->d_pulse_user;
		pCoory.x = p3.x / g_stu_pAxisA->d_pulse_user;		pCoory.y = p3.y / g_stu_pAxisA->d_pulse_user;
	}
//*****************************************************************************
	FILE*          fileDMC;
	if (fileDMC = fopen("D:\\Point.txt", "wt"))
	{
		fprintf(fileDMC, "PX %.4f,%.4f\n", p3.x,p3.y);
		fprintf(fileDMC, "PY1 %.4f,%.4f\n", p1.x,p1.y);
		fprintf(fileDMC, "PY2 %.4f,%.4f\n", p2.x,p2.y);
		fprintf(fileDMC, "PCOOR %.4f,%.4f\n", pCoor.x,pCoor.y);
		fprintf(fileDMC, "ANGLE %.4f\n", dSlantingAngle);
		fclose(fileDMC);
	}
	
//*****************************************************************************	
	
	int nRun = g_handdll.GetCommandInt((char *)((const char*)"run="));
	if(g_nTestRun != 1)
	{
		GetParent()->SendMessage(WM_AFFIRM, 0, nRun); 
	}
	Sleep(50);
	if (this->GetSafeHwnd()!=0)
	{
        CDialog::DestroyWindow();	
	}
}

void CDlg_affirm::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent==1)
	{
		char szRes[80];
		g_Controller.Command("MG_XQ",szRes,sizeof(szRes));
		if (atoi(szRes)<0) 
		{
			KillTimer(1);
			OnButtonTimer();
		}
	}
	else if(nIDEvent==2)
	{
		lDisplay = g_handdll.GetIn(IN_LIGHT);
		m_ocxDisplay.SetRgby(lDisplay);
	}
	CDialog::OnTimer(nIDEvent);
}
