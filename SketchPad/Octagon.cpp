#include "pch.h"
#include "Octagon.h"


Octagon::Octagon(std::vector<CPoint> points, int m_radius) {
	this->m_points = points;
	this->m_radius = m_radius;
}

void Octagon::Draw(CDC* pDC) const {
    // ��ȡԲ�ĺͰ뾶
    CPoint center = m_points[0]; // ���ĵ�
    int radius = m_radius;     // �뾶

    // ����˸������λ��
    std::vector<CPoint> points(8);
    for (int i = 0; i < 8; ++i) {
        // ����Ƕ�
        double angle = 2 * 3.14159265 * i / 8; // 360�� / 8 = 45��
        // ���㶥������
        points[i].x = static_cast<int>(center.x + radius * cos(angle));
        points[i].y = static_cast<int>(center.y + radius * sin(angle));
    }

    // ���ư˱���
    for (int i = 0; i < 8; ++i) {
        pDC->MoveTo(points[i]); // �ƶ�����ǰ��
        pDC->LineTo(points[(i + 1) % 8]); // ���ӵ���һ����
    }
}

std::vector<CPoint> Octagon::GetPoints() {
	return m_points;
}

void Octagon::SetPoints(std::vector<CPoint> points) {
	m_points.push_back(points[0]);
}
