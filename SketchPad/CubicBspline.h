#pragma once
#include "Graphic.h"


class CubicBspline : public Graphic {
public:
    CubicBspline(std::vector<CPoint> points); // 构造函数
    void Draw(CDC* pDC) const override; // 使用pDC绘制图形
    std::vector<CPoint> GetPoints() override; // getter方法，返回点集
    void SetPoints(std::vector<CPoint> points) override; // setter方法，设置点集

    CPoint CalculateCubicBsplinePoint(int i, float t) const;
private:
    std::vector<CPoint> m_points; // 存储点的集合
};

