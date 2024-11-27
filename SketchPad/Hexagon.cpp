#include "pch.h"
#include "Hexagon.h"



Hexagon::Hexagon(std::vector<CPoint> points, int m_radius, bool m_raw) {
    this->m_points = points;
    this->m_radius = m_radius;
    this->m_raw = m_raw;

    // ��ȡ�����ε����ĺͰ뾶
    CPoint center = m_points[0]; // ���ĵ�
    int radius = m_radius;     // �뾶
    // �������������λ��
    std::vector<CPoint> calcPoints(6);
    for (int i = 0; i < 6; ++i) {
        // ����Ƕ�
        double angle = 2 * 3.14159265 * i / 6; // 360�� / 6 = 60��
        // ���㶥������
        calcPoints[i].x = static_cast<int>(center.x + radius * cos(angle));
        calcPoints[i].y = static_cast<int>(center.y + radius * sin(angle));
        m_points.push_back(calcPoints[i]);
    }
}

void Hexagon::Draw(CDC* pDC) const {
    // ���û���
    COLORREF color = RGB(0, 0, 0);
    CPen rawPen(PS_SOLID, 1, color);
    CPen newPen(PS_DASH, 3, color);
    CPen* pOldPen;
    if (m_raw) {
        pOldPen = pDC->SelectObject(&rawPen); // ����ɵĻ���
    }
    else {
        pOldPen = pDC->SelectObject(&newPen); // ����ɵĻ���
    }
    // ��������
    std::vector<CPoint> calcPoints(6);
    for (int i = 0; i < 6; ++i) {
        calcPoints[i] = m_points[i + 1];
    }
    // ����������
    for (int i = 0; i < 6; ++i) {
        pDC->MoveTo(calcPoints[i]); // �ƶ�����ǰ��
        pDC->LineTo(calcPoints[(i + 1) % 6]); // ���ӵ���һ����
    }

    pDC->SelectObject(pOldPen);

}

std::vector<CPoint> Hexagon::GetPoints() {
    return m_points;
}

void Hexagon::SetPoints(std::vector<CPoint> points) {
    m_points.clear();
    for (int i = 0; i < points.size(); i++) {
        m_points.push_back(points[i]);
    }
}
bool Hexagon::GetRaw() {
    return m_raw;
}