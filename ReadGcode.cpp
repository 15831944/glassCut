// ReadGcode.cpp: implementation of the CReadGcode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bender.h"
#include "ReadGcode.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReadGcode::CReadGcode()
{
    m_nVecSize  = 0;
	m_vecGCode.clear();
	m_rct.SetRect(0,0,0,0);
	InitGcodeStu();		
}

CReadGcode::~CReadGcode()
{
	if (!m_vecGCode.empty())
		m_vecGCode.clear();
	m_nVecSize = 0;
}
//初始化m_Gcode的信息
void CReadGcode::InitGcodeStu()
{
	m_Gcode.bDraw = false;
	m_Gcode.bG00 = false;
	m_Gcode.strGCode = "";
	m_Gcode.stuData.arc.bDirect = false;
	m_Gcode.stuData.arc.bg.x = 0.0;
	m_Gcode.stuData.arc.bg.y = 0.0;
	m_Gcode.stuData.arc.en.x = 0.0;
	m_Gcode.stuData.arc.en.y = 0.0;
	m_Gcode.stuData.arc.o.x = 0.0;
	m_Gcode.stuData.arc.o.y = 0.0;
	m_Gcode.stuData.arc.r = 0.0;
	m_Gcode.stuData.arc.fStart = 0.0f;
	m_Gcode.stuData.arc.fSweep = 0.0f;
	m_Gcode.stuData.bLineOrArc = false;
	m_Gcode.stuData.line.bg.x = 0.0;
	m_Gcode.stuData.line.bg.y = 0.0;
	m_Gcode.stuData.line.en.x = 0.0;
	m_Gcode.stuData.line.en.y = 0.0;
}
//设置需要解析的G代码的目录
//strFile目录内容
//返回0成功
int CReadGcode::SetGFile(CString strFile)
{
	CStdioFile file;
	if (strFile == "")		return 1;	
	if (!m_vecGCode.empty())
		m_vecGCode.clear();
	m_nVecSize = 0;
	m_rct.SetRect(0,0,0,0);
	m_PointEnd.x = 0.0;
	m_PointEnd.y = 0.0;
	if (!file.Open( strFile, CFile::modeRead))
	{
		return 1;
	}
	CString strIn;
	while (file.ReadString(strIn))//按行读
	{	
		if (strIn.IsEmpty())
			continue;		
		if(true == RemoveOriginal(strIn))
			continue;
		InitGcodeStu();
		m_Gcode.strGCode = strIn;
		m_Gcode.strGCode.TrimLeft();
		m_Gcode.strGCode.TrimRight();
		m_Gcode.bDraw = false;		
		AnalyzeGCode(strIn);
		m_vecGCode.push_back(m_Gcode);
		m_nVecSize ++;
	}
	file.Close();
	return 0;
}

//解析G,并存在容器链表中
//strGcode : G代码
void CReadGcode::AnalyzeGCode(CString strGcode)
{
	strGcode.Remove(' ');
    int nPos = strGcode.Find('G');
	if (nPos > -1)//G
	{
		int nG = atoi(strGcode.Mid(nPos + 1));
		if (nG == 0)//G00
		{
			m_Gcode.bDraw = true;
			m_Gcode.bG00 = true;
            m_PointEnd.x = atof(strGcode.Mid(strGcode.Find('X') +1));
            m_PointEnd.y = atof(strGcode.Mid(strGcode.Find('Y') +1));
			m_Gcode.stuData.line.en = m_PointEnd;
			SetRange(m_PointEnd.x,m_PointEnd.y);
		}
		else if (nG == 1)//G01
		{
			m_Gcode.bDraw = true;
			m_Gcode.bG00 = false;
			m_Gcode.stuData.bLineOrArc = true;
			m_Gcode.stuData.line.bg = m_PointEnd;
			m_PointEnd.x = atof(strGcode.Mid(strGcode.Find('X') +1));
            m_PointEnd.y = atof(strGcode.Mid(strGcode.Find('Y') +1));
			m_Gcode.stuData.line.en = m_PointEnd;
			SetRange(m_PointEnd.x,m_PointEnd.y);
		}
		else if (nG == 2)//G02
		{
            AnalyzeArc(strGcode,false);
		}
		else if (nG == 3)//G03
		{
            AnalyzeArc(strGcode,true);
		}
		return;
	}	
}

//排除小片信息
//str:G代码行
//G代码信息返回false;小片信息true
bool CReadGcode::RemoveOriginal(CString str)
{
	CString strP;
	for (int i=0; i<12; i++)
	{
		strP.Format("P%d",3000+i);
		if (str.Find(strP) != -1)
			return true;
	}
	if (str.Find("P4") != -1)
		return true;
	return false;
}

void CReadGcode::SetRange(double fx, double fy)
{
	if(fx<m_rct.left)       m_rct.left = (long)fx;
	if(fx>m_rct.right)      m_rct.right = (long)fx;
	if(fy<m_rct.bottom)     m_rct.bottom = (long)fy;
	if(fy>m_rct.top)        m_rct.top = (long)fy;
}

//解析圆弧
//strArc:G圆弧字符；bDirect:方向0顺时针；1:逆时针
void CReadGcode::AnalyzeArc(CString strArc,bool bDirect)
{
	m_Gcode.bDraw = true;
	m_Gcode.bG00 = false;
	m_Gcode.stuData.bLineOrArc = false;
	m_Gcode.stuData.arc.bDirect = bDirect;
	m_Gcode.stuData.arc.bg = m_PointEnd;
	m_PointEnd.x = atof(strArc.Mid(strArc.Find('X') +1));
	m_PointEnd.y = atof(strArc.Mid(strArc.Find('Y') +1));
	m_Gcode.stuData.arc.en = m_PointEnd;
	SetRange(m_PointEnd.x,m_PointEnd.y);
	
	POINT2D pointVec;//圆心相对于起点的位移
	pointVec.x = atof(strArc.Mid(strArc.Find('I') +1));
	pointVec.y = atof(strArc.Mid(strArc.Find('J') +1));
    m_Gcode.stuData.arc.o.x = m_Gcode.stuData.arc.bg.x + pointVec.x;
    m_Gcode.stuData.arc.o.y = m_Gcode.stuData.arc.bg.y + pointVec.y;
	m_Gcode.stuData.arc.r = _hypot(pointVec.x,pointVec.y);
	Point2D p1,p2,p3;//圆心，起点，终点
	p1.x = m_Gcode.stuData.arc.o.x;
	p1.y = m_Gcode.stuData.arc.o.y;
	p2.x = m_Gcode.stuData.arc.bg.x;
	p2.y = m_Gcode.stuData.arc.bg.y;
	p3.x = m_PointEnd.x;
	p3.y = m_PointEnd.y;				
	double dBeginAngle = g_Dmcgc.PointAngleTo(&p1,&p2);
	double dEndAngle = g_Dmcgc.PointAngleTo(&p1,&p3);
	double dSweepAngle = dEndAngle - dBeginAngle;
	if (m_Gcode.stuData.arc.bDirect)
	{
		if (dEndAngle < dBeginAngle)
			dSweepAngle += 360.0; 
	}
	else
	{  
		if (dEndAngle > dBeginAngle)
			dSweepAngle -= 360.0;
	}  
	if (fabs(dSweepAngle) < .000001)
	{
		if (m_Gcode.stuData.arc.bDirect)
			dSweepAngle = 360.0;
		else
			dSweepAngle = -360.0;
	}
	m_Gcode.stuData.arc.fStart = float(dBeginAngle);
	m_Gcode.stuData.arc.fEnd = float(dEndAngle);
	m_Gcode.stuData.arc.fSweep = float(dSweepAngle);
	GetCRRange(m_Gcode.stuData.arc);
}

//确定图形的尺寸，m_rct
void CReadGcode::GetCRRange(tagArc arc)
{
	if(!arc.bDirect)	//如果是顺时针
	{
		if(arc.fStart+arc.fSweep <= 0.0)								//如果经过零度
		{
			SetRange(arc.o.x+arc.r,arc.o.y);
		}
		if( (arc.fStart > 90.0 && arc.fStart+arc.fSweep < 90.0)
			|| arc.fStart+arc.fSweep <= -270.0)	//如果经过90度
		{
			SetRange(arc.o.x,arc.o.y+arc.r);
		}
		if( (arc.fStart > 180.0 && arc.fStart+arc.fSweep < 180.0)
			|| arc.fStart+arc.fSweep <= -180.0)//如果经过180度
		{
			SetRange(arc.o.x-arc.r,arc.o.y);
		}
		if( (arc.fStart > 270.0 && arc.fStart+arc.fSweep < 270.0)
			|| arc.fStart+arc.fSweep <= -90.0)//如果经过270度
		{
			SetRange(arc.o.x,arc.o.y-arc.r);
		}
	}
	else				//如果是逆时针
	{
		if(arc.fStart+arc.fSweep >= 360.0)								//如果经过零度
		{
			SetRange(arc.o.x+arc.r,arc.o.y);
		}
		if( (arc.fStart < 90.0 && arc.fStart+arc.fSweep> 90.0)
			|| arc.fStart+arc.fSweep >= 450.0)	//如果经过90度
		{
			SetRange(arc.o.x,arc.o.y+arc.r);
		}
		if( (arc.fStart < 180.0 && int(arc.fStart+arc.fSweep)%360 > 180.0)
			|| arc.fStart+arc.fSweep >= 540.0)//如果经过180度
		{
			SetRange(arc.o.x-arc.r,arc.o.y);
		}
		if( (arc.fStart < 270.0 && int(arc.fStart+arc.fSweep)%360 > 270.0)
			|| arc.fStart+arc.fSweep >= 630.0)//如果经过270度
		{
			SetRange(arc.o.x,arc.o.y-arc.r);
		}
	}
}