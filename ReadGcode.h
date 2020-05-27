// ReadGcode.h: interface for the CReadGcode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_READGCODE_H__9C8FC065_A2BE_4E28_AB1F_D66A790D8AC7__INCLUDED_)
#define AFX_READGCODE_H__9C8FC065_A2BE_4E28_AB1F_D66A790D8AC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <vector>
struct tagLine  //�߶�
{
	POINT2D bg;
	POINT2D en;
};	
struct tagArc  //Բ��
{
	bool bDirect;//����0˳ʱ�룻1:��ʱ��
	POINT2D bg; //���
	POINT2D en; //�յ�
	POINT2D o; //Բ��
	double  r; //�뾶
	float  fStart;//��ʼ�Ƕ�
	float  fEnd;  //ĩ�Ƕ�
	float  fSweep;//�ƹ��Ƕ�
};
struct tagGcode //���߶�
{
	bool     bLineOrArc; //ֵΪTRUE��ʾ�ý��洢�߶���Ϣ,FALSE�洢Բ����Ϣ
	tagLine  line; //�߶�
	tagArc   arc; //Բ��	
};
struct G_Code  //G����ÿ�е���Ϣ
{
	bool     bDraw;//�ǻ�����Ϣ
	bool     bG00;//��λΪtrue
	CString  strGCode;//G����Բ��	
	tagGcode stuData;//�������ͼ����Ϣ
};
class CReadGcode  
{
public:
	CReadGcode();
	virtual ~CReadGcode();
	//������Ҫ������G�����Ŀ¼
	//strFileĿ¼����
	//����0�ɹ�
	int SetGFile(CString strFile);
private:
	
	G_Code  m_Gcode; // һ��G������Ϣ m_vecGCodeһ���ڵ�
    POINT2D m_PointEnd;//��¼�յ�����


	//����G,����������������
	//strGcode : G������
	void AnalyzeGCode(CString strGcode);	

	//�ų�СƬ��Ϣ
	//str:G������
	//G������Ϣ����false;СƬ��Ϣtrue
	bool RemoveOriginal(CString str);

	//ȷ��ͼ�εĳߴ磬m_rct
	void SetRange(double fx, double fy);

	//ȷ��ͼ�εĳߴ磬m_rct
	void GetCRRange(tagArc arc);

	//����Բ��
	//strArc:GԲ���ַ���bDirect:����0˳ʱ�룻1:��ʱ��
    void AnalyzeArc(CString strArc,bool bDirect);

	//��ʼ��m_Gcode����Ϣ
	void InitGcodeStu();
public:
	std::vector<G_Code> m_vecGCode;//G����
	int m_nVecSize;//�����Ĵ�С
	CRect m_rct;    //ͼ�εķ�Χ

};

#endif // !defined(AFX_READGCODE_H__9C8FC065_A2BE_4E28_AB1F_D66A790D8AC7__INCLUDED_)
