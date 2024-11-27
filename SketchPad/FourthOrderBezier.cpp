#include "pch.h"
#include "FourthOrderBezier.h"


FourthOrderBezier::FourthOrderBezier(std::vector<CPoint> points) {
	this->m_points = points;
}

void FourthOrderBezier::Draw(CDC* pDC) const {
    int numPoints = m_points.size();

    // 确保至少有5个控制点
    if (numPoints < 5) return;

    // 选择不同的颜色和线型
    std::vector<COLORREF> colors = { RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255), RGB(255, 255, 0) };
    int colorIndex = 0;

    // 保存原画笔
    CPen* pOldPen = pDC->GetCurrentPen();

    pDC->MoveTo(m_points[0]);

    // 绘制每段四阶贝塞尔曲线
    for (int i = 0; i <= numPoints - 5; i += 4) {
        // 设置颜色
        pDC->SetBkMode(TRANSPARENT);
        CPen newPen(PS_SOLID, 2, colors[colorIndex]);
        pDC->SelectObject(&newPen);



        // 绘制贝塞尔曲线
        for (float t = 0; t <= 1; t += 0.01) {
            // 贝塞尔曲线公式
            CPoint point(
                pow(1 - t, 4) * m_points[i].x +
                4 * pow(1 - t, 3) * t * m_points[i + 1].x +
                6 * pow(1 - t, 2) * t * t * m_points[i + 2].x +
                4 * (1 - t) * t * t * t * m_points[i + 3].x +
                t * t * t * t * m_points[i + 4].x,

                pow(1 - t, 4) * m_points[i].y +
                4 * pow(1 - t, 3) * t * m_points[i + 1].y +
                6 * pow(1 - t, 2) * t * t * m_points[i + 2].y +
                4 * (1 - t) * t * t * t * m_points[i + 3].y +
                t * t * t * t * m_points[i + 4].y
            );
            pDC->LineTo(point);
        }
        // 绘制控制多边形
        for (int j = 0; j < 5; j++) {
            pDC->MoveTo(m_points[i + j]);
            if (j < 4) {
                pDC->LineTo(m_points[i + j + 1]);
            }
        }
        // 切换颜色
        colorIndex = (colorIndex + 1) % colors.size();
    }

    // 绘制控制点
    for (const auto& point : m_points) {
        pDC->Ellipse(point.x - 3, point.y - 3, point.x + 3, point.y + 3);
    }

    // 恢复原画笔
    pDC->SelectObject(pOldPen);
}

std::vector<CPoint> FourthOrderBezier::GetPoints() {
	return m_points;
}

void FourthOrderBezier::SetPoints(std::vector<CPoint> points) {
	this->m_points = points;
}
