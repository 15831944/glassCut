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
	double           gl_x;          /* X方向数据 */
	double           gl_y;          /* Y方向数据 */
	int				 glColor;
	bool             bDraw;          //true为画箭头。在抬刀的时候画箭头。
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
	DOUBLEPOINT m_dpGlassPos;//玻璃的偏移
	double      m_dGlassAngle;//玻璃的旋转
	TRACK       Track;          /* 跟踪数据结构       */
	PTRACK      pcurrTrack;     /* 跟踪数据结构的指针 */
	PTRACK      pTrack;         /* 跟踪数据结构的指针 */
	PTRACK      pcurrGreen;     /* 跟踪数据结构的指针 */
	PTRACK      pGreen;         /* 跟踪数据结构的指针 */
    long        m_lPosPreX;     //X上一次保存的坐标
    long        m_lPosPreY;     //Y上一次保存的坐标
    long        m_lPosPreZ;     //Z上一次保存的坐标
// Implementation
public:
    int  m_nShowShelf;    //是否显示货架号1显示；0显示厂名
	double      m_dZoom;					//放大比例
	double		m_dBaseX, m_dBaseY;		//图形显示的基坐标，用于平移
	virtual ~C2DDraw();
	BOOL Create(CWnd *pParentWnd, CRect rect);

	void CalGreen(); //把图形的结构转换为画图的结构数据

	bool DrawTail();//记录跟踪轨迹
	void RestoreDisplay();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void ZoomOut();
	void ZoomIn();
	
	void FreeBlocks();		//释放块
	void FreeGreens();  //更换工件时，将所照过的部分全都删节
	void DrawTrack();		//显示跟踪的图形
	void DrawGreen();		//显示打开的图形	
	void ErasureTracks();//擦除跟踪轨迹

	//设置全屏显示的比例
	void SetMaxShow(double dScale);

	void SetAdditionInf(pShowInf pinf);     //写入原边信息

	void FreeExtraShow();
    void AddExtraShowData();    //复制当前显示在主界面的图形数据结构，用于在扩展时显示，保存在g_ExtraShow里

	void SaveFileOpenGreen();//保存打开文件后的加工图形。不保存光电定位后的。
	
protected:
	double m_dFullScreenZoom;//根据图形大小显示最大化的图形的放大比例
	double m_dFullBaseX,m_dFullBaseY;//根据图形大小显示最大化的图形的移动值
	pShowInf      m_pShowAddtion;  //需要显示的原边信息
	TRACK       Green;          /* 画图的数据结构       */
	TRACK       GreenFileOpen;  //保存打开文件后的加工图形
	void ShowAdditionInf(CDC* pDCMenu);    //显示原边信息。
	void DDrawRect(CDC* pDCMenu,int ox,int oy,int x,int y,int nFill=1);
	int DDrawTextOut(CDC* pDCMenu,int x,int y,const char* cstr,int nBig);
	void gltDrawArc(PTRACK pBe,PDMC pDmc,float interval);
	void DrawBottero();
	void FreeFileOpen();  //更换工件时，将保存打开文件后的加工图形全都删节

	//画箭头,在终点上画
	//pDC画图dc；起点终点
	void DrawArrowhead(CDC *pDC, CGrPoint &ptBgn, CGrPoint &ptEnd);	

	int m_nShelfFont;//画图时客户名称的大小
  
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
