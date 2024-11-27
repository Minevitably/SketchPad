#include "pch.h"
#include "Polygon.h"

namespace MyGraphics {
	// 构造函数
	Polygon::Polygon(std::vector<CPoint> points) {
		this->m_points = points;
	}

	// 绘制多边形的函数
	void Polygon::Draw(CDC* pDC) const {
		if (m_points.size() < 2) {
			// 顶点不足，无法绘制
			return;
		}

		// 遍历多边形的点，依次绘制边
		for (size_t i = 0; i < m_points.size(); ++i) {
			CPoint start = m_points[i];
			CPoint end = m_points[(i + 1) % m_points.size()]; // 最后一条边连接到第一个点

			// 调用 MFC 提供的直线绘制函数
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




	// 绘制多边形
	void Polygon::Draw(CDC* pDC, COLORREF color) const {
		if (m_points.size() < 2) return;

		CPen pen(PS_SOLID, 1, color);
		CPen* pOldPen = pDC->SelectObject(&pen);

		// 连接多边形所有点并闭合
		pDC->MoveTo(m_points[0]);
		for (size_t i = 1; i < m_points.size(); ++i) {
			pDC->LineTo(m_points[i]);
		}
		pDC->LineTo(m_points[0]);

		pDC->SelectObject(pOldPen);
	}

	// 裁剪多边形
	void Polygon::Clip(const CRect& clipRect) {
		std::vector<CPoint> input = m_points;

		// 裁剪窗口的四条边：左、右、下、上
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

	// 判断点是否在指定边界内
	bool Polygon::IsInside(const CPoint& p, const CRect& rect, int edge) {
		switch (edge) {
		case 0: return p.x >= rect.left;  // 左边界
		case 1: return p.x <= rect.right; // 右边界
		case 2: return p.y >= rect.top;   // 上边界
		case 3: return p.y <= rect.bottom; // 下边界
		}
		return false;
	}

	// 计算边界与多边形边的交点
	CPoint Polygon::ComputeIntersection(const CPoint& p1, const CPoint& p2, const CRect& rect, int edge) {
		double x, y;

		switch (edge) {
		case 0: // 左边界
			x = rect.left;
			y = p1.y + (p2.y - p1.y) * (rect.left - p1.x) / (p2.x - p1.x);
			break;
		case 1: // 右边界
			x = rect.right;
			y = p1.y + (p2.y - p1.y) * (rect.right - p1.x) / (p2.x - p1.x);
			break;
		case 2: // 上边界
			y = rect.top;
			x = p1.x + (p2.x - p1.x) * (rect.top - p1.y) / (p2.y - p1.y);
			break;
		case 3: // 下边界
			y = rect.bottom;
			x = p1.x + (p2.x - p1.x) * (rect.bottom - p1.y) / (p2.y - p1.y);
			break;
		}

		return CPoint(static_cast<int>(x + 0.5), static_cast<int>(y + 0.5)); // 四舍五入取整
	}
}