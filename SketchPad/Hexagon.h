#pragma once
#include "Graphic.h"
class Hexagon : public Graphic
{
public:
    Hexagon(std::vector<CPoint> points, int m_radius, bool m_raw); // 构造函数
    void Draw(CDC* pDC) const override; // 使用pDC绘制图形
    std::vector<CPoint> GetPoints() override; // getter方法，返回点集
    void SetPoints(std::vector<CPoint> points) override; // setter方法，设置点集

    bool GetRaw();
private:
    std::vector<CPoint> m_points; // 存储点的集合
    int m_radius;
    bool m_raw; // 标记六边形是否为变换前的六边形
};

