
// SketchPadView.h: CSketchPadView 类的接口
//

#pragma once
#include "AxisUtil.h"
#include <algorithm>
#include <iostream>
#include <vector>

#include "Graphic.h"
#include "Line.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Octagon.h"

#include "Hexagon.h"
#include "TransformUtil.h"

#include "FourthOrderBezier.h"
#include "CubicBspline.h"
#include "CubicBezierSplice.h"


#include "Polygon.h"
#include <afxwin.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "TGraphic.h"
#include "TCube.h"
#include "TSphere.h"

#define M_PI 3.1415926


// 定义裁剪窗口的边界
const int LEFT = 100;
const int RIGHT = 300;
const int BOTTOM = 100;
const int TOP = 300;

// 定义方向位编码
enum OutCode {
	INSIDE = 0,  // 0000
	LEFT_BIT = 1, // 0001
	RIGHT_BIT = 2, // 0010
	BOTTOM_BIT = 4, // 0100
	TOP_BIT = 8  // 1000
};
enum Mode {
	V_DEFAULT = 0,
	V_FRONT = 1,
	V_SIDE = 2,
	V_TOP = 3
};


class CSketchPadView : public CView
{
private:
	std::vector<Graphic*> m_graphics; // 二维图形
	HGLRC m_hGLRC;
	BOOL m_isGLInit;
	Mode m_view;
	std::vector<TGraphic*> tGraphics; //三维图形

	void DrawCayleyTree(CDC* pDC, int x, int y, double length, double angle, int depth);

	void DrawKockCurve(CDC* pDC, int x1, int y1, int x2, int y2, int depth);
	void DrawKockSnowflake(CDC* pDC, int x, int y, int size, int depth);
	void InitOpenGL();
	void OnDestroy();
	void ChangeView(Mode mode);
protected: // 仅从序列化创建
	CSketchPadView() noexcept;
	DECLARE_DYNCREATE(CSketchPadView)

// 特性
public:
	CSketchPadDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL CSketchPadView::OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CSketchPadView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClearSketchPad();
	afx_msg void OnBasicDdaline();
	afx_msg void OnBasicBreline();
	afx_msg void OnBasicBrelinePro();
	afx_msg void OnBasicSysline();
	afx_msg void OnBasicCircle();
	afx_msg void OnBasicEllipse();
	afx_msg void OnBasicOctagon();
	afx_msg void OnTransBasicZoom();
	afx_msg void OnTransBasicShear();
	afx_msg void OnTransBasicShift();
	afx_msg void OnTransBasicSymmetricByLine();
	afx_msg void OnTransBasicRotate();
	afx_msg void OnTransCompositeShift();
	afx_msg void OnTransCompositeZoomShear();
	afx_msg void OnTransRotateByPoint();
	afx_msg void OnTransSymmetricByLine();
	afx_msg void OnCurveFourthOrderBezier();
	afx_msg void OnCurveCubicBspline();
	afx_msg void OnCurveCubicBezierSplice();
	afx_msg void OnClipLine();
	afx_msg void OnClipPolygon();
	afx_msg void OnFillByColor();
	afx_msg void OnThreedDesignSphere();
	afx_msg void OnThreedDesignCube();
	afx_msg void OnThreedShowFrontview();
	afx_msg void OnThreedShowSideview();
	afx_msg void OnThreedShowTopview();
	afx_msg void OnFractalCayleyTree();
	afx_msg void OnFractalDragonCurve();
	afx_msg void OnFractalKockCurve();
	afx_msg void OnTransHexagon();
	// 删除变换后的图形
	void RemoveNewHexagon();
	afx_msg void OnFillByRed();
	afx_msg void OnFillByGreen();
	afx_msg void OnFillByBlue();
	afx_msg void OnThreedAxis();
};

#ifndef _DEBUG  // SketchPadView.cpp 中的调试版本
inline CSketchPadDoc* CSketchPadView::GetDocument() const
   { return reinterpret_cast<CSketchPadDoc*>(m_pDocument); }
#endif

