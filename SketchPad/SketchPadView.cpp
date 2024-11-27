
// SketchPadView.cpp: CSketchPadView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "SketchPad.h"
#endif

#include "SketchPadDoc.h"
#include "SketchPadView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSketchPadView

IMPLEMENT_DYNCREATE(CSketchPadView, CView)

BEGIN_MESSAGE_MAP(CSketchPadView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_CLEAR_SKETCH_PAD, &CSketchPadView::OnClearSketchPad)
	ON_COMMAND(ID_BASIC_DDALINE, &CSketchPadView::OnBasicDdaline)
	ON_COMMAND(ID_BASIC_BRELINE, &CSketchPadView::OnBasicBreline)
	ON_COMMAND(ID_BASIC_BRELINE_PRO, &CSketchPadView::OnBasicBrelinePro)
	ON_COMMAND(ID_BASIC_SYSLINE, &CSketchPadView::OnBasicSysline)
	ON_COMMAND(ID_BASIC_CIRCLE, &CSketchPadView::OnBasicCircle)
	ON_COMMAND(ID_BASIC_ELLIPSE, &CSketchPadView::OnBasicEllipse)
	ON_COMMAND(ID_BASIC_OCTAGON, &CSketchPadView::OnBasicOctagon)
	ON_COMMAND(ID_TRANS_BASIC_ZOOM, &CSketchPadView::OnTransBasicZoom)
	ON_COMMAND(ID_TRANS_BASIC_SHEAR, &CSketchPadView::OnTransBasicShear)
	ON_COMMAND(ID_TRANS_BASIC_SHIFT, &CSketchPadView::OnTransBasicShift)
	ON_COMMAND(ID_TRANS_BASIC_SYMMETRIC_BY_LINE, &CSketchPadView::OnTransBasicSymmetricByLine)
	ON_COMMAND(ID_TRANS_BASIC_ROTATE, &CSketchPadView::OnTransBasicRotate)
	ON_COMMAND(ID_TRANS_COMPOSITE_SHIFT, &CSketchPadView::OnTransCompositeShift)
	ON_COMMAND(ID_TRANS_COMPOSITE_ZOOM_SHEAR, &CSketchPadView::OnTransCompositeZoomShear)
	ON_COMMAND(ID_TRANS_ROTATE_BY_POINT, &CSketchPadView::OnTransRotateByPoint)
	ON_COMMAND(ID_TRANS_SYMMETRIC_BY_LINE, &CSketchPadView::OnTransSymmetricByLine)
	ON_COMMAND(ID_CURVE_FOURTH_ORDER_BEZIER, &CSketchPadView::OnCurveFourthOrderBezier)
	ON_COMMAND(ID_CURVE_CUBIC_BSPLINE, &CSketchPadView::OnCurveCubicBspline)
	ON_COMMAND(ID_CURVE_CUBIC_BEZIER_SPLICE, &CSketchPadView::OnCurveCubicBezierSplice)
	ON_COMMAND(ID_CLIP_LINE, &CSketchPadView::OnClipLine)
	ON_COMMAND(ID_CLIP_POLYGON, &CSketchPadView::OnClipPolygon)
	ON_COMMAND(ID_FILL_BY_COLOR, &CSketchPadView::OnFillByColor)
	ON_COMMAND(ID_THREED_DESIGN_SPHERE, &CSketchPadView::OnThreedDesignSphere)
	ON_COMMAND(ID_THREED_DESIGN_CUBE, &CSketchPadView::OnThreedDesignCube)
	ON_COMMAND(ID_THREED_SHOW_FRONTVIEW, &CSketchPadView::OnThreedShowFrontview)
	ON_COMMAND(ID_THREED_SHOW_SIDEVIEW, &CSketchPadView::OnThreedShowSideview)
	ON_COMMAND(ID_THREED_SHOW_TOPVIEW, &CSketchPadView::OnThreedShowTopview)
	ON_COMMAND(ID_FRACTAL_CAYLEY_TREE, &CSketchPadView::OnFractalCayleyTree)
	ON_COMMAND(ID_FRACTAL_DRAGON_CURVE, &CSketchPadView::OnFractalDragonCurve)
	ON_COMMAND(ID_FRACTAL_KOCK_CURVE, &CSketchPadView::OnFractalKockCurve)
	ON_COMMAND(ID_TRANS_HEXAGON, &CSketchPadView::OnTransHexagon)
END_MESSAGE_MAP()

// CSketchPadView 构造/析构

CSketchPadView::CSketchPadView() noexcept
{
	// TODO: 在此处添加构造代码

}

CSketchPadView::~CSketchPadView()
{
}

BOOL CSketchPadView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CSketchPadView 绘图

void CSketchPadView::OnDraw(CDC* pDC)
{
	CSketchPadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码
	AxisUtil::SetCartesian(this, pDC); // 设置为标准笛卡尔坐标系
	AxisUtil::DrawAxis(this, pDC); 	// 绘制坐标轴

	for (Graphic * pGraphic : m_graphics) {
		pGraphic->Draw(pDC);
	}


	pDC->MoveTo(CPoint(0,0));
	pDC->LineTo(CPoint(250, 50));
}


// CSketchPadView 打印

BOOL CSketchPadView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CSketchPadView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CSketchPadView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CSketchPadView 诊断

#ifdef _DEBUG
void CSketchPadView::AssertValid() const
{
	CView::AssertValid();
}

void CSketchPadView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSketchPadDoc* CSketchPadView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSketchPadDoc)));
	return (CSketchPadDoc*)m_pDocument;
}
#endif //_DEBUG


// CSketchPadView 消息处理程序

// 清空画板
void CSketchPadView::OnClearSketchPad()
{
	int size = m_graphics.size();
	// TODO: 在此添加命令处理程序代码
	for (int i = 0; i < size; i++) {
		delete m_graphics[i];
	}
	m_graphics.clear();
	Invalidate();
	AfxMessageBox(_T("画板已清空"));
}

// DDA绘制线型为虚线的直线
void CSketchPadView::OnBasicDdaline()
{
	std::vector<CPoint> points;
	CPoint start = CPoint(0, 0);
	CPoint end = CPoint(50, 250);
	points.push_back(start);
	points.push_back(end);
	// line必须使用内存分配，否则会被内存回收机制带走
	Line *line = new Line(points, DDA_LINE);
	m_graphics.push_back(line);
	//AfxMessageBox(_T("DDA绘制线型为虚线的直线"));
	// 更新画板
	Invalidate();
}

// Bresenham绘制线宽为2的直线
void CSketchPadView::OnBasicBreline()
{
	// TODO: 在此添加命令处理程序代码
	std::vector<CPoint> points;
	CPoint start = CPoint(0, 0);
	CPoint end = CPoint(100, 200);
	points.push_back(start);
	points.push_back(end);
	// line必须使用内存分配，否则会被内存回收机制带走
	Line* line = new Line(points, BRE_LINE);
	m_graphics.push_back(line);
	//AfxMessageBox(_T("Bresenham绘制线宽为2的直线"));
	// 更新画板
	Invalidate();
}

// 改进的Bresenham绘制红色直线
void CSketchPadView::OnBasicBrelinePro()
{
	// TODO: 在此添加命令处理程序代码
	std::vector<CPoint> points;
	CPoint start = CPoint(0, 0);
	CPoint end = CPoint(150, 150);
	points.push_back(start);
	points.push_back(end);
	// line必须使用内存分配，否则会被内存回收机制带走
	Line* line = new Line(points, BRE_LINE_PRO);
	m_graphics.push_back(line);
	//AfxMessageBox(_T("改进的Bresenham绘制红色直线"));
	// 更新画板
	Invalidate();

}

// 系统库函数绘制直线
void CSketchPadView::OnBasicSysline()
{
	// TODO: 在此添加命令处理程序代码
	std::vector<CPoint> points;
	CPoint start = CPoint(0, 0);
	CPoint end = CPoint(200, 100);
	points.push_back(start);
	points.push_back(end);
	// line必须使用内存分配，否则会被内存回收机制带走
	Line* line = new Line(points, SYS_LINE);
	m_graphics.push_back(line);
	//AfxMessageBox(_T("系统库函数绘制直线"));
	Invalidate();
}

// Bresenham绘制圆心不在原点的圆
void CSketchPadView::OnBasicCircle()
{
	std::vector<CPoint> points;
	CPoint center = CPoint(-150, 150);
	int radius = 50;
	points.push_back(center);
	Circle* circle = new Circle(points, radius);
	m_graphics.push_back(circle);
	// TODO: 在此添加命令处理程序代码
	//AfxMessageBox(_T("Bresenham绘制圆心不在原点的圆"));
	Invalidate();
}

// Bresenham绘制椭圆
void CSketchPadView::OnBasicEllipse()
{
	std::vector<CPoint> points;
	CPoint center = CPoint(-150, -100);
	int a = 70;
	int b = 50;
	points.push_back(center);
	// 这里和库函数产生了冲突
	MyGraphics::Ellipse* ellipse = new MyGraphics::Ellipse(points, a, b);
	m_graphics.push_back(ellipse);
	// TODO: 在此添加命令处理程序代码
	//AfxMessageBox(_T("Bresenham绘制椭圆"));
	Invalidate();

}

// 八边形的绘制
void CSketchPadView::OnBasicOctagon()
{
	std::vector<CPoint> points;
	CPoint center = CPoint(125, -100);
	int radius = 50;
	points.push_back(center);
	Octagon* octagon = new Octagon(points, radius);
	m_graphics.push_back(octagon);
	// TODO: 在此添加命令处理程序代码
	//AfxMessageBox(_T("八边形的绘制"));
	Invalidate();
}

// 六边形的绘制
void CSketchPadView::OnTransHexagon()
{
	// TODO: 在此添加命令处理程序代码
	std::vector<CPoint> points;
	CPoint center = CPoint(250, 100);
	int radius = 50;
	// 使用一个bool值标记原图
	bool raw = true;
	points.push_back(center);
	Hexagon* hexagon = new Hexagon(points, radius, raw);
	m_graphics.push_back(hexagon);
	// TODO: 在此添加命令处理程序代码
	//AfxMessageBox(_T("六边形的绘制"));
	Invalidate();
}

// 删除变换后的图形
void CSketchPadView::RemoveNewHexagon()
{
	// TODO: 在此添加命令处理程序代码
	for (int i = 0; i < m_graphics.size(); ) { // 注意这里的 i 不自增
		Graphic* pGraphic = m_graphics[i];

		// 使用 dynamic_cast 进行类型检查
		if (Hexagon* hexagon = dynamic_cast<Hexagon*>(pGraphic)) {
			if (!hexagon->GetRaw()) {
				// 通过 erase-remove 习惯模式删除元素
				m_graphics.erase(m_graphics.begin() + i);
				// 注意：这里不增加 i，因为我们已经移除了当前元素
				continue; // 继续检查下一个元素
			}
		}
		i++; // 仅在未移除元素时自增 i
	}
}
// 平移变换
void CSketchPadView::OnTransBasicShift()
{
	RemoveNewHexagon();
	// 创建一个新的图形用于变换
	std::vector<CPoint> points;
	CPoint center = CPoint(250, 100);
	int radius = 50;
	// 使用一个bool值标记原图
	bool raw = false;
	points.push_back(center);
	// 变换
	Hexagon* newHexagon = new Hexagon(points, radius, raw);
	std::vector<CPoint> newPoints = newHexagon->GetPoints();

	// 向x负方向平移500个单位
	newHexagon->SetPoints(TransformUtil::Translate(newPoints, -500, 0));
	m_graphics.push_back(newHexagon);
	AfxMessageBox(_T("向x负方向平移500个单位"));
	Invalidate();
}
// 整体比例变换
void CSketchPadView::OnTransBasicZoom()
{
	RemoveNewHexagon();
	// 创建一个新的图形用于变换
	std::vector<CPoint> points;
	CPoint center = CPoint(250, 100);
	int radius = 50;
	// 使用一个bool值标记原图
	bool raw = false;
	points.push_back(center);
	// 变换
	Hexagon* newHexagon = new Hexagon(points, radius, raw);
	std::vector<CPoint> newPoints = newHexagon->GetPoints();

	// 整体放大1.2倍
	newHexagon->SetPoints(TransformUtil::Scale(newPoints, 1.2f, 1.2f));
	m_graphics.push_back(newHexagon);
	AfxMessageBox(_T("整体放大1.2倍"));
	Invalidate();
}
// 沿y方向的错切变换
void CSketchPadView::OnTransBasicShear()
{
	// TODO: 在此添加命令处理程序代码
	RemoveNewHexagon();
	// 创建一个新的图形用于变换
	std::vector<CPoint> points;
	CPoint center = CPoint(250, 100);
	int radius = 50;
	// 使用一个bool值标记原图
	bool raw = false;
	points.push_back(center);
	// 变换
	Hexagon* newHexagon = new Hexagon(points, radius, raw);
	std::vector<CPoint> newPoints = newHexagon->GetPoints();

	// 沿y方向的错切变换，错切因子为0.3f
	newHexagon->SetPoints(TransformUtil::Shear(newPoints, 0.3f));
	m_graphics.push_back(newHexagon);
	AfxMessageBox(_T("沿y方向的错切变换，错切因子为0.3f"));
	Invalidate();
}
// 关于直线 y = -x 的对称变换
void CSketchPadView::OnTransBasicSymmetricByLine()
{
	// TODO: 在此添加命令处理程序代码
	RemoveNewHexagon();
	// 创建一个新的图形用于变换
	std::vector<CPoint> points;
	CPoint center = CPoint(250, 100);
	int radius = 50;
	// 使用一个bool值标记原图
	bool raw = false;
	points.push_back(center);
	// 变换
	Hexagon* newHexagon = new Hexagon(points, radius, raw);
	std::vector<CPoint> newPoints = newHexagon->GetPoints();

	// 关于直线 y = -x 的对称变换
	newHexagon->SetPoints(TransformUtil::Reflect(newPoints));
	m_graphics.push_back(newHexagon);
	AfxMessageBox(_T("关于直线 y = -x 的对称变换"));
	Invalidate();
}
// 顺时针旋转60°的旋转变换
void CSketchPadView::OnTransBasicRotate()
{
	// TODO: 在此添加命令处理程序代码
		// TODO: 在此添加命令处理程序代码
	RemoveNewHexagon();
	// 创建一个新的图形用于变换
	std::vector<CPoint> points;
	CPoint center = CPoint(250, 100);
	int radius = 50;
	// 使用一个bool值标记原图
	bool raw = false;
	points.push_back(center);
	// 变换
	Hexagon* newHexagon = new Hexagon(points, radius, raw);
	std::vector<CPoint> newPoints = newHexagon->GetPoints();

	// 绕原点顺时针旋转60°的旋转变换
	newHexagon->SetPoints(TransformUtil::Rotate(newPoints, 60.0f));
	m_graphics.push_back(newHexagon);
	AfxMessageBox(_T("绕原点顺时针旋转60°的旋转变换"));
	Invalidate();

}
// 复合平移变换
void CSketchPadView::OnTransCompositeShift()
{
	// TODO: 在此添加命令处理程序代码
	// 先沿y轴平移-200单位，再向x轴平移-200单位
	RemoveNewHexagon();
	// 创建一个新的图形用于变换
	std::vector<CPoint> points;
	CPoint center = CPoint(250, 100);
	int radius = 50;
	// 使用一个bool值标记原图
	bool raw = false;
	points.push_back(center);
	// 变换
	Hexagon* newHexagon = new Hexagon(points, radius, raw);
	std::vector<CPoint> newPoints = newHexagon->GetPoints();

	// 先沿y轴平移-200单位，再向x轴平移-200单位
	newHexagon->SetPoints(TransformUtil::Translate(newPoints, -200, -200));
	m_graphics.push_back(newHexagon);
	AfxMessageBox(_T("先沿y轴平移-200单位，再向x轴平移-200单位"));
	Invalidate();
}
// 先比例变换再错切变换
void CSketchPadView::OnTransCompositeZoomShear()
{
	// TODO: 在此添加命令处理程序代码
	// 先沿y轴平移-200单位，再向x轴平移-200单位
	RemoveNewHexagon();
	// 创建一个新的图形用于变换
	std::vector<CPoint> points;
	CPoint center = CPoint(250, 100);
	int radius = 50;
	// 使用一个bool值标记原图
	bool raw = false;
	points.push_back(center);
	// 变换
	Hexagon* newHexagon = new Hexagon(points, radius, raw);
	std::vector<CPoint> newPoints = newHexagon->GetPoints();

	// 先比例变换，比例因子（1.2f, 1.2f），再错切变换，错切因子0.3f
	newHexagon->SetPoints(TransformUtil::ScaleAndShear(newPoints, 1.2f, 1.2f, 0.3f));
	m_graphics.push_back(newHexagon);
	AfxMessageBox(_T("先比例变换，比例因子（1.2f, 1.2f），再错切变换，错切因子0.3f"));
	Invalidate();
}
// 相对点（5, 10）的旋转变换
void CSketchPadView::OnTransRotateByPoint()
{
	// TODO: 在此添加命令处理程序代码
	// 先沿y轴平移-200单位，再向x轴平移-200单位
	RemoveNewHexagon();
	// 创建一个新的图形用于变换
	std::vector<CPoint> points;
	CPoint center = CPoint(250, 100);
	int radius = 50;
	// 使用一个bool值标记原图
	bool raw = false;
	points.push_back(center);
	// 变换
	Hexagon* newHexagon = new Hexagon(points, radius, raw);
	std::vector<CPoint> newPoints = newHexagon->GetPoints();

	// 相对点（5, 10）顺时针旋转30°
	newHexagon->SetPoints(TransformUtil::RotateByPoint(newPoints, -30.0f, 5, 10));
	m_graphics.push_back(newHexagon);
	AfxMessageBox(_T("相对点（5, 10）顺时针旋转30°"));
	Invalidate();
}
// 关于直线 y = x 的反射变换
void CSketchPadView::OnTransSymmetricByLine()
{
	// TODO: 在此添加命令处理程序代码
	// 先沿y轴平移-200单位，再向x轴平移-200单位
	RemoveNewHexagon();
	// 创建一个新的图形用于变换
	std::vector<CPoint> points;
	CPoint center = CPoint(250, 100);
	int radius = 50;
	// 使用一个bool值标记原图
	bool raw = false;
	points.push_back(center);
	// 变换
	Hexagon* newHexagon = new Hexagon(points, radius, raw);
	std::vector<CPoint> newPoints = newHexagon->GetPoints();

	// 关于直线 y = x 的反射变换
	newHexagon->SetPoints(TransformUtil::ReflectByYX(newPoints));
	m_graphics.push_back(newHexagon);
	AfxMessageBox(_T("关于直线 y = x 的反射变换"));
	Invalidate();
}


// 四次Bezier曲线绘制
void CSketchPadView::OnCurveFourthOrderBezier()
{
	// TODO: 在此添加命令处理程序代码
}

// 三次B样条曲线绘制
void CSketchPadView::OnCurveCubicBspline()
{
	// TODO: 在此添加命令处理程序代码
}

// 3段三次Bezier曲线的拼接
void CSketchPadView::OnCurveCubicBezierSplice()
{
	// TODO: 在此添加命令处理程序代码
}

// 直线的裁剪
void CSketchPadView::OnClipLine()
{
	// TODO: 在此添加命令处理程序代码
}

// 多边形裁剪
void CSketchPadView::OnClipPolygon()
{
	// TODO: 在此添加命令处理程序代码
}

// 图形填充
// 要求可以改变填充颜色，不可直接调用系统函数
void CSketchPadView::OnFillByColor()
{
	// TODO: 在此添加命令处理程序代码
}

// 设计三维球体
void CSketchPadView::OnThreedDesignSphere()
{
	// TODO: 在此添加命令处理程序代码
}

// 设计三维立方体
void CSketchPadView::OnThreedDesignCube()
{
	// TODO: 在此添加命令处理程序代码
}

// 显示前视图
void CSketchPadView::OnThreedShowFrontview()
{
	// TODO: 在此添加命令处理程序代码
}

// 显示侧视图
void CSketchPadView::OnThreedShowSideview()
{
	// TODO: 在此添加命令处理程序代码
}

// 显示俯视图
void CSketchPadView::OnThreedShowTopview()
{
	// TODO: 在此添加命令处理程序代码
}

// 绘制Cayley树
void CSketchPadView::OnFractalCayleyTree()
{
	// TODO: 在此添加命令处理程序代码
}

// 绘制龙状曲线
void CSketchPadView::OnFractalDragonCurve()
{
	// TODO: 在此添加命令处理程序代码
}

// 绘制Kock雪花曲线
void CSketchPadView::OnFractalKockCurve()
{
	// TODO: 在此添加命令处理程序代码
}




