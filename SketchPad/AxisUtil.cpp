#include "pch.h"
#include "AxisUtil.h"

void AxisUtil::SetCartesian(CView* pCView, CDC* pDC) {
	// ��ȡ��ͼ�Ĵ�С
	CRect cRect;
	pCView->GetClientRect(&cRect);

	// �������ĵ�
	CPoint center = CPoint(cRect.Width() / 2, cRect.Height() / 2);
	// ����ԭ��
	pDC->SetViewportOrg(center.x, center.y);
	// ��תY��
	pDC->SetMapMode(MM_ANISOTROPIC);
	// Y�ᷴ��
	pDC->SetViewportExt(1, -1); 
	// ����X��
	pDC->SetWindowExt(1, 1);    

}

void AxisUtil::DrawAxis(CView* pCView, CDC* pDC) {
	// ��ȡ��ͼ�Ĵ�С
	CRect cRect;
	pCView->GetClientRect(&cRect);

	// �������ĵ�
	CPoint center = CPoint(cRect.Width() / 2, cRect.Height() / 2);

	// ���û���
	COLORREF color = RGB(0, 0, 0);
	CPen pen(PS_SOLID, 2, color);
	CPen* pOldPen = pDC->SelectObject(&pen); // ����ɵĻ���

	int margin = 50;
	CPoint xAxisStart = CPoint(-center.x + margin, 0);
	CPoint xAxisEnd = CPoint(center.x - margin, 0);
	CPoint yAxisStart = CPoint(0, -center.y + 50);
	CPoint yAxisEnd = CPoint(0, center.y - 50);


	// ���� X ��
	pDC->MoveTo(xAxisStart);
	pDC->LineTo(xAxisEnd);

	// ���� X ���ͷ
	pDC->MoveTo(xAxisEnd.x - 10, 5);
	pDC->LineTo(xAxisEnd.x, 0);
	pDC->LineTo(xAxisEnd.x - 10, -5);

	// ���� Y ��
	pDC->MoveTo(yAxisStart);
	pDC->LineTo(yAxisEnd);

	// ���� Y ���ͷ
	pDC->MoveTo(5, yAxisEnd.y - 10);
	pDC->LineTo(0, yAxisEnd.y);
	pDC->LineTo(-5, yAxisEnd.y - 10);

	// �ָ��ɵĻ���
	pDC->SelectObject(pOldPen);
}
