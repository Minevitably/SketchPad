#include "pch.h"
#include "Circle.h"



Circle::Circle(std::vector<CPoint> points, int m_radius) {
	this->m_points = points;
	this->m_radius = m_radius;
}

void Circle::Draw(CDC* pDC) const {

	// Բ�ĺͰ뾶
	CPoint center = m_points[0]; // Բ��
	int radius = m_radius;     // �뾶

	int x = 0;
	int y = radius;
	int d = 3 - 2 * radius; // ��ʼ���߲���

	// ���ư˸��ԳƵ�
	while (y >= x) {
		// �����˸��ԳƵ�
		pDC->SetPixel(center.x + x, center.y + y, RGB(0, 0, 0)); // ��һ����
		pDC->SetPixel(center.x - x, center.y + y, RGB(0, 0, 0)); // �ڶ�����
		pDC->SetPixel(center.x + x, center.y - y, RGB(0, 0, 0)); // ��������
		pDC->SetPixel(center.x - x, center.y - y, RGB(0, 0, 0)); // ��������
		pDC->SetPixel(center.x + y, center.y + x, RGB(0, 0, 0)); // ��������
		pDC->SetPixel(center.x - y, center.y + x, RGB(0, 0, 0)); // ��������
		pDC->SetPixel(center.x + y, center.y - x, RGB(0, 0, 0)); // ��������
		pDC->SetPixel(center.x - y, center.y - x, RGB(0, 0, 0)); // �ڰ�����

		// ���¾��߲���
		if (d < 0) {
			d = d + 4 * x + 6; // ѡ���Ϸ���
		}
		else {
			d = d + 4 * (x - y) + 10; // ѡ�����Ϸ���
			y--; // y ��С
		}
		x++; // x ����
	}

}

std::vector<CPoint> Circle::GetPoints() {
	return m_points;
}

void Circle::SetPoints(std::vector<CPoint> points) {
	m_points.push_back(points[0]);
}
