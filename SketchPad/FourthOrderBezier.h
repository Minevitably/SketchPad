#pragma once
#include "Graphic.h"


class FourthOrderBezier : public Graphic {
public:
    FourthOrderBezier(std::vector<CPoint> points); // 构造函数
    void Draw(CDC* pDC) const override; // 使用pDC绘制图形
    std::vector<CPoint> GetPoints() override; // getter方法，返回点集
    void SetPoints(std::vector<CPoint> points) override; // setter方法，设置点集

private:
    std::vector<CPoint> m_points; // 存储点的集合
};

