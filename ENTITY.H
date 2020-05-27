#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "base.h"

#define PICK_RADIUS 0.01 // 选取半径

#define ENTITY_NUM	10 // 图元的种类数
enum EEntityType // 图元的类型
{
	etUnknow	= 0,
	etPoint		= 1,
	etLine		= 2,
	etRectangle = 3,
	etCircle	= 4,
	etArc		= 5,
	etBspline	= 6,
	etEllipse	= 7,
	etText		= 8,
	etPolyline	= 9
};

enum EDrawMode // 绘图模式
{
	dmNormal = 0, // 正常状态
	dmSelect = 1, // 选中状态	
	dmPrompt = 2, // 提示状态
	dmDrag   = 3, // 拖动状态
	dmInvalid = 4 // 擦除状态
};

//////////////////////////
// define API function
//
void	SetDrawEnvir(CDC*	pDC, int drawMode, CPen* pPen);

//计算根据圆弧信息圆心
void polylineToArc(Position& BeginPoint, Position& EndPoint, double u, Position& CenterPoint);

class CEntity : public CObject
{
	DECLARE_SERIAL(CEntity) 
public:
	// 成员变量
	int			m_type;		// 图元类型（EEntityType）改用为圆弧的方向G02 or G03
	int			m_acrDirect; // 用于多段线
	COLORREF	m_color ;   // 图元颜色
	UINT		m_lineStyle ; // 图元的线型
	int			m_lineWidth ; // 图元的线宽
	int         m_layer;      //图元的图层
	long        m_iIndex;//图元的句柄、序号,初始化时为负值-1，排序后是正值,表示输出的顺序	
//    BOOL		bPaiXu;    //是否已经排序
	BOOL		bPositive; //是否是正向，即不颠倒元素顺序
public:	
	virtual BOOL reverseElement(CObList* pEntityList, POSITION pos){return TRUE;}
	// 构造函数和析构函数
	CEntity() ;
	CEntity(const CEntity& entity);
	~CEntity() {}
	
	CEntity operator = (const CEntity& entity); // 重载等号
	virtual	CEntity*	Copy() { return NULL; } // 指针拷贝

	virtual	void	Init(); // 初始化成员变量值
	virtual	int		GetType() { return m_type; }  // 返回图元的类型（EEntityType）
	COLORREF		GetColor() { return m_color; } // 返回图元颜色
	void			SetColor(COLORREF color) { m_color = color; } // 设置图元颜色
    
	//add by hao 2004.6.7 由继承函数去处理
	virtual double		GetChordAngle(){ return 0.0; };
	virtual Position	GetBeginPos(){ return 0; }; 
	virtual Position	GetEndPos(){ return 0; };
	virtual Position	GetCenterPos(){ return 0; };
	virtual double	    GetStartAngle(){return 0;};
	virtual double	    GetEndAngle(){return 0;};
	virtual double 	    GetRadius(){return 0;};
	int                 GetLayer(){return m_layer;};
	virtual int        GetGrahStyle(){return 2;}; //2表示是直线
	virtual int			GetAcrDirect(){return m_acrDirect;};

	void				SetLayer(int layer){m_layer=layer;};

    virtual void	SetBeginPos(Position p){}; 
	virtual void	SetEndPos(Position p){};
	virtual void	SetCenterPos(Position p){};
	virtual void	SetStartAngle(float x){};
	virtual void	SetEndAngle(float x){};
	virtual void 	SetRadius(double x){};
    //add end by hao 2004.6.7

	virtual void Draw(CDC * pDC, int drawMode = dmNormal ) {}; // 绘制图元对象

	// 给定一点及拾取半径，判断图元是否被选中
	virtual BOOL Pick(const Position& pos, const double pick_radius) { return FALSE; } 
	// 得到对象的最小包围盒，该包围盒将被用于图元的选取和全屏显示
	virtual void GetBox(BOX2D* pBox){}
	// 给定一个基点和一个目标点平移图元
	virtual void Move(const Position& basePos,const Position& desPos) {}
	// 给定一个基点和一个角度值旋转图元
	virtual void Rotate(const Position& basePos, const double angle) {}
	// 给定两点镜像图元，布尔变量bCopy用于确定是否删除原来位置的图元
	virtual void Mirror(const Position& pos1, const Position& pos2){}
	// 改变光标
	virtual	void LoadPmtCursor() {}
	// Get a feature position of a entity near the giving position.
	// Input : giving a pos
	// output : TRUE or FALSE
	// Note : if true , the giving pos is reset to the feature position
	virtual BOOL GetSnapPos(Position& pos) { return FALSE; }

	virtual void Serialize(CArchive& ar) ; // 图元对象串行化
};

////////////////////////////
// CLASS CLine
//
class CLine : public CEntity
{
	DECLARE_SERIAL(CLine)
protected:
	Position	m_begin , m_end ; // 起点和终点
	double m_fBeginAngle,m_fEndAngle,m_fNextCorner;
public:
    double      GetStartAngle();
	double      GetEndAngle();
	int                 GetLayer(){return m_layer;};
	void				SetLayer(int layer){m_layer=layer;};
	void SetBeginPos(Position p);
	void SetEndPos(Position p);
	CLine() ;
	CLine(const CLine& line);
	CLine(const Position& begin,const Position& end);
	~CLine() ;

	CLine&	operator = (const CLine& line);
	CEntity*	Copy();

	int			GetType();
	void		Init(); 
	Position	GetBeginPos(); // 返回起点值
	Position	GetEndPos();   // 返回终点值
	
	void Draw(CDC * pDC, int drawMode = dmNormal ) ;

	//对图元的编辑操作：拾取，平移，旋转，镜向和获得最小包围盒
	BOOL Pick(const Position& pos, const double pick_radius) ;
	void GetBox(BOX2D* pBox);
	
	void Move(const Position& basePos,const Position& desPos);
	void Rotate(const Position& basePos, const double angle);
	void Mirror(const Position& pos1, const Position& pos2);
	
	BOOL GetSnapPos(Position& pos);
	void LoadPmtCursor();

	void Serialize(CArchive& ar) ;

	BOOL reverseElement(CObList* pEntityList, POSITION pos);
};

////////////////////////////
// CLASS CRectangle
//
class CRectangle : public CEntity
{
	DECLARE_SERIAL(CRectangle)
protected:
	Position	m_LeftTop , m_RightBottom ; // 起点和终点
public:
	CRectangle() ;
	CRectangle(const CRectangle& rect);
	CRectangle(const Position& LeftTop,const Position& RightBottom);
	~CRectangle() ;

	CRectangle&	operator = (const CRectangle& rect);
	CEntity*	Copy();

	int			GetType();
	void		Init(); 
	Position	GetLeftTopPos();		// 返回左上角的值
	Position	GetRightBottomPos();	// 返回右下角的值
	
	void Draw(CDC * pDC, int drawMode = dmNormal ) ;

	//对图元的编辑操作：拾取，平移，旋转，镜向和获得最小包围盒
	BOOL Pick(const Position& pos, const double pick_radius) ;
	void GetBox(BOX2D* pBox);
	
	void Move(const Position& basePos,const Position& desPos);
	void Rotate(const Position& basePos, const double angle);
	void Mirror(const Position& pos1, const Position& pos2);
	
	BOOL GetSnapPos(Position& pos);
	void LoadPmtCursor() ;

	void Serialize(CArchive& ar) ;
};

/////////////////
// Class CCircle
//
class CCircle : public CEntity
{
	DECLARE_SERIAL(CCircle)
protected:
	//member variables
	Position	m_center ;
	Position	m_begin  ;
	Position    m_end    ;
	double		m_dRadius ;
public:
	Position GetEndPos();
	Position GetBeginPos();
	//void SetBeginPos(Position p);
	// constructor and destructor
	CCircle() ;
	CCircle(const CCircle& circle);
	CCircle(const Position& center,const double& radius);
	CCircle(const Position& center,const Position& aroud);
	~CCircle() ;

	CEntity*	Copy();
	//-----------------------------------------------
	// member function
	// Attributes
	int			GetType();
	void		Init(); // initialize member variables
	Position	GetCenterPos();
	double		GetRadius();
	
	void SetCenterPos(Position p);

	void Draw(CDC * pDC, int drawMode = dmNormal ) ;

	//对图元的编辑操作：拾取，平移，旋转，镜向和获得最小包围盒
	BOOL Pick(const Position& pos, const double pick_radius) ;
	void GetBox(BOX2D* pBox);
	
	void Move(const Position& basePos,const Position& desPos);
	void Rotate(const Position& basePos, const double angle);
	void Mirror(const Position& pos1, const Position& pos2);
	
	BOOL GetSnapPos(Position& pos);
	void LoadPmtCursor() ;

	void Serialize(CArchive& ar) ;
	BOOL reverseElement(POSITION pos);
};

////////////////////////////
// CLASS CArc
//
class CArc : public CEntity
{
	DECLARE_SERIAL(CArc)
protected:
	//member variables
	Position	m_center ;
	Position	m_begin  ;
	Position    m_end    ;
    double      m_fStartAngle;//弧度
	double      m_fEndAngle;

public:
	double GetDis(Position pos1, Position pos2);
	BOOL reverseElement(CObList* pEntityList, POSITION pos);
	void SetEndAngle(double angle);
	void SetStartAngle(double angle);
	void SetBeginPos(Position p);
	void SetEndPos(Position p);
	void SetCenterPos(Position p);
	// constructor and destructor
	CArc() ;
	CArc(const CArc& arc);
	CArc(const Position& center,const Position& startPos, const Position& endPos);
	~CArc() ;

	CEntity*	Copy();
	//-----------------------------------------------
	// member function
	// Attributes
	int			GetType();
	void		Init(); // initialize member variables
	Position	GetBeginPos();
	Position	GetEndPos();
	Position	GetCenterPos() ;
	BOOL		GetSnapPos(Position& pos) ;
    double      GetStartAngle();
	double      GetEndAngle();
	double		GetRadius();
	double		GetChordAngle();
		
	void Draw(CDC * pDC, int drawMode = dmNormal ) ;

	//对图元的编辑操作：拾取，平移，旋转，镜向和获得最小包围盒
	BOOL Pick(const Position& pos, const double pick_radius) ;
	void Move(const Position& basePos,const Position& desPos) ;
	void Rotate(const Position& basePos, const double angle) ;
	void Mirror(const Position& FstPos, const Position& SecPos);
	void GetBox(BOX2D* pBox);

	void LoadPmtCursor();
	void Serialize(CArchive& ar) ;
};
//////////////////////////////////////////////////////////
// CLASS CPolyLine
//
class CPolyLine : public CEntity
{
	DECLARE_SERIAL(CPolyLine)
protected:
	Position	m_begin , m_end, m_circenter; // 起点和终点,圆心坐标
	int			m_styleflag;    //图形类型。1 圆弧，2 直线。3椭圆直线
	double m_fBeginAngle,m_fEndAngle,m_fNextCorner;
public:
    double      GetStartAngle();
	double      GetEndAngle();
	void SetEndAngle(double angle);
	void SetStartAngle(double angle);

	int                 GetLayer(){return m_layer;};
	void				SetLayer(int layer){m_layer=layer;};
	void SetBeginPos(Position p);
	void SetEndPos(Position p);
	CPolyLine();
	CPolyLine(const CPolyLine& polyline);
	CPolyLine(const Position& begin,const Position& end,const Position& circenter,int typeflag=2);
	~CPolyLine() ;
	
	CPolyLine&	operator = (const CPolyLine& polyline);
	CEntity*	Copy();
	
	int			GetType();
	void		Init(); 
	Position	GetBeginPos(); // 返回起点值
	Position	GetEndPos();   // 返回终点值
	Position	GetCenterPos();   // 返回圆心坐标
	int         GetGrahStyle(){return m_styleflag;};
	
	void Draw(CDC * pDC, int drawMode = dmNormal ) ;
	
	//对图元的编辑操作：拾取，平移，旋转，镜向和获得最小包围盒
	BOOL Pick(const Position& pos, const double pick_radius) ;
	void GetBox(BOX2D* pBox);
	
	void Move(const Position& basePos,const Position& desPos);
	void Rotate(const Position& basePos, const double angle);
	void Mirror(const Position& pos1, const Position& pos2);
	
	BOOL GetSnapPos(Position& pos);
	void LoadPmtCursor();
	
	void Serialize(CArchive& ar) ;
	
	BOOL reverseElement(CObList* pEntityList, POSITION pos);

};

#endif