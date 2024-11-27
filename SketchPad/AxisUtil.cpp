#include "pch.h"
#include "AxisUtil.h"

void AxisUtil::SetCartesian(CView* pCView, CDC* pDC) {
	// 获取视图的大小
	CRect cRect;
	pCView->GetClientRect(&cRect);

	// 计算中心点
	CPoint center = CPoint(cRect.Width() / 2, cRect.Height() / 2);
	// 坐标原点
	pDC->SetViewportOrg(center.x, center.y);
	// 反转Y轴
	pDC->SetMapMode(MM_ANISOTROPIC);
	// Y轴反向
	pDC->SetViewportExt(1, -1); 
	// 保持X轴
	pDC->SetWindowExt(1, 1);    

}

void AxisUtil::DrawAxis(CView* pCView, CDC* pDC) {
	// 获取视图的大小
	CRect cRect;
	pCView->GetClientRect(&cRect);

	// 计算中心点
	CPoint center = CPoint(cRect.Width() / 2, cRect.Height() / 2);

	// 设置画笔
	COLORREF color = RGB(0, 0, 0);
	CPen pen(PS_SOLID, 2, color);
	CPen* pOldPen = pDC->SelectObject(&pen); // 保存旧的画笔

	int margin = 50;
	CPoint xAxisStart = CPoint(-center.x + margin, 0);
	CPoint xAxisEnd = CPoint(center.x - margin, 0);
	CPoint yAxisStart = CPoint(0, -center.y + 50);
	CPoint yAxisEnd = CPoint(0, center.y - 50);


	// 绘制 X 轴
	pDC->MoveTo(xAxisStart);
	pDC->LineTo(xAxisEnd);

	// 绘制 X 轴箭头
	pDC->MoveTo(xAxisEnd.x - 10, 5);
	pDC->LineTo(xAxisEnd.x, 0);
	pDC->LineTo(xAxisEnd.x - 10, -5);

	// 绘制 Y 轴
	pDC->MoveTo(yAxisStart);
	pDC->LineTo(yAxisEnd);

	// 绘制 Y 轴箭头
	pDC->MoveTo(5, yAxisEnd.y - 10);
	pDC->LineTo(0, yAxisEnd.y);
	pDC->LineTo(-5, yAxisEnd.y - 10);

	// 恢复旧的画笔
	pDC->SelectObject(pOldPen);
}
