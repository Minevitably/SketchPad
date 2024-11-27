#include "pch.h"
#include "Circle.h"



Circle::Circle(std::vector<CPoint> points, int m_radius) {
	this->m_points = points;
	this->m_radius = m_radius;
}

void Circle::Draw(CDC* pDC) const {

	// 圆心和半径
	CPoint center = m_points[0]; // 圆心
	int radius = m_radius;     // 半径

	int x = 0;
	int y = radius;
	int d = 3 - 2 * radius; // 初始决策参数

	// 绘制八个对称点
	while (y >= x) {
		// 画出八个对称点
		pDC->SetPixel(center.x + x, center.y + y, RGB(0, 0, 0)); // 第一象限
		pDC->SetPixel(center.x - x, center.y + y, RGB(0, 0, 0)); // 第二象限
		pDC->SetPixel(center.x + x, center.y - y, RGB(0, 0, 0)); // 第三象限
		pDC->SetPixel(center.x - x, center.y - y, RGB(0, 0, 0)); // 第四象限
		pDC->SetPixel(center.x + y, center.y + x, RGB(0, 0, 0)); // 第五象限
		pDC->SetPixel(center.x - y, center.y + x, RGB(0, 0, 0)); // 第六象限
		pDC->SetPixel(center.x + y, center.y - x, RGB(0, 0, 0)); // 第七象限
		pDC->SetPixel(center.x - y, center.y - x, RGB(0, 0, 0)); // 第八象限

		// 更新决策参数
		if (d < 0) {
			d = d + 4 * x + 6; // 选择东南方向
		}
		else {
			d = d + 4 * (x - y) + 10; // 选择西南方向
			y--; // y 减小
		}
		x++; // x 增加
	}

}

std::vector<CPoint> Circle::GetPoints() {
	return m_points;
}

void Circle::SetPoints(std::vector<CPoint> points) {
	m_points.push_back(points[0]);
}
