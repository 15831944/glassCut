#if !defined(AFX_2DDRAW_H__9A6D3A11_0BAF_4516_9F92_438E639017B9__INCLUDED_)
#define AFX_2DDRAW_H__9A6D3A11_0BAF_4516_9F92_438E639017B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 2DDraw.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// C2DDraw window
struct tagTRACK
{
	double           gl_x;          /* X�������� */
	double           gl_y;          /* Y�������� */
	int				 glColor;
	bool             bDraw;          //trueΪ����ͷ����̧����ʱ�򻭼�ͷ��
	struct  tagTRACK  *Next;         /* Next block */
	struct  tagTRACK  *Prev;         /* Previous block */
}; 
typedef struct tagTRACK TRACK, *PTRACK;

class C2DDraw : public CWnd
{
// Construction
public:
	C2DDraw();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C2DDraw)
	//}}AFX_VIRTUAL
protected:
	DOUBLEPOINT m_dpGlassPos;//������ƫ��
	double      m_dGlassAngle;//��������ת
	TRACK       Track;          /* �������ݽṹ       */
	PTRACK      pcurrTrack;     /* �������ݽṹ��ָ�� */
	PTRACK      pTrack;         /* �������ݽṹ��ָ�� */
	PTRACK      pcurrGreen;     /* �������ݽṹ��ָ�� */
	PTRACK      pGreen;         /* �������ݽṹ��ָ�� */
    long        m_lPosPreX;     //X��һ�α��������
    long        m_lPosPreY;     //Y��һ�α��������
    long        m_lPosPreZ;     //Z��һ�α��������
// Implementation
public:
    int  m_nShowShelf;    //�Ƿ���ʾ���ܺ�1��ʾ��0��ʾ����
	double      m_dZoom;					//�Ŵ����
	double		m_dBaseX, m_dBaseY;		//ͼ����ʾ�Ļ����꣬����ƽ��
	virtual ~C2DDraw();
	BOOL Create(CWnd *pParentWnd, CRect rect);

	void CalGreen(); //��ͼ�εĽṹת��Ϊ��ͼ�Ľṹ����

	bool DrawTail();//��¼���ٹ켣
	void RestoreDisplay();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void ZoomOut();
	void ZoomIn();
	
	void FreeBlocks();		//�ͷſ�
	void FreeGreens();  //��������ʱ�������չ��Ĳ���ȫ��ɾ��
	void DrawTrack();		//��ʾ���ٵ�ͼ��
	void DrawGreen();		//��ʾ�򿪵�ͼ��	
	void ErasureTracks();//�������ٹ켣

	//����ȫ����ʾ�ı���
	void SetMaxShow(double dScale);

	void SetAdditionInf(pShowInf pinf);     //д��ԭ����Ϣ

	void FreeExtraShow();
    void AddExtraShowData();    //���Ƶ�ǰ��ʾ���������ͼ�����ݽṹ����������չʱ��ʾ��������g_ExtraShow��

	void SaveFileOpenGreen();//������ļ���ļӹ�ͼ�Ρ��������綨λ��ġ�
	
protected:
	double m_dFullScreenZoom;//����ͼ�δ�С��ʾ��󻯵�ͼ�εķŴ����
	double m_dFullBaseX,m_dFullBaseY;//����ͼ�δ�С��ʾ��󻯵�ͼ�ε��ƶ�ֵ
	pShowInf      m_pShowAddtion;  //��Ҫ��ʾ��ԭ����Ϣ
	TRACK       Green;          /* ��ͼ�����ݽṹ       */
	TRACK       GreenFileOpen;  //������ļ���ļӹ�ͼ��
	void ShowAdditionInf(CDC* pDCMenu);    //��ʾԭ����Ϣ��
	void DDrawRect(CDC* pDCMenu,int ox,int oy,int x,int y,int nFill=1);
	int DDrawTextOut(CDC* pDCMenu,int x,int y,const char* cstr,int nBig);
	void gltDrawArc(PTRACK pBe,PDMC pDmc,float interval);
	void DrawBottero();
	void FreeFileOpen();  //��������ʱ����������ļ���ļӹ�ͼ��ȫ��ɾ��

	//����ͷ,���յ��ϻ�
	//pDC��ͼdc������յ�
	void DrawArrowhead(CDC *pDC, CGrPoint &ptBgn, CGrPoint &ptEnd);	

	int m_nShelfFont;//��ͼʱ�ͻ����ƵĴ�С
  
	//{{AFX_MSG(C2DDraw)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_2DDRAW_H__9A6D3A11_0BAF_4516_9F92_438E639017B9__INCLUDED_)
