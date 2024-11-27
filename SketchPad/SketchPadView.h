
// SketchPadView.h: CSketchPadView 类的接口
//

#pragma once
#include "AxisUtil.h"
#include <algorithm>
#include <iostream>
#include <vector>

#include "Graphic.h"
#include "Line.h"



class CSketchPadView : public CView
{
private:
	std::vector<Graphic*> m_graphics;

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
};

#ifndef _DEBUG  // SketchPadView.cpp 中的调试版本
inline CSketchPadDoc* CSketchPadView::GetDocument() const
   { return reinterpret_cast<CSketchPadDoc*>(m_pDocument); }
#endif

