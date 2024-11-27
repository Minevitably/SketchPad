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
	COLORREF color = RGB(255, 0, 0);
	CPen pen(PS_SOLID, 3, color);
	CPen* pOldPen = pDC->SelectObject(&pen); // ����ɵĻ���

	// ���� X ��
	pDC->MoveTo(-center.x, 0);
	pDC->LineTo(center.x, 0);

	// ���� X ���ͷ
	pDC->MoveTo(center.x - 10, 5);
	pDC->LineTo(center.x, 0);
	pDC->LineTo(center.x - 10, -5);

	// ���� Y ��
	pDC->MoveTo(0, -center.y);
	pDC->LineTo(0, center.y);

	// ���� Y ���ͷ
	pDC->MoveTo(5, center.y - 10);
	pDC->LineTo(0, center.y);
	pDC->LineTo(-5, center.y - 10);

	// �ָ��ɵĻ���
	pDC->SelectObject(pOldPen);
}
