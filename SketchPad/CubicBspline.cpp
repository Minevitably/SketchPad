#include "pch.h"
#include "CubicBspline.h"

CubicBspline::CubicBspline(std::vector<CPoint> points) {
    this->m_points = points;
}
void CubicBspline::Draw(CDC* pDC) const {
    int numPoints = m_points.size();

    // ȷ��������4�����Ƶ�
    if (numPoints < 4) return;

    // ����ԭ����
    CPen* pOldPen = pDC->GetCurrentPen();
    pDC->SetBkMode(TRANSPARENT);

    // ������ɫ����
    std::vector<COLORREF> colors = { RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255), RGB(255, 255, 0) };

    // ���� B ��������
    for (int i = 0; i <= numPoints - 4; ++i) {
        // ���õ�ǰ�εĻ�����ɫ
        CPen newPen(PS_SOLID, 2, colors[i % colors.size()]);
        pDC->SelectObject(&newPen);

        // ���Ƶ�ǰ�ε� B ��������
        for (float t = 0; t <= 1; t += 0.01) {
            // ���� B ���������ϵĵ�
            CPoint point = CalculateCubicBsplinePoint(i, t);
            // �������ߵ�
            pDC->SetPixel(point, colors[i % colors.size()]); // ʹ�����ػ��ƣ���ʹ�� LineTo ���ӵ�
        }

        // ���ƿ��ƶ����
        for (int j = 0; j < 4; j++) {
            pDC->MoveTo(m_points[i + j]);
            if (j < 3) {
                pDC->LineTo(m_points[i + j + 1]);
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

CPoint CubicBspline::CalculateCubicBsplinePoint(int i, float t) const {
    // �������� B ������������ֵ
    float b0 = (1 - t) * (1 - t) * (1 - t) / 6.0f; // N0
    float b1 = (3 * t * t * t - 6 * t * t + 4) / 6.0f; // N1
    float b2 = (-3 * t * t * t + 3 * t * t + 3 * t + 1) / 6.0f; // N2
    float b3 = t * t * t / 6.0f; // N3

    CPoint point;
    point.x = b0 * m_points[i].x + b1 * m_points[i + 1].x + b2 * m_points[i + 2].x + b3 * m_points[i + 3].x;
    point.y = b0 * m_points[i].y + b1 * m_points[i + 1].y + b2 * m_points[i + 2].y + b3 * m_points[i + 3].y;

    return point;
}

std::vector<CPoint> CubicBspline::GetPoints() {
    return m_points;
}

void CubicBspline::SetPoints(std::vector<CPoint> points) {
    this->m_points = points;
}
