#include "pch.h"
#include "Ellipse.h"


namespace MyGraphics {
    Ellipse::Ellipse(std::vector<CPoint> points, int a, int b) {
        this->m_points = points;
        this->m_a = a;
        this->m_b = b;
    }

    void Ellipse::Draw(CDC* pDC) const {
        // 椭圆的中心、长轴和短轴
        CPoint center = m_points[0]; // 椭圆中心
        int a = m_a; // 长轴（水平半轴）
        int b = m_b; // 短轴（垂直半轴）

        // 初始化坐标和决策参数
        int x = 0;
        int y = b;
        int a2 = a * a;
        int b2 = b * b;
        int fa2 = 4 * a2;
        int fb2 = 4 * b2;
        int d = 0;

        // 第一阶段：绘制椭圆的上半部分
        while (a2 * y > b2 * x) {
            // 绘制对称点
            pDC->SetPixel(center.x + x, center.y + y, RGB(0, 0, 0)); // 第一象限
            pDC->SetPixel(center.x - x, center.y + y, RGB(0, 0, 0)); // 第二象限
            pDC->SetPixel(center.x + x, center.y - y, RGB(0, 0, 0)); // 第三象限
            pDC->SetPixel(center.x - x, center.y - y, RGB(0, 0, 0)); // 第四象限

            // 更新决策参数
            d += fb2 * x + b2;
            if (d > 0) {
                y--;
                d -= fa2 * y;
            }
            x++;
        }

        // 第二阶段：绘制椭圆的下半部分
        d = 0;
        x = a;
        y = 0;

        while (b2 * x > a2 * y) {
            // 绘制对称点
            pDC->SetPixel(center.x + x, center.y + y, RGB(0, 0, 0)); // 第一象限
            pDC->SetPixel(center.x - x, center.y + y, RGB(0, 0, 0)); // 第二象限
            pDC->SetPixel(center.x + x, center.y - y, RGB(0, 0, 0)); // 第三象限
            pDC->SetPixel(center.x - x, center.y - y, RGB(0, 0, 0)); // 第四象限

            // 更新决策参数
            d += fa2 * y + a2;
            if (d > 0) {
                x--;
                d -= fb2 * x;
            }
            y++;
        }
    }

    std::vector<CPoint> Ellipse::GetPoints() {
        return m_points;
    }

    void Ellipse::SetPoints(std::vector<CPoint> points) {
        m_points.push_back(points[0]);
    }
}