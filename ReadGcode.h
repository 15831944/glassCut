// ReadGcode.h: interface for the CReadGcode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_READGCODE_H__9C8FC065_A2BE_4E28_AB1F_D66A790D8AC7__INCLUDED_)
#define AFX_READGCODE_H__9C8FC065_A2BE_4E28_AB1F_D66A790D8AC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <vector>
struct tagLine  //线段
{
	POINT2D bg;
	POINT2D en;
};	
struct tagArc  //圆弧
{
	bool bDirect;//方向0顺时针；1:逆时针
	POINT2D bg; //起点
	POINT2D en; //终点
	POINT2D o; //圆心
	double  r; //半径
	float  fStart;//起始角度
	float  fEnd;  //末角度
	float  fSweep;//绕过角度
};
struct tagGcode //曲线段
{
	bool     bLineOrArc; //值为TRUE表示该结点存储线段信息,FALSE存储圆弧信息
	tagLine  line; //线段
	tagArc   arc; //圆弧	
};
struct G_Code  //G代码每行的信息
{
	bool     bDraw;//是画的信息
	bool     bG00;//定位为true
	CString  strGCode;//G代码圆形	
	tagGcode stuData;//解析后的图形信息
};
class CReadGcode  
{
public:
	CReadGcode();
	virtual ~CReadGcode();
	//设置需要解析的G代码的目录
	//strFile目录内容
	//返回0成功
	int SetGFile(CString strFile);
private:
	
	G_Code  m_Gcode; // 一行G代码信息 m_vecGCode一个节点
    POINT2D m_PointEnd;//记录终点坐标


	//解析G,并存在容器链表中
	//strGcode : G代码行
	void AnalyzeGCode(CString strGcode);	

	//排除小片信息
	//str:G代码行
	//G代码信息返回false;小片信息true
	bool RemoveOriginal(CString str);

	//确定图形的尺寸，m_rct
	void SetRange(double fx, double fy);

	//确定图形的尺寸，m_rct
	void GetCRRange(tagArc arc);

	//解析圆弧
	//strArc:G圆弧字符；bDirect:方向0顺时针；1:逆时针
    void AnalyzeArc(CString strArc,bool bDirect);

	//初始化m_Gcode的信息
	void InitGcodeStu();
public:
	std::vector<G_Code> m_vecGCode;//G容器
	int m_nVecSize;//容器的大小
	CRect m_rct;    //图形的范围

};

#endif // !defined(AFX_READGCODE_H__9C8FC065_A2BE_4E28_AB1F_D66A790D8AC7__INCLUDED_)
