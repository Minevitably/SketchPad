#include "pch.h"
#include "Hexagon.h"



Hexagon::Hexagon(std::vector<CPoint> points, int m_radius, bool m_raw) {
    this->m_points = points;
    this->m_radius = m_radius;
    this->m_raw = m_raw;

    // 获取六边形的中心和半径
    CPoint center = m_points[0]; // 中心点
    int radius = m_radius;     // 半径
    // 计算六个顶点的位置
    std::vector<CPoint> calcPoints(6);
    for (int i = 0; i < 6; ++i) {
        // 计算角度
        double angle = 2 * 3.14159265 * i / 6; // 360度 / 6 = 60度
        // 计算顶点坐标
        calcPoints[i].x = static_cast<int>(center.x + radius * cos(angle));
        calcPoints[i].y = static_cast<int>(center.y + radius * sin(angle));
        m_points.push_back(calcPoints[i]);
    }
}

void Hexagon::Draw(CDC* pDC) const {
    // 设置画笔
    COLORREF color = RGB(0, 0, 0);
    CPen rawPen(PS_SOLID, 1, color);
    CPen newPen(PS_DASH, 3, color);
    CPen* pOldPen;
    if (m_raw) {
        pOldPen = pDC->SelectObject(&rawPen); // 保存旧的画笔
    }
    else {
        pOldPen = pDC->SelectObject(&newPen); // 保存旧的画笔
    }
    // 六个顶点
    std::vector<CPoint> calcPoints(6);
    for (int i = 0; i < 6; ++i) {
        calcPoints[i] = m_points[i + 1];
    }
    // 绘制六边形
    for (int i = 0; i < 6; ++i) {
        pDC->MoveTo(calcPoints[i]); // 移动到当前点
        pDC->LineTo(calcPoints[(i + 1) % 6]); // 连接到下一个点
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