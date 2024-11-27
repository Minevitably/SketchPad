#include "pch.h"
#include "Polygon.h"

namespace MyGraphics {
	// ���캯��
	Polygon::Polygon(std::vector<CPoint> points) {
		this->m_points = points;
	}

	// ���ƶ���εĺ���
	void Polygon::Draw(CDC* pDC) const {
		if (m_points.size() < 2) {
			// ���㲻�㣬�޷�����
			return;
		}

		// ��������εĵ㣬���λ��Ʊ�
		for (size_t i = 0; i < m_points.size(); ++i) {
			CPoint start = m_points[i];
			CPoint end = m_points[(i + 1) % m_points.size()]; // ���һ�������ӵ���һ����

			// ���� MFC �ṩ��ֱ�߻��ƺ���
			pDC->MoveTo(start);
			pDC->LineTo(end);
		}
	}





	std::vector<CPoint> Polygon::GetPoints() {
		return m_points;
	}

	void Polygon::SetPoints(std::vector<CPoint> points) {
		this->m_points = points;
	}




	// ���ƶ����
	void Polygon::Draw(CDC* pDC, COLORREF color) const {
		if (m_points.size() < 2) return;

		CPen pen(PS_SOLID, 1, color);
		CPen* pOldPen = pDC->SelectObject(&pen);

		// ���Ӷ�������е㲢�պ�
		pDC->MoveTo(m_points[0]);
		for (size_t i = 1; i < m_points.size(); ++i) {
			pDC->LineTo(m_points[i]);
		}
		pDC->LineTo(m_points[0]);

		pDC->SelectObject(pOldPen);
	}

	// �ü������
	void Polygon::Clip(const CRect& clipRect) {
		std::vector<CPoint> input = m_points;

		// �ü����ڵ������ߣ����ҡ��¡���
		for (int edge = 0; edge < 4; ++edge) {
			std::vector<CPoint> output;

			for (size_t i = 0; i < input.size(); ++i) {
				const CPoint& current = input[i];
				const CPoint& prev = input[(i + input.size() - 1) % input.size()];

				bool currInside = IsInside(current, clipRect, edge);
				bool prevInside = IsInside(prev, clipRect, edge);

				if (currInside) {
					if (!prevInside) {
						output.push_back(ComputeIntersection(prev, current, clipRect, edge));
					}
					output.push_back(current);
				}
				else if (prevInside) {
					output.push_back(ComputeIntersection(prev, current, clipRect, edge));
				}
			}

			input = output;
		}

		m_points = input;
	}

	// �жϵ��Ƿ���ָ���߽���
	bool Polygon::IsInside(const CPoint& p, const CRect& rect, int edge) {
		switch (edge) {
		case 0: return p.x >= rect.left;  // ��߽�
		case 1: return p.x <= rect.right; // �ұ߽�
		case 2: return p.y >= rect.top;   // �ϱ߽�
		case 3: return p.y <= rect.bottom; // �±߽�
		}
		return false;
	}

	// ����߽������αߵĽ���
	CPoint Polygon::ComputeIntersection(const CPoint& p1, const CPoint& p2, const CRect& rect, int edge) {
		double x, y;

		switch (edge) {
		case 0: // ��߽�
			x = rect.left;
			y = p1.y + (p2.y - p1.y) * (rect.left - p1.x) / (p2.x - p1.x);
			break;
		case 1: // �ұ߽�
			x = rect.right;
			y = p1.y + (p2.y - p1.y) * (rect.right - p1.x) / (p2.x - p1.x);
			break;
		case 2: // �ϱ߽�
			y = rect.top;
			x = p1.x + (p2.x - p1.x) * (rect.top - p1.y) / (p2.y - p1.y);
			break;
		case 3: // �±߽�
			y = rect.bottom;
			x = p1.x + (p2.x - p1.x) * (rect.bottom - p1.y) / (p2.y - p1.y);
			break;
		}

		return CPoint(static_cast<int>(x + 0.5), static_cast<int>(y + 0.5)); // ��������ȡ��
	}
}