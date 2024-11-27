#include "pch.h"
#include "Octagon.h"


Octagon::Octagon(std::vector<CPoint> points, int m_radius) {
	this->m_points = points;
	this->m_radius = m_radius;
}

void Octagon::Draw(CDC* pDC) const {
    // 获取圆心和半径
    CPoint center = m_points[0]; // 中心点
    int radius = m_radius;     // 半径

    // 计算八个顶点的位置
    std::vector<CPoint> points(8);
    for (int i = 0; i < 8; ++i) {
        // 计算角度
        double angle = 2 * 3.14159265 * i / 8; // 360度 / 8 = 45度
        // 计算顶点坐标
        points[i].x = static_cast<int>(center.x + radius * cos(angle));
        points[i].y = static_cast<int>(center.y + radius * sin(angle));
    }

    // 绘制八边形
    for (int i = 0; i < 8; ++i) {
        pDC->MoveTo(points[i]); // 移动到当前点
        pDC->LineTo(points[(i + 1) % 8]); // 连接到下一个点
    }
}

std::vector<CPoint> Octagon::GetPoints() {
	return m_points;
}

void Octagon::SetPoints(std::vector<CPoint> points) {
	m_points.push_back(points[0]);
}
