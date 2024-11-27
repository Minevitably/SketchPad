#include "pch.h"
#include "CubicBezierSplice.h"

CubicBezierSplice::CubicBezierSplice(std::vector<CPoint> points) {
    this->m_points = points;
}

void CubicBezierSplice::Draw(CDC* pDC) const {
    // 确保有足够的控制点
    if (m_points.size() < 12) return; // 每段三次贝塞尔曲线需要4个控制点

    // 定义颜色数组
    std::vector<COLORREF> colors = { RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255) };

    // 保存原画笔
    CPen* pOldPen = pDC->GetCurrentPen();
    pDC->SetBkMode(TRANSPARENT);

    pDC->MoveTo(m_points[0]);

    // 绘制每段三次贝塞尔曲线
    for (int i = 0; i < 3; ++i) {
        int baseIndex = i * 4; // 每段需要4个控制点

        // 设置画笔颜色
        CPen newPen(PS_SOLID, 2, colors[i]);
        pDC->SelectObject(&newPen);

        // 绘制贝塞尔曲线
        for (float t = 0; t <= 1; t += 0.01) {
            // 使用贝塞尔曲线公式计算点
            CPoint point = CalculateCubicBezierPoint(m_points[baseIndex], m_points[baseIndex + 1],
                m_points[baseIndex + 2], m_points[baseIndex + 3], t);
            pDC->LineTo(point); // 绘制曲线点，或使用 LineTo 连接
        }

        // 绘制控制多边形
        for (int j = 0; j < 4; ++j) {
            pDC->MoveTo(m_points[baseIndex + j]);
            if (j < 3) {
                pDC->LineTo(m_points[baseIndex + j + 1]);
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

CPoint CubicBezierSplice::CalculateCubicBezierPoint(CPoint p0, CPoint p1,CPoint p2, CPoint p3, float t) const {
    // 使用三次贝塞尔曲线公式计算点
    float x = pow(1 - t, 3) * p0.x +
        3 * pow(1 - t, 2) * t * p1.x +
        3 * (1 - t) * t * t * p2.x +
        t * t * t * p3.x;

    float y = pow(1 - t, 3) * p0.y +
        3 * pow(1 - t, 2) * t * p1.y +
        3 * (1 - t) * t * t * p2.y +
        t * t * t * p3.y;

    return CPoint(static_cast<int>(x), static_cast<int>(y));
}

std::vector<CPoint> CubicBezierSplice::GetPoints() {
    return m_points;
}

void CubicBezierSplice::SetPoints(std::vector<CPoint> points) {
    this->m_points = points;
}
