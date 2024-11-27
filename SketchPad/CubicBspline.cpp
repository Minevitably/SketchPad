#include "pch.h"
#include "CubicBspline.h"

CubicBspline::CubicBspline(std::vector<CPoint> points) {
    this->m_points = points;
}
void CubicBspline::Draw(CDC* pDC) const {
    int numPoints = m_points.size();

    // 确保至少有4个控制点
    if (numPoints < 4) return;

    // 保存原画笔
    CPen* pOldPen = pDC->GetCurrentPen();
    pDC->SetBkMode(TRANSPARENT);

    // 定义颜色数组
    std::vector<COLORREF> colors = { RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255), RGB(255, 255, 0) };

    // 绘制 B 样条曲线
    for (int i = 0; i <= numPoints - 4; ++i) {
        // 设置当前段的画笔颜色
        CPen newPen(PS_SOLID, 2, colors[i % colors.size()]);
        pDC->SelectObject(&newPen);

        // 绘制当前段的 B 样条曲线
        for (float t = 0; t <= 1; t += 0.01) {
            // 计算 B 样条曲线上的点
            CPoint point = CalculateCubicBsplinePoint(i, t);
            // 绘制曲线点
            pDC->SetPixel(point, colors[i % colors.size()]); // 使用像素绘制，或使用 LineTo 连接点
        }

        // 绘制控制多边形
        for (int j = 0; j < 4; j++) {
            pDC->MoveTo(m_points[i + j]);
            if (j < 3) {
                pDC->LineTo(m_points[i + j + 1]);
            }
        }
    }

    // 绘制控制点
    for (const auto& point : m_points) {
        pDC->Ellipse(point.x - 3, point.y - 3, point.x + 3, point.y + 3);
    }

    // 恢复原画笔
    pDC->SelectObject(pOldPen);
}

CPoint CubicBspline::CalculateCubicBsplinePoint(int i, float t) const {
    // 计算三次 B 样条基函数的值
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
