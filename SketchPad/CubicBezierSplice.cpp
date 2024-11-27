#include "pch.h"
#include "CubicBezierSplice.h"

CubicBezierSplice::CubicBezierSplice(std::vector<CPoint> points) {
    this->m_points = points;
}

void CubicBezierSplice::Draw(CDC* pDC) const {
    // ȷ�����㹻�Ŀ��Ƶ�
    if (m_points.size() < 12) return; // ÿ�����α�����������Ҫ4�����Ƶ�

    // ������ɫ����
    std::vector<COLORREF> colors = { RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255) };

    // ����ԭ����
    CPen* pOldPen = pDC->GetCurrentPen();
    pDC->SetBkMode(TRANSPARENT);

    pDC->MoveTo(m_points[0]);

    // ����ÿ�����α���������
    for (int i = 0; i < 3; ++i) {
        int baseIndex = i * 4; // ÿ����Ҫ4�����Ƶ�

        // ���û�����ɫ
        CPen newPen(PS_SOLID, 2, colors[i]);
        pDC->SelectObject(&newPen);

        // ���Ʊ���������
        for (float t = 0; t <= 1; t += 0.01) {
            // ʹ�ñ��������߹�ʽ�����
            CPoint point = CalculateCubicBezierPoint(m_points[baseIndex], m_points[baseIndex + 1],
                m_points[baseIndex + 2], m_points[baseIndex + 3], t);
            pDC->LineTo(point); // �������ߵ㣬��ʹ�� LineTo ����
        }

        // ���ƿ��ƶ����
        for (int j = 0; j < 4; ++j) {
            pDC->MoveTo(m_points[baseIndex + j]);
            if (j < 3) {
                pDC->LineTo(m_points[baseIndex + j + 1]);
            }
        }
    }

    // ���ƿ��Ƶ�
    for (const auto& point : m_points) {
        pDC->Ellipse(point.x - 3, point.y - 3, point.x + 3, point.y + 3);
    }

    // �ָ�ԭ����
    pDC->SelectObject(pOldPen);
}

CPoint CubicBezierSplice::CalculateCubicBezierPoint(CPoint p0, CPoint p1,CPoint p2, CPoint p3, float t) const {
    // ʹ�����α��������߹�ʽ�����
    float x = pow(1 - t, 3) * p0.x +
        3 * pow(1 - t, 2) * t * p1.x +
        3 * (1 - t) * t * t * p2.x +
        t * t * t * p3.x;

    float y = pow(1 - t, 3) * p0.y +
        3 * pow(1 - t, 2) * t * p1.y +
        3 * (1 - t) * t * t * p2.y +
        t * t * t * p3.y;

    return CPoint(static_cast<int>(x), static_cast<int>(y));
}

std::vector<CPoint> CubicBezierSplice::GetPoints() {
    return m_points;
}

void CubicBezierSplice::SetPoints(std::vector<CPoint> points) {
    this->m_points = points;
}
